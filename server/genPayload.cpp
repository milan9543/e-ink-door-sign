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
    unsigned i=0;
    fprintf(stdout, "{\n");
    fprintf(stdout, " \"channel\": \"%s\",\n", argv[2]);
    fprintf(stdout, " \"data\": [\n");
    while(infile >> a){
            pixel_byte |= (a << (7-pixel_byte_pos)); // endianess issue
            pixel_byte_pos++;
            if(pixel_byte_pos == 8) {
	       img_array[i] = pixel_byte&0xff;
	       i++;
               pixel_byte_pos = 0;
               pixel_byte = 0;
            }
    }

    for(int j=0; j<i-1; j++) {
        fprintf(stdout, "%u,", img_array[j]&0xFF);
    }
    fprintf(stdout, "%u", img_array[i-1]&0xFF);

    printf("\n]\n");
    printf("}\n");

    return 0;
}
