#ifndef GOERTZEL_FILTER_H
#define GOERTZEL_FILTER_H

#include <math.h>

// Function declaration for the single-bin DTFT
float run_goertzel(float *x, int N, float f_target, float fs, float *phase_out);

#endif