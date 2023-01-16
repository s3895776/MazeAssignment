.default: all

all: main

main: Node.o NodeList.o PathPlanner.o Env.o main.o
	g++ -Wall -Werror -std=c++14 -O -fsanitize=address -g -o $@ $^
	
%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -fsanitize=address -g -c $^


clean:
	rm -f main *.o