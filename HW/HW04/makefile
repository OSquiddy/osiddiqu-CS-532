CC = gcc
CFLAGS = -Wall -lpthread
SRC = osiddiqu_HW04.c makefile
OBJ = osiddiqu_HW04.o
EXECS = hw4

all: $(EXECS)

$(EXECS): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $<

clean: 
	rm *.o output.txt $(EXECS)
