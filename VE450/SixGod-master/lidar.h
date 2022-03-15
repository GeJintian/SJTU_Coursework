#ifndef SIXGOD_LIDAR_H
#define SIXGOD_LIDAR_H

/// Start the lidar
/// \param device_address  The address of UART port
/// \return 0 for success, -1 otherwise
int StartLidar(const char * device_address);

/// Get the scan data, the function is processed on another thead.
/// \param LidarCloud       The output data
/// \return 0 for success, -1 otherwise
int GetLidar(double* LidarCloud);

/// Fuse the lidar cloud to possible landmarks
/// \param LidarCloud       Raw data from Lidar
/// \param LandMark         Fused Landmarks
/// \param LidarCloudNum    Number of Fused Landmarks
/// \return 0 for success, -1 otherwise
int LandMarkFusion(double* LidarCloud, double* LandMark,int LidarCloudNum);//返回值是LandMark数量
int StopLidar();
#endif //SIXGOD_LIDAR_H
