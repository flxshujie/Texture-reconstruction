#include "LoopyBeliefProgation.h"
static DATA_TYPE g_lambda = 10;
LoopyBF::LoopyBF(vector< vector<int> >connections, int num_labels)
{
    this->connections = connections ;
    this->num_labels  = num_labels  ;
}

void LoopyBF::creatLBPGraph(void)
{
    this->nodes.resize(this->connections.size());//the number of the total faces

    for(size_t i=0; i<this->connections.size(); ++i)
    {
        size_t num_neighbours = this->connections[i].size();//the number of neighbor faces for each face
        LBPNode &current = nodes[i];

        current.data_cost.resize(this->num_labels, 0);//the number of the cameras
        current.msg.resize(num_neighbours);
        current.send_to.resize(num_neighbours);

        for(size_t j=0; j<num_neighbours; ++j)
        {
            current.send_to[j].first = -1;
        }

    }

    for(size_t i=0; i<connections.size(); ++i)
    {
        size_t num_neighbours = connections[i].size();
        LBPNode &current = nodes[i];

        for(size_t j=0; j<num_neighbours; ++j)
        {
            int dst = connections[i][j];
            current.msg[j].resize(num_labels, 0);

            int t = -1;

            for(size_t k=0; k<current.send_to.size(); ++k)
            {
                if(current.send_to[k].first == dst)
                {
                    t = k;
                    break;
                }
            }

            for(int k=nodes[dst].send_to.size()-1; k>=0; --k)
            {
                if(k==t)
                    continue;
                if(nodes[dst].send_to[k].first == -1)
                {
                    nodes[dst].send_to[k] = pair<int,int>(i,j);
                    break;
                }
            }
        }
    }
}

DATA_TYPE LoopyBF::smoothCost(int i, int j)
{
    if(i==j)
    {
        return 0;
    }
    return g_lambda;
}


