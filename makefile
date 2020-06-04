CC = g++
OBJS = main.o struct.o snakeGame.o

game: ${OBJS}
	${CC} -o $@ ${OBJS} -lncurses

clean:
	rm -f *.o

%.o: %.cpp %.h
	${CC} -c $<

%.o: %.cpp
	${CC} -c $<
