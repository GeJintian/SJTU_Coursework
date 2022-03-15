# Project SixGod
## Introduction
Project SixGod is a project for the VE/VM450-Major Design Experience at Shanghai Jiaotong University - University of Michigan Joint Institute.
 This project build a complete operating and localization system for Automated Guided Vehicle with support of velocity and steering angle control, picture taking, lidar support and 
 other useful functions.
## Contributors
Xia Binyu, Ge Jintian, Qian Xinyu, Wu Jiahao, Wang Jiaqi
## Installation Guide
### Material List
1. Computation
   - Odroid XU4
   - DJI Robomaster Development Board A
2. Communication
   - USB to UART Serial Port Module
3. Sensoring
   - Yahboom Raspberry Pi camera 1080p 120fps
   - Slamtec RPLIDAR-A2
   - Bashing! Battery 6500mAh 60C 11.1V 3S xt90
   - 5V Voltage Transformer


## Use Guide
### Basic Use
    cd SixGod
    cmake .
    make
    ./SixGod
    ./Stop
### mm.sh
File [mm.sh](./mm.sh) provide a easy way to collect the new photo and
 build and execute the code. You may refer to it and modify the code
 with your system.
 **Notice:** mm.sh does not include cmake process, you at least run cmake by yourself
 once.
## Code File Structure

## Q&A
## README TODO
1. Write TODO
2. Write Installation Guide
3. List of Materials
4. Code File Description
5. Q&A
## TODO

## Other Git Pakage We Used
- lidar: https://github.com/Slamtec/rplidar_ros
- openCV: https://github.com/opencv/opencv
