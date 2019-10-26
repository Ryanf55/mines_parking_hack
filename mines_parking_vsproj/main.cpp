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




void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	bool isMouseClick = false;
	if (event == EVENT_LBUTTONDOWN)
	{
		//cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		isMouseClick = true;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		isMouseClick = true;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		isMouseClick = true;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		//cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

	}

	if (isMouseClick) {
		//mouse x,y
		std::pair<int, int> position(x, y);
		//add the event type
		std::pair< int, std::pair<int, int >> eventAndPosition(event, position);
		//push back the mouse click into mouse_clicks
		mouseClicks.push_back(eventAndPosition);

		for (int i = 0; i < mouseClicks.size(); i++){
			cout << mouseClicks[i].second.first << "," << mouseClicks[i].second.second << endl;
		}
	}
}

void getParkingSpotLines() {
	// Read image from file 
	Mat img = imread("parking1.png");

	//if fail to read the image
	if (img.empty())
	{
		cout << "Error loading the image" << endl;
	}

	//Create a window
	namedWindow("My Window", 1);

	//set the callback function for any mouse event
	cv::setMouseCallback("My Window", CallBackFunc, NULL);

	//show the image
	cv::imshow("My Window", img);

	// Wait until user press escape key.
	while (1)
		if (cv::waitKey(33) == 27) {
			break;
		}
}

int main(int argc, char** argv)
{
	getParkingSpotLines();


	//Process the parking spots. 

	return 0;

}