#include <Magick++.h>
#include <iostream>
#include <cstring>

using namespace Magick;

char filename[20];

int main(int argc, char **argv) {
    InitializeMagick(*argv);

    FILE *file = fopen("frameData.txt", "w");

    for (int frame = 1; frame <= 2192; frame++){
        memset(filename, '\0', 20);
        strcpy(filename, "frame_");
        filename[6] = (frame / 1000) + '0';
        filename[7] = ((frame % 1000) / 100) + '0';
        filename[8] = ((frame % 100) / 10) + '0';
        filename[9] = (frame % 10) + '0';
        strcat(filename, ".bmp");
        Image img(filename);

        float total = 0;
        int output;
        for(int i = 0; i < 150 * 150; i++){
            for(int j = 0; j < 6; j++){
                ColorRGB rgb(img.pixelColor((i % 150) * 3, (i / 150) * 2));
                total += (rgb.red() + rgb.green() + rgb.blue()) / 3;
            }
            total = total / 6;
            if(total > 0.5){output = 1;}
            else{output = 0;}
            
            fprintf(file, "%d", output);
        }
        printf("Done frame %i\n", frame);
    }
    


    fclose(file);
    
    return 0;
}