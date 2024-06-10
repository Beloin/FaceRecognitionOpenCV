//
// Created by beloin on 04/05/24.
//

#include "face_models.h"
#include "opencvutils.h"

static std::string detectorPath;

Ptr<FaceDetectorYN> GetDetector(std::string &path, Size size) {
    auto scoreThreshold = .9F;
    auto nmsThreshold = .3F;
    auto topK = 5000;
    return FaceDetectorYN::create(path, "", size, scoreThreshold, nmsThreshold, topK);
}

void SetDetectorPath(std::string &path) {
    detectorPath = path;
}

bool FindFaces(Mat &image, Mat &faces) {
    const Size &sz = image.size();
    auto detector = GetDetector(detectorPath, Size(sz.width, sz.height));

    detector->detect(image, faces);
    if (faces.rows < 1) return false;

    return true;
}

void FindAndShow(Mat &image) {
    Mat faces;
    TickMeter tm;
    tm.start();
    auto found = FindFaces(image, faces);
    if (!found) {
        cout << "could not find any face" << endl;
        return;
    }
    tm.stop();

    visualize(image, -1, faces, tm.getFPS());
}

