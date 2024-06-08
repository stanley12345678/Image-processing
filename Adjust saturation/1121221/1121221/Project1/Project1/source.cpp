#include <opencv2/opencv.hpp>
using namespace cv;
//Find colors in a specified HSV range

void on_trackbar(int pos, void* pData) {
	Mat* pSrc = (Mat*)pData;
	Mat hsv, hsvPlanes[3], rlt;

	//Get HSVplanes
	cvtColor(*pSrc, hsv, COLOR_BGR2HSV);
	split(hsv, hsvPlanes);
	float satRatio = pos / 100.0;
	hsvPlanes[1] *= satRatio;
	merge(hsvPlanes, 3, hsv);
	cvtColor(hsv, rlt, COLOR_HSV2BGR);

	imshow("Result", rlt);

}


int main(void) {
	Mat src = imread("sample.bmp", IMREAD_REDUCED_COLOR_2);
	if (!src.empty()) {
		int satValue = 100;

		imshow("Source", src);
		createTrackbar("Satauration", "Source", &satValue, 200, on_trackbar, &src);

		waitKey(0);
	}
	return 0;
}