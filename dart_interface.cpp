//
// Created by beloin on 10/06/24.
//

#include <csignal>
#include "src/SimpleRecognizer.h"
#include "src/utils/file_exists.h"
#include "./dart_interface.h"

#define COS_T 0.363
#define L2_T  1.128

bool are_equalcpp(const char *p1, const char *p2);

std::string get_pwd();

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((visibility("default")))
__attribute__((used))
int are_equal(char *p1, char *p2) {
    return are_equalcpp(p1, p2);
}

#ifdef __cplusplus
}
#endif

bool are_equalcpp(const char *p1, const char *p2) {
    std::string p1str{p1};
    std::string p2str{p2};

    auto pwd = get_pwd();
    std::string detectorPath{pwd + "/face_detection_yunet_2023mar.onnx"};
    std::string recognizerPath{pwd + "/face_recognition_sface_2021dec.onnx"};

    auto isValid_00 = valid_file(p1str);
    auto isValid_01 = valid_file(p2str);

    if (!(isValid_00 & isValid_01)) {
        fprintf(stderr, "could not read one of files: %s and %s", p1, p2);
        exit(1);
    }

    Mat p1_mat = imread(p1str);
    Mat p2_mat = imread(p2str);

    auto reco = SimpleRecognizer{detectorPath, recognizerPath, COS_T, L2_T};

    return reco.Equals(p1_mat, p2_mat);
}

std::string get_pwd() {
    char str[100];
    getcwd(str, 99);
    return str;
}