/*
 * Author: Jeongseok Suh, Chris Gotuaco
 * Filename: circleBoard.h
 * Final Project
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include "gfx.h"
using namespace std;

const double PI = 3.14159265;
const int PAUSE = 10000;

/*
 * Circle structure that will be used to record information about all user-placed circles
 * pathMidX : X value of the location of the circle's midpoint of revolution
 * pathMidY : Y value of the location of the circle's midpoint of revolution
 * circMidX : X value of the circle's midpoint
 * circMidY : Y Value of the circle's midpoint
 * pathRadius : radius of the revolution of the circle
 * speed : speed of the circle. Used in the degree equation
 * orientation : clockwise or counter-clockwise. Represented by a 1 or a -1. Used in the degree equation
 * circRadius : radius of the circle
 * degree : current position in the revolution of the circle.
 *      - Calculated by degree = degree + (orientation * speed)
 */
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


/*
 * CircleBoard class that will contain all of the methods and variables necessary.
 * Function descriptions provided in circleBoard.cpp
 */
class CircleBoard{
public:
    // Constructors
    CircleBoard();
    ~CircleBoard();
    // Accessors
    void newCircle(int, int, double, int, int, int, int);
    int getCurrScore();
    void resetScore();
    //Utility
    void advanceCircles(int);
    void clearCircles();
    bool checkCollision(int);
    void drawButtons();
    void drawTutorial();
    void addPoints(int);
    void checkSetHighscore(int);
private:
    vector<Circle> circleVect;
    int highScore;
    int currScore;
};

double getPathRadius(int, int, int, int);
int getDegree(int, int, int, int);