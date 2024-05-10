//
// Created by beloin on 09/05/24.
//

#include "Recognizer.h"

Recognizer::Recognizer(std::string &path) {
    recognizer = FaceRecognizerSF::create(path, "");
}

void Recognizer::ExtractFeatures(Mat &image, Mat &faces, Mat &outFeatures) {
    Mat alignedFace;
    recognizer->alignCrop(image, faces.row(0), alignedFace);
    recognizer->feature(alignedFace, outFeatures);
    outFeatures = outFeatures.clone();
}

double Recognizer::CosScore(Mat &feature01, Mat &feature02) {
    return recognizer->match(feature01, feature02, FaceRecognizerSF::DisType::FR_COSINE);
}

double Recognizer::L2Score(Mat &feature01, Mat &feature02) {
    return recognizer->match(feature01, feature02, FaceRecognizerSF::DisType::FR_NORM_L2);
}
