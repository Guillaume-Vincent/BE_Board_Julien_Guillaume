FLAGS=-Wall -std=c++11 -pthread

all: arduino

arduino: board.o core_simulation.o mydevices.o sketch_ino.o
	g++ $(FLAGS) -o arduino board.o core_simulation.o mydevices.o sketch_ino.o
	

board.o: board.cpp
	g++ $(FLAGS) -c board.cpp

core_simulation.o: core_simulation.cpp
	g++ $(FLAGS) -c core_simulation.cpp
	
mydevices.o: mydevices.cpp
	g++ $(FLAGS) -c mydevices.cpp
	
sketch_ino.o: sketch_ino.cpp
	g++ $(FLAGS) -c sketch_ino.cpp
	

clean:
	@rm -rf *.o