#include "Canvas.h"
#include "Circle.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>
#include <thread>

#define length 150
#define frames 2192
#define calcX (((i % length) * 2) + 1) * circleSize + 100
#define calcY (((i / length) * 2) + 1) * circleSize


Canvas canvas(800, 600);
std::vector<Circle> circles;


int numPix = (length * length);
int circleSize = (600 / length) / 2;

char pixels[length * length * 2192];
int waitTime = 1000 / 10;
void updateDrawing();


int main(){
    srand(time(NULL));
    FILE *file = fopen("frames/frameData.txt", "r");

    for(int i = 0; i < numPix; i++){
        Circle circ(calcX, calcY, circleSize * 1, "white");
        circles.push_back(circ);
    }

    int circSize = circles.size();
    for(int i = 0; i < circSize; i++){
        canvas.addCircle(circles[i]);
    }

    fread(pixels, 1, length * length * frames, file);
    int colour = 0;

    for(int repeats = 0; repeats < frames; repeats++){
        /*for(int i = 0; i < numPix; i++){
            if(rand() % 4 == 0){
                pixels[i] = 1;
            }
        }*/
        
        
        for(int i = 0; i < length * length; i++){
            colour = (int)pixels[(length * length * repeats) + i] - 48;
            if(colour == 1){
                circles[i].setColour("Black");
            }
            else{
                circles[i].setColour("White");
            }
        }
        canvas.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
    }
    
    fclose(file);
    
    printf("program done\n");
    return 0;
}

