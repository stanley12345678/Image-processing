/*#include <opencv2/opencv.hpp>
using namespace cv;
#define PERCENT 1 //percentage of salt and pepper noices
// Add pepper and salt noise to image
int main(void) {
	Mat src = imread("sample.bmp", IMREAD_REDUCED_GRAYSCALE_2);
	if (!src.empty()) {
		//Generate random matrix, pepper and salt masks
		Mat randMtx = Mat::zeros(src.size(), CV_8U);
		randu(randMtx, 0, 255);
		Mat pepperMask = randMtx < 2.55 * PERCENT; //Generate the mask of pepper noice
		Mat saltMask = randMtx > 255 - 2.55 * PERCENT; //Generate the mask of salt noice
		//Add the pepper and salt noise to image
		Mat dst = src.clone();
		dst.setTo(255, saltMask); //Add salt noice
		dst.setTo(0, pepperMask); //Add pepper noice
		//Show results
		imshow("Source", src);
		imshow("Noise Image", dst);
		waitKey(0);
	}
	return(0);
}*/

/*#include <opencv2/opencv.hpp>
using namespace cv;
#define PERCENT 1 //percentage of salt and pepper noices
#define K_SIZE 3 // width of the median filter
// Applying the median filter to input image
int main(void) {
	Mat src = imread("sample.bmp", IMREAD_REDUCED_GRAYSCALE_2);
	if (!src.empty()) {
		//Generate random matrix, pepper and salt masks
		Mat randMtx = Mat::zeros(src.size(), CV_8U);
		randu(randMtx, 0, 255);
		Mat pepperMask = randMtx < 2.55 * PERCENT; //Generate the mask of pepper noice
		Mat saltMask = randMtx > 255 - 2.55 * PERCENT; //Generate the mask of salt noice
		//Add the pepper and salt noise to image
		Mat dst = src.clone();
		dst.setTo(255, saltMask); //Add salt noice
		dst.setTo(0, pepperMask); //Add pepper noice
		Mat dst;
		//Median filter
		medianBlur(src, dst, K_SIZE);
		//Show results
		imshow("Source", src);
		imshow("Result", dst);
		waitKey(0);
		}
		return(0);
	}*/
/*int main(void) {
	Mat src = imread("sample.bmp", IMREAD_REDUCED_GRAYSCALE_2);
	if (!src.empty()) {
		Mat dst;
		//Median filter
		medianBlur(src, dst, K_SIZE);
		//Show results
		imshow("Source", src);
		imshow("Result", dst);
		waitKey(0);
	}
	return(0);
}*/