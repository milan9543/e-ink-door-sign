#!/bin/bash
# used to prep the png image of the screen for transfer from the server to the device
# author: stf

mkdir -p _tmp

# Clear the image
cp blank.png screen_b.png

./tidetimes.sh # Append the tide information to the display

#-==-==-==- Convert into a binary payload -==-==-==-==-==-==-
#Black screen
convert screen_b.png -resize 800x480 _tmp/resize_screen_b.png
python3 rawPixels.py -i _tmp/resize_screen_b.png > _tmp/pixels_b.raw
./genPayload _tmp/pixels_b.raw b > _tmp/data_b.json

# Red screen
convert screen_r.png -resize 800x480 _tmp/resize_screen_r.png
python3 rawPixels.py -i _tmp/resize_screen_r.png > _tmp/pixels_r.raw
./genPayload _tmp/pixels_r.raw r > _tmp/data_r.json
#=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=--=
