//
// Created by beloin on 04/05/24.
//

#ifndef FACE_RECOGNITION_FACE_MODELS_H
#define FACE_RECOGNITION_FACE_MODELS_H

#include <opencv2/opencv.hpp>

using namespace cv;

typedef Ptr<FaceDetectorYN> Detector;
typedef Ptr<FaceRecognizerSF> Recognizer;

Detector GetDetector(std::string &path, Size size);

Recognizer GetRecognizer(std::string &path);

void SetDetectorPath(std::string &path);

void SetRecognizerPath(std::string &path);

bool FindFaces(Mat &image, Mat &faces);

void FindAndShow(Mat &image);

/**
 * Accepts only if faces is only one row
 * @param image
 * @param faces
 * @param outFeatures
 */
void ExtractFeatures(Mat &image, Mat &faces, Mat &outFeatures);

double CosScore(Mat &feature01, Mat &feature02);

double L2Score(Mat &feature01, Mat &feature02);

#endif //FACE_RECOGNITION_FACE_MODELS_H


