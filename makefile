all:
	g++ -std=c++11 src/*.cpp src/log/*.cpp src/model/*.cpp -o main
clean:
	rm -f main*