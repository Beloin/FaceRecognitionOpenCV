//
// Created by beloin on 09/05/24.
//

#ifndef FACE_RECOGNITION_RECOGNIZER_H
#define FACE_RECOGNITION_RECOGNIZER_H

#include <opencv2/opencv.hpp>

using namespace cv;

typedef Ptr<FaceDetectorYN> Detector;
typedef Ptr<FaceRecognizerSF> FaceRecognizer;

class Recognizer {
private:
    FaceRecognizer recognizer;


public:
    explicit Recognizer(std::string &path);

    /**
     * Accepts only if faces is only one row
     * @param image
     * @param faces
     * @param outFeatures
     */
    void ExtractFeatures(Mat &image, Mat &faces, Mat &outFeatures);

    double CosScore(Mat &feature01, Mat &feature02);

    double L2Score(Mat &feature01, Mat &feature02);
};


#endif //FACE_RECOGNITION_RECOGNIZER_H
