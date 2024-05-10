#include <opencv2/opencv.hpp>
#include <csignal>
#include "src/face_models.h"
#include "src/Recognizer.h"

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
    Recognizer recognizer = Recognizer{recognizerPath};


    // Both faces are the same person
    Mat eminem_1 = imread("../data/named/eminem_1.png"); // TODO: Remember to use something more stable, os asks in input
    Mat eminem_2 = imread("../data/named/eminem_2.png");
    Mat randomPerson = imread("../data/named/taylor_1.png");

    // TODO: To make it faster we could create a pipeline that includes lowering image size to add to detector and recognizer
    Mat firstFaces, secondFaces, thirdFaces;
    FindFaces(eminem_1, firstFaces);
    FindFaces(eminem_2, secondFaces);
    FindFaces(randomPerson, thirdFaces);

//    FindAndShow(theRock00);
//    FindAndShow(theRock01);
//    FindAndShow(randomPerson);

    Mat firstFeature, secondFeature, thirdFeature;
    recognizer.ExtractFeatures(eminem_1, firstFaces, firstFeature);
    recognizer.ExtractFeatures(eminem_2, secondFaces, secondFeature);
    recognizer.ExtractFeatures(randomPerson, thirdFaces, thirdFeature);

    double ftosCosFeature = recognizer.CosScore(firstFeature, secondFeature);
    double ftotCosFeature = recognizer.CosScore(firstFeature, thirdFeature);
    double stotCosFeature = recognizer.CosScore(secondFeature, thirdFeature);

    double ftosL2Feature = recognizer.L2Score(firstFeature, secondFeature);
    double ftotL2Feature = recognizer.L2Score(firstFeature, thirdFeature);
    double stotL2Feature = recognizer.L2Score(secondFeature, thirdFeature);

    std::cout << "Cosine Similarity - The higher the similar { x >= " << cosine_similar_thresh << " }" << std::endl;
    std::cout << "\t" << "First to Second { " << ftosCosFeature << " }" << '\n';
    std::cout << "\t" << "First to Third { " << ftotCosFeature << " }" << '\n';
    std::cout << "\t" << "Second to Third { " << stotCosFeature << " }" << '\n';
    std::cout << "NormL2 Distance - The lower the similar { x <= " << l2norm_similar_thresh << " }" << std::endl;
    std::cout << "\t" << "First to Second { " << ftosL2Feature << " }" << '\n';
    std::cout << "\t" << "First to Third { " << ftotL2Feature << " }" << '\n';
    std::cout << "\t" << "Second to Third { " << stotL2Feature << " }" << '\n';
    std::fflush(stdout);

    return 0;
}


