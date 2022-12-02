#ifndef ALGO_UNPACKED_H
#define ALGO_UNPACKED_H

#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_stream.h"
#include "defines.h"

void algo_unpacked(ap_uint<128> link_in[N_CH_IN], ap_uint<128> link_out[N_CH_OUT]);

#endif
