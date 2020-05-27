CC = g++
OBJS = main.o snake.o snakeGame.o

game: ${OBJS}
	${CC} -o $@ ${OBJS} -lncurses

clean:
	rm -f *.o

%.o: %.cpp %.h
	${CC} -c $<

%.o: %.cpp
	${CC} -c $<
