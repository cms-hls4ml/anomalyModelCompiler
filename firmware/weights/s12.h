//Numpy array shape [1, 1, 1, 3]
//Min 0.002359049395
//Max 0.002915417077
//Number of zeros 0

#ifndef S12_H_
#define S12_H_

#ifdef LOAD_WEIGHTS_FROM_TXT
conv_alpha_scale_t s12[3];
#else
conv_alpha_scale_t s12[3] = {0.00235904939472675, 0.00266005308367312, 0.00291541707701981};
#endif

#endif
