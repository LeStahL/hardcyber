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

#define pat4(a,b,c,d,x) mod(x,1.)<.25 ? a : mod(x,1.)<.5 ? b : mod(x,1.) < .75 ? c : d

#define NTIME 7
const float pos_B[7] = float[7](0.,2.,10.,26.,27.,28.,144.);
const float pos_t[7] = float[7](0.,3.428571,16.949698,43.616365,45.237986,46.816934,225.278472);
const float pos_BPS[6] = float[6](.5833,.5917,.6,.6167,.6333,.65);
const float pos_SPB[6] = float[6](1.7144,1.69,1.6667,1.6215,1.579,1.5385);
float BPS, SPB, BT;

float Tsample;

const float filterthreshold = 1e-3;

//TEXCODE

float s_atan(float a) { return 2./PI * atan(a); }

float lpnoise(float t, float fq)
{
    t *= fq;
    float tt = fract(t);
    float tn = t - tt;
    return mix(pseudorandom(floor(tn) / fq), pseudorandom(floor(tn + 1.0) / fq), smoothstep(0.0, 1.0, tt));
}

float env_AHDSR(float x, float L, float A, float H, float D, float S, float R)
{
    return (x<A ? x/A : x<A+H ? 1. : x<A+H+D ? (1. - (1.-S)*(x-H-A)/D) : x<=L-R ? S : x<=L ? S*(L-x)/R : 0.);
}

