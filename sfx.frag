#version 130
#define PI radians(180.)
float clip(float a) { return clamp(a,-1.,1.); }
float theta(float x) { return smoothstep(0.,1e-3,clamp(x,0.,1e-3)); }
float _sin(float a) { return sin(2. * PI * mod(a,1.)); }
float _sin_(float a, float p) { return sin(2. * PI * mod(a,1.) + p); }
float _sq_(float a,float pwm) { return sign(2.*fract(a) - 1. + pwm); }
float _psq_(float a, float pwm) { return clip(50.*(_sin(a) - pwm)); } 
float _tri(float a) { return (4.*abs(fract(a)-.5) - 1.); }
float freqC1(float note){ return 32.7 * pow(2., note/12.); }
float minus1hochN(int n) { return (1. - 2.*float(n % 2)); }
float minus1hochNminus1halbe(int n) { return sin(.5*PI*float(n)); }
float pseudorandom(float x) { return fract(sin(dot(vec2(x),vec2(12.9898,78.233))) * 43758.5453); }
float fhelp(float x) { return 1. + .333*x; } // 1. + .33333*x + .1*x*x + .02381*x*x*x + .00463*x*x*x*x;

#define pat4(a,b,c,d,x) mod(x,1.)<.25 ? a : mod(x,1.)<.5 ? b : mod(x,1.) < .75 ? c : d

#define NTIME 20
const float pos_B[20] = float[20](0.,2.,8.,10.,11.,12.,31.,34.,40.,42.,46.,50.,51.,52.,64.,65.,70.,71.,72.,95.);
const float pos_t[20] = float[20](0.,4.705882,18.552036,22.996481,25.139338,27.208303,65.208303,71.109943,82.722846,86.722846,94.998708,103.134301,105.134301,107.069785,129.569785,131.505269,141.341334,143.276818,145.151818,186.97);
const float pos_BPS[19] = float[19](.425,.4333,.45,.4667,.4833,.5,.5083,.5167,.5,.4833,.4917,.5,.5167,.5333,.5167,.5083,.5167,.5333,.55);
const float pos_SPB[19] = float[19](2.3529,2.3079,2.2222,2.1427,2.0691,2.,1.9673,1.9354,2.,2.0691,2.0338,2.,1.9354,1.8751,1.9354,1.9673,1.9354,1.8751,1.8182);
float BPS, SPB, BT;

const float Fsample = 44100.; // CAUTION: THIS SHOULD BE 44100. FOR NR4.
const float Tsample = 1./Fsample;

const float filterthreshold = 1e-3;

//TEXCODE

float s_atan(float a) { return 2./PI * atan(a); }
float squarey(float a, float edge) { return abs(a) < edge ? a : floor(4.*a+.5)*.25; } 

float doubleslope(float t, float a, float d, float s)
{
    return smoothstep(-.00001,a,t) - (1.-s) * smoothstep(0.,d,t-a);
}

float drop_phase(float time, float t1, float f0, float f1)
{
    float t = min(time, t1);
    float phi = f0*t + .5*(f1-f0)/t1*t*t;

    if(time > t1)
    {
        phi += f1 * (time - t1);
    }
    return phi;
}

float lpnoise(float t, float fq)
{
    t *= fq;
    float tt = fract(t);
    float tn = t - tt;
    return mix(pseudorandom(floor(tn) / fq), pseudorandom(floor(tn + 1.0) / fq), smoothstep(0.0, 1.0, tt));
}

float reverb_phase(float t, float amt)
{
    float r = lpnoise(t, 100.0) + 0.2*lpnoise(t, 550.0) + 0.1*lpnoise(t, 1050.0)*exp(-5.*t);
    return amt * r;
}

float env_AHDSR(float x, float L, float A, float H, float D, float S, float R)
{
    return (x<A ? x/A : x<A+H ? 1 : x<A+H+D ? (1. - (1.-S)*(x-H-A)/D) : x<=L-R ? S : x<=L ? S*(L-x)/R : 0.);
}

float waveshape(float s, float amt, float A, float B, float C, float D, float E)
{
    float w;
    float m = sign(s);
    s = abs(s);

    if(s<A) w = B * smoothstep(0.,A,s);
    else if(s<C) w = C + (B-C) * smoothstep(C,A,s);
    else if(s<=D) w = s;
    else if(s<=1.)
    {
        float _s = (s-D)/(1.-D);
        w = D + (E-D) * (1.5*_s*(1.-.33*_s*_s));
    }
    else return 1.;
    
    return m*mix(s,w,amt);
}

float sinshape(float x, float amt, float parts)
{
    return (1.-amt) * x + amt * sign(x) * 0.5 * (1. - cos(parts*PI*x));
}

float comp_SAW(int N, float inv_N, float PW) {return inv_N * (1. - _sin(float(N)*PW));}
float comp_TRI(int N, float inv_N, float PW) {return N % 2 == 0 ? .1 * inv_N * _sin(float(N)*PW) : inv_N * inv_N * (1. - _sin(float(N)*PW));}
float comp_SQU(int N, float inv_N, float PW) {return inv_N * (minus1hochN(N) * _sin(.5*float(N)*PW + .25) - 1.);}
float comp_HAE(int N, float inv_N, float PW) {return N % 2 == 0 ? 0. : inv_N * (1. - minus1hochNminus1halbe(N))*_sin(PW);}

float MADD(float t, float f, float p0, int NMAX, int NINC, float MIX, float CO, float NDECAY, float RES, float RES_Q, float DET, float PW, int keyF)
{
    float ret = 0.;
    float INR = keyF==1 ? 1./CO : f/CO;
    float IRESQ = keyF==1 ? 1./RES_Q : 1./(RES_Q*f);
    
    float p = f*t;
    float float_N, inv_N, comp_mix, filter_N;
    for(int N=1; N<=NMAX; N+=NINC)
    {
        float_N = float(N);
        inv_N = 1./float_N;
        comp_mix = MIX < 0. ? (MIX+1.) * comp_TRI(N,inv_N,PW)  -     MIX  * comp_SAW(N,inv_N,PW)
                 : MIX < 1. ? (1.-MIX) * comp_TRI(N,inv_N,PW)  +     MIX  * comp_SQU(N,inv_N,PW)
                            : (MIX-1.) * comp_HAE(N,inv_N,PW)  + (2.-MIX) * comp_SQU(N,inv_N,PW);

        if(abs(comp_mix) < 1e-6) continue;

        filter_N = pow(1. + pow(float_N*INR,NDECAY),-.5) + RES * exp(-pow((float_N*f-CO)*IRESQ,2.));
                
        ret += comp_mix * filter_N * (_sin_(float_N * p, p0) + _sin_(float_N * p * (1.+DET), p0));
    }
    return s_atan(ret);
}

float QFM_FB(float PH, float FB) // my guessing of feedback coefficients, FB>0 'saw', FB<0 'sq'
{
    if(FB > 0.) return abs(FB) * .8*_sin(PH + .35*_sin(PH));
    else return abs(FB) * _sin(PH + .5*PI);
}

