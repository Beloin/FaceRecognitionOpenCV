cmake_minimum_required(VERSION 3.1...3.29)


project(
  face_recognition
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(face_recognition main.cpp src/face_models.cpp src/face_models.h src/opencvutils.h src/Recognizer.cpp src/Recognizer.h)

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(face_recognition ${OpenCV_LIBRARIES})

configure_file(./face_detection_yunet_2023mar.onnx face_detection_yunet_2023mar.onnx COPYONLY)
configure_file(./face_recognition_sface_2021dec.onnx face_recognition_sface_2021dec.onnx COPYONLY)

