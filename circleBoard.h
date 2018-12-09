//
// Created by Daniel Suh on 12/1/18.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include "gfx.h"
using namespace std;

const double PI = 3.14159265;
const int PAUSE = 10000;

struct Circle{
    int pathMidX;
    int pathMidY;
    int circMidX;
    int circMidY;
    double pathRadius;
    int speed;
    int orientation;
    int circRadius;
    int degree;
};

class CircleBoard{
public:
    // Constructors
    CircleBoard();
    ~CircleBoard();
    // Accessors
    void newCircle(int, int, double, int, int, int, int);
    int getSpeed(int);
    int getOrientation(int);
    int getCircRadius(int);
    int getCurrScore();
    void resetScore();
    //Utility
    void advanceCircles(int);
    void clearCircles();
    bool checkCollision(int);
    void drawButtons();
    void addPoints(int);
    void checkSetHighscore(int);
private:
    vector<Circle> circleVect;
    int highScore;
    int currScore;
};

double getPathRadius(int, int, int, int);
int getDegree(int, int, int, int);