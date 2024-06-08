#include <opencv2/opencv.hpp>
using namespace cv;
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
	copyMakeBorder(f, padded, 0, m - f.rows, 0, n - f.cols,
		BORDER_CONSTANT, Scalar::all(0));
	// allocate memory for storing frequency data and doing DFT

	Mat planes[] = { Mat_<float>(padded), Mat(padded.size(), CV_32F, 0.0f) };
	merge(planes, 2, F);
	dft(F, F);
	swapFreq(F);
	return F;
}


int main(void)
{
	Mat f = imread("sample.bmp", IMREAD_REDUCED_GRAYSCALE_2);
	Mat f1 = imread("images1.bmp", IMREAD_REDUCED_GRAYSCALE_2);
	Mat f2 = imread("images2.bmp", IMREAD_REDUCED_GRAYSCALE_2);

	if (!f.empty()) {
		f.convertTo(f, CV_32F, 1.f / 255);
		f1.convertTo(f1, CV_32F, 1.f / 255);
		f2.convertTo(f2, CV_32F, 1.f / 255);


		Mat F = myDFT(f);
		Mat F1 = myDFT(f1);
		Mat F2 = myDFT(f2);

		Mat planes[2], Fmag, Fmag1, Fmag2;
		split(F, planes); // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		magnitude(planes[0], planes[1], Fmag); // Fmag = magnitude
		
		split(F1, planes); // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		magnitude(planes[0], planes[1], Fmag1); // Fmag = magnitude

		split(F2, planes); // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		magnitude(planes[0], planes[1], Fmag2); // Fmag = magnitude



		//log enhancement
		Fmag += 1;
		log(Fmag, Fmag);
		
		Fmag1 += 1;
		log(Fmag1, Fmag1);

		Fmag2 += 1;
		log(Fmag2, Fmag2);

		//show result	
		imshow("sample.bmp" , f);
		normalize(Fmag, Fmag, 0, 1, NORM_MINMAX);
		imshow("magnitude of F", Fmag);
		normalize(Fmag, Fmag, 0, 255, NORM_MINMAX);
		imwrite("F.bmp", Fmag);

		imshow("images1.bmp", f1);
		normalize(Fmag1, Fmag1, 0, 1, NORM_MINMAX);
		imshow("magnitude of F1", Fmag1);
		normalize(Fmag1, Fmag1, 0, 255, NORM_MINMAX);
		imwrite("F1.bmp", Fmag1);

		imshow("images2.bmp", f2);
		normalize(Fmag2, Fmag2, 0, 1, NORM_MINMAX);
		imshow("magnitude of F2", Fmag2);
		normalize(Fmag2, Fmag2, 0, 255, NORM_MINMAX);
		imwrite("F2.bmp", Fmag2);


		waitKey(0);
	}
	return(0);
}