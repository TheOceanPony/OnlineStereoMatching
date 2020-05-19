#pragma once
#include "opencv2/opencv.hpp"
using namespace cv;

int h(int i, int d, Mat L, Mat R);
int g(int d, int b, int alpha = 1);

Mat initBinaryPenalty(int MAX_DISP, float alpha);
Mat initPrevMatrix(int height, int width);
Mat initWeightsMatrix(int MAX_DISP);
Mat getRow(int row, Mat im);