#include "functions.h"
#include <iostream>


int h(int i, int d, Mat L, Mat R)
{
    if ( d > i )
        return abs(L.at<uchar>(0, i) - R.at<uchar>(0, 0));
    else 
        return abs(L.at<uchar>(0, i) - R.at<uchar>(0, i - d));
}


int g(int d, int b, int alpha)
{
        return alpha*abs(d - b);
}

Mat initBinaryPenalty(int MAX_DISP, float alpha)
{
    Mat g = Mat(MAX_DISP + 1, MAX_DISP + 1, CV_32S);
    int maxdi = g.cols;
    for (int di = 0; di < maxdi; di++)
    {
        for (int dj = 0; dj < maxdi; dj++)
        {
            g.at<int>(di, dj) = alpha * abs(di - dj);
        }
    }
  
    return g;
}


Mat initPrevMatrix(int height, int width)
{
    Mat P = Mat(height, width, CV_8U);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            P.at<uchar>(i, j) = 0;
        }
        //P.at<uchar>(i, 0) = 0;
    }
    return P;
}


Mat initWeightsMatrix(int height)
{
    Mat W = Mat(height, 1, CV_32S);
    for (int d = 0; d < height; d++)
    {
        W.at<int>(d, 0) = 0;
    }
    return W;
}


Mat getRow(int row, Mat im)
{
    Mat R = Mat(1, im.cols, CV_8U);
    for (int i = 0; i < im.cols; i++)
    {
        R.at<uchar>(0, i) = im.at<uchar>(row, i);
    }
    return R;
}