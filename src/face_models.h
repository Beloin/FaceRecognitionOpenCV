//
// Created by beloin on 04/05/24.
//

#ifndef FACE_RECOGNITION_FACE_MODELS_H
#define FACE_RECOGNITION_FACE_MODELS_H

#include <opencv2/opencv.hpp>

using namespace cv;

typedef Ptr<FaceDetectorYN> Detector;

Detector GetDetector(std::string &path, Size size);

void SetDetectorPath(std::string &path);

bool FindFaces(Mat &image, Mat &faces);

void FindAndShow(Mat &image);


#endif //FACE_RECOGNITION_FACE_MODELS_H


