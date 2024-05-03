#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }

  Mat image;
  image = imread(argv[1], IMREAD_COLOR);

  if (!image.data) {
    printf("No image data \n");
    return -1;
  }
  namedWindow("Display Image", WINDOW_AUTOSIZE);
  imshow("Display Image", image);

  while(waitKey(0) != 'q');

  return 0;
}
