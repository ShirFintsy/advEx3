#include "anomaly_detection_util.h"
#include <ctgmath>

/*
 * Assignment 1
 * Name: Shir Fintsy & Ohad Marmur
 */
float find_avr(float* x, int size);
/*
 * This function return the covariance of the arrays X and Y. Both in this size.
 * The calculate of this covariance is: 𝑐𝑜𝑣(𝑋,𝑌)=𝐸(𝑋𝑌)−𝐸(𝑋)𝐸(𝑌)=𝐸((𝑋−𝐸(𝑋))(𝑌−𝐸(𝑌))
 * while E(X) is the average of the floats in the X array.
 */
float cov(float* x, float* y, int size) {
    if (size == 0) {
        return 0;
    }
    float avrX = find_avr(x, size);
    float avrY = find_avr(y, size);
    float arrXY[size]; // creating array of XY.
    for (int i = 0; i < size; ++i) {
        arrXY[i] = x[i] * y[i];
    }
    float avrXY = find_avr(arrXY, size);
    return avrXY - (avrX * avrY);
}
/*
 * This function return the average value of an array X in this size.
 */
float find_avr(float* x, int size) {
    if (size == 0) {
        return 0;
    }
    float sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += x[i];
    }
    return sum / (float) size;
}
/*
 * This function returns the variance for X array in this size.
 */
float var(float* x, int size) {
    if (size == 0) {
        return 0;
    }
    // both start at 0 in order to add them value by iterations.
    float sum = 0, expectationValue = 0;
    for (int i = 0; i < size; i++) {
        float temp = pow(x[i], 2);
        sum += temp;
        expectationValue += x[i];
    }
    // 1/N * the sigma:
    sum = (1 / (float) size) * sum;
    expectationValue = (1 / (float) size) * expectationValue;
    expectationValue = pow(expectationValue, 2);
    return sum - expectationValue;
}
/*
 * This function return the linear line of the given points and check if there is a Linear correlation.
 */
Line linear_reg(Point** points, int size) {
    float pointsX[size], pointsY[size];
    // init two arrays that contains the x'es values and the y's values
    for (int i = 0; i < size; ++i) {
        pointsX[i] = points[i]->x;
        pointsY[i] = points[i]->y;
    }
    float a = cov(pointsX, pointsY, size) / var(pointsX, size);
    float b = find_avr(pointsY, size) - a * find_avr(pointsX, size);
    //float b = var(pointsY, size) - a * var(pointsX, size);
    Line l(a, b);
    return l;
}

/*
 * This is the pearson function, to calculate the linear correlation.
 * the calculate is: the portion of the returned value of cov(X,Y) by the duplication of X and Y's variance.
 * */
float pearson(float* x, float* y, int size) {
    if (size == 0) {
        return 0;
    }
    float varX = (float) pow(var(x, size), 0.5);
    float varY = (float) pow(var(y, size), 0.5);
    return cov(x, y, size) / (varX * varY);
}
/*
 * This is the dev function that returns he distance between the point p and the correlation line that created by the
 * given points.
 * */
float dev(Point p, Point** points, int size) {
    if (size == 0) return 0;
    // the equation of the points:
    Line linePointsEquation = linear_reg(points, size);
    // gets the y value of the checked point:
    float yPoint = p.y; // will be done
    // gets the y value of the line in the x of the checked point:
    float yLine = linePointsEquation.f(p.x); // will be done
    // returns the difference between the Ys points:
    float dis = yPoint - yLine;
    if(dis < 0) {
        return -1 * dis;
    }
    else return dis;
}

/*
 * This function returns the distance between the point p and the line l.
 */
float dev(Point p,Line l) {
    float fx = l.f(p.x);
    float dis = fx - p.y;
    if(dis < 0) {
        return -1 * dis;
    } else return dis;
}