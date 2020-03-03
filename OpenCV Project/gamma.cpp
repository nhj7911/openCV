#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("zx.png", 0); // grayscale
	Mat gamma_img;
	MatIterator_<uchar> it, end;
	float gamma = 0.5;
	unsigned char pix[256]; // LUT(������̺�) ��� �迭

	for (int i = 0; i < 256; i++) {
		pix[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma)*255.0f);
	}
	gamma_img = image.clone();

	for (it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++) {
		*it = pix[(*it)]; // �Է� ������ ������ �� �������ϰ�, �������� ���� ���������� ���� LUT�� Ȱ����
	}
	
	imshow("Input image", image);
	imshow("Gamma transfomation", gamma_img);
	waitKey(0);
	return 0;
}