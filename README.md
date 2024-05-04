# Face Recognition

## Instalation

1. `sudo pacman -S opencv`

## Pipeline

1. Video acquisition
2. Face Detection
3. Feature Extraction
3. Face Recognition

![Pipeline](./pipeline.jpg)

## Face Detection

https://www.geeksforgeeks.org/opencv-c-program-face-detection/

## Face Recognition

https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html


## References

1. [Reference Article](https://www.mdpi.com/1424-8220/20/2/342) 
2. [OpenCV Site for face Recognition](https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html)
3. [Face Detection](https://www.geeksforgeeks.org/opencv-c-program-face-detection/)

# Usage of example gaved by OpenCV itself:
Compile with:

```bash
g++ face_reco_example.cpp -L /usr/lib64/libopencv_*  -I/usr/include/opencv4  -o face_reco_example
```

Run example
```
./face_reco_example --i1=./data/rock_02.jpg --i2=./data/rock_03.jpg --fd=./face_detection_yunet_2023mar.onnx --fr=./face_recognition_sface_2021dec.onnx
```
