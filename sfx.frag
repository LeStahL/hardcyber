#version 130
#define PI radians(180.)
float clip(float a) { return clamp(a,-1.,1.); }
float theta(float x) { return smoothstep(0.,1e-3,clamp(x,0.,1e-3)); }
float _sin(float a) { return sin(2. * PI * mod(a,1.)); }
float _sin_(float a, float p) { return sin(2. * PI * mod(a,1.) + p); }
float _sq_(float a,float pwm) { return sign(2.*fract(a) - 1. + pwm); }
float _tri(float a) { return (4.*abs(fract(a)-.5) - 1.); }
float freqC1(float note){ return 32.7 * pow(2., note/12.); }
float minus1hochN(int n) { return (1. - 2.*float(n % 2)); }
float minus1hochNminus1halbe(int n) { return sin(.5*PI*float(n)); }
float pseudorandom(float x) { return fract(sin(dot(vec2(x),vec2(12.9898,78.233))) * 43758.5453); }
float fhelp(float x) { return 1. + .333*x; } // 1. + .33333*x + .1*x*x + .02381*x*x*x + .00463*x*x*x*x;
float linmix(float x, float a, float b, float y0, float y1) { return mix(y0,y1,clamp(a*x+b,0.,1.)); }

#define pat4(a,b,c,d,x) mod(x,1.)<.25 ? a : mod(x,1.)<.5 ? b : mod(x,1.) < .75 ? c : d

#define NTIME 12
const float pos_B[12] = float[12](0.,2.,10.,18.,25.,26.,27.,102.,110.,118.,126.,144.);
const float pos_t[12] = float[12](0.,3.4286,16.9497,30.283,41.7899,43.3899,44.9483,157.4483,169.6002,181.9079,194.3754,222.7965);
const float pos_BPS[11] = float[11](.5833,.5917,.6,.6083,.625,.6417,.6667,.6583,.65,.6417,.6333);
const float pos_SPB[11] = float[11](1.7144,1.69,1.6667,1.6439,1.6,1.5584,1.4999,1.5191,1.5385,1.5584,1.579);
float BPS, SPB, BT;

float Tsample;

const float filterthreshold = 1e-3;

//TEXCODE

float s_atan(float a) { return 2./PI * atan(a); }

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

float metalnoise(float t, float fac1, float fac2)
{
    return .666*pseudorandom(t) - 1.333*pseudorandom(t-Tsample) + .333*(pseudorandom(t+fac1*Tsample)+pseudorandom(t+fac2*Tsample));
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
    return (x<A ? x/A : x<A+H ? 1. : x<A+H+D ? (1. - (1.-S)*(x-H-A)/D) : x<=L-R ? S : x<=L ? S*(L-x)/R : 0.);
}

