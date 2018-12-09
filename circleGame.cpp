//
// Created by Daniel Suh on 12/1/18.
//

#include <iostream>
#include "gfx.h"
#include "circleBoard.h"
using namespace std;

int main(){
    CircleBoard circleBoard = CircleBoard();
    bool key = true;
    int clickOrder = 1;
    char event = 0;
    int midX1, midY1, midX2, midY2, xPos, yPos;
    double pathRadius;
    int speed = 1;
    int orientation = 1;
    int circRadius = 20;
    int degree = 0;
    int circleNum = 0;
    int pointSize, pointSpeed;
    gfx_open(1200, 800, "My window");
    circleBoard.drawButtons();



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
                cout << "First Click" << endl;
                midX1 = xPos;
                midY1 = yPos;
                clickOrder = 2;
            }
            else if(event == 1 && clickOrder == 2 && yPos < 600) {
                cout << "Second Click" << endl;
                midX2 = xPos;
                midY2 = yPos;
                pathRadius = getPathRadius(midX1, midY1, midX2, midY2);
                if (pathRadius > circRadius){
                    degree = getDegree(midX1, midY1, midX2, midY2);
                    // Testing purposes. Move add points below new circle after done
                    circleBoard.addPoints(circRadius / 10 * speed);
                    circleBoard.newCircle(midX1, midY1, pathRadius, speed, orientation, circRadius, degree);
                    circleNum++;
                    clickOrder = 1;
                }
            }
            // ASCII 27 is esc
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
            if (event == 'q'){
                key = false;
            }
        }
        if (circleNum >= 1){
            gfx_clear();
            circleBoard.drawButtons();
            for (int i = 0 ; i <= circleNum-1 ; i++){
                circleBoard.advanceCircles(i);
            }
            gfx_flush();
            usleep(PAUSE);
        }
    }
    return 0;
}