#include <iostream>
#include <opencv2/opencv.hpp>
#include <limits>
#include "functions.h"

int WindowStartX = 500, WindowStartY = 100, WindowMargin = 10, Scale = 1;

int main()
{
	Mat imL = imread("../imgs/3d/view2.png", IMREAD_GRAYSCALE);
	Mat imR = imread("../imgs/3d/view1.png", IMREAD_GRAYSCALE);
	int width = imL.cols, height = imL.rows;
	int MAX_DISP = 50; //< 255
	Mat depth_map = Mat(height, width, CV_8U);
	

	//For one row
	for (int row = 0; row < 400; row++)
	{
		Mat L = getRow(row, imL);
		Mat R = getRow(row, imR);
		Mat P = initPrevMatrix(MAX_DISP + 1, width);
		Mat W = initWeightsMatrix(MAX_DISP + 1);
		Mat W2 = initWeightsMatrix(MAX_DISP + 1);


		//--Computing PrevMatrix--
		for (int t = 1; t < width; t++)
		{
			for (int d = 0; d < MAX_DISP + 1; d++)
			{
				int temp_sum;
				int  Wmin = std::numeric_limits<int>::max();
				for (int b = 0; b < MAX_DISP + 1; b++)
				{
					temp_sum = W.at<int>(b, 0) + h(t, b, L, R) + g(d, b, 2);
					//std::cout << d << " | " << b << " | " << temp_sum << std::endl;
					if (temp_sum < Wmin)
					{
						Wmin = temp_sum;
						W2.at<int>(d, 0) = Wmin;
						P.at<uchar>(d, t) = b;
					}
				}
				W = W2;
				//std::cout << t << " | " << d << " | "<< static_cast<int>(P.at<uchar>(d, t)) << std::endl;
				//std::cout << d << " | " << W2.at<int>(d, 0) << std::endl;
			}
		}


		//--Restore depth_string--
		Mat depth_string = Mat(1, width, CV_8U);
			//Finding d_n
		int temp_sum, d, n = width - 1;
		int  Wmin = std::numeric_limits<int>::max();
		for (int b = 0; b < MAX_DISP + 1; b++)
		{
			temp_sum = W.at<int>(b, 0) + h(n, b, L, R);
			//std::cout << d << " | " << b << " | " << temp_sum << std::endl;
			if (temp_sum < Wmin)
			{
				Wmin = temp_sum;
				d = b;
			}
		}
			//Computing depth_string
		depth_string.at<uchar>(0, n) = d;
		for (int i = n - 1; i > 0; i--)
		{
			int k = static_cast<int>(depth_string.at<uchar>(0, i + 1));
			depth_string.at<uchar>(0, i) = P.at<uchar>(k, i + 1);
			//std::cout << i << " | " << static_cast<int>(depth_string.at<uchar>(0, i)) << std::endl;
		}


		//Writing data to depth_map
		for (int i = 0; i < width; i++)
		{
			depth_map.at<uchar>(row, i) = depth_string.at<uchar>(0, i);
		}
		std::cout << "[ " << row << " / " << height << " ] \r";
	}






	namedWindow("Window1", WINDOW_FREERATIO);
	imshow("Window1", depth_map);
	//resizeWindow("Window1", width * Scale, height * Scale);
	//moveWindow("Window1", WindowStartX, WindowStartY);
	waitKey();
}







/*
	Mat imL = imread("../imgs/3d/view2.png", IMREAD_GRAYSCALE);
	Mat imR = imread("../imgs/3d/view1.png", IMREAD_GRAYSCALE);

	int width = imL.cols, height = imL.rows;
	int MAX_DISP = 50;

	std::cout << "Max disparity: " << MAX_DISP << std::endl;
	std::cout << "Width: " << width << " Height: " << height << std::endl;


	Mat depth_map = Mat(width, height, CV_32S);

	Mat G = initBinaryPenalty(MAX_DISP, 1);
	Mat W = initWeightsMatrix(MAX_DISP);
	Mat P = initPrevMatrix(width, MAX_DISP + 1);


	for (int t = 0; t < width-1; t++)
	{
		for (int d = 0; d <= MAX_DISP; d++)
		{
			int Wmin = 999;
			for (int k = 0; k <= MAX_DISP; k++)
			{
				double temp = W.at<int>(0, k) + h(t, k, 0, imL, imR) + G.at<int>(d, k);
				if (temp < Wmin)
				{
					Wmin = temp;

				}
			}

			//W.at<int>(0, d) = ;
		}
	}

	*/