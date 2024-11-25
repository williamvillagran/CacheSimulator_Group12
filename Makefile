CC = gcc
CFLAGS = -o

TARGET = CacheSim_v1.12.exe

all: $(TARGET)

$(TARGET): main.c
	$(CC) main.c $(CFLAGS) $(TARGET)

clean:
	rm -f $(TARGET) *.exe