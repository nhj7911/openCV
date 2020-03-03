#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> // equlizeHist, calcHist ����ϱ����� �߰�
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


Mat drawHistogram(Mat src) {
	Mat hist, histImage;

	// establish the number of bins 
	int i, hist_w, hist_h, bin_w, histSize;
	float range[] = { 0, 256 }; // �Է°��� ������ �����ִ� �κ� 
	const float* histRange = { range };

	// ������׷��� �׸� ĵ���� ������
	hist_w = 512;
	hist_h = 400;
	histSize = 256; 
	bin_w = cvRound((double)hist_w / histSize); // ĵ���� ũ�� ��� bin�� ������ �����ָ� �ϳ��� bin�� width �� �� �ִ�.

	// compute the histograms 
	// &src: input image, 1: #of src image, 0: #of channels numerated from 0 ~ channels()-1, Mat(): optional mask 
	// hist: output histogram, 1: histogram dimension, &histSize: array of histogram size,  &histRange: array of histogram��s boundaries 
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange); // ������׷��� ����ϴ� �κ�

	//draw the histogram 
	histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255)); // ������׷��� �۱� ���� ĵ���� ����. �ʱ������ ���

	// normalize the result to [0, histImage.rows] 
	// hist: input Mat, hist: output Mat, 0: lower range boundary of range normalization, histImage.rows: upper range boundary 
	// NORM_MINMAX: normalization type, -1: when negative, the ouput array has the same type as src, Mat(): optional mask 
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat()); // ĵ���� ���̸� �̿��ؼ� ����� ������׷��� ����ȭ ��Ŵ.


	for (i = 1; i < histSize; i++) {
		rectangle(histImage, Point(bin_w*i, hist_h), Point(bin_w*i, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), 2, 8, 0);
	}
	return histImage;
}

int main() {
	Mat image;
	Mat hist_equalized_image;
	Mat hist_graph;
	Mat hist_equalized_graph;

	image = imread("lena.png", 0);
	if (!image.data) exit(1); // check image

	equalizeHist(image, hist_equalized_image); //histogram equlization

	hist_graph = drawHistogram(image);
	hist_equalized_graph = drawHistogram(hist_equalized_image);

	imshow("Input image", image);
	imshow("Hist Equalizd Image", hist_equalized_image);
	imshow("Hist Graph", hist_graph);
	imshow("Hist qualized Graph", hist_equalized_graph);

	waitKey(0);
	return 0;
}
