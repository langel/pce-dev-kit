#include <math.h>

typedef struct {
	float a0, a1, a2, a3, a4;
	float xm1, xm2, xm3, xm4;
	float ym1, ym2, ym3, ym4;
} linkwitz_riley_biquad;

typedef struct {
	float crossover_frequency;
	float sample_rate;
	float b1, b2, b3, b4;
	linkwitz_riley_biquad hp;
	linkwitz_riley_biquad lp;
} linkwitz_riley_scheme;

linkwitz_riley_scheme linkwitz_riley_setup(float crossover_frequency, float sample_rate) {
	linkwitz_riley_scheme scheme;
	scheme.crossover_frequency = crossover_frequency;
	scheme.sample_rate = sample_rate;
	float pi = 3.141f;
	float wc1 = 2 * pi * crossover_frequency;
	float wc2 = wc1 * wc1;
	float wc3 = wc2 * wc1;
	float wc4 = wc2 * wc2;
	float k1 = wc1 / tan(pi * crossover_frequency / sample_rate);
	float k2 = k1 * k1;
	float k3 = k2 * k1;
	float k4 = k2 * k2;
	float sqr = sqrt(2);
	float sq1 = sqr * wc3 * k1;
	float sq2 = sqr * wc1 * k3;
	float atp = 4 * wc2 * k2 + 2 * sq1 + k4 + 2 * sq2 + wc4;
	scheme.b1 = (4 * (wc4 + sq1 - k4 - sq2)) / atp;
	scheme.b2 = (6 * wc4 - 8 * wc2 * k2 + 6 * k4) / atp;
	scheme.b3 = (4 * (wc4 - sq1 + sq2 - k4)) / atp;
	scheme.b4 = (k4 - 2 * sq1 + wc4 - 2 * sq2 + 4 * wc2 * k2) / atp;
	scheme.hp.xm1 = scheme.hp.xm2 = scheme.hp.xm3 = scheme.hp.xm4 = 0.f;
	scheme.hp.ym1 = scheme.hp.ym2 = scheme.hp.ym3 = scheme.hp.ym4 = 0.f;
	scheme.hp.a0 = k4 / atp;
	scheme.hp.a1 = 4 * k4 / atp;
	scheme.hp.a2 = 6 * k4 / atp;
	scheme.hp.a3 = scheme.hp.a1;
	scheme.hp.a4 = scheme.hp.a0;
	scheme.lp.xm1 = scheme.lp.xm2 = scheme.lp.xm3 = scheme.lp.xm4 = 0.f;
	scheme.lp.ym1 = scheme.lp.ym2 = scheme.lp.ym3 = scheme.lp.ym4 = 0.f;
	scheme.lp.a0 = wc4 / atp;
	scheme.lp.a1 = 4 * wc4 / atp;
	scheme.lp.a2 = 6 * wc4 / atp;
	scheme.lp.a3 = scheme.lp.a1;
	scheme.lp.a4 = scheme.lp.a0;
	return scheme;
}

float linkwitz_riley_process_highpass(linkwitz_riley_scheme scheme, float sample) {
	float temp = 
		scheme.hp.a0 * sample +
		scheme.hp.a1 * scheme.hp.xm1 +
		scheme.hp.a2 * scheme.hp.xm2 +
		scheme.hp.a3 * scheme.hp.xm3 +
		scheme.hp.a4 * scheme.hp.xm4 -
		scheme.b1 * scheme.hp.ym1 -
		scheme.b2 * scheme.hp.ym2 -
		scheme.b3 * scheme.hp.ym3 -
		scheme.b4 * scheme.hp.ym4;
	scheme.hp.xm4 = scheme.hp.xm3;
	scheme.hp.xm3 = scheme.hp.xm2;
	scheme.hp.xm2 = scheme.hp.xm1;
	scheme.hp.xm1 = sample;
	scheme.hp.ym4 = scheme.hp.ym3;
	scheme.hp.ym3 = scheme.hp.ym2;
	scheme.hp.ym2 = scheme.hp.ym1;
	scheme.hp.ym1 = temp;
	return temp;
}

float linkwitz_riley_process_lowpass(linkwitz_riley_scheme scheme, float sample) {
	float temp = 
		scheme.lp.a0 * sample +
		scheme.lp.a1 * scheme.lp.xm1 +
		scheme.lp.a2 * scheme.lp.xm2 +
		scheme.lp.a3 * scheme.lp.xm3 +
		scheme.lp.a4 * scheme.lp.xm4 -
		scheme.b1 * scheme.lp.ym1 -
		scheme.b2 * scheme.lp.ym2 -
		scheme.b3 * scheme.lp.ym3 -
		scheme.b4 * scheme.lp.ym4;
	scheme.lp.xm4 = scheme.lp.xm3;
	scheme.lp.xm3 = scheme.lp.xm2;
	scheme.lp.xm2 = scheme.lp.xm1;
	scheme.lp.xm1 = sample;
	scheme.lp.ym4 = scheme.lp.ym3;
	scheme.lp.ym3 = scheme.lp.ym2;
	scheme.lp.ym2 = scheme.lp.ym1;
	scheme.lp.ym1 = temp;
	return temp;
}


// the following code was stolen from : 
// https://www.musicdsp.org/en/latest/Filters/266-4th-order-linkwitz-riley-filters.html

