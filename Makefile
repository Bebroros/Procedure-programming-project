CC = gcc
CFLAGS = -Ilib/include -Wall
LDFLAGS = -lX11 -lpng

SRCS = app/main.c lib/src/make_screenshot.c lib/src/png_encode.c

TARGET = app/screenshot_app

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
