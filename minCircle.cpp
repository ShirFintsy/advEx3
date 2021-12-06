#include "minCircle.h"
#include <cassert>
#include <cmath>
#include <vector>

// Function to return the euclidean distance between two points
double dist(const Point& first, const Point& second)
{
    return sqrt(pow(first.x - second.x, 2)
                + pow(first.y - second.y, 2));
}

// Function to check whether a point lies inside
// or on the boundaries of the circle
bool is_inside(const Circle& c, const Point& p)
{
    return dist(c.center, p) <= c.radius;
}

/* The following two functions are used
To find the equation of the circle when
three points are given.

Helper method to get a circle defined by 3 points
*/
Point get_circle_center(double bx, double by,
                        double cx, double cy)
{
    double B = bx * bx + by * by;
    double C = cx * cx + cy * cy;
    double D = bx * cy - by * cx;
    return { static_cast<float>((cy * B - by * C) / (2 * D)), static_cast<float>((bx * C - cx * B) / (2 * D)) };
}

/* Function to return a unique circle that
intersects three points
 */
Circle circle_from(const Point& first, const Point& second, const Point& third)
{
    Point center = get_circle_center(second.x - first.x, second.y - first.y, third.x - first.x, third.y - first.y);

    center.x += first.x;
    center.y += first.y;
    return { center, static_cast<float>(dist(center, first)) };
}

/* Function to return the smallest circle
that intersects 2 points
*/
Circle circle_from(const Point& first, const Point& second)
{
    // Set the center to be the midpoint of first and second
    Point C = {static_cast<float>((first.x + second.x) / 2.0), static_cast<float>((first.y + second.y) / 2.0) };
    // Set the radius to be half the distance AB
    return { C, static_cast<float>(dist(first, second) / 2.0) };
}

/* Function to check whether a circle
encloses the given points
 */
bool is_valid_circle(const Circle& c, const vector<Point>& P)
{
    /* Iterating through all the points to check  whether the points lie inside the circle or not */
    for (const Point& p : P)
        if (!is_inside(c, p))
            return false;
    return true;
}

Circle min_circle_trivial(vector<Point>& P) {
    assert(P.size() <= 3);
    if (P.empty()) {
        return {{0, 0}, 0};
    } else if (P.size() == 1) {
        return {P[0], 0};
    } else if (P.size() == 2) {
        return circle_from(P[0], P[1]);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {

            Circle c = circle_from(P[i], P[j]);
            if (is_valid_circle(c, P))
                return c;
        }
    }
    return circle_from(P[0], P[1], P[2]);
}


Circle welzel(Point **points, vector<Point> rPoints, size_t size) {
    if (size == 0 || rPoints.size() == 3)
        return min_circle_trivial(rPoints);
    Circle temp = welzel(points, rPoints, size - 1);
    Point p = *points[size - 1];
    // If d contains p, return d
    if (is_inside(temp, p)) {
        return temp;
    }
    // Otherwise, must be on the boundary of the MEC
    rPoints.push_back(p);
    // Return the MEC for P - {p} and R U {p}
    return welzel(points, rPoints, size - 1);
}

Circle findMinCircle(Point **points, size_t size) {
    vector<Point> R;
    return welzel(points, R, size);
}