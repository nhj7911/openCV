#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {
	Mat image, thresh;
	int thresh_T, low_cnt, high_cnt, low_sum, high_sum, i, j, th;
	
	thresh_T = 200; // �ʱ� T��
	th = 10; // �ʱ� T���� �ٽ� ������ T���� ���̰� ����ũ�� ���ϸ� ���ߴµ� ����ϴ°�
	low_cnt = high_cnt = low_sum = high_sum = 0;
	
	image = imread("zx.png", 0);
	cout << "threshold value:" << thresh_T << endl;
	
	while (1) {
		for (j = 0; j < image.rows; j++) {
			for (i = 0; i < image.cols; i++) {
				if (image.at<uchar>(j, i) < thresh_T) {
					low_sum += image.at<uchar>(j, i);
					low_cnt++;
				}
				else {
					high_sum += image.at<uchar>(j, i);
					high_cnt++;
				}
			}
		}
		if (abs(thresh_T - (low_sum / low_cnt + high_sum / high_cnt) / 2.0f) < th) { // ���ο� T�� < th�϶� 
			break; // ����
		}
		else {
			thresh_T = (low_sum / low_cnt + high_sum / high_cnt) / 2.0f;
			cout << "threshold value:" << thresh_T << endl;
			low_cnt = high_cnt = low_sum = high_sum = 0;
		}
	}
	threshold(image, thresh, thresh_T, 255, THRESH_BINARY);
	
	imshow("Input image", image);
	imshow("thresholding", thresh);
	waitKey(0);
}