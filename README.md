# mines_parking_hack


The purpose of this project is a hackathon submission for the Mines Data Analytix Hackathon that took place on October 25-26,2019. This (disorganized) repository is a chronicle of our work within OpenCV to create an app to draw the parking lot spaces and the further processing within Matlab to identify which spots are occupied by cars. Due to the time constraints of the competition, we implemented a naive approch by segmenting the image and comparing to a previous frame to determine which spots have changed. 

The c++ code, main.cpp, is an interface to read in a single image of a webcam and allow the user to draw the parking spot lines. Encapsulate the parking spots in closed contours (any order) by clicking to add points. You can undo up to one line with the 'u' key(undercase), and when complete press escape. It then saves a csv of the points of each line ending in x,y pairs by row. 

The Matlab script uses a filter to generate 


For the results of the competition, we obtained the first place prize for best overall hack, as well as best presentation and best overall hack. 

The presentation for the project with underlying theory is uploaded to the Repo in PDF format as "MinesPark.pdf".

Below are notes we used for the project and exploration: 
* http://cnrpark.it/
* opencv tensor parking implementation: https://towardsdatascience.com/find-where-to-park-in-real-time-using-opencv-and-tensorflow-4307a4c3da03
* cascade Calssifier: https://docs.opencv.org/2.4/modules/objdetect/doc/cascade_classification.html
* cascade python implementation with trained xml: https://www.geeksforgeeks.org/opencv-python-program-vehicle-detection-video-frame/
*  

Theory of operation
1. Establish where spots are by drawing lines. Detect spots by any 4 corner closed polygon. Save this to a file that can be applied to any image along with the source image that can be transformed to the original coordinates

  * spot1
    * <corner1x,corner1y>
    * <corner2x,corner2y>
    * <corner3x,corner3y>
    * <corner4x,corner4y>
  * spot2
    * <corner1x,corner1y>
    * <corner2x,corner2y>
    * <corner3x,corner3y>
    * <corner4x,corner4y>
    
2. Any closed polygon will be a mask spot. Count the number of masks to get number of spots

3. Compare two images by subtracing them and absolute valuing the difference. Any difference can be assumed a car leaves or enters. Compare the spot to close area adjacent to it to see if its a spot or not?

4. Establish an output image of green/red depending if is occupied -> Done, but based on hard coded initial positions of the cars. 

5. Upload to sql database and create online stats of where spots are. Could be live projected normal image?


Blob References:
* http://nghiaho.com/uploads/code/opencv_connected_component/blob.cpp
* https://docs.opencv.org/2.4/doc/tutorials/imgproc/shapedescriptors/find_contours/find_contours.html
* https://www.analyticsvidhya.com/blog/2019/03/opencv-functions-computer-vision-python/

Vehicle Tracking
* https://www.behance.net/gallery/4057777/Vehicle-Detection-Tracking-and-Counting
* Haar Classifier: https://www.geeksforgeeks.org/opencv-python-program-vehicle-detection-video-frame/
* Cascade Tutorial: https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html

CNN Detection
* https://jivp-eurasipjournals.springeropen.com/articles/10.1186/s13640-018-0350-2/figures/1
* Mask-RCNN https://medium.com/@ageitgey/snagging-parking-spaces-with-mask-r-cnn-and-python-955f2231c400
  
