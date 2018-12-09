/*
 * Author: Jeongseok Suh, Chris Gotuaco
 * Filename: circleBoard.cpp
 * Final Project
 */
#include <iostream>
#include <cmath>
#include <cstdio>
#include "circleBoard.h"
using namespace std;

// Constructors
CircleBoard::CircleBoard(){
    highScore = 0;
    currScore = 0;
}
CircleBoard::~CircleBoard(){}

// Accessors
/*
 * Creates a new circle object and adds it into a vector of Circles
 */
void CircleBoard::newCircle(int pMX, int pMY, double pR, int sp, int o, int cR, int d){
    Circle newCirc;
    newCirc.pathMidX = pMX;
    newCirc.pathMidY = pMY;
    newCirc.circMidX = 0;
    newCirc.circMidY = 0;
    newCirc.pathRadius = pR;
    newCirc.speed = sp;
    newCirc.orientation = o;
    newCirc.circRadius = cR;
    newCirc.degree = d;
    circleVect.push_back(newCirc);
}

/*
 * Returns the user's current score. Used to display the score.
 */
int CircleBoard::getCurrScore() {
    return currScore;
}

//Utility
/*
 * Draws the buttons and the score onto the screen
 */
void CircleBoard::drawButtons() {
    //Horizontal Lines
    gfx_line(1, 599, 1199, 599);
    gfx_line(1, 649, 1199, 649);
    gfx_line(1, 699, 1199, 699);
    gfx_line(1, 749, 1199, 749);
    gfx_line(1, 799, 1199, 799);

    // Vertical Lines
    gfx_line(1, 599, 1, 799);
    gfx_line(400, 599, 400, 799);
    gfx_line(800, 599, 800, 799);
    gfx_line(1199, 599, 1199, 799);

    // Text
    gfx_text(175, 575, "Size");
    gfx_text(575, 575, "Speed");
    gfx_text(950, 575, "Orientation");
    gfx_text(150, 625, "Radius = 1");
    gfx_text(150, 675, "Radius = 2");
    gfx_text(150, 725, "Radius = 3");
    gfx_text(150, 775, "Radius = 4");
    gfx_text(550, 625, "Speed = 1");
    gfx_text(550, 675, "Speed = 2");
    gfx_text(550, 725, "Speed = 4");
    gfx_text(550, 775, "Speed = 8");
    gfx_text(950, 625, "Clockwise");
    gfx_text(950, 675, "Counter Clockwise");

    char str[15];
    char buf[15];
    sprintf(str, "%i", highScore);
    const char* hs = str;
    sprintf(buf, "%i", currScore);
    const char* cs = buf;

    gfx_text(1050, 50, "High Score: ");
    gfx_text(1050, 75, "Your Score: ");
    gfx_text(1130, 50, hs);
    gfx_text(1130, 75, cs);

    gfx_text(50, 50, "Press q to quit");
    gfx_text(50, 75, "Press esc to clear the board");
}

/*
 * Calls the drawButtons function, and adds extra text to the screen
 */
void CircleBoard::drawTutorial()
{
    drawButtons();
    gfx_text(100, 100, "Welcome to the Circle Game!! ");
    gfx_text(100, 120, "The goal of the game is to get as many moving circles as possible without having any of them collide with each other.");
}

/*
 * Advances a circle that is called by cNum by the equation
 *      degree = degree + (speed * orientation)
 * Also checks to see whether the circle's degree is within the range of 0 - 360, and resets the degree if it is not.
 */
void CircleBoard::advanceCircles(int cNum){
    srand(time(NULL));
    if(circleVect[cNum].degree >= 360){
        circleVect[cNum].degree = circleVect[cNum].degree - 360;
    }
    if(circleVect[cNum].degree <= 0){
        circleVect[cNum].degree = circleVect[cNum].degree + 360;
    }
    circleVect[cNum].degree = circleVect[cNum].degree + (circleVect[cNum].speed * circleVect[cNum].orientation);

    int circMidX, circMidY;
    circleVect[cNum].circMidX = circleVect[cNum].pathMidX + (circleVect[cNum].pathRadius * cos(circleVect[cNum].degree * PI/180));
    circleVect[cNum].circMidY = circleVect[cNum].pathMidY + (circleVect[cNum].pathRadius * sin(circleVect[cNum].degree * PI/180));
    gfx_circle(circleVect[cNum].circMidX, circleVect[cNum].circMidY, circleVect[cNum].circRadius);
}

/*
 * Checks whether or not two circles have collided. This is calculated through the equation
 *      (x2 - x1)^2 + (y2 - y1)^2 <= (radius1 + radius2)^2
 */
bool CircleBoard::checkCollision(int cNum){
    double collideDistance, actualDistance;
    for (int i = 0; i < circleVect.size() ; i++){
        if (i != cNum){
            collideDistance = pow(circleVect[i].circRadius + circleVect[cNum].circRadius, 2);
            actualDistance = pow(circleVect[cNum].circMidX - circleVect[i].circMidX, 2) + pow(circleVect[cNum].circMidY - circleVect[i].circMidY, 2);
            if (actualDistance <= collideDistance){
                return true;
            }
        }
    }
    return false;
}

/*
 * Clears the circleVect vector
 */
void CircleBoard::clearCircles() {
    circleVect.erase(circleVect.begin(), circleVect.end());
}

/*
 * Adds a certain amount of points to the current score
 * Runs the checkSetHighscore function
 */
void CircleBoard::addPoints(int points){
    currScore = currScore + points;
    checkSetHighscore(currScore);
}

/*
 * Checks the high score, if the number of points is higher than the high score,
 * it sets the high score to the number of points
 */
void CircleBoard::checkSetHighscore(int points) {
    if (points > highScore){
        highScore = points;
    }
}

/*
 * Resets the current score to 0.
 */
void CircleBoard::resetScore(){
    currScore = 0;
}

/*
 * Calculates and returns the radius of the revolution
 *      - Based on the distance formula
 */
double getPathRadius(int midX1, int midY1, int midX2, int midY2){
    return sqrt(pow(midX2 - midX1, 2) + pow(midY2 - midY1, 2));
}

/*
 * Calculates and returns the degree that the circle is currently at
 */
int getDegree(int midX1, int midY1, int midX2, int midY2){
    if(midX2!=midX1){
        return atan2(midY2-midY1,midX2 - midX1) * 180/PI;
    }
    else if (midX2 == midX1){
        if (midX2 > midX1) return 0;
        else if(midX2 < midX1) return 180;
    }
    return 0;
}