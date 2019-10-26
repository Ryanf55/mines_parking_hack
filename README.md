# mines_parking_hack

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

4. Establish an output image of green/red depending if is occupied

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
https://jivp-eurasipjournals.springeropen.com/articles/10.1186/s13640-018-0350-2/figures/1
  
