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
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>      // std::ifstream, std::ofstream
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


	}
}

void getParkingSpotLines(string imageName) {

	//Creat the CSV export:
	std::ofstream outfile("xy_points.csv", std::ofstream::binary);

	// Read image from file 

	Mat img = imread(imageName);

	//if fail to read the image
	if (img.empty())
	{
		cout << "Error loading the image" << endl;
		return;
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
			
			//TODO Erica save the csv below
			for (int i = 0; i < mouseClicks.size(); i++) {
				cout << mouseClicks.at(i).second.first << "," << mouseClicks.at(i).second.second << endl;
				outfile << mouseClicks.at(i).second.first << "," << mouseClicks.at(i).second.second << endl;
			}
			outfile.close();
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

cv::Mat drawParkingSpotLines(string imageName, vector<vector<int>> parkingLineVec) {
	string maskedWindowName = "maskedWindow";
	//namedWindow(maskedWindowName,2);
	cv::Mat imWithParkingLines, gray,thresholded;
	imWithParkingLines = imread(imageName);
	if (!imWithParkingLines.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return imWithParkingLines;
	}
	namedWindow("Display windowX", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display windowX", imWithParkingLines);                   // Show our image inside it.

	cvtColor(imWithParkingLines, gray, cv::COLOR_BGR2GRAY); //perform gray scale conversion
	
	const cv::Scalar colorOfParkingLines(0, 0,0);
	

	for (int i = 0; i < parkingLineVec.size(); i = i+2) {
		cout << "Drawing Line "<< i/2 << endl;
		cout << "\t" << parkingLineVec.at(i).at(0) << " " << parkingLineVec.at(i).at(1) << endl;
		cout << "\t" << parkingLineVec.at(i+1).at(0) << " " << parkingLineVec.at(i+1).at(1) << endl;
		cv::Point xyPair1(parkingLineVec.at(i).at(0), parkingLineVec.at(i).at(1));
		cv::Point xyPair2(parkingLineVec.at(i+1).at(0), parkingLineVec.at(i+1).at(1));
		cv::line(gray, xyPair1, xyPair2, colorOfParkingLines, 3);
		
	}
	//threshold on black lines
	cv::threshold(gray, thresholded, 1, 255, cv::THRESH_BINARY);

		
	imshow("Display windowX", thresholded);
	cout << "Done Drawing" << endl;
	cv::waitKey(0);
	return gray;
}

int main(int argc, char** argv)
{
	string sourceImageName = "..\\overhead1.jpg";
	getParkingSpotLines(sourceImageName);
	
	/* Example Data:
	327,365
	364,300
	379,374
	416,304
	455,367
	467,312
	345,331
	457,336
	364,297
	468,307
	326,365
	454,367
	*/

	vector<vector<int>> parkingLines{
		{327,365},
		{364,300},
		{379,374 },
		{416,304 },
		{455,367},
		{467,312 },
		{345,331 },
		{457,336 },
		{364,297 },
		{468,307 },
		{326,365 },
		{454,367 },
	};

	cv::Mat imWithParkingLines = drawParkingSpotLines(sourceImageName, parkingLines);


	//Process the parking spots. 

	return 0;

}


