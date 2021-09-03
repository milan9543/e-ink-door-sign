
.PHONY: pallette.gif

all: image_b.h image_r.h 

pallette.gif: 
	magick xc:red xc:white xc:black +append palette.gif	

_transformed_image_b.png: pallette.gif screen_b.png
	#magick  screen.png -remap palette.gif _transformed_image.png
	cp screen_b.png _transformed_image_b.png

_transformed_image_r.png: pallette.gif screen_r.png
	#magick  screen.png -remap palette.gif _transformed_image.png
	cp screen_r.png _transformed_image_r.png

image_b.png: _transformed_image_b.png
	convert _transformed_image_b.png -resize 800x480 image_b.png

image_r.png: _transformed_image_r.png
	convert _transformed_image_r.png -resize 800x480 image_r.png

image_b.h: genHeader pixels_b.raw
	./genHeader pixels_b.raw screen_data_b > image_b.h
	cp image_b.h ../device/StaticDoorSign/

image_r.h: genHeader pixels_r.raw
	./genHeader pixels_r.raw screen_data_r > image_r.h
	cp image_r.h ../device/StaticDoorSign/

genHeader: genHeader.cpp
	g++ genHeader.cpp -o genHeader
	
pixels_b.raw: image_b.png 
	python3 rawPixels.py -i image_b.png > pixels_b.raw 

pixels_r.raw: image_r.png 
	python3 rawPixels.py -i image_r.png > pixels_r.raw 

clean:
	rm -rf pallette.gif
	rm -rf _transformed_image_b.png
	rm -rf image_b.png
	rm -rf pixels_b.raw
	rm -rf image_b.h
	rm -rf _transformed_image_r.png
	rm -rf image_r.png
	rm -rf pixels_r.raw
	rm -rf image_r.h
	rm -rf genHeader
