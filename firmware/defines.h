#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_int.h"
#include "ap_fixed.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 252
#define N_LAYER_2 15
#define N_LAYER_6 1

#define N_CH_IN 36
#define N_CH_OUT 2

//hls-fpga-machine-learning insert layer-precision
typedef ap_ufixed<10,10> inputs_accum_t;
typedef ap_ufixed<10,10> input_t;
typedef ap_fixed<20,18> dense1_accum_t;
typedef ap_fixed<20,18> layer2_t;
typedef ap_fixed<2,1> weight2_t;
typedef ap_uint<1> bias2_t;
typedef ap_uint<1> layer2_index;
typedef ap_fixed<15,12,AP_RND,AP_SAT,AP_SAT> layer4_t;
typedef ap_fixed<18,3> qbn1_scale_t;
typedef ap_fixed<18,3> qbn1_bias_t;
typedef ap_ufixed<5,2,AP_RND,AP_SAT,AP_SAT> layer5_t;
typedef ap_fixed<18,8> relu1_table_t;
typedef ap_fixed<11,5> output_accum_t;
typedef ap_fixed<11,5> result_t;
typedef ap_fixed<4,1> weight6_t;
typedef ap_uint<1> bias6_t;
typedef ap_uint<1> layer6_index;

#endif