/*
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <assert.h>

class LRCrossoverFilter { // LR4 crossover filter
private:
    struct filterCoefficents {
        float a0, a1, a2, a3, a4;
    } lpco, hpco;

    float b1co, b2co, b3co, b4co;

    struct {
        float xm1 = 0.0f;
        float xm2 = 0.0f;
        float xm3 = 0.0f;
        float xm4 = 0.0f;
        float ym1 = 0.0f, ym2 = 0.0f, ym3 = 0.0f, ym4 = 0.0f;
    } hptemp, lptemp;

    float coFreqRunningAv = 100.0f;
public:
    void setup(float crossoverFrequency, float sr);
    void processBlock(float * in, float * outHP, float * outLP, int numSamples);
    void dumpCoefficents(struct filterCoefficents x) {
        std::cout << "a0: " << x.a0 << "\n";
        std::cout << "a1: " << x.a1 << "\n";
        std::cout << "a2: " << x.a2 << "\n";
        std::cout << "a3: " << x.a3 << "\n";
        std::cout << "a4: " << x.a4 << "\n";
    }
    void dumpInformation() {
        std::cout << "-----\nfrequency: "<< coFreqRunningAv << "\n";
        std::cout << "lpco:\n";
        dumpCoefficents(lpco);
        std::cout << "hpco:\n";
        dumpCoefficents(hpco);
        std::cout << "bco:\nb1: ";
        std::cout << b1co << "\nb2: " << b2co << "\nb3: " <<  b3co << "\nb4: " << b4co << "\n";
    }


};


void LRCrossoverFilter::setup(float crossoverFrequency, float sr) {

    const float pi = 3.141f;

    coFreqRunningAv = crossoverFrequency;

    float cowc=2*pi*coFreqRunningAv;
    float cowc2=cowc*cowc;
    float cowc3=cowc2*cowc;
    float cowc4=cowc2*cowc2;

    float cok=cowc/tan(pi*coFreqRunningAv/sr);
    float cok2=cok*cok;
    float cok3=cok2*cok;
    float cok4=cok2*cok2;
    float sqrt2=sqrt(2);
    float sq_tmp1 = sqrt2 * cowc3 * cok;
    float sq_tmp2 = sqrt2 * cowc * cok3;
    float a_tmp = 4*cowc2*cok2 + 2*sq_tmp1 + cok4 + 2*sq_tmp2+cowc4;

    b1co=(4*(cowc4+sq_tmp1-cok4-sq_tmp2))/a_tmp;


    b2co=(6*cowc4-8*cowc2*cok2+6*cok4)/a_tmp;


    b3co=(4*(cowc4-sq_tmp1+sq_tmp2-cok4))/a_tmp;


    b4co=(cok4-2*sq_tmp1+cowc4-2*sq_tmp2+4*cowc2*cok2)/a_tmp;



    //================================================
    // low-pass
    //================================================
    lpco.a0=cowc4/a_tmp;
    lpco.a1=4*cowc4/a_tmp;
    lpco.a2=6*cowc4/a_tmp;
    lpco.a3=lpco.a1;
    lpco.a4=lpco.a0;

    //=====================================================
    // high-pass
    //=====================================================
    hpco.a0=cok4/a_tmp;
    hpco.a1=-4*cok4/a_tmp;
    hpco.a2=6*cok4/a_tmp;
    hpco.a3=hpco.a1;
    hpco.a4=hpco.a0;


}

void LRCrossoverFilter::processBlock(float * in, float * outHP, float * outLP, int numSamples) {

    float tempx, tempy;
    for (int i = 0; i<numSamples; i++) {
        tempx=in[i];

        // High pass

        tempy = hpco.a0*tempx +
        hpco.a1*hptemp.xm1 +
        hpco.a2*hptemp.xm2 +
        hpco.a3*hptemp.xm3 +
        hpco.a4*hptemp.xm4 -
        b1co*hptemp.ym1 -
        b2co*hptemp.ym2 -
        b3co*hptemp.ym3 -
        b4co*hptemp.ym4;

        hptemp.xm4=hptemp.xm3;
        hptemp.xm3=hptemp.xm2;
        hptemp.xm2=hptemp.xm1;
        hptemp.xm1=tempx;
        hptemp.ym4=hptemp.ym3;
        hptemp.ym3=hptemp.ym2;
        hptemp.ym2=hptemp.ym1;
        hptemp.ym1=tempy;
        outHP[i]=tempy;

        assert(tempy<10000000);

        // Low pass

        tempy = lpco.a0*tempx +
        lpco.a1*lptemp.xm1 +
        lpco.a2*lptemp.xm2 +
        lpco.a3*lptemp.xm3 +
        lpco.a4*lptemp.xm4 -
        b1co*lptemp.ym1 -
        b2co*lptemp.ym2 -
        b3co*lptemp.ym3 -
        b4co*lptemp.ym4;

        lptemp.xm4=lptemp.xm3; // these are the same as hptemp and could be optimised away
        lptemp.xm3=lptemp.xm2;
        lptemp.xm2=lptemp.xm1;
        lptemp.xm1=tempx;
        lptemp.ym4=lptemp.ym3;
        lptemp.ym3=lptemp.ym2;
        lptemp.ym2=lptemp.ym1;
        lptemp.ym1=tempy;
        outLP[i] = tempy;

        assert(!isnan(outLP[i]));
    }
}


int main () {
    LRCrossoverFilter filter;
    float data[2000];
    float lp[2000], hp[2000];

    filter.setup(50.0, 44100.0f);
    filter.dumpInformation();

    for (int i = 0; i<2000; i++) {
        data[i] = sinf(i/100.f);
    }
    filter.processBlock(data, hp, lp, 2000);

}
*/
