#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("zx.png", 0); // grayscale
	Mat f_img, log_img;
	double c = 0.5f; // ���
	image.convertTo(f_img, CV_32F); // log�Լ� Ȱ���ϱ� ���� float������ ��ȯ
	f_img = abs(f_img) + 1; // ���밪 ������. �ȼ����� 0~255�̱� ������ ū �ǹ̴�x
	log(f_img, f_img);
	normalize(f_img, f_img, 0, 255, NORM_MINMAX); // 0~ 255������ ����ȭ
	convertScaleAbs(f_img, log_img, c); // �ȼ� ���� c���� ���ؼ� unsigned 8-bit Ÿ������ �� ��ȯ��Ŵ
	imshow("Input image", image);
	imshow("Log transfomation", log_img);

	waitKey(0);
	return 0;
}