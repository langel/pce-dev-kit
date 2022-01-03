
#include <math.h>

typedef struct {
	double sample_rate;
	double frequency;
	double sqrt;
	double tan;
	double scale;
	double b1, b2, b3, b4;
} lowpass_scheme;

lowpass_scheme lowpass_setup(double sample_rate, double frequency) {
	lowpass_scheme scheme;
	scheme.sample_rate = sample_rate;
	scheme.frequency = frequency;
	scheme.sqrt = sqrt(2.0);
	scheme.tan = tan(3.14159 * frequency / sample_rate);
	scheme.scale = (1.0 / (1.0 + scheme.sqrt * scheme.tan + scheme.tan * scheme.tan));
	scheme.b1 = scheme.b2 = scheme.b3 = scheme.b4 = 0.0;
	return scheme;
}

double lowpass_process(lowpass_scheme * scheme, double sample) {
	double hi1 = (sample - (scheme->sqrt + scheme->tan) * scheme->b1 - scheme->b2) * scheme->scale;
	double band1 = scheme->tan * hi1 + scheme->b1;
	scheme->b1 = scheme->tan * hi1 + band1;
	double lo1 = scheme->tan * band1 + scheme->b2;
	scheme->b2 = scheme->tan * band1 + lo1;
	double hi2 = (lo1 - (scheme->sqrt + scheme->tan) * scheme->b3 - scheme->b4) * scheme->scale;
	double band2 = scheme->tan * hi2 + scheme->b3;
	scheme->b3 = scheme->tan * hi2 + band2;
	double lo2 = scheme->tan * band2 + scheme->b4;
	scheme->b4 = scheme->tan * band2 + lo2;
	return lo2;
}
