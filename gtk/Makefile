CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -I/usr/include/libayatana-appindicator-glib
LDFLAGS =`pkg-config --libs gtk+-3.0`  -L/usr/lib -layatana-appindicator-glib -lgio-2.0 -lgobject-2.0 -lglib-2.0

TARGET = main
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

test:
	./$(TARGET)