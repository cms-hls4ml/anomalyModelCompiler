//
//    rfnoc-hls-neuralnet: Vivado HLS code for neural-net building blocks
//
//    Copyright (C) 2017 EJ Kreinar
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <iostream>

#include "myproject.h"
#include "parameters.h"

void myproject(
    input_t In[N_INPUT_1_1],
    result_t layer14_out[N_LAYER_10]
) {

    //hls-fpga-machine-learning insert IO
    #pragma HLS ARRAY_RESHAPE variable=In complete dim=0
    #pragma HLS ARRAY_PARTITION variable=layer14_out complete dim=0
    #pragma HLS INTERFACE ap_vld port=In,layer14_out 
    #pragma HLS DATAFLOW 

#ifdef LOAD_WEIGHTS_FROM_TXT
    static bool loaded_weights = false;
    if (!loaded_weights) {
        //hls-fpga-machine-learning insert load weights
        nnet::load_weights_from_txt<weight3_t, 27>(w3, "w3.txt");
        nnet::load_weights_from_txt<bias3_t, 3>(b3, "b3.txt");
        nnet::load_weights_from_txt<conv_alpha_scale_t, 3>(s12, "s12.txt");
        nnet::load_weights_from_txt<conv_alpha_bias_t, 3>(b12, "b12.txt");
        nnet::load_weights_from_txt<weight7_t, 2880>(w7, "w7.txt");
        nnet::load_weights_from_txt<bias7_t, 20>(b7, "b7.txt");
        nnet::load_weights_from_txt<dense1_alpha_scale_t, 20>(s13, "s13.txt");
        nnet::load_weights_from_txt<dense1_alpha_bias_t, 20>(b13, "b13.txt");
        nnet::load_weights_from_txt<weight10_t, 20>(w10, "w10.txt");
        nnet::load_weights_from_txt<bias10_t, 1>(b10, "b10.txt");
        nnet::load_weights_from_txt<output_alpha_scale_t, 1>(s14, "s14.txt");
        nnet::load_weights_from_txt<output_alpha_bias_t, 1>(b14, "b14.txt");
        loaded_weights = true;
    }
#endif

    // ****************************************
    // NETWORK INSTANTIATION
    // ****************************************

    //hls-fpga-machine-learning insert layers

    layer3_t layer3_out[OUT_HEIGHT_3*OUT_WIDTH_3*N_FILT_3];
    #pragma HLS ARRAY_PARTITION variable=layer3_out complete dim=0
    nnet::conv_2d_cl<input_t, layer3_t, config3>(In, layer3_out, w3, b3); // conv

    layer12_t layer12_out[OUT_HEIGHT_3*OUT_WIDTH_3*N_FILT_3];
    #pragma HLS ARRAY_PARTITION variable=layer12_out complete dim=0
    nnet::normalize<layer3_t, layer12_t, config12>(layer3_out, layer12_out, s12, b12); // conv_alpha

    layer5_t layer5_out[OUT_HEIGHT_3*OUT_WIDTH_3*N_FILT_3];
    #pragma HLS ARRAY_PARTITION variable=layer5_out complete dim=0
    nnet::relu<layer12_t, layer5_t, relu_config5>(layer12_out, layer5_out); // relu1

    layer7_t layer7_out[N_LAYER_7];
    #pragma HLS ARRAY_PARTITION variable=layer7_out complete dim=0
    nnet::dense<layer5_t, layer7_t, config7>(layer5_out, layer7_out, w7, b7); // dense1

    layer13_t layer13_out[N_LAYER_7];
    #pragma HLS ARRAY_PARTITION variable=layer13_out complete dim=0
    nnet::normalize<layer7_t, layer13_t, config13>(layer7_out, layer13_out, s13, b13); // dense1_alpha

    layer9_t layer9_out[N_LAYER_7];
    #pragma HLS ARRAY_PARTITION variable=layer9_out complete dim=0
    nnet::relu<layer13_t, layer9_t, relu_config9>(layer13_out, layer9_out); // relu2

    layer10_t layer10_out[N_LAYER_10];
    #pragma HLS ARRAY_PARTITION variable=layer10_out complete dim=0
    nnet::dense<layer9_t, layer10_t, config10>(layer9_out, layer10_out, w10, b10); // output

    nnet::normalize<layer10_t, result_t, config14>(layer10_out, layer14_out, s14, b14); // output_alpha

}
