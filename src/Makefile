CC      = gcc
CFLAGS  = -Wall
LDFLAGS = -lSDL2
OBJFILES = main.o
TARGET = objectsRotator

default: all

all: $(TARGET)

run:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) && ./$(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)