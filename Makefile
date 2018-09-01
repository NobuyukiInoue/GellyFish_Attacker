CC = gcc
OBJS = .
LIBS =
LDFLAGS = -lncurses -lm

TARGET = JellyFish_Attacker

all:	$(TARGET)

JellyFish_Attacker: JellyFish_Attacker.c
	$(CC) -o JellyFish_Attacker JellyFish_Attacker.c $(LDFLAGS)
	chmod a+x JellyFish_Attacker

clean:;	rm -f $(TARGET)

.PHONY: all clean