float QFM(float t, float f, float phase, float LV1, float LV2, float LV3, float LV4, float FR1, float FR2, float FR3, float FR4, float FB1, float FB2, float FB3, float FB4, float ALGO)
{
    int iALGO = int(ALGO);
    float PH1 = FR1 * f * t + phase;
    float PH2 = FR2 * f * t + phase;
    float PH3 = FR3 * f * t + phase;
    float PH4 = FR4 * f * t + phase;
    
    float LINK41 = 0., LINK42 = 0., LINK43 = 0., LINK32 = 0., LINK31 = 0., LINK21 = 0.; 
    if(iALGO == 1)       {LINK43 = 1.; LINK32 = 1.; LINK21 = 1.;}
    else if(iALGO == 2)  {LINK42 = 1.; LINK32 = 1.; LINK21 = 1.;}    
    else if(iALGO == 3)  {LINK41 = 1.; LINK32 = 1.; LINK21 = 1.;}
    else if(iALGO == 4)  {LINK42 = 1.; LINK43 = 1.; LINK31 = 1.; LINK21 = 1.;}
    else if(iALGO == 5)  {LINK41 = 1.; LINK31 = 1.; LINK21 = 1.;}
    else if(iALGO == 6)  {LINK43 = 1.; LINK32 = 1.;}
    else if(iALGO == 7)  {LINK43 = 1.; LINK32 = 1.; LINK31 = 1.;}
    else if(iALGO == 8)  {LINK21 = 1.; LINK43 = 1.;}
    else if(iALGO == 9)  {LINK43 = 1.; LINK42 = 1.; LINK41 = 1.;}
    else if(iALGO == 10) {LINK43 = 1.; LINK42 = 1.;}
    else if(iALGO == 11) {LINK43 = 1.;}

    float OP4 = LV4 * _sin(PH4 + QFM_FB(PH4, FB4));
    float OP3 = LV3 * _sin(PH3 + QFM_FB(PH3, FB3) + LINK43*OP4);
    float OP2 = LV2 * _sin(PH2 + QFM_FB(PH2, FB2) + LINK42*OP4 + LINK32*OP3);
    float OP1 = LV1 * _sin(PH1 + QFM_FB(PH1, FB1) + LINK41*OP4 + LINK31*OP3 + LINK32*OP2);
    
    float sum = OP1;
    if(LINK21 > 0.) sum += OP2;
    if(LINK31 + LINK32 > 0.) sum += OP3;
    if(LINK41 + LINK42 + LINK43 > 0.) sum += OP4;
    
    return s_atan(sum);
}

float protokick(float t, float f_start, float f_end, float fdecay, float hold, float decay, float drive, float detune, float rev_amount, float rev_hold, float rev_decay, float rev_drive)
{
    float phi = drop_phase(t, fdecay, f_start, f_end);
    float rev_phi = phi + reverb_phase(t, 1.);
    return clamp(drive*.5*(_sin(phi)+_sin((1.-detune)*phi)),-1.,1.) * exp(-max(t-hold, 0.)/decay)
         + rev_amount*clamp(rev_drive*.5*(_sin(rev_phi)+_sin((1.-detune)*rev_phi)),-1.,1.) * exp(-max(t-rev_hold, 0.)/rev_decay);
} 

uniform float iBlockOffset;
uniform float iSampleRate;
uniform float iVolume;
uniform int iTexSize;
uniform sampler2D iSequence;
uniform float iSequenceWidth;

// Read short value from texture at index off
float rshort(float off)
{
    float hilo = mod(off, 2.);
    off *= .5;
    vec2 ind = (vec2(mod(off, iSequenceWidth), floor(off/iSequenceWidth))+.05)/iSequenceWidth;
    vec4 block = texture(iSequence, ind);
    vec2 data = mix(block.rg, block.ba, hilo);
    return round(dot(vec2(255., 65280.), data));
}

// Read float value from texture at index off
float rfloat(int off)
{
    float d = rshort(float(off));
    float sign = floor(d/32768.),
        exponent = floor(d/1024.-sign*32.),
        significand = d-sign*32768.-exponent*1024.;

    if(exponent == 0.)
         return mix(1., -1., sign) * 5.960464477539063e-08 * significand;
    return mix(1., -1., sign) * (1. + significand * 9.765625e-4) * pow(2.,exponent-15.);
}

#define NTRK 17
#define NMOD 220
#define NPTN 41
#define NNOT 1979
#define NDRM 40

int trk_sep(int index)      {return int(rfloat(index));}
int trk_syn(int index)      {return int(rfloat(index+1+1*NTRK));}
float trk_norm(int index)   {return     rfloat(index+1+2*NTRK);}
float trk_rel(int index)    {return     rfloat(index+1+3*NTRK);}
float trk_pre(int index)    {return     rfloat(index+1+4*NTRK);}
float trk_slide(int index)  {return     rfloat(index+1+5*NTRK);} // idea for future: change to individual note_slide_time
float mod_on(int index)     {return     rfloat(index+1+6*NTRK);}
float mod_off(int index)    {return     rfloat(index+1+6*NTRK+1*NMOD);}
int mod_ptn(int index)      {return int(rfloat(index+1+6*NTRK+2*NMOD));}
float mod_transp(int index) {return     rfloat(index+1+6*NTRK+3*NMOD);}
int ptn_sep(int index)      {return int(rfloat(index+1+6*NTRK+4*NMOD));}
float note_on(int index)    {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN);}
float note_off(int index)   {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+1*NNOT);}
float note_pitch(int index) {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+2*NNOT);}
float note_pan(int index)   {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+3*NNOT);}
float note_vel(int index)   {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+4*NNOT);}
float note_slide(int index) {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+5*NNOT);}
float note_aux(int index)   {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+6*NNOT);}
float drum_rel(int index)   {return     rfloat(index+2+6*NTRK+4*NMOD+NPTN+7*NNOT);}

