//
//  main.cpp
//  CS320P02Garcia
//
//  Created by Mason Garcia on 2/27/21.
//
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
// #include <algorithm>

#include "point.h"
#include "comparisons.h"
#include "merge.h"

using namespace std;

int pNum;
vector<Point> p;

vector<Point> bruteForce(vector<Point> p) {
    int psize = p.size();
    if (psize < 2)
        return p;
    else
    {
        double min = calDist(p[0], p[1]);
        Point p1 = p[0], p2 = p[1];
        for (int i = 0; i < psize; i++)
            for (int j = i + 1; j < psize; j++)
            {
                double distpp = calDist(p[i], p[j]);
                if (distpp < min) {
                    min = distpp;
                    //Two min distance pair:
                    p1 = p[i];
                    p2 = p[j];
                }
            }
        vector<Point> minPoints;
        minPoints.push_back(p1);
        minPoints.push_back(p2);
        return minPoints;
    }
}

// Returns a pair with minimum distance
vector<Point> closestPair(vector<Point> points) {
    if (points.size() <= 3) {
        // return min distance between these using brute-force
        return bruteForce(points);
    }
    int pointsSize = points.size();
    int half = pointsSize / 2;
    vector<Point> leftPairs;
    vector<Point> rightPairs;
    vector<Point> leftResult, rightResult;

    if (pointsSize % 2 == 0) {
        for (int i = 0; i < half; i++)
        {
            leftPairs.push_back(points[i]);
            rightPairs.push_back(points[i + half]);
        }
    }
    else
    {
        for (int i = 0; i <= half; i++)
        {
            leftPairs.push_back(points[i]);
        }
        for (int i = half + 1; i < pointsSize; i++)
        {
            rightPairs.push_back(points[i]);
        }
    }

    leftResult = closestPair(leftPairs);
    rightResult = closestPair(rightPairs);
    double minLeft = calDist(leftResult[0], leftResult[1]);
    double minRight = calDist(rightResult[0], rightResult[1]);
    double minLR = min(minLeft, minRight);
    vector<Point> stripPoints;
    // Since we have a sorted points based on their x,
    // It suffices to check only points around px
    for (int i = half-1; i > 0; i--)
    {
        if (points[half].x - points[i].x < minLR)
            stripPoints.push_back(points[i]);
        else
            break; // In case px>min
    }
    for (int i = half + 1; i < pointsSize; i++)
    {
        if (points[i].x- points[half].x < minLR)
            stripPoints.push_back(points[i]);
        else
            break; // In case px>min
    }
    stripPoints.push_back(points[half]);
    vector<Point> sortedStripPointsy;
    vector<Point> stripClosestPair;
    if (stripPoints.size() > 1) // At least one 2 points be in the strip area
    {
        // If there is a point in Strip Area
        // sort stripPoint by their y-coordinates
        double min = minLR;
        sortedStripPointsy = mergeSort(stripPoints, "y");
        int sizePointStrip = sortedStripPointsy.size();
        for (int i = 0; i < sizePointStrip - 1; i++)
            for (int j = i + 1; j < sizePointStrip && (sortedStripPointsy[j].y - sortedStripPointsy[i].y < min); j++)
            {
                double pairDistance = calDist(sortedStripPointsy[i], sortedStripPointsy[j]);
                if (pairDistance < min)
                {
                    min = pairDistance;
                    stripClosestPair.clear();
                    stripClosestPair.push_back(sortedStripPointsy[i]);
                    stripClosestPair.push_back(sortedStripPointsy[j]);
                }
            }

        if (stripClosestPair.size()>0) // If closest pair is in the strip line
            return stripClosestPair;
        else
            return (minLeft < minRight) ? leftResult : rightResult;
    }
    else
        return (minLeft < minRight) ? leftResult : rightResult;
}

int main() {
    cout << "Closest Pair" << endl;
    
    string line;
    
    string fileName;
    cout << "Enter Filename: ";
    cin >> fileName;
    cout << "------------------------------------------------" << endl;
   
    // File Reading
    ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        getline(inputFile, line);
        pNum = stoi(line);
        int i = 0;
        
        while (getline(inputFile, line)) {
            double x = stod(line.substr(0, line.find(" ")));
            double y = stod(line.substr(line.find(" ")));
            Point pTemp;
            pTemp.x = x;
            pTemp.y = y;
            p.push_back(pTemp);
            i++;
            // Test
            // cout << "File is open" << endl;
        }
        inputFile.close();
    }
    else {
        cout << "Problem reading input file" << endl;
    }
    // END File Reading
    
    // Brute Force
    vector<Point> minPointsBruteForce;
    minPointsBruteForce = bruteForce(p);
    double distMin = calDist(minPointsBruteForce[0], minPointsBruteForce[1]);
    cout << "Brute-Force:" << endl;
    cout << "Minimum Dist: " << distMin << endl;
    cout << "Closest points are: (" << minPointsBruteForce[0].x << ", " << minPointsBruteForce[0].y << ") and (" << minPointsBruteForce[1].x << ", " << minPointsBruteForce[1].y << ") with distance = " << distMin << endl;
    // END Brute Force
     
    cout << "------------------------------------------------" << endl;
    
    // Divide & Conquer Strategy
    cout << "Divide & Conquer:" << endl;
    // If there are 2 points, return the distance between both points (Base Case)
    if (p.size() < 2) {
        cout << "p1: " << p[0].x << " " << p[0].y << " , p2: " << p[1].x << " " << p[1].y << calDist(p[0], p[1]) << endl;
    }
    else {
        vector<Point> sortedPx;
        sortedPx = mergeSort(p, "x");
        vector<Point> closestP = closestPair(sortedPx);
        cout << "Minimum Dist: " << calDist(closestP[0], closestP[1]) << endl;
        cout << "Closest points are: (" << closestP[0].x << ", " << closestP[0].y << ") and (" << closestP[1].x << ", " << closestP[1].y << ") with distance = " << calDist(closestP[0], closestP[1]) << endl;
    }
    // END Divide & Conquer Strategy
    
    cout << " " << endl;
    return 0;
}
