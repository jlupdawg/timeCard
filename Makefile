main.exe: main.o Display.o Log.o
	g++ main.o Display.o Log.o -o main.exe

main.o: main.cpp Display.h Log.h
	g++ -Wall -c main.cpp

Display.o: Display.cpp Display.h Log.h
	g++ -Wall -c Display.cpp

Log.o: Log.cpp Log.h
	g++ -Wall -c Log.cpp

clean:
	rm *.o main.exe