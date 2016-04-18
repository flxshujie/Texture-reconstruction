#ifndef LOOPYBELIEFPROGATION_H
#define LOOPYBELIEFPROGATION_H
#include "../../io/LBPNode.h"
/**
*@belief This class could find a best label for each node (face)
*/

class LoopyBF
{
    public:
    /**\brief
      * \param connections: the outer size of the vector is the number of the faces, the inner size 0f the vector is the number of the face's
                            neighbors.
      * \param num_labels : the number of the cameras.
      * \param nodes      : all nodes in the graph.
      *
      */
        LoopyBF(vector< vector<int> > connections, int num_labels, vector<LBPNode> nodes);
    /** \brief get functions
      */
        void creatLBPGraph(void);
        DATA_TYPE smoothCost(int i, int j);
        inline int getNumLabels(void){return this->num_labels;}
        inline vector<LBPNode> getNodes(void){return this->nodes;}
        inline vector<vector<int>> getConnections(void){return this->connections;}
    private:

        vector< vector<int> > connections;
        int num_labels;
        vector<LBPNode> nodes;


};
#endif
