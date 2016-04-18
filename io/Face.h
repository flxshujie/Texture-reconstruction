#ifndef FACE_H
#define FACE_H
#include<vector>
using namespace std;
class Face
{
    public:
        /**
         * @brief get and set the image number
         */
        void setImageNum(int idx);
         int  getImageNum() ;
        /**
         * @brief the id of the point in the space. v1,v2,v3 namely the vertices of the triangle.
         */
        unsigned int v1, v2, v3;
        /**
         * @brief the centre of the triangle
         */
        float x, y, z;
        /**
         * @brief the normal of the triangle
         */
        float nx, ny, nz;
        /**
         * @brief texture UV coords
         */
        float u[3], v[4];
        /**
         * @brief the id of the image which could see this face(after optimizing the labels,i.e.. the best label)
         */
        int imageNum;
        /**
         * @brief the id of the images which could see the face
         */
        vector <int> visible_in;
};
#endif // FACE_H
