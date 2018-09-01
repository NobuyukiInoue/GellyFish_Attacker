CC = gcc
OBJS = .
LIBS =
LDFLAGS = -lncurses -lm

TARGET = JellyFish_Attacker sample1

all:	$(TARGET)

sample1: sample1.c
	$(CC) -o sample1 sample1.c $(LDFLAGS)
	chmod a+x sample1

JellyFish_Attacker: JellyFish_Attacker.c
	$(CC) -o JellyFish_Attacker JellyFish_Attacker.c $(LDFLAGS)
	chmod a+x JellyFish_Attacker


clean:;	rm -f $(TARGET)

.PHONY: all clean
