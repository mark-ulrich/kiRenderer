##
# kiRasterizer
#
# @file
# @version 0.1

CC=g++.exe

INCDIRS =																	\
	-I ./include																\
	-I ./3rd_party/SDL2-2.0.12/x86_64-w64-mingw32/include

LIBDIRS =																	\
	-L ./3rd_party/SDL2-2.0.12/x86_64-w64-mingw32/lib

LIBS = 																		\
	-lmingw32																\
	-lSDL2main																\
	-lSDL2

CFLAGS =	$(INCDIRS)															\
		$(LIBDIRS)   															\
		$(LIBS)   															\
		-Wall																\
		-Wpedantic



OBJECTS =																	\
	kiError.o																\
	kiColor.o																\
	zlib.o																	\
	PNGLib.o																	\
	kiTexture.o																\
	kiRenderer.o																\
	kiDisplay.o																\
	main.o

OUTFILE = build/renderer.exe

release: $(OBJECTS)
	$(CC) -o $(OUTFILE) $(OBJECTS) $(CFLAGS) -O3

debug: $(OBJECTS)
	$(CC) -o $(OUTFILE) $(OBJECTS) $(CFLAGS) -g

%.o: src/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBDIRS) $(LIBS)


clean:
	@echo [*] Cleaning...
	rm -f *.o
	rm build/renderer.exe

# end
