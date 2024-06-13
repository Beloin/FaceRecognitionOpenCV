FROM ubuntu:18.04 as OPENCV_BUILD_STAGE

# Install requirements
RUN apt-get update && apt-get install -y \
    # OpenCV dependencies
    build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev \
    python3-dev python3-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev \
    libcanberra-gtk-module libcanberra-gtk3-module

# Clone, build and install OpenCV
RUN git clone https://github.com/opencv/opencv.git && \
    cd /opencv && mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j"$(nproc)" && \
    make install && \
    rm -rf /opencv

RUN ls /usr/

FROM ubuntu:18.04 as CXX_BUILD_STAGE
WORKDIR /app

RUN apt-get update && apt-get install -y build-essential cmake git make

COPY --from=OPENCV_BUILD_STAGE /usr/local/include/opencv4/opencv2 /usr/local/include/opencv2
COPY --from=OPENCV_BUILD_STAGE /usr/local/bin /usr/local/bin
COPY --from=OPENCV_BUILD_STAGE /usr/local/lib /usr/local/lib
COPY --from=OPENCV_BUILD_STAGE /usr/lib /usr/lib
COPY --from=OPENCV_BUILD_STAGE /lib /lib

COPY . .

RUN pwd
RUN ls
RUN rm -rf build
RUN bash -c "cmake -S . -Bbuild"

WORKDIR build
RUN pwd
RUN ls
RUN bash -c "make"

RUN ls

FROM python:3.10-slim-buster

WORKDIR /app

COPY req.txt req.txt
RUN pip3 install -r req.txt

COPY main_server.py main_server.py

COPY --from=OPENCV_BUILD_STAGE /usr/local/include/opencv4/opencv2 /usr/local/include/opencv2
COPY --from=OPENCV_BUILD_STAGE /usr/local/bin /usr/local/bin
COPY --from=OPENCV_BUILD_STAGE /usr/local/lib /usr/local/lib
COPY --from=OPENCV_BUILD_STAGE /usr/lib /usr/lib
COPY --from=OPENCV_BUILD_STAGE /lib /lib

COPY --from=CXX_BUILD_STAGE /app/build/libdart_interface.so /app/libdart_interface.so

EXPOSE 5000
ENTRYPOINT [ "python3", "-m" , "flask", "--app", "main_server", "run", "--host=0.0.0.0"]