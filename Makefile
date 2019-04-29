EXENAME = Diffie
OBJS = Diffie.o
CXX = g++
LD = g++


LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic

all: $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

Diffie.o : diffie.cpp diffie.h
	$(CXX) $(CXXFLAGS) diffie.cpp

clean:
	rm *.o diffie
