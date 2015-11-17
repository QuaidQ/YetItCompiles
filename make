cs2123p5Driver.o:
        gcc -g -o cs2123p5Driver.o cs2123p5Driver.c
cs2123p5.o:
        gcc -g -o cs2123p5.o cs2123p5.c
p5: cs2123p5.o cs2123p5Driver.o 
        gcc -g -o p5 cs2123p5Driver.o cs2123p5.o 
clean:
    rm -rf *.o
    rm -rf p5
