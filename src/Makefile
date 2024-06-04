CC      = gcc
CFLAGS  = -Wall -Wpedantic
LDFLAGS = -lSDL2
OBJFILES = main.o
TARGET = objectsRotator

default: all

all: $(TARGET)

run: $(TARGET)
	./$<

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)