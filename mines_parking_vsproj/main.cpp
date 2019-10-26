// Main.cpp - Import images



#include <iostream>


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

		/*
		for (int i = 0; i < mouseClicks.size(); i++){
			cout << mouseClicks[i].second.first << "," << mouseClicks[i].second.second << endl;
		}
		*/
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
	cv::Mat prevImg = img;
	const cv::Scalar colorOfParkingLines(0, 0, 0);
	while (1) {
		

		int waitKeyVal = cv::waitKey(33);
		if (waitKeyVal == 27) { //escape, stop drawing lines
			break;
		}
		else if (waitKeyVal == 117) {//undo. Remove a point
			if (numLinesDrawn) {
				mouseClicks.pop_back();
			}
		}

		if (mouseClicks.size() > numLinesDrawn+1) { //2 new mouse click so draw a line
			cv::Point xy_firstPoint(mouseClicks.at(mouseClicks.size() - 1).second.first, mouseClicks.at(mouseClicks.size() - 1).second.second);
			cv::Point xy_SecondPoint(mouseClicks.at(mouseClicks.size() - 2).second.first, mouseClicks.at(mouseClicks.size() - 2).second.second);
			cv::line(img, xy_firstPoint, xy_SecondPoint, colorOfParkingLines, 5);
			numLinesDrawn = mouseClicks.size();
			cout << "Draw line" << endl;
		}


		prevImg = img;
		cv::imshow("My Window", img);
			
	}
}

int main(int argc, char** argv)
{
	getParkingSpotLines("overhead1.jpg");


	//Process the parking spots. 

	return 0;

}