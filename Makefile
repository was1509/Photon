CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all:
	$(CXX) $(CXXFLAGS) src/main.cpp -o main
	./main > image.ppm
	open image.ppm

clean:
	rm -f main image.ppm
	