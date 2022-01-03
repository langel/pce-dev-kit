
#include <math.h>

typedef struct {
	double alpha;
	double b1, b2, b3, b4;
} lowpass_scheme;

lowpass_scheme lowpass_setup(double sample_rate, double frequency) {
	lowpass_scheme scheme;
	// angular frequency?
	double rc = 1.0 / (3.14159 * 2 * frequency);
	// time length of sample
	double dt = 1.0 / sample_rate;
	scheme.alpha = dt / (rc+dt);
	scheme.b1 = scheme.b2 = scheme.b3 = scheme.b4 = 0.0;
	return scheme;
}

double lowpass_process(lowpass_scheme * scheme, double sample) {
	scheme->b1 = sample;
	scheme->b2 = scheme->b1 + (scheme->alpha * (scheme->b2 - scheme->b1));
	return scheme->b2;
	scheme->b3 = scheme->b2 + (scheme->alpha * (scheme->b3 - scheme->b2));
	scheme->b4 = scheme->b3 + (scheme->alpha * (scheme->b4 - scheme->b3));
	return scheme->b4;
}
