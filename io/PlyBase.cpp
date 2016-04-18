#include "PlyBase.h"

PlyReader::PlyReader(const string& path)
{
    this->mPlyDir = path ;
}

void PlyReader::parsePly(void)
{
    std::cout<<"1.Start to parse PLY file..."<<std::endl;
    try
    {
        string PlyName = this->mPlyDir + "/mesh.ply" ;
        ifstream ifs(PlyName.c_str());
        if(ifs.is_open())
        {
            parseMeta(ifs);
            parsePoints(ifs);
            parseFaces(ifs);
        }
        else
        {
            cout<<"PLY file failed to open"<<endl;
        }
        ifs.close();
    }
    catch(exception e)
	{
		cerr<<e.what()<<endl;
		exit(1);
	}
	std::cout<<"2.Parse PLY file successfully!"<<std::endl;
}

 void PlyReader::parseMeta(ifstream& fs)
 {
    std::cout<<"1.Start to parse PLY file meta..."<<std::endl;
    try
    {
        char head[1024];
        string token ;

        fs.getline(head, sizeof(head));
        stringstream str(head);
        str>>token ;

        if(token != "ply")
        {
            cerr << "Not a PLY format" << endl;
            exit(1);
        }

        size_t num_vertex, num_face;

        while(fs.getline(head, sizeof(head)))
        {
           str.str(head);
           str.clear();
           str>>token;

           if(token == "element")
           {
               str>>token;
               if(token == "vertex")
               {
                   str>>num_vertex;
               }
               else if(token == "face")
               {
                   str>>num_face;
               }
           }
           else if(token == "end_header")
                break;
        }
        this->vertexes.resize(num_vertex);
        this->faces.resize(num_face);
    }catch(exception e)
    {
      cerr<<e.what()<<endl;
      exit(1);
    }
    std::cout<<"2.Parse PLY file meta successfully!"<<std::endl;
}

void PlyReader::parsePoints(ifstream& fs)
{
    std::cout<<"1.Start to parse PLY file Points..."<<std::endl;
    try
    {
        char line[1024];
        string token;
        stringstream str;

        for(int i=0; i<this->vertexes.size(); ++i)
        {
            fs.getline(line, sizeof(line));
            str.str(line);
            str.clear();

            str>>this->vertexes[i].x;
            str>>this->vertexes[i].y;
            str>>this->vertexes[i].z;
        }


    }catch(exception e)
    {
      cerr<<e.what()<<endl;
      exit(1);
    }
    std::cout<<"2.Parse PLY file Points successfully!"<<std::endl;
}

void PlyReader::parseFaces(ifstream& fs)
{
    std::cout<<"1.Start to parse PLY file Faces..."<<std::endl;
    try
    {
        char line[1024];
        string token;
        stringstream str;

        for(int i=0; i<this->faces.size(); ++i)
        {
            fs.getline(line, sizeof(line));
            str.str(line);
            str.clear();
            int n;

            str>>n;
            str>>faces[i].v1;
            str>>faces[i].v2;
            str>>faces[i].v3;

            faces[i].x = (vertexes[faces[i].v1].x + vertexes[faces[i].v2].x + vertexes[faces[i].v3].x)/3;
            faces[i].y = (vertexes[faces[i].v1].y + vertexes[faces[i].v2].y + vertexes[faces[i].v3].y)/3;
            faces[i].z = (vertexes[faces[i].v1].z + vertexes[faces[i].v2].z + vertexes[faces[i].v3].z)/3;

            NormalFrom3Vertex(vertexes[faces[i].v1], vertexes[faces[i].v2], vertexes[faces[i].v3], faces[i].nx, faces[i].ny, faces[i].nz);
        }

    }catch(exception e)
    {
      cerr<<e.what()<<endl;
      exit(1);
    }
    std::cout<<"2.Parse PLY file Faces successfully!"<<std::endl;
}
void PlyReader::NormalFrom3Vertex(const Point3D &v1, const Point3D &v2, const Point3D &v3, float &nx, float &ny, float &nz)
{
    float x1 = v2.x - v1.x;
    float y1 = v2.y - v1.y;
    float z1 = v2.z - v1.z;

    float x2 = v3.x - v2.x;
    float y2 = v3.y - v2.y;
    float z2 = v3.z - v2.z;

    float mag1 = sqrt(x1*x1 + y1*y1 + z1*z1);
    float mag2 = sqrt(x2*x2 + y2*y2 + z2*z2);

    x1 /= mag1;
    y1 /= mag1;
    z1 /= mag1;

    x2 /= mag2;
    y2 /= mag2;
    z2 /= mag2;

    nx = y1*z2 - z1*y2;
    ny = z1*x2 - x1*z2;
    nz = x1*y2 - y1*x2;
}

PlyReader::~PlyReader()
{

}
