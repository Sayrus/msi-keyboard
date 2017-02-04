CC=g++
CFLAGS=-c -Wall `pkg-config hidapi-libusb --cflags`
LDFLAGS=
LDLIBS=`pkg-config hidapi-libusb --libs`
SOURCES=main.cpp keyboard.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=msi-keyboard

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(LDLIBS)  $< -o $@
clean:
	rm -f $(EXECUTABLE) *.o .*.*~ *.*~ .*.swp
