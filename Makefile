CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

.PHONY: all test clean

all:
	$(CXX) $(CXXFLAGS) src/main.cpp -o main
	./main > image.ppm
	open image.ppm

test:
	g++ -std=c++17 test/unit-test/vec3_ut.cpp -o vec3_ut
	./vec3_ut

clean:
	rm -f main vec3_test image.ppm
