#ifndef POINT_H
#define POINT_H
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
class Point3D: public cv::Point3f
{
    public:
        vector<int> visible_in;
};
#endif