float env_limit_length(float x, float length, float release)
{
    return clamp(x * 1e3, 0., 1.) * clamp(1 - (x-length)/release, 0., 1.);
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

#define NTRK 7
#define NMOD 71
#define NPTN 71
#define NNOT 3229
#define NDRM 47

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

    time = mod(time, 231.432318);
    
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
                if(syn == 125)
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

                if(syn == 125)
                {
                    env = trk_norm(trk) * theta(Bprog) * theta(L - Bprog);
                    if(drum == 0) { sidechain = min(sidechain, 1. - vel * (clamp(1e4 * Bprog,0.,1.) - pow(Bprog/(L-rel),8.))); }
                    
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
                        amaysynL = .6*theta(Bprog)*exp(-3.2*Bprog)*clip(2.*(.6+(.4*_sin(.256*BT)))*MADD(_t,f,.3*lpnoise(_t + 0.,8330.)*env_AHDSR(Bprog,L,.08,0.,.2,.4,1.)+.3*lpnoise(_t + 0.,510.)*env_AHDSR(Bprog,L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0));
                        amaysynR = .6*theta(Bprog)*exp(-3.2*Bprog)*clip(2.*(.6+(.4*_sin(.256*BT)))*MADD(_t2,f,.3*lpnoise(_t2 + 0.,8330.)*env_AHDSR(Bprog,L,.08,0.,.2,.4,1.)+.3*lpnoise(_t2 + 0.,510.)*env_AHDSR(Bprog,L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0));
                    }
                    else if(syn == 122){
                        time2 = time-5e-2; _t2 = _t-5e-2;
                        amaysynL = s_atan(2.2*(1.0*env_limit_length((Bprog-BPS*0.000),.5*(L-rel),1.)*theta((Bprog-BPS*0.000))*exp(-4.1*(Bprog-BPS*0.000))*MADD((_t-0.000),f,.3*lpnoise((_t-0.000) + 0.,8330.)*env_AHDSR((Bprog-BPS*0.000),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t-0.000) + 0.,510.)*env_AHDSR((Bprog-BPS*0.000),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +6.0e-02*env_limit_length((Bprog-BPS*9.430e-01),.5*(L-rel),1.)*theta((Bprog-BPS*9.430e-01))*exp(-4.1*(Bprog-BPS*9.430e-01))*MADD((_t-9.430e-01),f,.3*lpnoise((_t-9.430e-01) + 0.,8330.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t-9.430e-01) + 0.,510.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +3.6e-03*env_limit_length((Bprog-BPS*1.886),.5*(L-rel),1.)*theta((Bprog-BPS*1.886))*exp(-4.1*(Bprog-BPS*1.886))*MADD((_t-1.886),f,.3*lpnoise((_t-1.886) + 0.,8330.)*env_AHDSR((Bprog-BPS*1.886),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t-1.886) + 0.,510.)*env_AHDSR((Bprog-BPS*1.886),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)));
                        amaysynR = s_atan(2.2*(1.0*env_limit_length((Bprog-BPS*0.000),.5*(L-rel),1.)*theta((Bprog-BPS*0.000))*exp(-4.1*(Bprog-BPS*0.000))*MADD((_t2-0.000),f,.3*lpnoise((_t2-0.000) + 0.,8330.)*env_AHDSR((Bprog-BPS*0.000),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t2-0.000) + 0.,510.)*env_AHDSR((Bprog-BPS*0.000),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +6.0e-02*env_limit_length((Bprog-BPS*9.430e-01),.5*(L-rel),1.)*theta((Bprog-BPS*9.430e-01))*exp(-4.1*(Bprog-BPS*9.430e-01))*MADD((_t2-9.430e-01),f,.3*lpnoise((_t2-9.430e-01) + 0.,8330.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t2-9.430e-01) + 0.,510.)*env_AHDSR((Bprog-BPS*9.430e-01),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)
      +3.6e-03*env_limit_length((Bprog-BPS*1.886),.5*(L-rel),1.)*theta((Bprog-BPS*1.886))*exp(-4.1*(Bprog-BPS*1.886))*MADD((_t2-1.886),f,.3*lpnoise((_t2-1.886) + 0.,8330.)*env_AHDSR((Bprog-BPS*1.886),L,.08,0.,.2,.4,1.)+.3*lpnoise((_t2-1.886) + 0.,510.)*env_AHDSR((Bprog-BPS*1.886),L,.02,.1,.3,.2,1.),64,1,(.6+(.4*_sin(.256*BT))),10000.,100.,0.,0.,.001,.5+.1*(.6+(.4*_sin(.256*BT))),0)));
                    }
                    else if(syn == 123){
                        time2 = time-0.005; _t2 = _t-0.005;
                        amaysynL = (sinshape(MADD((_t-0.0*(1.+.1*_sin(.5*_t))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t-0.0*(1.+.1*_sin(.5*_t))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.)
      +sinshape(MADD((_t-1.0e-02*(1.+.1*_sin(.5*_t))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t-1.0e-02*(1.+.1*_sin(.5*_t))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.))*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8)
      +.45*_sin_(.4998*_t,(.5+(.5*_sin_(.37*Bprog,1.57))))*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8);
                        amaysynR = (sinshape(MADD((_t2-0.0*(1.+.1*_sin(.5*_t2))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t2-0.0*(1.+.1*_sin(.5*_t2))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.)
      +sinshape(MADD((_t2-1.0e-02*(1.+.1*_sin(.5*_t2))),.998*f,0.,50,1,.9,666.*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),8.,0.,100.,.007,.8+.5*(.5+(.5*_sin_(.37*Bprog,1.57)))*(.5+(.5*_sin(.4*Bprog))),0)+MADD((_t2-1.0e-02*(1.+.1*_sin(.5*_t2))),f,0.,50,1,-1.,1234.*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8),5.,0.,10.,.017,.7+-.2*(.5+(.5*_sin(.4*Bprog))),0),.1*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8),3.))*env_AHDSR(Bprog,L,.09*vel,.14,.2,.5,.8)
      +.45*_sin_(.4998*_t2,(.5+(.5*_sin_(.37*Bprog,1.57))))*env_AHDSR(Bprog,L,.15*vel,.14,.15,.7,.8);
                    }
                    
                    sL += amtL * s_atan(trk_norm(trk) * clamp(env,0.,1.) * amaysynL);
                    sR += amtR * s_atan(trk_norm(trk) * clamp(env,0.,1.) * amaysynR);
                }
            }
        }
    }
    return vec2(s_atan(.666*(sidechain * sL + dL)), s_atan(.666*(sidechain * sR + dR)));
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
