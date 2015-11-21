HEADERS = cs2123p5.h
OBJECTS = cs2123p5Driver.o cs2123p5DM.o cs2123p5JM.o cs2123p5QQ.o cs2123p5GG.o 

%.o: %.c ${HEADERS}
	gcc -g -c $<
p5: ${OBJECTS}
	gcc -g -o p5 ${OBJECTS}
clean:
	-rm -f ${OBJECTS}
