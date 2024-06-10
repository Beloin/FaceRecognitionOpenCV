//
// Created by beloin on 09/05/24.
//

#include "SimpleRecognizer.h"
#include "face_models.h"
#include "Recognizer.h"

bool SimpleRecognizer::Equals(Mat &a, Mat &b) {
    SetDetectorPath(detectorPath);

    Mat aFace, bFace;
    bool foundA = FindFaces(a, aFace);
    bool foundB = FindFaces(b, bFace);
    if (!foundA || !foundB) throw std::runtime_error("could not find a face in one of both images"); // or return false

    auto recognizer = Recognizer{recognizerPath};

    Mat aFeature, bFeature;
    recognizer.ExtractFeatures(a, aFace, aFeature);
    recognizer.ExtractFeatures(b, bFace, bFeature);

    auto cosScore = recognizer.CosScore(aFeature, bFeature);
    auto l2Score = recognizer.L2Score(aFeature, bFeature);

    if (cosScore >= cosThreshold && l2Score <= l2Threshold) {
        return true;
    }

    return false;
}

SimpleRecognizer::SimpleRecognizer(std::string &detectorPath, std::string &recognizerPath, float cosThreshold,
                                   float l2Threshold) :
        detectorPath(detectorPath),
        recognizerPath(recognizerPath),
        cosThreshold(cosThreshold),
        l2Threshold(l2Threshold) {}

