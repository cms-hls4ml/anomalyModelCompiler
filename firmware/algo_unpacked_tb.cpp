#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "algo_unpacked.h"

using namespace std;

ap_uint<128> link_in[N_CH_IN];
ap_uint<128> link_out[N_CH_OUT];

int main(int argc, char ** argv) {

    string test_vector;
    test_vector = argv[1];

    string ifname(test_vector + "_inp.txt"); // input test vector
    string ofname(test_vector + "_out.txt"); // output test vector
    string orfname(test_vector + "_out_ref.txt"); // reference output vector

    // Open input stream...
    ifstream ifs(ifname.c_str());
    if (!ifs.is_open()) {
        cerr << "Error opening input file: " << ifname << endl;
        exit(1);
    }

    //...and position at the beginning of input test data
    string line;
    while (true) {
        ifs >> line;
        if (line.compare("#BeginData") == 0)
            break;
    }

    // Open output stream and write a header
    ofstream ofs(ofname.c_str());
    if (!ofs.is_open()) {
        cerr << "Error opening output file: " << ofname << endl;
        exit(1);
    }

    // Open output reference stream...
    ifstream orfs(orfname.c_str());
    if (!orfs.is_open()) {
        cerr << "Error opening output reference file: " << orfname << endl;
        exit(1);
    }

    uint32_t wordCnt = 0;

    ofs << "=============================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================" << endl;
    ofs << "WordCnt             LINK_00               LINK_01" << endl;
    ofs << "#BeginData" << endl;

    while (!ifs.eof()) {
        for (int cyc = 0; cyc < 4; cyc++) {
            ifs >> hex >> wordCnt;
            if  (ifs.eof())
                break;

            for (int link = 0; link < N_CH_IN; link++)
            {
                ap_uint<32> tmp;
                if (cyc == 0) {
                    ifs >> hex >> tmp;
                    link_in[link].range(31, 0) = tmp;
                }
                else if (cyc == 1) {
                    ifs >> hex >> tmp;
                    link_in[link].range(63, 32) = tmp;
                }
                else if (cyc == 2) {
                    ifs >> hex >> tmp;
                    link_in[link].range(95, 64) = tmp;
                }
                else {
                    ifs >> hex >> tmp;
                    link_in[link].range(127, 96) = tmp;
                }
                if  (ifs.eof())
                    break;
            }
        }

        if  (ifs.eof())
            break;

        algo_unpacked(link_in, link_out);

        wordCnt-=3;
        for (int cyc = 0; cyc < 4; cyc++) {
            ofs << "0x" << setfill('0') << setw(4) << hex << wordCnt++ << "   ";
            for (int link = 0; link < N_CH_OUT; link++) {
                if (cyc == 0) {
                    ofs << "0x" << setw(8) << hex << link_out[link].range(31,0).to_int() << "    ";
                }
                else if (cyc == 1) {
                    ofs << "0x" << setw(8) << hex << link_out[link].range(63,32).to_int() << "    ";
                }
                else if (cyc == 2) {
                    ofs << "0x" << setw(8) << hex << link_out[link].range(95,64).to_int() << "    ";
                }
                else {
                    ofs << "0x" << setw(8) << hex << link_out[link].range(127,96).to_int() << "    ";
                }

            }
            ofs<< std::endl;
        }
    }

    string output_diff("diff -w " + ofname + " " + orfname);

    cerr << "All Good!" << endl;
    if (system(output_diff.c_str())) {
        cout << "*** Output data verification. FAILED! ***" << endl;
        return 0;
    } else {
        cout << "*** Output data verification. PASSED ***" << endl;
        return 0;
    }
}
