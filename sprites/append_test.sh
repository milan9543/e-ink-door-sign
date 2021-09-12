#!/bin/bash

# Testing appending sprites together

convert swimming.png weather.png -background None -layers Flatten _screen_b.png 
convert _screen_b.png -background white -alpha remove -alpha off screen_b.png
