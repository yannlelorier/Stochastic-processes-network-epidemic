/*
    Temporary script to develop a simple algorithm to section a circle in n points
    Carlos Garcia 06/07/2020
*/
#include <iostream>
#include <math.h>
#include <iomanip>

int main(){
    static double PI = 4*atan(1);
    double x, y, xCenter, yCenter;
    x = y = xCenter = yCenter = 0;

    x = xCenter + (cos(0));
    y = yCenter + (sin(0));

    std::cout << std::fixed << std::setprecision(20) << "X = " << x << "\nY = " << y << std::endl;
	std::cout << "-----------------------------------------" << std::endl; 
    int n = 4;

    double change = (2*PI)/n;
    double circleCounter = change;

    for (circleCounter; circleCounter <= 2*PI; circleCounter += change){
        x = xCenter + (cos(circleCounter));
        y = yCenter + (sin(circleCounter));
        std::cout << std::fixed << std::setprecision(20) << "X = " << x << "\nY = " << y << "\n" << std::endl;
    }
}
