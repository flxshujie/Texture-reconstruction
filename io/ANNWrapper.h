#ifndef ANNWRAPPER_H
#define ANNWRAPPER_H
#include "Point.h"
#include <vector>
#include <ANN.h>
using namespace std;

class ANNWrapper
{
    public:
        ANNWrapper();
        ~ANNWrapper();
        void Free();
        void SetPoints(const std::vector <Point3D> &P);
        void FindClosest(const Point3D &P, double *sq_distance, int *index);
        void SetResults(int a);
    private:
        int			    m_npts;					// actual number of data points
        ANNpointArray	m_data_pts;				// data points
        ANNpoint		m_query_pt;				// query point
        ANNidxArray		m_nnidx;					// near neighbor indices
        ANNdistArray	m_dists;					// near neighbor distances
        ANNkd_tree*		m_kdtree;					// search structure

        static const int dim = 3;
        int m_k;
        double m_eps;
        bool m_anything_to_free;
};
#endif
