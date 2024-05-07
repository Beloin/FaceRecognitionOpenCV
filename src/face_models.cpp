//
// Created by beloin on 04/05/24.
//

#include "face_models.h"
#include "opencvutils.h"

static std::string detectorPath;
static std::string recognizerPath;

Ptr<FaceDetectorYN> GetDetector(std::string &path, Size size) {
    auto scoreThreshold = .9F;
    auto nmsThreshold = .3F;
    auto topK = 5000;
    return FaceDetectorYN::create(path, "", size, scoreThreshold, nmsThreshold, topK);
}

Ptr<FaceRecognizerSF> GetRecognizer(std::string &path) {
    return FaceRecognizerSF::create(path, "");
}

void SetDetectorPath(std::string &path) {
    detectorPath = path;
}

void SetRecognizerPath(std::string &path) {
    recognizerPath = path;
}

bool FindFaces(Mat &image, Mat &faces) {
    const Size &sz = image.size();
    auto detector = GetDetector(detectorPath, Size(sz.width, sz.height));

    int status = detector->detect(image, faces);
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

static Recognizer recognizer;

void ExtractFeatures(Mat &image, Mat &faces, Mat &outFeatures) {
    if (recognizer.empty())
        recognizer = GetRecognizer(recognizerPath);

    Mat alignedFace;
    recognizer->alignCrop(image, faces.row(0), alignedFace);
    recognizer->feature(alignedFace, outFeatures);
    outFeatures = outFeatures.clone();
}

double CosScore(Mat &feature01, Mat &feature02) {
    return recognizer->match(feature01, feature02, FaceRecognizerSF::DisType::FR_COSINE);
}

double L2Score(Mat &feature01, Mat &feature02) {
    return recognizer->match(feature01, feature02, FaceRecognizerSF::DisType::FR_NORM_L2);
}