vec2 mainSynth(float time)
{
    float sL = 0.;
    float sR = 0.;
    float dL = 0.;
    float dR = 0.;

    
    int _it;
    for(_it = 0; _it < NTIME - 2 && pos_t[_it + 1] < time; _it++);
    BPS = pos_BPS[_it];
    SPB = pos_SPB[_it];
    BT = pos_B[_it] + (time - pos_t[_it]) * BPS;
    
    float time2 = time - .0002;
    float sidechain = 1.;

    float amaysynL, amaysynR, amaydrumL, amaydrumR, B, Bon, Boff, Bprog, Bproc, L, tL, _t, _t2, vel, rel, pre, f, amtL, amtR, env, slide, aux;
    int tsep0, tsep1, _modU, _modL, ptn, psep0, psep1, _noteU, _noteL, syn, drum;

    for(int trk = 0; trk < NTRK; trk++)
    {
        tsep0 = trk_sep(trk);
        tsep1 = trk_sep(trk + 1);

        syn = trk_syn(trk);
        rel = trk_rel(trk);
        pre = trk_pre(trk);
 
        for(_modU = tsep0; (_modU < tsep1 - 1) && (BT > mod_on(_modU + 1) - pre); _modU++);             
        for(_modL = tsep0; (_modL < tsep1 - 1) && (BT >= mod_off(_modL) + rel); _modL++);

        for(int _mod = _modL; _mod <= _modU; _mod++)
        {
            B = BT - mod_on(_mod);

            ptn   = mod_ptn(_mod);
            psep0 = ptn_sep(ptn);
            psep1 = ptn_sep(ptn + 1);
                         
            for(_noteU = psep0; (_noteU < psep1 - 1) && (B > note_on(_noteU + 1) - pre); _noteU++);
            for(_noteL = psep0; (_noteL < psep1 - 1) && (B >= note_off(_noteL) + rel); _noteL++);

            for(int _note = _noteL; _note <= _noteU; _note++)
            {
                if(syn == 119)
                {
                    drum = int(note_pitch(_note));
                    rel = drum_rel(drum);
                }

                amaysynL  = 0.;
                amaysynR  = 0.;
                amaydrumL = 0.;
                amaydrumR = 0.;

                Bon   = note_on(_note) - pre;
                Boff  = note_off(_note) + rel;
                L     = Boff - Bon;
                tL    = L * SPB;
                Bprog = B - Bon;
                Bproc = Bprog / L;
                _t    = Bprog * SPB;
                _t2   = _t - .0002;
                vel   = note_vel(_note);
                amtL  = clamp(1. - note_pan(_note), 0., 1.);
                amtR  = clamp(1. + note_pan(_note), 0., 1.);
                slide = note_slide(_note);
                aux   = note_aux(_note);

                if(syn == 119)
                {
                    env = trk_norm(trk) * theta(Bprog) * theta(L - Bprog);
                    if(drum == 0) { sidechain = min(sidechain, 1. - vel * (clamp(1e4 * Bprog,0.,1.) - pow(Bprog/(L-rel),8.))); }
                    else if(drum == 1){
                        amaydrumL = vel*.2*fract(sin(_t*100.*.9)*50000.*.9)*doubleslope(_t,.03,.1,.1);
                        amaydrumR = vel*.2*fract(sin(_t2*100.*.9)*50000.*.9)*doubleslope(_t2,.03,.1,.1);
                    }
                    else if(drum == 2){
                        amaydrumL = vel*(lpnoise(_t,10000.)*smoothstep(0.,.01,_t)*(1.-(1.-.13)*smoothstep(0.,.12,_t-.01))-.3*(1.00*lpnoise((_t-0.00),10000.)*smoothstep(0.,.01,(_t-0.00))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-0.00)-.01))+6.10e-01*lpnoise((_t-1.20e-03),10000.)*smoothstep(0.,.01,(_t-1.20e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-1.20e-03)-.01))+3.72e-01*lpnoise((_t-2.40e-03),10000.)*smoothstep(0.,.01,(_t-2.40e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-2.40e-03)-.01))));
                        amaydrumR = vel*(lpnoise(_t,10000.)*smoothstep(0.,.01,_t)*(1.-(1.-.13)*smoothstep(0.,.12,_t-.01))-.3*(1.00*lpnoise((_t-0.00),10000.)*smoothstep(0.,.01,(_t-0.00))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-0.00)-.01))+6.10e-01*lpnoise((_t-1.20e-03),10000.)*smoothstep(0.,.01,(_t-1.20e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-1.20e-03)-.01))+3.72e-01*lpnoise((_t-2.40e-03),10000.)*smoothstep(0.,.01,(_t-2.40e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-2.40e-03)-.01))));
                    }
                    else if(drum == 3){
                        amaydrumL = vel*fract(sin(_t*100.*1.)*50000.*1.)*doubleslope(_t,0.,.01,.1)*theta(Bprog)*exp(-10.*Bprog);
                        amaydrumR = vel*fract(sin(_t2*100.*1.)*50000.*1.)*doubleslope(_t2,0.,.01,.1)*theta(Bprog)*exp(-10.*Bprog);
                    }
                    else if(drum == 4){
                        amaydrumL = vel*fract(sin(_t*100.*.5)*50000.*.5)*doubleslope(_t,0.,.03,.1)*theta(Bprog)*exp(-13.*Bprog);
                        amaydrumR = vel*fract(sin(_t2*100.*.5)*50000.*.5)*doubleslope(_t2,0.,.03,.1)*theta(Bprog)*exp(-13.*Bprog);
                    }
                    else if(drum == 5){
                        amaydrumL = vel*.25*sinshape(fract(sin(_t*100.*30.)*50000.*20.)*doubleslope(_t,0.,.1,.1)+lpnoise(_t + 0.,6000.),1.,5.)*theta(Bprog)*exp(-2.*Bprog);
                        amaydrumR = vel*.25*sinshape(fract(sin(_t2*100.*30.)*50000.*20.)*doubleslope(_t2,0.,.1,.1)+lpnoise(_t2 + 0.,6000.),1.,5.)*theta(Bprog)*exp(-2.*Bprog);
                    }
                    else if(drum == 6){
                        amaydrumL = vel*(clamp(1.95*_tri(drop_phase(_t,.1,140.,114.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.24))+.07*clamp(.25*_tri(drop_phase(_t,.1,140.,114.)+.07*lpnoise(_t,4577.)),-1.,1.)*exp(-11.43*_t)+0.*lpnoise(_t,13098.)*(1.-smoothstep(0.,.32,_t-.76))+.75*lpnoise(_t,7668.)*exp(-_t*5.99)+.96*lpnoise(_t,1984.)*exp(-_t*20.65))*smoothstep(0.,.007,_t);
                        amaydrumR = vel*(clamp(1.95*_tri(drop_phase(_t2,.1,140.,114.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.24))+.07*clamp(.25*_tri(drop_phase(_t2,.1,140.,114.)+.07*lpnoise(_t2,4577.)),-1.,1.)*exp(-11.43*_t2)+0.*lpnoise(_t2,13098.)*(1.-smoothstep(0.,.32,_t2-.76))+.75*lpnoise(_t2,7668.)*exp(-_t2*5.99)+.96*lpnoise(_t2,1984.)*exp(-_t2*20.65))*smoothstep(0.,.007,_t2);
                    }
                    else if(drum == 8){
                        amaydrumL = vel*(.3+(.7*theta(Bprog)*exp(-10.*Bprog)))*sinshape(((clamp(.72*_tri(drop_phase(_t,.07,227.,107.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.09))+.69*clamp(.94*_tri(drop_phase(_t,.07,227.,107.)+.69*lpnoise(_t,8709.)),-1.,1.)*exp(-13.89*_t)+.06*lpnoise(_t,18745.)*(1.-smoothstep(0.,.67,_t-.17))+.28*lpnoise(_t,7506.)*exp(-_t*12.44)+.82*lpnoise(_t,2600.)*exp(-_t*17.54))*smoothstep(0.,.004,_t)),.6,9.);
                        amaydrumR = vel*(.3+(.7*theta(Bprog)*exp(-10.*Bprog)))*sinshape(((clamp(.72*_tri(drop_phase(_t2,.07,227.,107.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.09))+.69*clamp(.94*_tri(drop_phase(_t2,.07,227.,107.)+.69*lpnoise(_t2,8709.)),-1.,1.)*exp(-13.89*_t2)+.06*lpnoise(_t2,18745.)*(1.-smoothstep(0.,.67,_t2-.17))+.28*lpnoise(_t2,7506.)*exp(-_t2*12.44)+.82*lpnoise(_t2,2600.)*exp(-_t2*17.54))*smoothstep(0.,.004,_t2)),.6,9.);
                    }
                    else if(drum == 12){
                        amaydrumL = vel*(.79*lpnoise(_t,1.+3.31*_t)*(smoothstep(0.,1e-3,_t)-smoothstep(0.,.018,_t-.196)));
                        amaydrumR = vel*(.79*lpnoise(_t2,1.+3.31*_t2)*(smoothstep(0.,1e-3,_t2)-smoothstep(0.,.018,_t2-.196)));
                    }
                    else if(drum == 13){
                        amaydrumL = vel*((clamp(1.09*_tri(drop_phase(_t,.08,249.,77.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.04))+.97*clamp(.99*_tri(drop_phase(_t,.08,249.,77.)+.97*lpnoise(_t,9855.)),-1.,1.)*exp(-21.22*_t)+.03*lpnoise(_t,10655.)*(1.-smoothstep(0.,.58,_t-.81))+.71*lpnoise(_t,7520.)*exp(-_t*16.22)+.57*lpnoise(_t,4386.)*exp(-_t*29.48))*smoothstep(0.,.005,_t));
                        amaydrumR = vel*((clamp(1.09*_tri(drop_phase(_t2,.08,249.,77.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.04))+.97*clamp(.99*_tri(drop_phase(_t2,.08,249.,77.)+.97*lpnoise(_t2,9855.)),-1.,1.)*exp(-21.22*_t2)+.03*lpnoise(_t2,10655.)*(1.-smoothstep(0.,.58,_t2-.81))+.71*lpnoise(_t2,7520.)*exp(-_t2*16.22)+.57*lpnoise(_t2,4386.)*exp(-_t2*29.48))*smoothstep(0.,.005,_t2));
                    }
                    else if(drum == 14){
                        amaydrumL = vel*.42*((clamp(2.24*_tri(drop_phase(_t,.08,217.,64.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.29))+.7*clamp(.84*_tri(drop_phase(_t,.08,217.,64.)+.7*lpnoise(_t,1936.)),-1.,1.)*exp(-23.11*_t)+.08*lpnoise(_t,5166.)*(1.-smoothstep(0.,.16,_t-.55))+.77*lpnoise(_t,6784.)*exp(-_t*29.89)+.53*lpnoise(_t,4404.)*exp(-_t*24.64))*smoothstep(0.,.002,_t));
                        amaydrumR = vel*.42*((clamp(2.24*_tri(drop_phase(_t2,.08,217.,64.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.29))+.7*clamp(.84*_tri(drop_phase(_t2,.08,217.,64.)+.7*lpnoise(_t2,1936.)),-1.,1.)*exp(-23.11*_t2)+.08*lpnoise(_t2,5166.)*(1.-smoothstep(0.,.16,_t2-.55))+.77*lpnoise(_t2,6784.)*exp(-_t2*29.89)+.53*lpnoise(_t2,4404.)*exp(-_t2*24.64))*smoothstep(0.,.002,_t2));
                    }
                    else if(drum == 19){
                        amaydrumL = vel*(.61*(0.*lpnoise(_t,385.)+0.*lpnoise(_t,2973.)+0.*lpnoise(_t,1554.))*(smoothstep(0.,.01,_t)-smoothstep(0.,.54,_t-.02))+_sin(drop_phase(_t,.03,638.,304.))*exp(-_t*9.7)*.1+_sin(drop_phase(_t*1541.,.03,638.,304.))*exp(-_t*2.8)*.91);
                        amaydrumR = vel*(.61*(0.*lpnoise(_t2,385.)+0.*lpnoise(_t2,2973.)+0.*lpnoise(_t2,1554.))*(smoothstep(0.,.01,_t2)-smoothstep(0.,.54,_t2-.02))+_sin(drop_phase(_t2,.03,638.,304.))*exp(-_t2*9.7)*.1+_sin(drop_phase(_t2*1541.,.03,638.,304.))*exp(-_t2*2.8)*.91);
                    }
                    else if(drum == 20){
                        amaydrumL = vel*(.25*(0.*lpnoise(_t,260.)+0.*lpnoise(_t,868.)+0.*lpnoise(_t,454.))*(smoothstep(0.,.01,_t)-smoothstep(0.,.91,_t-.91))+_sin(drop_phase(_t,.02,559.,252.))*exp(-_t*5.5)*.4+_sin(drop_phase(_t*1444.,.02,559.,252.))*exp(-_t*6.9)*.3);
                        amaydrumR = vel*(.25*(0.*lpnoise(_t2,260.)+0.*lpnoise(_t2,868.)+0.*lpnoise(_t2,454.))*(smoothstep(0.,.01,_t2)-smoothstep(0.,.91,_t2-.91))+_sin(drop_phase(_t2,.02,559.,252.))*exp(-_t2*5.5)*.4+_sin(drop_phase(_t2*1444.,.02,559.,252.))*exp(-_t2*6.9)*.3);
                    }
                    else if(drum == 23){
                        amaydrumL = vel*((clamp(2.65*_tri(drop_phase(_t,.06,205.,52.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.09))+.91*clamp(.95*_tri(drop_phase(_t,.06,205.,52.)+.91*lpnoise(_t,8869.)),-1.,1.)*exp(-14.86*_t)+.04*lpnoise(_t,16440.)*(1.-smoothstep(0.,.77,_t-.52))+.16*lpnoise(_t,1524.)*exp(-_t*6.23)+.07*lpnoise(_t,5944.)*exp(-_t*13.51))*smoothstep(0.,.004,_t));
                        amaydrumR = vel*((clamp(2.65*_tri(drop_phase(_t2,.06,205.,52.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.09))+.91*clamp(.95*_tri(drop_phase(_t2,.06,205.,52.)+.91*lpnoise(_t2,8869.)),-1.,1.)*exp(-14.86*_t2)+.04*lpnoise(_t2,16440.)*(1.-smoothstep(0.,.77,_t2-.52))+.16*lpnoise(_t2,1524.)*exp(-_t2*6.23)+.07*lpnoise(_t2,5944.)*exp(-_t2*13.51))*smoothstep(0.,.004,_t2));
                    }
                    else if(drum == 24){
                        amaydrumL = vel*protokick(_t,242.,55.,.036,.088,.0666,1.42,.01,.45,.1,.15,.5)
      +.66*protokick(_t,3333.,340.,.008,0.,.01,2.,2.4,0.,.2,.3,1.);
                        amaydrumR = vel*protokick(_t2,242.,55.,.036,.088,.0666,1.42,.01,.45,.1,.15,.5)
      +.66*protokick(_t2,3333.,340.,.008,0.,.01,2.,2.4,0.,.2,.3,1.);
                    }
                    else if(drum == 25){
                        amaydrumL = vel*protokick(_t,3333.,340.,.008,0.,.01,2.,2.4,0.,.2,.3,1.);
                        amaydrumR = vel*protokick(_t2,3333.,340.,.008,0.,.01,2.,2.4,0.,.2,.3,1.);
                    }
                    else if(drum == 26){
                        amaydrumL = vel*((clamp(2.77*_tri(drop_phase(_t,.04,346.,71.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.15))+.93*clamp(.5*_tri(drop_phase(_t,.04,346.,71.)+.93*lpnoise(_t,8131.)),-1.,1.)*exp(-27.17*_t)+.05*lpnoise(_t,8351.)*(1.-smoothstep(0.,.7,_t-.56))+.22*lpnoise(_t,6693.)*exp(-_t*8.03)+.66*lpnoise(_t,6124.)*exp(-_t*14.68))*smoothstep(0.,.003,_t));
                        amaydrumR = vel*((clamp(2.77*_tri(drop_phase(_t2,.04,346.,71.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.15))+.93*clamp(.5*_tri(drop_phase(_t2,.04,346.,71.)+.93*lpnoise(_t2,8131.)),-1.,1.)*exp(-27.17*_t2)+.05*lpnoise(_t2,8351.)*(1.-smoothstep(0.,.7,_t2-.56))+.22*lpnoise(_t2,6693.)*exp(-_t2*8.03)+.66*lpnoise(_t2,6124.)*exp(-_t2*14.68))*smoothstep(0.,.003,_t2));
                    }
                    else if(drum == 27){
                        amaydrumL = vel*((clamp(1.18*_tri(drop_phase(_t,.07,170.,94.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.12))+.08*clamp(.41*_tri(drop_phase(_t,.07,170.,94.)+.08*lpnoise(_t,8015.)),-1.,1.)*exp(-8.8*_t)+.03*lpnoise(_t,1351.)*(1.-smoothstep(0.,.35,_t-.3))+.62*lpnoise(_t,2610.)*exp(-_t*18.02)+.27*lpnoise(_t,4995.)*exp(-_t*27.9))*smoothstep(0.,.009,_t));
                        amaydrumR = vel*((clamp(1.18*_tri(drop_phase(_t2,.07,170.,94.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.12))+.08*clamp(.41*_tri(drop_phase(_t2,.07,170.,94.)+.08*lpnoise(_t2,8015.)),-1.,1.)*exp(-8.8*_t2)+.03*lpnoise(_t2,1351.)*(1.-smoothstep(0.,.35,_t2-.3))+.62*lpnoise(_t2,2610.)*exp(-_t2*18.02)+.27*lpnoise(_t2,4995.)*exp(-_t2*27.9))*smoothstep(0.,.009,_t2));
                    }
                    else if(drum == 28){
                        amaydrumL = vel*sinshape(lpnoise(_t + 0.,10396.),.3,7.)*theta(Bprog)*exp(-8.*Bprog);
                        amaydrumR = vel*sinshape(lpnoise(_t2 + 0.,10396.),.3,7.)*theta(Bprog)*exp(-8.*Bprog);
                    }
                    else if(drum == 29){
                        amaydrumL = vel*(vel*(clamp(1.32*_tri(drop_phase(_t,.06,308.,80.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.15))+.82*clamp(.49*_tri(drop_phase(_t,.06,308.,80.)+.82*lpnoise(_t,4595.)),-1.,1.)*exp(-1.97*_t)+.09*lpnoise(_t,4032.)*(1.-smoothstep(0.,.97,_t-.79))+.1*lpnoise(_t,1111.)*exp(-_t*12.69)+.6*lpnoise(_t,7795.)*exp(-_t*1.08))*smoothstep(0.,.003,_t))
      +.5*((clamp(1.35*_tri(drop_phase(_t,.07,244.,112.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.09))+.27*clamp(.03*_tri(drop_phase(_t,.07,244.,112.)+.27*lpnoise(_t,5148.)),-1.,1.)*exp(-24.07*_t)+0.*lpnoise(_t,1959.)*(1.-smoothstep(0.,.98,_t-.64))+.43*lpnoise(_t,8238.)*exp(-_t*25.54)+.11*lpnoise(_t,3803.)*exp(-_t*10.51))*smoothstep(0.,.006,_t));
                        amaydrumR = vel*(vel*(clamp(1.32*_tri(drop_phase(_t2,.06,308.,80.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.15))+.82*clamp(.49*_tri(drop_phase(_t2,.06,308.,80.)+.82*lpnoise(_t2,4595.)),-1.,1.)*exp(-1.97*_t2)+.09*lpnoise(_t2,4032.)*(1.-smoothstep(0.,.97,_t2-.79))+.1*lpnoise(_t2,1111.)*exp(-_t2*12.69)+.6*lpnoise(_t2,7795.)*exp(-_t2*1.08))*smoothstep(0.,.003,_t2))
      +.5*((clamp(1.35*_tri(drop_phase(_t2,.07,244.,112.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.09))+.27*clamp(.03*_tri(drop_phase(_t2,.07,244.,112.)+.27*lpnoise(_t2,5148.)),-1.,1.)*exp(-24.07*_t2)+0.*lpnoise(_t2,1959.)*(1.-smoothstep(0.,.98,_t2-.64))+.43*lpnoise(_t2,8238.)*exp(-_t2*25.54)+.11*lpnoise(_t2,3803.)*exp(-_t2*10.51))*smoothstep(0.,.006,_t2));
                    }
                    else if(drum == 33){
                        amaydrumL = vel*((clamp(2.58*_tri(drop_phase(_t,.05,156.,91.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.04))+.35*clamp(.44*_tri(drop_phase(_t,.05,156.,91.)+.35*lpnoise(_t,6183.)),-1.,1.)*exp(-7.56*_t)+.08*lpnoise(_t,7245.)*(1.-smoothstep(0.,.58,_t-.2))+.72*lpnoise(_t,2591.)*exp(-_t*5.48)+.73*lpnoise(_t,3597.)*exp(-_t*29.4))*smoothstep(0.,.01,_t));
                        amaydrumR = vel*((clamp(2.58*_tri(drop_phase(_t2,.05,156.,91.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.04))+.35*clamp(.44*_tri(drop_phase(_t2,.05,156.,91.)+.35*lpnoise(_t2,6183.)),-1.,1.)*exp(-7.56*_t2)+.08*lpnoise(_t2,7245.)*(1.-smoothstep(0.,.58,_t2-.2))+.72*lpnoise(_t2,2591.)*exp(-_t2*5.48)+.73*lpnoise(_t2,3597.)*exp(-_t2*29.4))*smoothstep(0.,.01,_t2));
                    }
                    else if(drum == 34){
                        amaydrumL = vel*((clamp(1.42*_tri(drop_phase(_t,.02,261.,53.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.28))+.86*clamp(.04*_tri(drop_phase(_t,.02,261.,53.)+.86*lpnoise(_t,3210.)),-1.,1.)*exp(-20.77*_t)+.03*lpnoise(_t,2325.)*(1.-smoothstep(0.,.42,_t-.01))+.28*lpnoise(_t,4276.)*exp(-_t*14.57)+.72*lpnoise(_t,3219.)*exp(-_t*9.93))*smoothstep(0.,.007,_t));
                        amaydrumR = vel*((clamp(1.42*_tri(drop_phase(_t2,.02,261.,53.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.28))+.86*clamp(.04*_tri(drop_phase(_t2,.02,261.,53.)+.86*lpnoise(_t2,3210.)),-1.,1.)*exp(-20.77*_t2)+.03*lpnoise(_t2,2325.)*(1.-smoothstep(0.,.42,_t2-.01))+.28*lpnoise(_t2,4276.)*exp(-_t2*14.57)+.72*lpnoise(_t2,3219.)*exp(-_t2*9.93))*smoothstep(0.,.007,_t2));
                    }
                    else if(drum == 39){
                        amaydrumL = vel*((clamp(2.27*_tri(drop_phase(_t,.03,241.,72.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.01))+.91*clamp(.9*_tri(drop_phase(_t,.03,241.,72.)+.91*lpnoise(_t,8164.)),-1.,1.)*exp(-20.76*_t)+.05*lpnoise(_t,10466.)*(1.-smoothstep(0.,.18,_t-.56))+.56*lpnoise(_t,7123.)*exp(-_t*5.45)+.11*lpnoise(_t,1134.)*exp(-_t*13.82))*smoothstep(0.,.004,_t));
                        amaydrumR = vel*((clamp(2.27*_tri(drop_phase(_t2,.03,241.,72.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.01))+.91*clamp(.9*_tri(drop_phase(_t2,.03,241.,72.)+.91*lpnoise(_t2,8164.)),-1.,1.)*exp(-20.76*_t2)+.05*lpnoise(_t2,10466.)*(1.-smoothstep(0.,.18,_t2-.56))+.56*lpnoise(_t2,7123.)*exp(-_t2*5.45)+.11*lpnoise(_t2,1134.)*exp(-_t2*13.82))*smoothstep(0.,.004,_t2));
                    }
                    
                    dL += amtL * s_atan(env * amaydrumL);
                    dR += amtR * s_atan(env * amaydrumR);
                }
                else
                {
                    f = freqC1(note_pitch(_note) + mod_transp(_mod));

                    if(abs(slide) > 1e-3) // THIS IS SLIDEY BIZ
                    {
                        float Bslide = trk_slide(trk);
                        float fac = slide * log(2.)/12.;
                        if (Bprog <= Bslide)
                        {
                            float help = 1. - Bprog/Bslide;
                            f *= Bslide * (fhelp(fac) - help * fhelp(fac*help*help)) / Bprog;
                        }
                        else
                        {
                            f *= 1. + (Bslide * (fhelp(fac)-1.)) / Bprog;
                        }
                    }

                    env = theta(Bprog) * (1. - smoothstep(Boff-rel, Boff, B));
                    if(syn == 0){amaysynL = _sin(f*_t); amaysynR = _sin(f*_t2);}
                    else if(syn == 18){
                        amaysynL = env_AHDSR(Bprog,L,.1+.001*aux,0.,.1,1.,.15)*(.5*sinshape(_tri(f*(_t-0.0*(1.+.1*_sin(.025*SPB*_t)))+.005*aux*env_AHDSR(Bprog,L,.125,0.,.1,1.,0.)*(2.*fract(.5*f*(_t-0.0*(1.+.1*_sin(.025*SPB*_t))))-1.)+.01*aux*env_AHDSR(Bprog,L,.05+.006*aux,0.,.1,1.,0.)*clip((1.+.8)*(2.*fract(1.51*f*(_t-0.0*(1.+.1*_sin(.025*SPB*_t))))-1.)))+.6*clip((1.+.4)*_sin(.499*f*(_t-0.0*(1.+.1*_sin(.025*SPB*_t))))),.2+.03*aux*vel,3.)
      +.5*sinshape(_tri(f*(_t-1.0e-01*(1.+.1*_sin(.025*SPB*_t)))+.005*aux*env_AHDSR(Bprog,L,.125,0.,.1,1.,0.)*(2.*fract(.5*f*(_t-1.0e-01*(1.+.1*_sin(.025*SPB*_t))))-1.)+.01*aux*env_AHDSR(Bprog,L,.05+.006*aux,0.,.1,1.,0.)*clip((1.+.8)*(2.*fract(1.51*f*(_t-1.0e-01*(1.+.1*_sin(.025*SPB*_t))))-1.)))+.6*clip((1.+.4)*_sin(.499*f*(_t-1.0e-01*(1.+.1*_sin(.025*SPB*_t))))),.2+.03*aux*vel,3.))
      +.5*sinshape(_tri(f*floor(7888.*_t+.5)/7888.+.005*aux*env_AHDSR(Bprog,L,.125,0.,.1,1.,0.)*(2.*fract(.5*f*floor(7888.*_t+.5)/7888.)-1.)+.01*aux*env_AHDSR(Bprog,L,.05+.006*aux,0.,.1,1.,0.)*clip((1.+.8)*(2.*fract(1.51*f*floor(7888.*_t+.5)/7888.)-1.)))+.6*clip((1.+.4)*_sin(.499*f*floor(7888.*_t+.5)/7888.)),.2+.03*aux*vel,3.)*env_AHDSR(Bprog,L,.1+.001*aux,0.,.1,1.,.15);
                        amaysynR = env_AHDSR(Bprog,L,.1+.001*aux,0.,.1,1.,.15)*(.5*sinshape(_tri(f*(_t2-0.0*(1.+.1*_sin(.025*SPB*_t2)))+.005*aux*env_AHDSR(Bprog,L,.125,0.,.1,1.,0.)*(2.*fract(.5*f*(_t2-0.0*(1.+.1*_sin(.025*SPB*_t2))))-1.)+.01*aux*env_AHDSR(Bprog,L,.05+.006*aux,0.,.1,1.,0.)*clip((1.+.8)*(2.*fract(1.51*f*(_t2-0.0*(1.+.1*_sin(.025*SPB*_t2))))-1.)))+.6*clip((1.+.4)*_sin(.499*f*(_t2-0.0*(1.+.1*_sin(.025*SPB*_t2))))),.2+.03*aux*vel,3.)
      +.5*sinshape(_tri(f*(_t2-1.0e-01*(1.+.1*_sin(.025*SPB*_t2)))+.005*aux*env_AHDSR(Bprog,L,.125,0.,.1,1.,0.)*(2.*fract(.5*f*(_t2-1.0e-01*(1.+.1*_sin(.025*SPB*_t2))))-1.)+.01*aux*env_AHDSR(Bprog,L,.05+.006*aux,0.,.1,1.,0.)*clip((1.+.8)*(2.*fract(1.51*f*(_t2-1.0e-01*(1.+.1*_sin(.025*SPB*_t2))))-1.)))+.6*clip((1.+.4)*_sin(.499*f*(_t2-1.0e-01*(1.+.1*_sin(.025*SPB*_t2))))),.2+.03*aux*vel,3.))
      +.5*sinshape(_tri(f*floor(7888.*_t2+.5)/7888.+.005*aux*env_AHDSR(Bprog,L,.125,0.,.1,1.,0.)*(2.*fract(.5*f*floor(7888.*_t2+.5)/7888.)-1.)+.01*aux*env_AHDSR(Bprog,L,.05+.006*aux,0.,.1,1.,0.)*clip((1.+.8)*(2.*fract(1.51*f*floor(7888.*_t2+.5)/7888.)-1.)))+.6*clip((1.+.4)*_sin(.499*f*floor(7888.*_t2+.5)/7888.)),.2+.03*aux*vel,3.)*env_AHDSR(Bprog,L,.1+.001*aux,0.,.1,1.,.15);
                    }
                    else if(syn == 56){
                        amaysynL = ((QFM((_t-0.0*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-4.0e-04*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-8.0e-04*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-1.2e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-1.6e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-2.0e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-2.4e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-2.8e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-3.2e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t-3.6e-03*(1.+.5*_sin(1.1*_t))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.))*theta(Bprog)*exp(-3.*vel*Bprog)+.6*theta(Bprog)*exp(-3.*vel*Bprog)*sinshape(.8*MADD(_t,.5*f,0.,64,1,-.5,200.,10.,0.,3.,.013,.02*aux,0)+.2*MADD(_t,.999*f,0.,64,1,-.7,500.,10.,0.,3.,.013,.01*aux,0),.01*aux,3.));
                        amaysynR = ((QFM((_t2-0.0*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-4.0e-04*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-8.0e-04*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-1.2e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-1.6e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-2.0e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-2.4e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-2.8e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-3.2e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.)+QFM((_t2-3.6e-03*(1.+.5*_sin(1.1*_t2))),f,0.,.00787*126.,.00787*env_AHDSR(Bprog,L,.228*vel,.231,.183,.383,0.)*66.,.00787*env_AHDSR(Bprog,L,.06*vel,.196,.202,.27,0.)*68.,.00787*env_AHDSR(Bprog,L,.06*vel,.016,.1,.342,0.)*111.,.5,1.,1.001,1.,.00787*74.,.00787*86.,.00787*77.,.00787*4.,2.))*theta(Bprog)*exp(-3.*vel*Bprog)+.6*theta(Bprog)*exp(-3.*vel*Bprog)*sinshape(.8*MADD(_t2,.5*f,0.,64,1,-.5,200.,10.,0.,3.,.013,.02*aux,0)+.2*MADD(_t2,.999*f,0.,64,1,-.7,500.,10.,0.,3.,.013,.01*aux,0),.01*aux,3.));
                    }
                    else if(syn == 71){
                        amaysynL = (env_AHDSR(_t,tL,1e-3,0.,.063,.402,.003)*MADD(_t,f,0.,128,1,-.6,(1175.+(583.*_sin_(2.*B,.4))),24.,44.37,24.05,.015,.4*(.55+(.4*clip((1.+1.)*_sin(4.*B)))),0));
                        amaysynR = (env_AHDSR(_t2,tL,1e-3,0.,.063,.402,.003)*MADD(_t2,f,0.,128,1,-.6,(1175.+(583.*_sin_(2.*B,.4))),24.,44.37,24.05,.015,.4*(.55+(.4*clip((1.+1.)*_sin(4.*B)))),0));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),2);
                    }
                    else if(syn == 81){
                        amaysynL = (vel*waveshape(QFM(_t,f,0.,.00787*0.,.00787*119.,.00787*92.,.00787*101.,.5,1.,1.001,1.,.00787*100.,.00787*61.,.00787*25.,.00787*9.,1.),(.5+(.5*_sin(.4*B))),.05,.46,.3,.7,.8)*env_AHDSR(_t,tL,.2,0.,.01,1.,.05)+vel*clip((1.+2.)*_sin(f*_t)));
                        amaysynR = (vel*waveshape(QFM(_t2,f,0.,.00787*0.,.00787*119.,.00787*92.,.00787*101.,.5,1.,1.001,1.,.00787*100.,.00787*61.,.00787*25.,.00787*9.,1.),(.5+(.5*_sin(.4*B))),.05,.46,.3,.7,.8)*env_AHDSR(_t2,tL,.2,0.,.01,1.,.05)+vel*clip((1.+2.)*_sin(f*_t2)));
                    }
                    else if(syn == 90){
                        amaysynL = (vel*env_AHDSR(_t,tL,.398,0.,.1,1.,.388)*waveshape(MADD(_t,f,0.,80,1,-.95,(1922.+(1572.*clip((1.+.0297)*_sin((.861-.088*aux)*B)))),12.267,.594,8.74,.008,-.75,0),0.,.1,.5,.2,.5,.6));
                        amaysynR = (vel*env_AHDSR(_t2,tL,.398,0.,.1,1.,.388)*waveshape(MADD(_t2,f,0.,80,1,-.95,(1922.+(1572.*clip((1.+.0297)*_sin((.861-.088*aux)*B)))),12.267,.594,8.74,.008,-.75,0),0.,.1,.5,.2,.5,.6));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),3);
                    }
                    else if(syn == 101){
                        amaysynL = (vel*env_AHDSR(_t,tL,.158+0.05*aux,0.,.1,1.,.17)*waveshape(MADD(_t,f,0.,256,1,-.388,(5141.+(2277.*clip((1.+.681)*_sin(.126*B)))),9.292,1.023,4.85,.016,-.86,0),-.86,.1,.5,.2,.5,.6)+.5*vel*env_AHDSR(_t,tL,.158+0.04*aux,0.,.1,1.,.17)*MADD(_t,.501*f,0.,64,1,-.388,(5141.+(2277.*clip((1.+.681)*_sin(.126*B)))),9.292,1.023,4.85,.016,.2*-.86,0));
                        amaysynR = (vel*env_AHDSR(_t2,tL,.158+0.05*aux,0.,.1,1.,.17)*waveshape(MADD(_t2,f,0.,256,1,-.388,(5141.+(2277.*clip((1.+.681)*_sin(.126*B)))),9.292,1.023,4.85,.016,-.86,0),-.86,.1,.5,.2,.5,.6)+.5*vel*env_AHDSR(_t2,tL,.158+0.04*aux,0.,.1,1.,.17)*MADD(_t2,.501*f,0.,64,1,-.388,(5141.+(2277.*clip((1.+.681)*_sin(.126*B)))),9.292,1.023,4.85,.016,.2*-.86,0));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),4);
                    }
                    else if(syn == 112){
                        amaysynL = (vel*sinshape(QFM(_t,f,0.,.00787*103.,.00787*env_AHDSR(Bprog,L,.0001,.024,.11,.185,0.)*0.,.00787*env_AHDSR(Bprog,L,.0001,.19,.161,.096,0.)*2.,.00787*env_AHDSR(Bprog,L,.0001,.16,.197,.035,0.)*85.,.999,1.,1.+.0084*(.5+(.5*_sin(.01*Bprog))),2.,.00787*30.,.00787*37.,.00787*117.,.00787*32.,11.),.03*aux,3.)*env_AHDSR(Bprog,L,.0001,.015,.071,.66,.003));
                        amaysynR = (vel*sinshape(QFM(_t2,f,0.,.00787*103.,.00787*env_AHDSR(Bprog,L,.0001,.024,.11,.185,0.)*0.,.00787*env_AHDSR(Bprog,L,.0001,.19,.161,.096,0.)*2.,.00787*env_AHDSR(Bprog,L,.0001,.16,.197,.035,0.)*85.,.999,1.,1.+.0084*(.5+(.5*_sin(.01*Bprog))),2.,.00787*30.,.00787*37.,.00787*117.,.00787*32.,11.),.03*aux,3.)*env_AHDSR(Bprog,L,.0001,.015,.071,.66,.003));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),3);
                    }
                    else if(syn == 115){
                        amaysynL = (vel*sinshape(QFM(_t,f,0.,.00787*101.,.00787*env_AHDSR(Bprog,L,.0001,.213,.215,.02,0.)*39.,.00787*env_AHDSR(Bprog,L,.0001,.216,.123,.054,0.)*122.,.00787*env_AHDSR(Bprog,L,.0001,.214,.243,.174,0.)*21.,.999,1.,1.+.0285*(.5+(.5*_sin(.24*Bprog))),2.,.00787*28.,.00787*43.,.00787*95.,.00787*115.,10.),.03*aux,3.)*env_AHDSR(Bprog,L,.0001,.03,.15,.177,.102));
                        amaysynR = (vel*sinshape(QFM(_t2,f,0.,.00787*101.,.00787*env_AHDSR(Bprog,L,.0001,.213,.215,.02,0.)*39.,.00787*env_AHDSR(Bprog,L,.0001,.216,.123,.054,0.)*122.,.00787*env_AHDSR(Bprog,L,.0001,.214,.243,.174,0.)*21.,.999,1.,1.+.0285*(.5+(.5*_sin(.24*Bprog))),2.,.00787*28.,.00787*43.,.00787*95.,.00787*115.,10.),.03*aux,3.)*env_AHDSR(Bprog,L,.0001,.03,.15,.177,.102));
                    }
                    else if(syn == 117){
                        amaysynL = (vel*sinshape(QFM(_t,f,0.,.00787*125.,.00787*env_AHDSR(Bprog,L,.0001,.047,.01,.404,0.)*20.,.00787*env_AHDSR(Bprog,L,.0001,.151,.071,.069,0.)*110.,.00787*env_AHDSR(Bprog,L,.0001,.232,.08,.003,0.)*65.,.999,1.,1.+.0799*(.5+(.5*_sin(.18*Bprog))),2.,.00787*109.,.00787*21.,.00787*94.,.00787*0.,11.),.03*aux,3.)*env_AHDSR(Bprog,L,.0001,.03,.167,.796,.114))
      +_sq_(.501*f*_t,.4+.3*(.5+(.5*_sin(.8*Bprog))))
      +.6*clip((1.+.2*aux)*_sin(.25*f*_t));
                        amaysynR = (vel*sinshape(QFM(_t2,f,0.,.00787*125.,.00787*env_AHDSR(Bprog,L,.0001,.047,.01,.404,0.)*20.,.00787*env_AHDSR(Bprog,L,.0001,.151,.071,.069,0.)*110.,.00787*env_AHDSR(Bprog,L,.0001,.232,.08,.003,0.)*65.,.999,1.,1.+.0799*(.5+(.5*_sin(.18*Bprog))),2.,.00787*109.,.00787*21.,.00787*94.,.00787*0.,11.),.03*aux,3.)*env_AHDSR(Bprog,L,.0001,.03,.167,.796,.114))
      +_sq_(.501*f*_t2,.4+.3*(.5+(.5*_sin(.8*Bprog))))
      +.6*clip((1.+.2*aux)*_sin(.25*f*_t2));
                    }
                    else if(syn == 118){
                        amaysynL = env_AHDSR(Bprog,L,.05,0.,.05,.8,.5)*s_atan(23.*(s_atan(MADD(_t,.5*f,lpnoise(_t + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0)+MADD(_t,1.01*.5*f,lpnoise(_t + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0)+MADD(_t,2.005*.5*f,lpnoise(_t + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0)+MADD(_t,.499*.5*f,lpnoise(_t + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0))+.2*theta(Bprog)*exp(-10.*Bprog)*lpnoise(_t + 0.,500.)));
                        amaysynR = env_AHDSR(Bprog,L,.05,0.,.05,.8,.5)*s_atan(23.*(s_atan(MADD(_t2,.5*f,lpnoise(_t2 + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0)+MADD(_t2,1.01*.5*f,lpnoise(_t2 + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0)+MADD(_t2,2.005*.5*f,lpnoise(_t2 + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0)+MADD(_t2,.499*.5*f,lpnoise(_t2 + 0.,500.)*theta(Bprog)*exp(-10.*Bprog),8,1,(.4+(.6*_sin(.21*Bprog))),2000.,100.,5.,100.,.001,.7,0))+.2*theta(Bprog)*exp(-10.*Bprog)*lpnoise(_t2 + 0.,500.)));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),8);
                    }
                    
                    sL += amtL * s_atan(trk_norm(trk) * clamp(env,0.,1.) * amaysynL);
                    sR += amtR * s_atan(trk_norm(trk) * clamp(env,0.,1.) * amaysynR);
                }
            }
        }
    }
    return vec2(s_atan(sidechain * sL + dL), s_atan(sidechain * sR + dR));
}

void main()
{
   float t = (iBlockOffset + (gl_FragCoord.x) + (gl_FragCoord.y)*iTexSize)/iSampleRate;
   vec2 y = mainSynth(t);
   vec2 v  = floor((0.5+0.5*y)*65535.0);
   vec2 vl = mod(v,256.0)/255.0;
   vec2 vh = floor(v/256.0)/255.0;
   gl_FragColor = vec4(vl.x,vh.x,vl.y,vh.y);
}
