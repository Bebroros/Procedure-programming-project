CC = gcc
LDFLAGS = -lX11 -lpng

OBJS = src/make_screenshot.o src/png_encode.o

TARGET = libscreenshot.so

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(OBJS) -o $(TARGET) -shared $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)
