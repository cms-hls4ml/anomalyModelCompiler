#include "firmware/myproject.h" //include of the top level of HLS model
#include "emulator.h" //include of emulator modeling
#include <any>
#include "ap_fixed.h"

class caloADModel : public HLS4MLModel{
    private:
        input_t _input[N_INPUT_1_1];
        result_t _result[N_LAYER_10];
    public:
        virtual void prepare_input(std::any input)
        {
            input_t* input_p = std::any_cast<input_t*>(input);
            for(int i = 0; i < N_INPUT_1_1; ++i)
                _input[i] = std::any_cast<input_t>(input_p[i]);
        }

        virtual void predict()
        {
            myproject(_input, _result);
        }

        virtual void read_result(std::any result)
        {
            result_t *result_p = std::any_cast<result_t*>(result);
            for (int i = 0; i < N_LAYER_10; ++i)
                result_p[i] = _result[i];
        }

};

extern "C" HLS4MLModel* create_model()
{
    return new caloADModel;
}

extern "C" void destroy_model(HLS4MLModel* m)
{
    delete m;
}