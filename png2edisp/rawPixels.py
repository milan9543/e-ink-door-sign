from PIL import Image

im = Image.open("image.png")
pix = list(im.getdata())

width, height = im.size

# RAW Pixel data
for p in pix:
    if isinstance(p, tuple):
        val = (p[0] + p[1] + p[2])/3
    else:
        val = p

    if val > 25:
        print(1)
    else: 
        print(0)
