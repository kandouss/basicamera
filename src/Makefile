CC = gcc
CGLAGS = -g -O2 -Wall -std=c99

default: clean cam obj_rm

cam: camera.o cam_input.o sdl_output.o image_proc.o
	$(CC) camera.o cam_input.o sdl_output.o image_proc.o -o cam -lSDL

camera.o: camera.c config.h cam_input.h sdl_output.h image_proc.h
	$(CC) $(CFLAGS) -c camera.c

cam_input.o: cam_input.c config.h cam_input.h image_proc.h
	$(CC) $(CFLAGS) -c cam_input.c

sdl_output.o: sdl_output.c config.h sdl_output.h image_proc.h
	$(CC) -I/usr/include/SDL $(CFLAGS) -c sdl_output.c

image_proc.o: image_proc.c config.h image_proc.h
	$(CC) $(CFLAGS) -c image_proc.c


# Template for adding dependency "dep.c"
#
#dep.o:  dep.cpp dep.hpp
#	$(CC) $(CFLAGS) -c dep.cpp
#
#% : %.cpp
#        g++ $(CFLAGS) $(LIBS) -o $@ $<

clean: 
	$(RM) cam *.o 

obj_rm: 
	$(RM) *.o
