main: 
	g++ -std=c++17 src/*.cpp -o bin/main.o

clean: 
	rm -rf bin/*.o