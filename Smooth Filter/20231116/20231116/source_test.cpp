#include <opencv2/opencv.hpp>
#include <iostream>
#define PERCENT 10 //percentage of salt and pepper noices
// Add pepper and salt noise to image
#define MASK_SIZE 3
#define K_SIZE 5
using namespace cv;
using namespace std;

Mat averagefilter(Mat& src) {
	Mat dst;
		//Generate mask of mean filter and applying the filter
		Mat mask = Mat::ones(MASK_SIZE, MASK_SIZE, CV_32F)/ (float)(MASK_SIZE*MASK_SIZE);
		filter2D(src, dst, src.depth(), mask, Point(MASK_SIZE/2, MASK_SIZE/2)); // anchor = center point
		return dst;
}




Mat peppernoise(Mat & src) {
	Mat randMtx = Mat::zeros(src.size(), CV_8U);
	randu(randMtx, 0, 255);
	Mat pepperMask = randMtx < 2.55 * PERCENT; //Generate the mask of pepper noice
	Mat saltMask = randMtx > 255 - 2.55 * PERCENT; //Generate the mask of salt noice
	//Add the pepper and salt noise to image
	Mat dst = src.clone();
	dst.setTo(255, saltMask); //Add salt noice
	dst.setTo(0, pepperMask); //Add pepper noice
	//Show results
	return dst;
}


Mat medianfilter(Mat& src) {
	Mat dst;
	//Median filter
	medianBlur(src, dst, K_SIZE);
	return dst;
}


int main(void) {
	Mat src1, src2, src3, pepper;
	src1 = imread("sample.bmp", IMREAD_REDUCED_GRAYSCALE_2);
	if (src1.data) {
		//Generate random matrix, pepper and salt masks
		imshow("Src", src1);
		pepper = peppernoise(src1);
		imshow("Noise Image", pepper);
		src2 = pepper.clone();
		src3 = pepper.clone();
		imshow("Mean Filter", averagefilter(src2));
		imshow("Median Filter", medianfilter(src3));
		waitKey(0);
	}
	else cout << "Could not open or find the image" << endl;
	return(0);
}