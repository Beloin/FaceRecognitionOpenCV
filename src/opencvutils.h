//
// Created by beloin on 06/05/24.
//

#ifndef FACE_RECOGNITION_OPENCVUTILS_H
#define FACE_RECOGNITION_OPENCVUTILS_H


#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void visualize(Mat &input, int frame, Mat &faces, double fps,
                      int thickness = 2) {
    std::string fpsString = cv::format("FPS : %.2f", (float)fps);
    if (frame >= 0)
        cout << "Frame " << frame << ", ";
    cout << "FPS: " << fpsString << endl;
    for (int i = 0; i < faces.rows; i++) {
        // Print results
        cout << "Face " << i << ", top-left coordinates: (" << faces.at<float>(i, 0)
             << ", " << faces.at<float>(i, 1) << "), "
             << "box width: " << faces.at<float>(i, 2)
             << ", box height: " << faces.at<float>(i, 3) << ", "
             << "score: " << cv::format("%.2f", faces.at<float>(i, 14)) << endl;

        // Draw bounding box
        rectangle(input,
                  Rect2i(int(faces.at<float>(i, 0)), int(faces.at<float>(i, 1)),
                         int(faces.at<float>(i, 2)), int(faces.at<float>(i, 3))),
                  Scalar(0, 255, 0), thickness);
        // Draw landmarks
        circle(input,
               Point2i(int(faces.at<float>(i, 4)), int(faces.at<float>(i, 5))), 2,
               Scalar(255, 0, 0), thickness);
        circle(input,
               Point2i(int(faces.at<float>(i, 6)), int(faces.at<float>(i, 7))), 2,
               Scalar(0, 0, 255), thickness);
        circle(input,
               Point2i(int(faces.at<float>(i, 8)), int(faces.at<float>(i, 9))), 2,
               Scalar(0, 255, 0), thickness);
        circle(input,
               Point2i(int(faces.at<float>(i, 10)), int(faces.at<float>(i, 11))), 2,
               Scalar(255, 0, 255), thickness);
        circle(input,
               Point2i(int(faces.at<float>(i, 12)), int(faces.at<float>(i, 13))), 2,
               Scalar(0, 255, 255), thickness);
    }
    putText(input, fpsString, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(0, 255, 0), 2);


    if (!input.data) {
        printf("No image data \n");
        return;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", input);

    while(waitKey(0) != 'q');
}

#endif //FACE_RECOGNITION_OPENCVUTILS_H
