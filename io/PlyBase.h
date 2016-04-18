#ifndef PLYBASE_H
#define PLYBASE_H
#include <fstream>
#include <string>
#include <vector>
#include "Point.h"
#include "Face.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class PlyReader
{
    public:
        PlyReader(const string&);
        virtual ~PlyReader();
        /**
         *@brief parse the .ply
         */
        virtual void parsePly(void);
        /**
         *@brief parse the meta data (header) of the .ply
         */
        void parseMeta(ifstream& fs);
        void parsePoints(ifstream& fs);
        void parseFaces(ifstream& fs);

        void NormalFrom3Vertex(const Point3D &v1, const Point3D &v2, const Point3D &v3, float &nx, float &ny, float &nz);

        inline vector<Point3D> getVertexes()
        {
            return this->vertexes;
        }

        inline vector<Face> getFaces()
        {
            return this->faces;
        }

    private:
        vector<Point3D> vertexes;
        vector<Face> faces;
        /**
         *@brief the directory of the ply file
         */
        string mPlyDir;

};
#endif
