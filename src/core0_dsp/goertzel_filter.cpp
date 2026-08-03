#include "goertzel_filter.h"

// Single-bin DTFT magnitude and phase extraction
float run_goertzel(float *x, int N, float f_target, float fs, float *phase_out) {
    int k = (int)(0.5f + (N * f_target) / fs);
    float omega = 2.0f * M_PI * k / N;
    float coeff = 2.0f * cosf(omega);
    float s0, s1 = 0, s2 = 0;
    
    for (int n = 0; n < N; n++) {
        s0 = x[n] + coeff * s1 - s2;
        s2 = s1; 
        s1 = s0;
    }
    
    float real = s1 - s2 * cosf(omega);
    float imag = s2 * sinf(omega);
    
    *phase_out = atan2f(imag, real);
    
    // Return magnitude
    return sqrtf(real * real + imag * imag) / (N / 2.0f);
}