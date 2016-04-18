#ifndef ASSIGNVISIBLECAMERAS_H
#define ASSIGNVISIBLECAMERAS_H
#include <string>
#include <vector>
#include "Face.h"
#include "Point.h"
#include "PatchBase.h"
#include "PlyBase.h"

using namespace std;
using namespace cv;

class AsgVisCams
{
    public:
        /**
         *@brief construct,initial the directory.I do not how to write this function
         */
        AsgVisCams(){ }
        /**
         *@brief deconstruct.
         */
        virtual ~AsgVisCams();
        /**
         *@brief get the value of pointsFromPth.
         */
        inline vector<Point3D> getPointsFromPth(void)
        {
            return this->pointsFromPth;
        }
        /**
         *@brief get the value of vertexFromPly.
         */
        inline vector<Point3D> getVertexFromPly(void)
        {
            return this->vertexFromPly;
        }
         /**
         *@brief get the value of facesFromPly.
         */
        inline vector<Face> getFacesFromPly(void)
        {
            return this->facesFromPly;
        }

        inline vector< vector<int> > getConnections(void)
        {
            return this->connections;
        }
        inline vector < vector <int> > getVertex_face(void)
        {
            return this->vertex_face;
        }
        void AssignVisCams(PatchReader&, PlyReader& );
        void FindGraphConnections();
    private:
         vector<Point3D> pointsFromPth;
         vector<Point3D> vertexFromPly;
         vector<Face>    facesFromPly ;
         vector < vector<int> > connections;
         vector < vector <int> > vertex_face;
};
#endif // ASSIGNVISIBLECAMERAS_H
