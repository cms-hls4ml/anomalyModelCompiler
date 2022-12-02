
.PHONY: library

library: emulator.h caloADModel.cpp
	$(CXX) -O3 -fPIC -std=c++17 -Iap_types -Ifirmware -c firmware/myproject.cpp -o myproject.o
	$(CXX) -O3 -fPIC -std=c++17 -Iap_types -Ifirmware -c caloADModel.cpp -o caloADModel.o
	$(CXX) -O3 -fPIC -std=c++17 -Iap_types -Ifirmware -shared myproject.o caloADModel.o -o compiledModel.so
	rm myproject.o
	rm caloADModel.o