float env_limit_length(float x, float length, float release)
{
    return clamp(x * 1e3, 0., 1.) * clamp(1 - (x-length)/release, 0., 1.);
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

float _HCybHHClENV0(float t){return t <=.004? linmix(t,250.,0.,0.,1.):t <=.032? linmix(t,35.7143,-.1429,1.,0.):0.;}
float _HCybHHClENV1(float t){return t <=.009? linmix(t,111.1111,0.,0.,1.):t <=.06? linmix(t,19.6078,-.1765,1.,0.):0.;}
float _HCybHHClENV2(float t){return t <=.15? linmix(t,6.6667,0.,6000.,1000.):t <=.4? linmix(t,4.,-.6,1000.,200.):200.;}
float _HCybHHClENV3(float t){return t <=.18? linmix(t,5.5556,0.,4.123,4.04):4.04;}

uniform float iBlockOffset;
uniform float iSampleRate;
uniform float iTexSize;
uniform sampler2D iSequence;
uniform float iSequenceWidth;

// Read short value from texture at index off
float rshort(float off)
{
    float hilo = mod(off, 2.);
    off *= .5;
    vec2 ind = (vec2(mod(off, iSequenceWidth), floor(off/iSequenceWidth)))/iSequenceWidth+1.e-5;
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

#define NTRK 15
#define NMOD 290
#define NPTN 290
#define NNOT 9711
#define NDRM 48

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
    if(rshort(3.) == 20768.)
        return vec2(sin(5000.*time));
    
    float sL = 0.;
    float sR = 0.;
    float dL = 0.;
    float dR = 0.;

    time = mod(time, 229.1123);
    
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
                if(syn == 126)
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

                if(syn == 126)
                {
                    env = trk_norm(trk) * theta(Bprog) * theta(L - Bprog);
                    if(drum == 0) { sidechain = min(sidechain, 1. - vel * (clamp(1e4 * Bprog,0.,1.) - pow(Bprog/(L-rel),8.))); }
                    else if(drum == 1){
                        amaydrumL = vel*vel*.5*exp(-18.*max(_t-.01,0.))*metalnoise(.6*_t, 1., 2.)
      +.5*(lpnoise(_t,10000.)*smoothstep(0.,.01,_t)*(1.-(1.-.13)*smoothstep(0.,.12,_t-.01))-.3*(1.00*lpnoise((_t-0.00),10000.)*smoothstep(0.,.01,(_t-0.00))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-0.00)-.01))+6.10e-01*lpnoise((_t-1.20e-03),10000.)*smoothstep(0.,.01,(_t-1.20e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-1.20e-03)-.01))+3.72e-01*lpnoise((_t-2.40e-03),10000.)*smoothstep(0.,.01,(_t-2.40e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-2.40e-03)-.01))))*exp(-3.*max(_t-.2,0.));
                        amaydrumR = vel*vel*.5*exp(-18.*max(_t2-.01,0.))*metalnoise(.6*_t2, 1., 2.)
      +.5*(lpnoise(_t,10000.)*smoothstep(0.,.01,_t)*(1.-(1.-.13)*smoothstep(0.,.12,_t-.01))-.3*(1.00*lpnoise((_t-0.00),10000.)*smoothstep(0.,.01,(_t-0.00))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-0.00)-.01))+6.10e-01*lpnoise((_t-1.20e-03),10000.)*smoothstep(0.,.01,(_t-1.20e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-1.20e-03)-.01))+3.72e-01*lpnoise((_t-2.40e-03),10000.)*smoothstep(0.,.01,(_t-2.40e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-2.40e-03)-.01))))*exp(-3.*max(_t2-.2,0.));
                    }
                    else if(drum == 2){
                        amaydrumL = vel*vel*exp(-18.*max(_t-.03+10.*vel,0.))*metalnoise(.6*_t, .5, 2.)
      +vel*(lpnoise(_t,10000.)*smoothstep(0.,.01,_t)*(1.-(1.-.13)*smoothstep(0.,.12,_t-.01))-.3*(1.00*lpnoise((_t-0.00),10000.)*smoothstep(0.,.01,(_t-0.00))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-0.00)-.01))+6.10e-01*lpnoise((_t-1.20e-03),10000.)*smoothstep(0.,.01,(_t-1.20e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-1.20e-03)-.01))+3.72e-01*lpnoise((_t-2.40e-03),10000.)*smoothstep(0.,.01,(_t-2.40e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-2.40e-03)-.01))))*exp(-3.*max(_t-.25,0.));
                        amaydrumR = vel*vel*exp(-18.*max(_t2-.03+10.*vel,0.))*metalnoise(.6*_t2, .5, 2.)
      +vel*(lpnoise(_t,10000.)*smoothstep(0.,.01,_t)*(1.-(1.-.13)*smoothstep(0.,.12,_t-.01))-.3*(1.00*lpnoise((_t-0.00),10000.)*smoothstep(0.,.01,(_t-0.00))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-0.00)-.01))+6.10e-01*lpnoise((_t-1.20e-03),10000.)*smoothstep(0.,.01,(_t-1.20e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-1.20e-03)-.01))+3.72e-01*lpnoise((_t-2.40e-03),10000.)*smoothstep(0.,.01,(_t-2.40e-03))*(1.-(1.-.13)*smoothstep(0.,.12,(_t-2.40e-03)-.01))))*exp(-3.*max(_t2-.25,0.));
                    }
                    else if(drum == 3){
                        amaydrumL = vel*.88*(.1+(.8*exp(-20.*max(_t-.015,0.))))*sinshape(((clamp(.72*_tri(drop_phase(_t,.07,227.,107.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.09))+.69*clamp(.94*_tri(drop_phase(_t,.07,227.,107.)+.69*lpnoise(_t,8709.)),-1.,1.)*exp(-13.89*_t)+.06*lpnoise(_t,18745.)*(1.-smoothstep(0.,.67,_t-.17))+.28*lpnoise(_t,7506.)*exp(-_t*12.44)+.82*lpnoise(_t,2600.)*exp(-_t*17.54))*smoothstep(0.,.004,_t)),.6,9.);
                        amaydrumR = vel*.88*(.1+(.8*exp(-20.*max(_t2-.015,0.))))*sinshape(((clamp(.72*_tri(drop_phase(_t2,.07,227.,107.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.09))+.69*clamp(.94*_tri(drop_phase(_t2,.07,227.,107.)+.69*lpnoise(_t2,8709.)),-1.,1.)*exp(-13.89*_t2)+.06*lpnoise(_t2,18745.)*(1.-smoothstep(0.,.67,_t2-.17))+.28*lpnoise(_t2,7506.)*exp(-_t2*12.44)+.82*lpnoise(_t2,2600.)*exp(-_t2*17.54))*smoothstep(0.,.004,_t2)),.6,9.);
                    }
                    else if(drum == 4){
                        amaydrumL = vel*(vel*((_t <=0.004? smoothstep(0.,0.004,_t): exp(-10.6244*(_t-0.004)) )*(.87*_tri(drop_phase(_t,.067,230.539,107.)+.7*(_t <=0.004? smoothstep(0.,0.004,_t): exp(-10.6244*(_t-0.004)) )*lpnoise(_t,8700.0)))+0.));
                        amaydrumR = vel*(vel*((_t <=0.004? smoothstep(0.,0.004,_t): exp(-10.6244*(_t-0.004)) )*(.87*_tri(drop_phase((_t-.00021),.067,230.539,107.)+.7*(_t <=0.004? smoothstep(0.,0.004,_t): exp(-10.6244*(_t-0.004)) )*lpnoise((_t-.00021),8700.0)))+0.));
                    }
                    else if(drum == 5){
                        amaydrumL = vel*protokick(_t,242.,55.,.036,.03,.0666,1.42,.02,.25,.01,.1,.4)
      +protokick(_t,3333.,340.,.008,0.,.01,2.,2.4,0.,.2,.3,1.)
      +.7*((clamp(2.27*_tri(drop_phase(_t,.03,241.,72.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.01))+.91*clamp(.9*_tri(drop_phase(_t,.03,241.,72.)+.91*lpnoise(_t,8164.)),-1.,1.)*exp(-20.76*_t)+.05*lpnoise(_t,10466.)*(1.-smoothstep(0.,.18,_t-.56))+.56*lpnoise(_t,7123.)*exp(-_t*5.45)+.11*lpnoise(_t,1134.)*exp(-_t*13.82))*smoothstep(0.,.004,_t));
                        amaydrumR = vel*protokick(_t2,242.,55.,.036,.03,.0666,1.42,.02,.25,.01,.1,.4)
      +protokick(_t2,3333.,340.,.008,0.,.01,2.,2.4,0.,.2,.3,1.)
      +.7*((clamp(2.27*_tri(drop_phase(_t2,.03,241.,72.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.01))+.91*clamp(.9*_tri(drop_phase(_t2,.03,241.,72.)+.91*lpnoise(_t2,8164.)),-1.,1.)*exp(-20.76*_t2)+.05*lpnoise(_t2,10466.)*(1.-smoothstep(0.,.18,_t2-.56))+.56*lpnoise(_t2,7123.)*exp(-_t2*5.45)+.11*lpnoise(_t2,1134.)*exp(-_t2*13.82))*smoothstep(0.,.004,_t2));
                    }
                    else if(drum == 6){
                        amaydrumL = vel*(vel*(_HCybHHClENV0(_t)*(.13*sinshape(pseudorandom(_HCybHHClENV2(_t)*_t+1.*_HCybHHClENV0(_t)*(.5*lpnoise(_t,14142.828)+.5*lpnoise(_t,.463*14142.828))),_HCybHHClENV3(_t),3.))+_HCybHHClENV1(_t)*(.04*(.5*lpnoise(_t,14142.828)+.5*lpnoise(_t,.463*14142.828)))));
                        amaydrumR = vel*(vel*(_HCybHHClENV0(_t)*(.13*sinshape(pseudorandom(_HCybHHClENV2(_t)*(_t-.00044)+1.*_HCybHHClENV0(_t)*(.5*lpnoise((_t-.00044),14142.828)+.5*lpnoise((_t-.00044),.463*14142.828))),_HCybHHClENV3(_t),3.))+_HCybHHClENV1(_t)*(.04*(.5*lpnoise((_t-.00127),14142.828)+.5*lpnoise((_t-.00127),.463*14142.828)))));
                    }
                    else if(drum == 7){
                        amaydrumL = vel*(clamp(1.15*_tri(drop_phase(_t,.13,157.,76.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t-.13))+.81*clamp(.24*_tri(drop_phase(_t,.13,157.,76.)+.81*lpnoise(_t,2401.)),-1.,1.)*exp(-14.8*_t)+.01*lpnoise(_t,4079.)*(1.-smoothstep(0.,.7,_t-.12))+.5*lpnoise(_t,5164.)*exp(-_t*19.79)+.76*lpnoise(_t,8446.)*exp(-_t*24.))*smoothstep(0.,.002,_t);
                        amaydrumR = vel*(clamp(1.15*_tri(drop_phase(_t2,.13,157.,76.)),-1.,1.)*(1.-smoothstep(-1e-3,0.,_t2-.13))+.81*clamp(.24*_tri(drop_phase(_t2,.13,157.,76.)+.81*lpnoise(_t2,2401.)),-1.,1.)*exp(-14.8*_t2)+.01*lpnoise(_t2,4079.)*(1.-smoothstep(0.,.7,_t2-.12))+.5*lpnoise(_t2,5164.)*exp(-_t2*19.79)+.76*lpnoise(_t2,8446.)*exp(-_t2*24.))*smoothstep(0.,.002,_t2);
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
                    else if(syn == 20){
                        
                        amaysynL = (theta(Bprog)*exp(-11.*Bprog)*env_AHDSR(Bprog,L,.01,0.,.1+.5*vel,.01,.4)*clip((1.+theta(Bprog)*exp(-11.*Bprog))*_tri(f*_t+.2*env_AHDSR(Bprog,L,.5,1.,.1,1.,0.)*clip((1.+3.)*_sq_(1.99*f*_t,.3+2.*vel+.2*(2.*fract(3.97*f*_t)-1.)))+.2*vel*env_AHDSR(Bprog,L,.325,1.,.1,1.,0.)*(2.*fract(3.97*f*_t)-1.)))+.4*theta(Bprog)*exp(-11.*Bprog)*env_AHDSR(Bprog,L,.325,1.,.1,1.,0.)*clip((1.+3.)*_sq_(1.99*f*_t,.3+2.*vel+.2*(2.*fract(3.97*f*_t)-1.)))*env_AHDSR(Bprog,L,0.,0.,.2+.2*vel,.01,.4)+.4*env_AHDSR(Bprog,L,0.,0.,.05,0.,0.)*lpnoise(_t+0.,6000.+200.*note_pitch(_note)));
                        amaysynR = (theta(Bprog)*exp(-11.*Bprog)*env_AHDSR(Bprog,L,.01,0.,.1+.5*vel,.01,.4)*clip((1.+theta(Bprog)*exp(-11.*Bprog))*_tri(f*_t2+.2*env_AHDSR(Bprog,L,.5,1.,.1,1.,0.)*clip((1.+3.)*_sq_(1.99*f*_t2,.3+2.*vel+.2*(2.*fract(3.97*f*_t2)-1.)))+.2*vel*env_AHDSR(Bprog,L,.325,1.,.1,1.,0.)*(2.*fract(3.97*f*_t2)-1.)))+.4*theta(Bprog)*exp(-11.*Bprog)*env_AHDSR(Bprog,L,.325,1.,.1,1.,0.)*clip((1.+3.)*_sq_(1.99*f*_t2,.3+2.*vel+.2*(2.*fract(3.97*f*_t2)-1.)))*env_AHDSR(Bprog,L,0.,0.,.2+.2*vel,.01,.4)+.4*env_AHDSR(Bprog,L,0.,0.,.05,0.,0.)*lpnoise(_t2+0.,6000.+200.*note_pitch(_note)));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),2);
                    }
                    else if(syn == 84){
                        
                        amaysynL = (vel*waveshape(QFM(_t,f,0.,.00787*75.,.00787*59.,.00787*26.,.00787*53.,.5,1.,1.001,1.,.00787*1.,.00787*93.,.00787*18.,.00787*17.,7.),(.5+(.5*_sin(.4*B))),.05,.46,.3,.7,.8)*env_AHDSR(_t,tL,.2,0.,.01,1.,.05)+vel*clip((1.+2.)*_sin(f*_t)));
                        amaysynR = (vel*waveshape(QFM(_t2,f,0.,.00787*75.,.00787*59.,.00787*26.,.00787*53.,.5,1.,1.001,1.,.00787*1.,.00787*93.,.00787*18.,.00787*17.,7.),(.5+(.5*_sin(.4*B))),.05,.46,.3,.7,.8)*env_AHDSR(_t2,tL,.2,0.,.01,1.,.05)+vel*clip((1.+2.)*_sin(f*_t2)));
                    }
                    else if(syn == 110){
                        time2 = time-0.01; _t2 = _t-0.01;
                        amaysynL = (vel*QFM(_t,f,0.,.00787*85.,.00787*env_AHDSR(Bprog,L,.0001,.07,.093,.148,0.)*33.,.00787*env_AHDSR(Bprog,L,.0001,.285,.2,.357,0.)*68.,.00787*env_AHDSR(Bprog,L,.0001,.244,.181,.003,0.)*120.,.999,1.,1.+.0849*(.5+(.5*_sin(.25*Bprog))),2.,.00787*10.,.00787*53.,.00787*115.,.00787*38.,9.)*env_AHDSR(Bprog,L,.0001,.044,.163,.13,.129));
                        amaysynR = (vel*QFM(_t2,f,0.,.00787*85.,.00787*env_AHDSR(Bprog,L,.0001,.07,.093,.148,0.)*33.,.00787*env_AHDSR(Bprog,L,.0001,.285,.2,.357,0.)*68.,.00787*env_AHDSR(Bprog,L,.0001,.244,.181,.003,0.)*120.,.999,1.,1.+.0849*(.5+(.5*_sin(.25*Bprog))),2.,.00787*10.,.00787*53.,.00787*115.,.00787*38.,9.)*env_AHDSR(Bprog,L,.0001,.044,.163,.13,.129));
env = theta(Bprog)*pow(1.-smoothstep(Boff-rel, Boff, B),.5);
                    }
                    else if(syn == 119){
                        
                        amaysynL = env_AHDSR(Bprog,L,.034,0.,.1,1.,.08)*sinshape((s_atan((1.+aux)*MADD((_t-0.0*(1.+5.*_sin(.08*_t))),.5*f,0.,32,1,.15,200.,100.,0.,0.,.05,.48,0)+.8*_sin(f*(_t-0.0*(1.+5.*_sin(.08*_t)))))
      +s_atan((1.+aux)*MADD((_t-1.3e-03*(1.+5.*_sin(.08*_t))),.5*f,0.,32,1,.15,200.,100.,0.,0.,.05,.48,0)+.8*_sin(f*(_t-1.3e-03*(1.+5.*_sin(.08*_t)))))
      +s_atan((1.+aux)*MADD((_t-2.6e-03*(1.+5.*_sin(.08*_t))),.5*f,0.,32,1,.15,200.,100.,0.,0.,.05,.48,0)+.8*_sin(f*(_t-2.6e-03*(1.+5.*_sin(.08*_t)))))),.8,3.);
                        amaysynR = env_AHDSR(Bprog,L,.034,0.,.1,1.,.08)*sinshape((s_atan((1.+aux)*MADD((_t2-0.0*(1.+5.*_sin(.08*_t2))),.5*f,0.,32,1,.15,200.,100.,0.,0.,.05,.48,0)+.8*_sin(f*(_t2-0.0*(1.+5.*_sin(.08*_t2)))))
      +s_atan((1.+aux)*MADD((_t2-1.3e-03*(1.+5.*_sin(.08*_t2))),.5*f,0.,32,1,.15,200.,100.,0.,0.,.05,.48,0)+.8*_sin(f*(_t2-1.3e-03*(1.+5.*_sin(.08*_t2)))))
      +s_atan((1.+aux)*MADD((_t2-2.6e-03*(1.+5.*_sin(.08*_t2))),.5*f,0.,32,1,.15,200.,100.,0.,0.,.05,.48,0)+.8*_sin(f*(_t2-2.6e-03*(1.+5.*_sin(.08*_t2)))))),.8,3.);
                    }
                    else if(syn == 120){
                        time2 = time-0.011; _t2 = _t-0.011;
                        amaysynL = .9*vel*(s_atan(1.*(2.*fract(.2497*f*(_t-0.0*(1.+1.*_sin(.9*_t)))+.02)-1.)+MADD((_t-0.0*(1.+1.*_sin(.9*_t))),.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD((_t-0.0*(1.+1.*_sin(.9*_t))),.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0))
      +s_atan(1.*(2.*fract(.2497*f*(_t-3.0e-03*(1.+1.*_sin(.9*_t)))+.02)-1.)+MADD((_t-3.0e-03*(1.+1.*_sin(.9*_t))),.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD((_t-3.0e-03*(1.+1.*_sin(.9*_t))),.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0))
      +s_atan(1.*(2.*fract(.2497*f*(_t-6.0e-03*(1.+1.*_sin(.9*_t)))+.02)-1.)+MADD((_t-6.0e-03*(1.+1.*_sin(.9*_t))),.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD((_t-6.0e-03*(1.+1.*_sin(.9*_t))),.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0)))
      +.9*vel*(.8*(2.*fract(.2497*f*_t+.02)-1.)+MADD(_t,.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD(_t,.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0))
      +.5*vel*s_atan(1.*(2.*fract(.2497*f*_t+.02)-1.)+MADD(_t,.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD(_t,.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0));
                        amaysynR = .9*vel*(s_atan(1.*(2.*fract(.2497*f*(_t2-0.0*(1.+1.*_sin(.9*_t2)))+.02)-1.)+MADD((_t2-0.0*(1.+1.*_sin(.9*_t2))),.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD((_t2-0.0*(1.+1.*_sin(.9*_t2))),.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0))
      +s_atan(1.*(2.*fract(.2497*f*(_t2-3.0e-03*(1.+1.*_sin(.9*_t2)))+.02)-1.)+MADD((_t2-3.0e-03*(1.+1.*_sin(.9*_t2))),.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD((_t2-3.0e-03*(1.+1.*_sin(.9*_t2))),.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0))
      +s_atan(1.*(2.*fract(.2497*f*(_t2-6.0e-03*(1.+1.*_sin(.9*_t2)))+.02)-1.)+MADD((_t2-6.0e-03*(1.+1.*_sin(.9*_t2))),.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD((_t2-6.0e-03*(1.+1.*_sin(.9*_t2))),.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0)))
      +.9*vel*(.8*(2.*fract(.2497*f*_t2+.02)-1.)+MADD(_t2,.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD(_t2,.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0))
      +.5*vel*s_atan(1.*(2.*fract(.2497*f*_t2+.02)-1.)+MADD(_t2,.5009*f,0.,16,1,-1.,10.*f,1.,10.,1.,.015,1.,0)+.8*MADD(_t2,.25*f,0.,32,1,-.6,1000.,100.,0.,1.,.02,.3,0));
                    }
                    else if(syn == 121){
                        time2 = time-5e-3; _t2 = _t-5e-3;
                        amaysynL = .6*exp(-3.2*Bprog)*clip(2.*(.6+(.4*_sin(.256*BT)))*MADD(_t,f,.3*lpnoise(_t + 0.,8330.)*env_AHDSR(Bprog,L,.08,0.,.2,.4,1.)+.3*lpnoise(_t + 0.,510.)*env_AHDSR(Bprog,L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0));
                        amaysynR = .6*exp(-3.2*Bprog)*clip(2.*(.6+(.4*_sin(.256*BT)))*MADD(_t2,f,.3*lpnoise(_t2 + 0.,8330.)*env_AHDSR(Bprog,L,.08,0.,.2,.4,1.)+.3*lpnoise(_t2 + 0.,510.)*env_AHDSR(Bprog,L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0));
                    }
                    else if(syn == 122){
                        time2 = time-5e-2; _t2 = _t-5e-2;
                        amaysynL = s_atan(2.2*(1.0*env_limit_length((Bprog-BPS*0.000),.5*(L-rel),1.)*exp(-4.1*(Bprog-BPS*0.000))*MADD((_t-0.000),f,.3*lpnoise((_t-0.000) + 0.,8330.)*env_AHDSR((Bprog-BPS*0.000),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t-0.000) + 0.,510.)*env_AHDSR((Bprog-BPS*0.000),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +6.0e-02*env_limit_length((Bprog-BPS*9.430e-01),.5*(L-rel),1.)*exp(-4.1*(Bprog-BPS*9.430e-01))*MADD((_t-9.430e-01),f,.3*lpnoise((_t-9.430e-01) + 0.,8330.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t-9.430e-01) + 0.,510.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +3.6e-03*env_limit_length((Bprog-BPS*1.886),.5*(L-rel),1.)*exp(-4.1*(Bprog-BPS*1.886))*MADD((_t-1.886),f,.3*lpnoise((_t-1.886) + 0.,8330.)*env_AHDSR((Bprog-BPS*1.886),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t-1.886) + 0.,510.)*env_AHDSR((Bprog-BPS*1.886),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)));
                        amaysynR = s_atan(2.2*(1.0*env_limit_length((Bprog-BPS*0.000),.5*(L-rel),1.)*exp(-4.1*(Bprog-BPS*0.000))*MADD((_t2-0.000),f,.3*lpnoise((_t2-0.000) + 0.,8330.)*env_AHDSR((Bprog-BPS*0.000),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t2-0.000) + 0.,510.)*env_AHDSR((Bprog-BPS*0.000),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +6.0e-02*env_limit_length((Bprog-BPS*9.430e-01),.5*(L-rel),1.)*exp(-4.1*(Bprog-BPS*9.430e-01))*MADD((_t2-9.430e-01),f,.3*lpnoise((_t2-9.430e-01) + 0.,8330.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t2-9.430e-01) + 0.,510.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +3.6e-03*env_limit_length((Bprog-BPS*1.886),.5*(L-rel),1.)*exp(-4.1*(Bprog-BPS*1.886))*MADD((_t2-1.886),f,.3*lpnoise((_t2-1.886) + 0.,8330.)*env_AHDSR((Bprog-BPS*1.886),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t2-1.886) + 0.,510.)*env_AHDSR((Bprog-BPS*1.886),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)));
                    }
                    else if(syn == 123){
                        time2 = time-0.005; _t2 = _t-0.005;
                        amaysynL = vel*(sinshape(MADD((_t-0.0*(1.+.1*_sin(.5*_t))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t-0.0*(1.+.1*_sin(.5*_t))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.)
      +sinshape(MADD((_t-1.0e-02*(1.+.1*_sin(.5*_t))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t-1.0e-02*(1.+.1*_sin(.5*_t))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.))*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8)
      +.5*vel*_sin_(.4998*_t,(.5+(.5*_sin_(.37*Bprog,1.57))))*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8);
                        amaysynR = vel*(sinshape(MADD((_t2-0.0*(1.+.1*_sin(.5*_t2))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t2-0.0*(1.+.1*_sin(.5*_t2))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.)
      +sinshape(MADD((_t2-1.0e-02*(1.+.1*_sin(.5*_t2))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t2-1.0e-02*(1.+.1*_sin(.5*_t2))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.))*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8)
      +.5*vel*_sin_(.4998*_t2,(.5+(.5*_sin_(.37*Bprog,1.57))))*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8);
                    }
                    else if(syn == 125){
                        time2 = time-2e-3; _t2 = _t-2e-3;
                        amaysynL = .25*clamp(1.+(.13-Bprog)/(.01),exp(-7.*Bprog),1.)*clip((1.+5.+4.*(.5+(.5*_sin(.2*BT)))*(.5+(.5*_sin(.21*BT))))*_tri(.251*f*_t+.35*(.5+(.5*_sin(.5*Bprog)))))
      +.76*clamp(1.+(.13-Bprog)/(.01),exp(-7.*Bprog),1.)*_tri(.5*f*_t+.4+.15*(.5+(.5*_sin(.5*Bprog)))+.22*env_AHDSR(Bprog,L,.025,0.,.1,.3,0.)*clip((1.+5.+4.*(.5+(.5*_sin(.2*BT)))*(.5+(.5*_sin(.21*BT))))*_tri(.251*f*_t+.35*(.5+(.5*_sin(.5*Bprog))))));
                        amaysynR = .25*clamp(1.+(.13-Bprog)/(.01),exp(-7.*Bprog),1.)*clip((1.+5.+4.*(.5+(.5*_sin(.2*BT)))*(.5+(.5*_sin(.21*BT))))*_tri(.251*f*_t2+.35*(.5+(.5*_sin(.5*Bprog)))))
      +.76*clamp(1.+(.13-Bprog)/(.01),exp(-7.*Bprog),1.)*_tri(.5*f*_t2+.4+.15*(.5+(.5*_sin(.5*Bprog)))+.22*env_AHDSR(Bprog,L,.025,0.,.1,.3,0.)*clip((1.+5.+4.*(.5+(.5*_sin(.2*BT)))*(.5+(.5*_sin(.21*BT))))*_tri(.251*f*_t2+.35*(.5+(.5*_sin(.5*Bprog))))));
                    }
                    
                    sL += amtL * s_atan(trk_norm(trk) * clamp(env,0.,1.) * amaysynL);
                    sR += amtR * s_atan(trk_norm(trk) * clamp(env,0.,1.) * amaysynR);
                }
            }
        }
    }
    return vec2(s_atan(.44 * sidechain * sL + .77 * dL), s_atan(.44 * sidechain * sR + .77 * dR));
}

void main()
{
    Tsample = 1./iSampleRate;
    float t = (iBlockOffset + gl_FragCoord.x + gl_FragCoord.y*iTexSize) * Tsample;
    vec2 s = mainSynth(t);
    vec2 v  = floor((0.5+0.5*s)*65535.0);
    vec2 vl = mod(v,256.0)/255.0;
    vec2 vh = floor(v/256.0)/255.0;
    gl_FragColor = vec4(vl.x,vh.x,vl.y,vh.y);
}
