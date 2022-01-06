# Makefile feito a partir do arquivo que o professor disponibilizou no document do trabalho.


# o compilador. aqui eu troquei de gcc para c++ pois vou fazer o trabalho em c++
CC = g++

# flags do compilador:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

# o executável:
TARGET = principal

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
