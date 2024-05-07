#include <opencv2/opencv.hpp>
#include <csignal>
#include "src/face_models.h"

using namespace cv;

double cosine_similar_thresh = 0.363;
double l2norm_similar_thresh = 1.128;

int main(int argc, char **argv) {
    char str[100];
    getcwd(str, 99);
    const auto &basicString = std::string(str);

    std::string detectorPath{basicString + "/face_detection_yunet_2023mar.onnx"};
    std::string recognizerPath{basicString + "/face_recognition_sface_2021dec.onnx"};

    SetDetectorPath(detectorPath);
    SetRecognizerPath(recognizerPath);


    // Both faces are the same person
    Mat theRock00 = imread("../data/face_05.png"); // TODO: Remember to use something more stable, os asks in input
    Mat theRock01 = imread("../data/rock_02.jpg");
    Mat randomPerson = imread("../data/face_08.jpg");

    // TODO: To make it faster we could create a pipeline that includes lowering image size to add to detector and recognizer


    Mat firstFaces, secondFaces, thirdFaces;
    FindFaces(theRock00, firstFaces);
    FindFaces(theRock01, secondFaces);
    FindFaces(randomPerson, thirdFaces);

//    FindAndShow(theRock00);
//    FindAndShow(theRock01);
//    FindAndShow(randomPerson);

    Mat firstFeature, secondFeature, thirdFeature;
    ExtractFeatures(theRock00, firstFaces, firstFeature);
    ExtractFeatures(theRock01, secondFaces, secondFeature);
    ExtractFeatures(randomPerson, thirdFaces, thirdFeature);

    double ftosCosFeature = CosScore(firstFeature, secondFeature);
    double ftotCosFeature = CosScore(firstFeature, thirdFeature);
    double stotCosFeature = CosScore(secondFeature, thirdFeature);

    double ftosL2Feature = L2Score(firstFeature, secondFeature);
    double ftotL2Feature = L2Score(firstFeature, thirdFeature);
    double stotL2Feature = L2Score(secondFeature, thirdFeature);

    return 0;
}


