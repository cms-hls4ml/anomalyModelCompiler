#ifndef DEFINES_H_
#define DEFINES_H_

#include "ap_int.h"
#include "ap_fixed.h"
#include "nnet_utils/nnet_types.h"
#include <cstddef>
#include <cstdio>

//hls-fpga-machine-learning insert numbers
#define N_INPUT_1_1 252
#define N_SIZE_1_2 18
#define N_SIZE_2_2 14
#define N_SIZE_3_2 1
#define OUT_HEIGHT_3 8
#define OUT_WIDTH_3 6
#define N_FILT_3 3
#define N_SIZE_1_6 144
#define N_LAYER_7 20
#define N_LAYER_10 1

//hls-fpga-machine-learning insert layer-precision
typedef ap_ufixed<10,10> in_accum_t;
typedef ap_ufixed<10,10> input_t;
typedef ap_fixed<36,16> model_default_t;
typedef ap_fixed<22,18> conv_accum_t;
typedef ap_fixed<22,18> layer3_t;
typedef ap_fixed<16,5> weight3_t;
typedef ap_uint<1> bias3_t;
typedef ap_fixed<20,10> conv_alpha_accum_t;
typedef ap_fixed<20,10> layer12_t;
typedef ap_fixed<20,0> conv_alpha_scale_t;
typedef ap_int<1> conv_alpha_bias_t;
typedef ap_ufixed<16,4,AP_RND,AP_SAT,AP_SAT> layer5_t;
typedef ap_fixed<18,8> relu1_table_t;
typedef ap_fixed<22,14> dense1_accum_t;
typedef ap_fixed<22,14> layer7_t;
typedef ap_fixed<16,5> weight7_t;
typedef ap_uint<1> bias7_t;
typedef ap_uint<1> layer7_index;
typedef ap_fixed<20,8> dense1_alpha_accum_t;
typedef ap_fixed<20,8> layer13_t;
typedef ap_fixed<20,0> dense1_alpha_scale_t;
typedef ap_int<1> dense1_alpha_bias_t;
typedef ap_ufixed<16,4,AP_RND,AP_SAT,AP_SAT> layer9_t;
typedef ap_fixed<18,8> relu2_table_t;
typedef ap_fixed<20,10> output_accum_t;
typedef ap_fixed<20,10> layer10_t;
typedef ap_fixed<16,3> weight10_t;
typedef ap_uint<1> bias10_t;
typedef ap_uint<1> layer10_index;
typedef ap_fixed<12,10> output_alpha_accum_t;
typedef ap_fixed<12,10> result_t;
typedef ap_fixed<20,0> output_alpha_scale_t;
typedef ap_int<1> output_alpha_bias_t;

#endif
