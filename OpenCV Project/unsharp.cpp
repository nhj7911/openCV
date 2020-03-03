#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {
	Mat input = imread("zx.png");
	Mat gray, blur, sharp;
	cvtColor(input, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, blur, Size(5, 5), 3);
	addWeighted(gray, 1.5, blur, -0.5, 0, sharp); // gray(����ġ 1.5)�� blur(����ġ -0.5) ������ ������
	imshow("gray", gray);
	imshow("sharp", sharp);

	waitKey(0);
}