CC = gcc
CGLAGS = -g -ffast-math -O2 -Wall

default: clean cam obj_rm

cam: camera.o cam_input.o
	$(CC) $(CFLAGS) camera.o cam_input.o $(LIBS) -o cam

camera.o: camera.c camera.h cam_input.h sdl_output.h
	$(CC) $(CFLAGS) -c camera.c

cam_input.o: cam_input.c cam_input.h
	$(CC) $(CFLAGS) -c cam_input.c

sdl_output.o: sdl_output.c sdl_output.h cam_input.h
	$(CC) $(CFLAGS) -c sdl_output.c

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
