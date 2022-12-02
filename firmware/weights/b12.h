//Numpy array shape [3]
//Min 0.000000000000
//Max 0.000000000000
//Number of zeros 3

#ifndef B12_H_
#define B12_H_

#ifdef LOAD_WEIGHTS_FROM_TXT
conv_alpha_bias_t b12[3];
#else
conv_alpha_bias_t b12[3] = {0, 0, 0};
#endif

#endif
