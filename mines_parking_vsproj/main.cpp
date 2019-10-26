// Main.cpp - Import images


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file



#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <windows.h>

using namespace cv;
using namespace std;

#include "opencv2/highgui/highgui.hpp"

std::vector<std::pair<int, std::pair<int, int>>> mouseClicks;




void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	bool isMouseClick = false;
	enum LineAction {addFirstpoint , addSecondPoint,undoLastClick };
	LineAction desiredLineAction;
	if (event == EVENT_LBUTTONDOWN)
	{
		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		isMouseClick = true;
		desiredLineAction = addFirstpoint;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		isMouseClick = true;
		desiredLineAction = addSecondPoint;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		isMouseClick = true;
		desiredLineAction = undoLastClick;
	}


	if (isMouseClick) {
		//mouse x,y
		std::pair<int, int> position(x, y);
		//add the event type
		std::pair< int, std::pair<int, int >> eventAndPosition(event, position);

		//if left click, add a point.
		//push back the mouse click into mouse_clicks
		mouseClicks.push_back(eventAndPosition);

		for (int i = 0; i < mouseClicks.size(); i++){
			cout << mouseClicks[i].second.first << "," << mouseClicks[i].second.second << endl;
		}

		//Convert image to grayscale
		Mat gray, imageThresh,img = imread("parking1.png");
		cvtColor(img, gray, cv::COLOR_BGR2GRAY); //perform gray scale conversion

		//threshold the image
		adaptiveThreshold(gray,
			imageThresh, //output image matrix
			255, // output value where condition met
			cv::ADAPTIVE_THRESH_GAUSSIAN_C, // local neighborhood
			cv::THRESH_BINARY_INV, // threshold_type - invert
			5, // blockSize (any large number)
			0); // a constant to subtract from mean

		//erode and dilate
		cv::Mat ellipse_dilate = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
		cv::Mat ellipse_erode = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(4, 4));

		// Opening
		Mat opening, closing;
		dilate(imageThresh, opening, ellipse_dilate);
		erode(opening, closing, ellipse_erode);
		//cv::morphologyEx(imageThresh, opening, cv::MORPH_OPEN, ellipse);

		// Closing
		//cv::morphologyEx(imageThresh, closing, cv::MORPH_CLOSE, ellipse);

		std::vector<std::vector<cv::Point>> outputPoints;
		std::vector<cv::Vec4i> hierarchy;

		cv::findContours(closing,// input image (is destroyed)
			outputPoints,// A std::vector<std::vector<cv::Point>> output vector of contours
			hierarchy,// A cv::Vec4i in which to store the hierarchical representation
			cv::RETR_CCOMP,// retrieve all contours
			cv::CHAIN_APPROX_NONE);// all pixels of each contours

		//cv::imshow("Thresholded Image", opening);
		

		// iterate thru image andadd 1 to each 0 pixel
		// > 0 white
		// 1 blck

	}
}

void getParkingSpotLines(string imageName) {

	// Read image from file 

	Mat img = imread(imageName);

	//if fail to read the image
	if (img.empty())
	{
		cout << "Error loading the image" << endl;
	}

	//Create a window
	namedWindow("My Window", 1);

	//set the callback function for any mouse event
	cv::setMouseCallback("My Window", MouseCallBackFunc, NULL);
	

	//show the image
	cv::imshow("My Window", img);

	// Wait until user press escape key.
	size_t numLinesDrawn = mouseClicks.size();
	cv::Mat prevImg = img.clone();
	const cv::Scalar colorOfParkingLines(0, 0, 0);
	//drawing Loop
	while (1) { 
		

		int waitKeyVal = cv::waitKey(33);
		if (waitKeyVal == 27) { //escape, stop drawing lines
			
			cout << "TODO Erica save the csv below" << endl;
			for (int i = 0; i < mouseClicks.size(); i++) {
				cout << mouseClicks.at(i).second.first << "," << mouseClicks.at(i).second.second << endl;
			}
			break;
		}

		//undo. Remove a point
		else if (waitKeyVal == 117) {
			if (numLinesDrawn) {
				mouseClicks.pop_back();
				cout << "Pop from " << numLinesDrawn << "to" << numLinesDrawn-1 << endl;
				if (numLinesDrawn % 2 == 1) { //removed the start point. Undo the line.
					prevImg.copyTo(img);
					cout << "im reset" << endl;
				}
				numLinesDrawn = mouseClicks.size();
			}
			else {
				cout << "no points to remove" << endl;	
			}
			
		}

		//2 new mouse click so draw a line
		if (mouseClicks.size() > numLinesDrawn+1) { 
			cv::Point xy_firstPoint(mouseClicks.at(mouseClicks.size() - 1).second.first, mouseClicks.at(mouseClicks.size() - 1).second.second);
			cv::Point xy_SecondPoint(mouseClicks.at(mouseClicks.size() - 2).second.first, mouseClicks.at(mouseClicks.size() - 2).second.second);
			img.copyTo(prevImg);
			cv::line(img, xy_firstPoint, xy_SecondPoint, colorOfParkingLines, 3);
			numLinesDrawn = mouseClicks.size();
			cout << "Draw line. Prev is before the line" << endl;
		}


		
		cv::imshow("My Window", img);
			
	}
}

int main(int argc, char** argv)
{
	getParkingSpotLines("parking1.png");


	//Process the parking spots. 

	return 0;

}