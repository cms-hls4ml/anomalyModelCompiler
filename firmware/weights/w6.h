//Numpy array shape [15, 1]
//Min -0.125000000000
//Max 0.375000000000
//Number of zeros 2

#ifndef W6_H_
#define W6_H_

#ifdef LOAD_WEIGHTS_FROM_TXT
weight6_t w6[15];
#else
weight6_t w6[15] = {-0.125, 0.000, 0.250, 0.250, 0.250, -0.125, 0.250, 0.250, 0.125, 0.375, 0.000, -0.125, 0.375, 0.250, 0.125};
#endif

#endif
