#ifndef UTIL_H
#define UTIL_H

int letterFrequencyProblem(char fileName[20]);
void gameArena(char gamePlay[3][3],int row,int col,int count);
void fillTheArea(char gamePlay[3][3]);
int winCheck(char gameplay[3][3]);


typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
} Color;

double MeasureDistance(double x1, double y1, double z1, double x2, double y2, double z2);
int colMix(Color color1, Color color2, int (*mixer)(Color, Color));
int mixerColors(Color color1, Color color2);


#endif