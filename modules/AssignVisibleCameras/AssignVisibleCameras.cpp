#include "AssignVisibleCameras.h"
#include "ANNWrapper.h"

 void AsgVisCams::AssignVisCams(PatchReader &readPtch, PlyReader& readPly)
 {
     cout<<"start assigning cameras...."<<endl;
     readPtch.parsePatch();
     readPly.parsePly();

     this->pointsFromPth = readPtch.getPoints();
     this->vertexFromPly = readPly.getVertexes();
     this->facesFromPly  = readPly.getFaces();
     this->connections.resize(this->facesFromPly.size());
     this->vertex_face.resize(this->vertexFromPly.size()+1);

     ANNWrapper ann;
     ann.SetPoints(this->pointsFromPth);

     for(size_t i=0; i<(this->facesFromPly).size(); ++i)
     {
         Point3D p[3];
         p[0] = this->vertexFromPly[(this->facesFromPly)[i].v1];
         p[1] = this->vertexFromPly[(this->facesFromPly)[i].v2];
         p[2] = this->vertexFromPly[(this->facesFromPly)[i].v3];

         Point3D pd;

         pd.x = (p[0].x + p[1].x + p[2].x)/3.0;
         pd.y = (p[0].y + p[1].y + p[2].y)/3.0;
         pd.z = (p[0].z + p[1].z + p[2].z)/3.0;

         double dist2;
         int index;

         ann.FindClosest(pd, &dist2, &index);

         (this->facesFromPly)[i].visible_in= pointsFromPth[index].visible_in;
     }
     cout<<"assigning cameras successfully...."<<endl;
 }

void AsgVisCams::FindGraphConnections()
{
    cout<<"start finding the connection of the graph ..."<<endl;
    for(size_t i=0; i<this->facesFromPly.size(); ++i)
    {
        int v1 = this->facesFromPly[i].v1;
        int v2 = this->facesFromPly[i].v2;
        int v3 = this->facesFromPly[i].v3;

        this->vertex_face[v1].push_back(i);
        this->vertex_face[v2].push_back(i);
        this->vertex_face[v3].push_back(i);
    }

    for(size_t i=0; i<this->facesFromPly.size(); ++i)
    {
        int v1 = this->facesFromPly[i].v1;
        int v2 = this->facesFromPly[i].v2;
        int v3 = this->facesFromPly[i].v3;

        vector <int> shared_faces;
        vector <int>::iterator it, it2;

        shared_faces.insert(shared_faces.end(), this->vertex_face[v1].begin(), this->vertex_face[v1].end());
        shared_faces.insert(shared_faces.end(), this->vertex_face[v2].begin(), this->vertex_face[v2].end());
        shared_faces.insert(shared_faces.end(), this->vertex_face[v3].begin(), this->vertex_face[v3].end());

        sort(shared_faces.begin(), shared_faces.end());
        it2 = unique(shared_faces.begin(), shared_faces.end());

        for(it=shared_faces.begin(); it != it2; it++) {
            if(*it != (int)i) {
                this->connections[i].push_back(*it);
            }
        }
    }
    cout<<"finding the connection of the graph successfully..."<<endl;
}
AsgVisCams::~AsgVisCams()
{
}
