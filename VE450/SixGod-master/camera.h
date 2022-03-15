#ifndef SIXGOD_CAMERA_H
#define SIXGOD_CAMERA_H
//#include <Python.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace cv::dnn;
/// Start camera.
/// \return the camera as a VideoCapture type.
VideoCapture camera_start();

/// Stop camera.
/// \param cap  The camera to be endded.
void camera_end(VideoCapture cap);

/// Take a picture with camera.
/// \param cap the camera to be used
/// \return the captured picture as a Mat type.
Mat GetPicture(VideoCapture cap);

/// Segment the raw picture
/// \param frame        picture to be segmented.
/// \param start_point  range.
/// \param end_point    range.
/// \return picture after segmentation.
Mat Picture_segmentation(Mat frame, int start_point, int end_point);

/// Save the picture for training.
/// \param frame        picture to save
/// \param LandMark     Current LandMark
/// \param LandMarkNum  Current LandMarkNum
/// \param count        Count of Current LandMarkNum
void IMG_save(Mat frame, double * LandMark, int LandMarkNum, int count);


/// First call this function to get the CNN.
/// Then use next function to predict
/// \return The neural network.
Net getCNN();

/// Identify the LandMark
/// \param picture  The picture to identify
/// \param net      The neural network.
/// \param count1   Signature of picture for training.
/// \param count2   Signature of picture for training.
/// \return classification of Landmark
int classification(const Mat &picture,
                   Net net, int count1, int count2);


/// Interface for the main function
/// \param identify_result  The result of the function
/// \param net              The neural network.
/// \param frame            The picture
/// \param LandMark         The landmark to identify
/// \param LandMarkNum      The number of landmark to identify
/// \param count            Signature of picture for training.
/// \return 0 for success, -1 otherwise.
int IMG_identify(double * identify_result, Net net,
                 Mat frame, double * LandMark, int LandMarkNum, int count);

/// This is the  function for camera is disable.
///
/// \\param identify_result The result of the function
/// \param net              Not used
/// \param frame            Not used
/// \param LandMark         The landmark to identify
/// \param LandMarkNum      The number of landmark to identify
/// \param count            Signature of picture for training.
/// \return 0 for success, -1 otherwise.
int IMG_identifyCL(double * identify_result, Net net,
                   Mat frame, double * LandMark, int LandMarkNum, int count);
#endif //SIXGOD_CAMERA_H
