all: image_viewer

image_viewer: iv.c
	$(CC) iv.c -Wall -W -O2 -o image_viewer `pkg-config --cflags --libs sdl3`

clean:
	rm -rf image_viewer  


