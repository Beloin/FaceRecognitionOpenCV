#include <opencv2/opencv.hpp>
#include <csignal>
#include "src/face_models.h"

using namespace cv;


int main(int argc, char **argv) {
    char str[100];
    getcwd(str, 99);
    const auto &basicString = std::string(str);

    std::string detectorPath{basicString + "/face_detection_yunet_2023mar.onnx"};
    std::string recognizerPath{basicString + "/face_recognition_sface_2021dec.onnx"};

    SetDetectorPath(detectorPath);
    SetRecognizerPath(recognizerPath);

    Mat image = imread("../data/face_05.png"); // TODO: Remember to use something more stable, os asks in input
    Mat faces;

//    FindFaces(image, faces);
    FindAndShow(image);

    return 0;
}


