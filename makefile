CC = g++
OBJS = main.o struct.o snakeGame.o

game: ${OBJS}
	${CC} -o $@ ${OBJS} -lncursesw

clean:
	rm -f *.o

%.o: %.cpp %.h
	${CC} -std=c++14 -c $<

%.o: %.cpp
	${CC} -std=c++14 -c $<
