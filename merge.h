//
//  merge.h
//  CS320P02Garcia
//
//  Created by Mason Garcia on 2/27/21.
//

#ifndef merge_h
#define merge_h
#endif /* merge_h */

/* Sorts vector by X coordinate (if else) Y coordinate */
vector<Point> merge(vector<Point> left, vector<Point> right, string coord) {
    int i = 0;
    int j = 0;
    int k = 0;
    unsigned int lsize = left.size();
    unsigned int rsize = right.size();
    int size = lsize + rsize;

    vector<Point> sortedVect(size);
    for (i = 0; i < size; i++) {
        if (j < lsize && k < rsize) {
            // If coord = "x" or coord = "y"
            if (coord == "x") { // Sort By X-coordinate
                if (left[j].x <= right[k].x) {
                    sortedVect[i] = left[j];
                    j++;
                }
                else {
                    sortedVect[i] = right[k];
                    k++;
                }
            }
            else { // Sort By Y-coordinate
                if (left[j].y <= right[k].y) {
                    sortedVect[i] = left[j];
                    j++;
                }
                else {
                    sortedVect[i] = right[k];
                    k++;
                }
            }

        }
        else if (j < lsize) {
            sortedVect[i] = left[j];
            j++;
        }
        else if (k < rsize) {
            sortedVect[i] = right[k];
            k++;
        }
    }
    return sortedVect;
}

vector<Point> mergeSort(vector<Point> vect, string coord) {
    int size = vect.size();
    int mid = size / 2;
    vector<Point> left;
    vector<Point> right;
    if (size <= 1)//base case
        return vect;
    for (int i = 0; i < mid; i++)
    {
        left.push_back(vect[i]);
        right.push_back(vect[i + mid]);
    }
    if (size % 2 != 0)
        right.push_back(vect.back());//Push last element of vector to the right vector in case size of vect is odd

    left = mergeSort(left, coord);
    right = mergeSort(right, coord);

    return merge(left, right, coord);
}
