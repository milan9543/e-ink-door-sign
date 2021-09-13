#!/bin/bash

# grabs the current high and low tide times for swansea bay.

rm -rf index.html
wget https://www.tideschart.com/United-Kingdom/Wales/City-and-County-of-Swansea/Swansea-Bay-Beach/

HIGH_TIDE_TMP=`grep "<h3 class=\"text-dark mt-1 font-weight-normal\">Next high tide is at <br>" index.html | sed -n -e 's/^.*<br>//p'`
LOW_TIDE_TMP=`grep "<h3 class=\"text-dark mt-1 mb-0 font-weight-normal\">Next low tide is at <br>" index.html | sed -n -e 's/^.*<br>//p'`

HIGH_TIDE=${HIGH_TIDE_TMP::-5}
LOW_TIDE=${LOW_TIDE_TMP::-5}
echo "$HIGH_TIDE"
echo "$LOW_TIDE"

#convert -font helvetica -fill black -pointsize 80 -gravity center -draw "text -100,20 'HighTide@ ${HIGH_TIDE}" screen_b.png _lt_screen_b.png
#convert -font helvetica -fill black -pointsize 80 -gravity center -draw "text -200,80 'LowTide@ ${LOW_TIDE}" _lt_screen_b.png _ht_lt_screen_b.png

convert -font helvetica -fill black -pointsize 80 -draw "text 50,100 'HighTide@ ${HIGH_TIDE}" screen_b.png _lt_screen_b.png
convert -font helvetica -fill black -pointsize 80 -draw "text 875,100 'LowTide@ ${LOW_TIDE}" _lt_screen_b.png _ht_lt_screen_b.png

mv _ht_lt_screen_b.png screen_b.png
