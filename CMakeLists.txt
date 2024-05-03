cmake_minimum_required(VERSION 3.1...3.29)


project(
  face_recognition
  VERSION 1.0
  LANGUAGES CXX
)

add_executable(face_recognition main.cpp)

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(face_recognition ${OpenCV_LIBRARIES})
