#ifndef LBPNODE_H
#define LBPNODE_H

typedef double DATA_TYPE;

class LBPNode
{
    public:
        vector<DATA_TYPE> data_cost ;
        vector< vector<DATA_TYPE> msg ;
        vector< pair<int, int> > send_to;
        int best_label;
};
#endif
