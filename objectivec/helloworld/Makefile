CXX=cc
CxxFLAGS=-framework Foundation

target: objectivec
objectivec: helloworld.o 
	$(CXX) $(CxxFLAGS) -o $@ $?

helloworld.o: helloworld.m

.PHONY: clean
clean:
	rm *.o
	rm objectivec
