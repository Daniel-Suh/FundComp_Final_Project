/*
 * Author: Jeongseok Suh, Chris Gotuaco
 * Filename: project.cpp
 * Final Project
 */

#include <iostream>
#include "gfx.h"
#include "circleBoard.h"
using namespace std;

int main(){
    CircleBoard circleBoard = CircleBoard();
    // Booleans to run the overarching while loops
    bool key = true;
    bool keyTutorial = true;
    // Variables
    int clickOrder = 1;
    char event = 0;
    // Variable to determine and record location of mouse clicks
    int midX1, midY1, midX2, midY2, xPos, yPos;
    // Variables to pass into the newCircle function
    double pathRadius;
    int speed = 1;
    int orientation = 1;
    int circRadius = 20;
    int degree = 0;
    // How many circles are on the board
    int circleNum = 0;
    // Variable to determine which circle is being addressed
    int iter;

    gfx_open(1200, 800, "My window");
    // Tutorial Portion
    circleBoard.drawTutorial();
    while(keyTutorial){
        if(gfx_event_waiting()){
            event = gfx_wait();
            xPos = gfx_xpos();
            yPos = gfx_ypos();
            // First Click
            if (event == 1 && xPos > 590 && xPos < 615 && yPos > 400 && yPos < 425){
                midX1 = xPos;
                midY1 = yPos;
                clickOrder = 2;
            }
            // Second Click
            if (event == 1 && xPos > 400 && xPos < 425 && yPos > 400 && yPos < 425){
                midX2 = xPos;
                midY2 = yPos;
                pathRadius = getPathRadius(midX1, midY1, midX2, midY2);
                degree = getDegree(midX1, midY1, midX2, midY2);
                circleBoard.newCircle(midX1, midY1, pathRadius, speed, orientation, circRadius, degree);
                circleNum++;
                clickOrder = 3;
            }
            // Third Click
            if (event == 1 && xPos > 500 && xPos < 525 && yPos > 400 && yPos < 425){
                midX1 = xPos;
                midY1 = yPos;
                clickOrder = 4;
            }
            // Fourth Click
            if (event == 1 && xPos > 700 && xPos < 725 && yPos > 400 && yPos < 425){
                midX2 = xPos;
                midY2 = yPos;
                pathRadius = getPathRadius(midX1, midY1, midX2, midY2);
                degree = getDegree(midX1, midY1, midX2, midY2);
                circleBoard.newCircle(midX1, midY1, pathRadius, speed, orientation, circRadius, degree);
                circleNum++;
                clickOrder = 5;
            }
            if (event == 'p'){
                keyTutorial = false;
            }
        }
        if (clickOrder == 1) {
            // Step 1
            gfx_clear();
            gfx_text(100, 160, "Click somewhere in the demo square to set your center point.");
            circleBoard.drawTutorial();
            gfx_line(590, 400, 590, 425);
            gfx_line(590, 425, 615, 425);
            gfx_line(615, 425, 615, 400);
            gfx_line(615, 400, 590, 400);
        }
        if (clickOrder == 2) {
            // Step 2
            gfx_clear();
            gfx_text(100, 160, "Good job! Now press somewhere inside this second box to set your radius");
            circleBoard.drawTutorial();
            gfx_line(400, 400, 400, 425);
            gfx_line(400, 425, 425, 425);
            gfx_line(425, 425, 425, 400);
            gfx_line(425, 400, 400, 400);
        }
        if (clickOrder == 3) {
            // Step 3
            gfx_clear();
            gfx_text(100, 160, "Nice! Now lets make another circle.");
            circleBoard.drawTutorial();
            gfx_line(500, 400, 500, 425);
            gfx_line(500, 425, 525, 425);
            gfx_line(525, 425, 525, 400);
            gfx_line(525, 400, 500, 400);
        }
        if (clickOrder == 4) {
            // Step 4
            gfx_clear();
            circleBoard.drawTutorial();
            gfx_line(700, 400, 700, 425);
            gfx_line(700, 425, 725, 425);
            gfx_line(725, 425, 725, 400);
            gfx_line(725, 400, 700, 400);
        }
        if (clickOrder == 5) {
            gfx_clear();
            gfx_text(100, 160, "The Tutorial is finished! Press p to start playing the real game.");
            circleBoard.drawTutorial();
        }
        // Makes the circles revolve around their midpoints
        if (circleNum >= 1){
            iter = 0;
            while(iter <= circleNum-1 && circleNum > 0){
                circleBoard.advanceCircles(iter);
                iter++;
            }
            gfx_flush();
        }
        usleep(PAUSE);
    }

    //Reset values for the Actual Game
    circleNum = 0;
    circleBoard.clearCircles();
    gfx_clear();
    circleBoard.resetScore();
    circleBoard.drawButtons();

    clickOrder = 1;

    //Actual Game portion
    while(key){
        // Check for input and advance the circles
        if(gfx_event_waiting()){
            event = gfx_wait();
            xPos = gfx_xpos();
            yPos = gfx_ypos();
            // Check for mouse clicks on the buttons
            // Size Buttons
            if(event == 1 && xPos > 0 && xPos < 400 && yPos > 600){
                if (yPos > 600 && yPos < 650){
                    circRadius = 10;
                }
                else if (yPos > 650 && yPos < 700){
                    circRadius = 20;
                }
                else if (yPos > 700 && yPos < 750){
                    circRadius = 30;
                }
                else if (yPos > 750 && yPos < 800){
                    circRadius = 40;
                }
            }
            // Speed Buttons
            else if(event == 1 && xPos > 400 && xPos < 800 && yPos > 600){
                if (yPos > 600 && yPos < 650){
                    speed = 1;
                }
                else if (yPos > 650 && yPos < 700){
                    speed = 2;
                }
                else if (yPos > 700 && yPos < 750){
                    speed = 4;
                }
                else if (yPos > 750 && yPos < 800){
                    speed = 8;
                }
            }
            // Rotation Buttons
            else if(event == 1 && xPos > 800 && xPos < 1200 && yPos > 600){
                // Clockwise
                if (yPos > 600 && yPos < 650){
                    orientation = 1;
                }
                // Counter Clockwise
                else if (yPos > 650 && yPos < 700){
                    orientation = -1;
                }
            }

            // Check for mouse clicks on the board
            if (event == 1 && clickOrder == 1 && yPos < 600) {
                midX1 = xPos;
                midY1 = yPos;
                clickOrder = 2;
            }
            else if(event == 1 && clickOrder == 2 && yPos < 600) {
                midX2 = xPos;
                midY2 = yPos;
                pathRadius = getPathRadius(midX1, midY1, midX2, midY2);
                if (pathRadius > circRadius){
                    degree = getDegree(midX1, midY1, midX2, midY2);
                    circleBoard.newCircle(midX1, midY1, pathRadius, speed, orientation, circRadius, degree);
                    circleBoard.addPoints(circRadius / 10 * speed);
                    circleNum++;
                    clickOrder = 1;
                }
            }
            // ASCII 27 is esc
            // Quit the game
            if (event == 27){
                gfx_clear();
                gfx_text(500, 400, "Are You Sure You Want To End The Game?");
                gfx_text(550, 450, "Press esc Again To Quit");
                gfx_text(500, 500, "Press Any Other Key Except q To Continue");
                event = gfx_wait();
                if (event == 27){
                    circleNum = 0;
                    circleBoard.clearCircles();
                    gfx_clear();
                    circleBoard.resetScore();
                    circleBoard.drawButtons();
                    clickOrder = 1;
                }
            }
        }
        if (circleNum >= 1){
            gfx_clear();
            circleBoard.drawButtons();
            iter = 0;
            // Makes the circles revolve around their midpoints and checks for any collision between any two circles
            while(iter <= circleNum-1 && circleNum > 0){
                circleBoard.advanceCircles(iter);
                if (circleBoard.checkCollision(iter)){
                    gfx_text(575, 50, "You Lost!");
                    gfx_text(500, 100, "Press Any Key Except q to Play Again");
                    event = gfx_wait();
                    circleBoard.clearCircles();
                    gfx_clear();
                    circleBoard.resetScore();
                    circleBoard.drawButtons();
                    clickOrder = 1;
                    circleNum = 0;
                }
                iter++;
            }
            gfx_flush();
            usleep(PAUSE);
        }
        if (event == 'q'){
            key = false;
        }
    }
    return 0;
}