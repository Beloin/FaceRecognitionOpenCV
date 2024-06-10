//
// Created by beloin on 09/05/24.
//

#ifndef FACE_RECOGNITION_SIMPLERECOGNIZER_H
#define FACE_RECOGNITION_SIMPLERECOGNIZER_H

#include "opencv2/opencv.hpp"

using namespace cv;

class SimpleRecognizer {

    std::string detectorPath;
    std::string recognizerPath;

    float cosThreshold;
    float l2Threshold;

public:

    SimpleRecognizer(std::string &detectorPath, std::string &recognizerPath, float cosThreshold = 0.363,
                     float l2Threshold = 1.128);

    bool Equals(Mat &a, Mat &b);
};


#endif //FACE_RECOGNITION_SIMPLERECOGNIZER_H
