#ifndef PATCHBASE_H
#define PATCHBASE_H
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "PlyBase.h"
using namespace std;
using namespace cv;

class Point3D;

class PatchReader
{
    public:

        inline vector<Point3D> getPoints()
        {
            return this->points;
        }

        PatchReader(string&);
        void parsePatch(void);
        void parseMeta(ifstream&);
        void parsePoints(ifstream&);

    private:
        vector<Point3D> points;
        string mPatchDir;
};
#endif // PATCHBASE_H
