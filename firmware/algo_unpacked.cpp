#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <hls_math.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "myproject.h"
#include "algo_unpacked.h"

//using namespace std;

const uint16_t NRegionsPerLink = 7; // Bits 8-21, 22-39, 40-55,..., 104-119, keeping ranges (7, 0) and (127, 120) unused
const uint16_t MaxRegions = N_CH_IN * NRegionsPerLink;

void algo_unpacked(ap_uint<128> link_in[N_CH_IN], ap_uint<128> link_out[N_CH_OUT]) {

// !!! Retain these 4 #pragma directives below in your algo_unpacked implementation !!!
#pragma HLS ARRAY_PARTITION variable=link_in complete dim=0
#pragma HLS ARRAY_PARTITION variable=link_out complete dim=0
#pragma HLS PIPELINE II=4
#pragma HLS INTERFACE ap_ctrl_hs port=return
#pragma HLS latency min=4

//     for (int lnk = 0; lnk < N_CH_OUT ; lnk++) {
// #pragma HLS UNROLL
//     //pass-through "algo"
//         link_out[lnk].range(7,0) = 0;            // reserved for 8b10b control word
//         link_out[lnk].range(127,120) = 0;        // reserved for CRC word
//         link_out[lnk].range(119, 8) = link_in[lnk].range(119, 8);   // input to output pass-through
//     }

    static bool first = true; //true to print
    input_t et_calo[N_INPUT_1_1];
#pragma HLS ARRAY_RESHAPE variable=et_calo complete dim=0
    regionLoop: for(int iRegion = 0; iRegion < 252; iRegion++) {
#pragma HLS UNROLL
        if(iRegion > MaxRegions) {
            fprintf(stderr, "Too many regions - aborting");
            exit(1);
        }
        int link_idx = iRegion / NRegionsPerLink;
        int bitLo = ((iRegion - link_idx * NRegionsPerLink) % NRegionsPerLink) * 16 + 8;
        int bitHi = bitLo + 15;
        uint16_t region_raw = link_in[link_idx].range(bitHi, bitLo);
        et_calo[iRegion] = (region_raw & 0x3FF >> 0); // 10 bits
        //cout << "Calo region " << " ET: " << et_calo[iRegion] << endl;
    }
    //cout << "Got all regions" << endl;

    result_t layer6_out[N_LAYER_6];

#pragma HLS ARRAY_PARTITION variable=layer6_out complete dim=0

    myproject(et_calo, layer6_out);
    //cout << "Neural network output: " << " " << layer6_out[0] << endl;

    for (int i = 0; i < N_CH_OUT; i++){
#pragma HLS UNROLL
       link_out[i] = 0;
    }

    for(int i = 0; i < N_CH_OUT; i++){
#pragma HLS unroll
       link_out[i].range(119, 8) = layer6_out[0].range() & (2047);
    }
}
