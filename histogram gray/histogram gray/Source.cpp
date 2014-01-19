#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Histogram1D
{
private:
int histSize[1]; // number of bins
float hranges[2]; // min and max pixel value
const float* ranges[1];
int channels[1]; // only 1 channel used here
public:Histogram1D() {
// Prepare arguments for 1D histogram
histSize[0]= 256;
hranges[0]= 0.0;
hranges[1]= 255.0;
ranges[0]= hranges;
channels[0]= 0; // by default, we look at channel 0
}

// Computes the 1D histogram.
cv::MatND getHistogram(const cv::Mat &image) {
cv::MatND hist;
// Compute histogram
cv::calcHist(&image,
1, // histogram from 1 image only
channels, // the channel used
cv::Mat(), // no mask is used
hist, // the resulting histogram
1, // it is a 1D histogram
histSize, // number of bins
ranges // pixel value range
);
return hist;
}


// Computes the 1D histogram and returns an image of it.
cv::Mat getHistogramImage(const cv::Mat &image){
// Compute histogram first
cv::MatND hist= getHistogram(image);
// Get min and max bin values
double maxVal=0;
double minVal=0;
cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
// Image on which to display histogram
cv::Mat histImg(histSize[0], histSize[0],
CV_8U,cv::Scalar(255));
// set highest point at 90% of nbins
int hpt = static_cast<int>(0.9*histSize[0]);
// Draw a vertical line for each bin
for( int h = 0; h < histSize[0]; h++ ) {
float binVal = hist.at<float>(h);
int intensity = static_cast<int>(binVal*hpt/maxVal);
// This function draws a line between 2 points
cv::line(histImg,cv::Point(h,histSize[0]),
cv::Point(h,histSize[0]-intensity),
cv::Scalar::all(0));
}
return histImg;
}
};

int main()
{
  Mat src;
  src = imread("box.png");
 if( !src.data )
    { 
  cout<<"error";
  }

  namedWindow("image", CV_WINDOW_AUTOSIZE );
  imshow("image", src );
  waitKey(0);

  // The histogram object
Histogram1D h;
namedWindow("Histogram");
imshow("Histogram",h.getHistogramImage(src));
waitKey(0);

  return 1;

}
