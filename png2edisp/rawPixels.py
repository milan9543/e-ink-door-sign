from PIL import Image

import sys, getopt

def main(argv):
   inputfile = ''
   outputfile = ''
   try:
      opts, args = getopt.getopt(argv,"hi:",["ifile="])
   except getopt.GetoptError:
      print('rawPixels.py -i <inputfile>')
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         print('rawPixels.py -i <inputfile>')
         sys.exit()
      elif opt in ("-i", "--ifile"):
         inputfile = arg

   im = Image.open(inputfile)
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

if __name__ == "__main__":
   main(sys.argv[1:])

