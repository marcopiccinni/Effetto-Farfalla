# Per compilazione su distribuzioni linux (escluso Ubuntu 17.04)

OBJ = main.o inits.o game_functions.o interface.o IOfile.o secure.o
LIBALLEGRO = allegro-5.0 allegro_dialog-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0
LDLIBS=`pkg-config --libs glib-2.0 $(LIBALLEGRO)` -lm
CXXFLAGS=-Wall -std=c++11 `pkg-config --cflags glib-2.0 $(LIBALLEGRO)` 

VPATH=../src/header:../src/code

Butterfly: $(OBJ)
	g++  -o ../bin/Butterfly $(OBJ) $(LDLIBS)
 	
-include dependencies

.PHONY: depend debug clean cleanall install_dev
depend: 
	g++ -std=c++11 -MM ../src/code/*.cc > dependencies

debug: CXXFLAGS+=-D DEBUG_MODE
debug: clean Butterfly

clean:
	rm -f *.o
cleanall:
	rm -f ../bin/Butterfly *.o *~
	rm -rf ../doc/html
	rm -f ../bin/*.sav

install_dev:
	sudo apt-get install g++ libglib2.0-dev -y
	sudo apt-get install --install-suggests --install-recommends liballegro5-dev -y
