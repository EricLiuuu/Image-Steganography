all: proj3.exe

ColorClass.o: constant.h ColorClass.h ColorClass.cpp
	g++ -std=c++98 -g -Wall -c ColorClass.cpp -o ColorClass.o

MsgClass.o: constant.h MsgClass.h MsgClass.cpp
	g++ -std=c++98 -g -Wall -c MsgClass.cpp -o MsgClass.o

ColorImageClass.o: constant.h ColorImageClass.h ColorImageClass.cpp
	g++ -std=c++98 -g -Wall -c ColorImageClass.cpp -o ColorImageClass.o

project3.o: constant.h ColorClass.h MsgClass.h ColorImageClass.h project3.cpp
	g++ -std=c++98 -g -Wall -c project3.cpp -o project3.o

proj3.exe: ColorClass.o MsgClass.o ColorImageClass.o project3.o
	g++ ColorClass.o MsgClass.o ColorImageClass.o project3.o -o proj3.exe

clean:
	rm -f ColorClass.o MsgClass.o ColorImageClass.o project3.o proj3.exe
