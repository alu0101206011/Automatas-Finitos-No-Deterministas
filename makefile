CC = g++
CFLAGS = -g -Wall --std=c++17
OBJ = ./main_nfa.o ./nfa.o ./transition.o ./state.o
EXEC = nfa_simulation

all: $(OBJ)
	$(CC) $(CFLAGS) -o ./$(EXEC) $^

./%.o: ./%.cpp 
	$(CC) -c -o $@ $<

run: clean all
	./$(EXEC)

.PHONY: clean

clean:
	bash -O extglob -c "rm -vf !(*.cc|*.h|"makefile"|input.txt|README.md|*.nfa)"
