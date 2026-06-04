EXEC = bots
CC = g++

$(EXEC): bots.cpp
	$(CC) -o $(EXEC) bots.cpp -pthread

clean:
	rm -f *.o core a.out $(EXEC) QUOTE.txt
