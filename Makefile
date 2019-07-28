EXENAME = Diffie
OBJS = Diffie.o Main.o Server.o Client.o Chat.o
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

Server.o : Server.cpp Server.h
	$(CXX) $(CXXFLAGS) Server.cpp

Client.o : Client.cpp Client.h
	$(CXX) $(CXXFLAGS) Client.cpp

Chat.o : Chat.cpp Chat.h
	$(CXX) $(CXXFLAGS) Chat.cpp

clean:
	rm *.o diffie
