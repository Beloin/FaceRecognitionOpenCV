//
// Created by beloin on 10/06/24.
//

#ifndef FACE_RECOGNITION_FILE_EXISTS_H
#define FACE_RECOGNITION_FILE_EXISTS_H

#include <sys/stat.h>
#include <string>

inline bool valid_file(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

#endif //FACE_RECOGNITION_FILE_EXISTS_H
