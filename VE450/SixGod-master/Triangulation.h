//
// Created by 69009 on 2020/11/4.
//

#ifndef SIXGOD_TRIANGULATION_H
#define SIXGOD_TRIANGULATION_H

#include "main.h"
#include "Map.h"
struct Circle{
    double x=0;//x coordinate of circle
    double y=0;//y coordinate of circle
    double r=0;//distance from AGV
    double angle = 0;//angle between AGV and circle
};

/// Find the closest Landmark of our
/// measurement based on the map.
/// In this function, we will use information
/// to return a point in the map
/// \param Map              The given map
/// \param classification   The classification of the measurement (From Camera)
/// \param angle            The angle of obstacle
/// \param dis              The distance of obstacle
/// \param CurrentState     The current state of our AGV
/// \return                 The found circle
/// \throw  -1 for a measurement that cannot fit in any landmark.
Circle get_circle(Map_t * Map, int classification, double angle,
                  double dis, GodState_t &CurrentState);


///In this function, we will read information from
/// LandMarks and find corresponding points in map.
/// \param Map              The given map
/// \param cir_list         Landmark to find
/// \param LandMarks        Measurements from lidar
/// \param NumLandMark      Measuremetns Number
/// \param CurrentState     Current State of AGV
/// \return                 Number of Found Landmarks
int process_circle(Map_t * Map, Circle * cir_list, double * LandMarks,
                   int NumLandMark, GodState_t &CurrentState);

/// If only two landmarks, call this function. Return the position of vehicle
/// \param Map              The given map
/// \param position         The position of AGV to estimate
/// \param x                The position of AGV provided from thread 1
/// \param y                The position of AGV provided from thread 1
/// \param cir_list         Identified Landmarks
/// \param NumLandMark      Number of Identified Landmarks
void get_position2(Map_t * Map, double * position, double x,
                   double y, Circle * cir_list, int NumLandMark);

/// If at least three landmarks, call this function.
/// Return the position of vehicle
/// \param Map              The given map
/// \param position         The position of AGV to estimate
/// \param cir_list         Identified Landmarks
/// \param NumLandMark      Number of Identified Landmarks
void get_position3(Map_t * Map, double * position,
                   Circle * cir_list, int NumLandMark);


/// Interface for the main function.
/// \param position         The position to output
/// \param LandMark         The measurements from lidar
/// \param LandMarkNum      The number measurements from lidar
/// \param Map              The given map
/// \param MapNum           The number of map
/// \param CurrentState     The state of AGV when lidar is ready
void StaticFusion(double * position, double * LandMark,
                  int LandMarkNum, Map_t *Map, int MapNum, GodState_t &CurrentState);

#endif //SIXGOD_TRIANGULATION_H
