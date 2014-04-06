CXX=cc
CxxFLAGS=-framework Foundation

target: config
config: HLConfig.o HLConfig_test.o 
	$(CXX) $(CxxFLAGS) -o $@ $?

HLConfig.o: HLConfig.m HLConfig.h
HLConfig_test.o: HLConfig_test.m HLConfig.h

.PHONY: clean
clean:
	rm *.o
	rm config
