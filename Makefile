CXX = clang++
CXXFLAGS = -Wall -O3 -std=c++11 -stdlib=libc++

EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): mmkp.o enumerate.o main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o $(EXECUTABLE)
