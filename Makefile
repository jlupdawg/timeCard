main.exe: main.o Display.o
	g++ main.o Display.o -o main.exe

main.o: main.cpp Display.h
	g++ -Wall -c main.cpp

Display.o: Display.cpp Display.h
	g++ -Wall -c Display.cpp

clean:
	rm *.o main.exe