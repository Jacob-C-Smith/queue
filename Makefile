INCLUDES=-I./include -I/usr/local/include
CC=gcc
CFLAGS= -g -w
OBJECT_DIR=./object
AS=nasm
CPPARGS=
SRCS:=$(wildcard *.c)
OBJS=$(SRCS:.c=.o) 
TARGET=queue
SLIBTARGET=lib$(TARGET).a
SOTARGET=lib$(TARGET).so

.PHONY: depend clean

all: $(TARGET) libs

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) 

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(CPPARGS) -c $< -o $@

clean:
	rm *.o $(TARGET) *.a *.so || true

run: $(TARGET)
	./$(TARGET)

libs: $(OBJS)
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $(OBJS)
	ar -rc $(SLIBTARGET) $(TARGET).o || true
	$(CC) $(CFLAGS) -fPIC $(INCLUDES) -o $(SLIBTARGET) $(OBJS)
	$(CC) -shared -o $(SOTARGET) $(OBJS)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

