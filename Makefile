EXENAME = Diffie
OBJS = Diffie.o Main.o
CXX = g++
LD = g++


LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic

all: $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

Diffie.o : Diffie.cpp Diffie.h
	$(CXX) $(CXXFLAGS) Diffie.cpp

Main.o : Main.cpp
	$(CXX) $(CXXFLAGS) Main.cpp

clean:
	rm *.o diffie
