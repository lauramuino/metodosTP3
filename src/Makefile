#Bienvenidos al super makefile de laura!!! con asistencia de SO

#%: Es un comodin.
#$@: El target
#$<: La primer dependencia.
#$^: Todas las dependencias.
CC=g++ -std=c++11
CFLAGS=-c
SOURCES=mat.cpp aux.cpp video.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tp

.PHONY: all clean

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) `pkg-config --cflags opencv` $(OBJECTS) `pkg-config --libs opencv` -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f $(EXECUTABLE)