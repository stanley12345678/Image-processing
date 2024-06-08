#include <opencv2/opencv.hpp>
using namespace cv;

class MyData {
public:
	Mat f;
	int d0;
	int n;
};

void swapFreq(Mat& F)
{
	int cx = F.cols / 2;
	int cy = F.rows / 2;
	Mat q0(F, Rect(0, 0, cx, cy)); // Top-Left
	Mat q1(F, Rect(cx, 0, cx, cy)); // Top-Right
	Mat q2(F, Rect(0, cy, cx, cy)); // Bottom-Left
	Mat q3(F, Rect(cx, cy, cx, cy)); // Bottom-Right
	//swap quadrants
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}

Mat myDFT(Mat& f)
{
	Mat F; //frequency data
	Mat padded; //Padded image
	//Pad image to optimal DFT size with 0s
	int m = getOptimalDFTSize(f.rows);
	int n = getOptimalDFTSize(f.cols);
	copyMakeBorder(f, padded, 0, m - f.rows, 0, n - f.cols, BORDER_CONSTANT, Scalar::all(0));
	// allocate memory for storing frequency data and doing DFT
	Mat planes[] = { Mat_<float>(padded), Mat(padded.size(), CV_32F, 0.0f) };
	merge(planes, 2, F);
	dft(F, F);
	swapFreq(F);
	return F;
}

Mat myIDFT(Mat& F)
{
	Mat planes[2];
	swapFreq(F);
	idft(F, F, DFT_SCALE);
	split(F, planes);
	return planes[0].clone();
}

void showFreq(Mat& F, const char* winName) {
	Mat planes[2], Fmag;
	split(F, planes); // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], Fmag); // Fmag = magnitude
	//log enhancement
	Fmag += 1;
	log(Fmag, Fmag);
	//show result
	normalize(Fmag, Fmag, 0, 1, NORM_MINMAX);
	imshow("winName", Fmag);
}
void showFilter(Mat& H, const char* winName) {
	//show mask
	Mat maskH[2];
	split(H, maskH);
	imshow( winName, maskH[0]);
}

//Ideal low pass filter
void IdealLowPassFilter(Mat& F, int d0)
{
	Mat H(F.rows, F.cols, CV_32FC2, Scalar(0, 0));
	circle(H, Point(H.cols / 2, H.rows / 2), d0, Scalar::all(1), -1);
	F = F.mul(H);
	showFilter(H, "Ideal Low Pass Filter");
}

void GaussianLowPassFilter(Mat& F, int d0)
{
	Mat_<Vec2f> H = Mat(F.rows, F.cols, CV_32FC2);
	int cx = F.rows / 2;
	int cy = F.cols / 2;
	for (int u = 0; u < F.rows; u++) {
		for (int v = 0; v < F.cols; v++) {
			float d = sqrt((float)((u - cx) * (u - cx) + (v - cy) * (v - cy)));
			H(u, v)[0] = (float)exp((-d * d) / (2 * d0 * d0));
			H(u, v)[1] = H(u, v)[0];
		}
	}
	F = F.mul(H);
	showFilter(H, "GaussianLowPassFilter");
}


void ButterworthLowPassFilter(Mat& F, int d0,int n)
{
	Mat_<Vec2f> H = Mat(F.rows, F.cols, CV_32FC2);
	int cx = F.rows / 2;
	int cy = F.cols / 2;
	for (int u = 0; u < F.rows; u++) {
		for (int v = 0; v < F.cols; v++) {
			float d = sqrt((float)((u - cx) * (u - cx) + (v - cy) * (v - cy)));
			H.at<Vec2f>(u, v)[0]=1.f/(1.f+pow(d/d0,2*n));
			H.at<Vec2f>(u, v)[1]= H.at < Vec2f>(u,v)[0];
		}
	}
	F = F.mul(H);
	showFilter(H, "Butterworth Low Pass Filter");
}

void on_trackbar_d0(int d0 , void* vPtr)
{	
	My
	imshow("Linear Blend", dst);
}