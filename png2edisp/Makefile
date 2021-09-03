
.PHONY: pallette.gif

all: image.h 

pallette.gif: 
	magick xc:red xc:white xc:black +append palette.gif	

_transformed_image.png: pallette.gif screen.png
	#magick  screen.png -remap palette.gif _transformed_image.png
	cp screen.png _transformed_image.png

image.png: _transformed_image.png
	convert _transformed_image.png -resize 800x480 image.png

image.h: genHeader pixels.raw
	./genHeader > image.h
	cp image.h ../device/StaticDoorSign/

genHeader: genHeader.cpp
	g++ genHeader.cpp -o genHeader
	
pixels.raw: image.png 
	python3 rawPixels.py > pixels.raw 

clean:
	rm -rf pallette.gif
	rm -rf _transformed_image.png
	rm -rf image.png
	rm -rf pixels.raw
	rm -rf image.h
	rm -rf genHeader
