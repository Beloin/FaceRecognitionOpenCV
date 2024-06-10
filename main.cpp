#include <opencv2/opencv.hpp>
#include <csignal>
#include "src/face_models.h"
#include "src/Recognizer.h"
#include "src/SimpleRecognizer.h"
#include "src/utils/file_exists.h"

using namespace cv;

#define cosine_similar_thresh 0.363
#define l2norm_similar_thresh 1.128

int main(int argc, char **argv) {
    char str[100];
    getcwd(str, 99);
    const auto &pwd = std::string(str);

    std::string detectorPath{pwd + "/face_detection_yunet_2023mar.onnx"};
    std::string recognizerPath{pwd + "/face_recognition_sface_2021dec.onnx"};

    auto isValid_00 = valid_file("../data/named/eminem_1.png");
    auto isValid_01 = valid_file("../data/named/eminem_2.png");
    auto isValid_02 = valid_file("../data/named/taylor_1.png");

    if (!(isValid_00 & isValid_01 & isValid_02)) {
        std::cout << "Invalid input";
        exit(1);
    }

    Mat eminem_1 = imread("../data/named/eminem_1.png");
    Mat eminem_2 = imread("../data/named/eminem_2.png");
    Mat randomPerson = imread("../data/named/taylor_1.png");
    auto simpleReco = SimpleRecognizer(detectorPath, recognizerPath, cosine_similar_thresh, l2norm_similar_thresh);

    if (simpleReco.Equals(eminem_1, eminem_2))
        std::cout << "Eminem is indeed Eminem" << std::endl;

    if (!simpleReco.Equals(eminem_1, randomPerson))
        std::cout << "Eminem is indeed not Taylor" << std::endl;


    return 0;
}


