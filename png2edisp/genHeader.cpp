#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <fstream>

char pixel_byte; // for the data array 
unsigned pixel_byte_pos;

char img_array[48000];

int main(int argc, char *argv[])
{

    std::ifstream infile(argv[1]);

    pixel_byte = 0;
    pixel_byte_pos = 0;

    int a;
    fprintf(stdout, "const unsigned char %s[48000] = {\n", argv[2]);
    while(infile >> a){
            pixel_byte |= (a << (7-pixel_byte_pos)); // endianess issue
            pixel_byte_pos++;
            if(pixel_byte_pos == 8) {
               fprintf(stdout, "0x%02x,", pixel_byte&0xff);
               pixel_byte_pos = 0;
               pixel_byte = 0;
            }
    }
    for(int i=0; i<7800; i++) {
        fprintf(stdout, "0xFF,");
    }
    printf("};\n");


    //    for(i = 0 ; i < w; i++){
    //        pixel_byte |= (img[j * w + i] << pixel_byte_pos);
    //        pixel_byte_pos++;
    //        if(pixel_byte_pos == 8) {
    //           printf("0x%02x,", pixel_byte&0xff);
    //           pixel_byte_pos = 0;
    //           pixel_byte = 0;
    //        }
    //    }
    //        
    //    printf("\n");
    //}
    //printf("};\n");

    return 0;
}
