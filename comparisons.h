//
//  Comparisons.h
//  CS320P02Garcia
//
//  Created by Mason Garcia on 2/26/21.
//

#ifndef Comparisons_h
#define Comparisons_h
#endif /* Comparisons_h */

// Finds distance between the two points
float calDist(Point p1, Point p2) {
    return abs(sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)));
}

// Finds min of two float values
float min(float x, float y)
{
    return (x < y)? x : y;
}
