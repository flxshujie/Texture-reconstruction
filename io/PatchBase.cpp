#include<iostream>
#include "PatchBase.h"

PatchReader::PatchReader(string& path)
{
    this->mPatchDir = path ;
}

void PatchReader::parsePatch(void)
{
    cout<<"start parse Patch file..."<<endl;
    try
    {
        string patchName = this->mPatchDir + "/option-0000.patch" ;
        ifstream ifs(patchName.c_str());
        if( ifs.is_open() )
        {
            parseMeta(ifs);
            parsePoints(ifs);
        }
        else
        {
            cout<<"could not open this file"<<endl;
            exit(0);
        }
    }catch(exception e)
	{
		cerr<<e.what()<<endl;
		exit(1);
	}
	std::cout<<"Parse PATCH file successfully!"<<std::endl;
}

void PatchReader::parseMeta(ifstream& ifs)
{
    cout<<"Parse patch file Meta ..."<<endl;
    try
    {
        char line[1024];
        ifs.getline(line, sizeof(line));
        stringstream str(line);
        string token;
        int num_pts;
        str>>token;

        if(token != "PATCHES")
        {
            cout<<"this is not a PATCHES file"<<endl;
            exit(0);
        }

        ifs.getline(line, sizeof(line));
        str.str(line);
        str.clear();
        str>>num_pts;

        this->points.resize(num_pts);

    }catch(exception e)
	{
		cerr<<e.what()<<endl;
		exit(1);
	}
	std::cout<<"Parse PATCH file Meta successfully!"<<std::endl;
}

void PatchReader::parsePoints(ifstream& ifs)
{
    cout<<"Parse patch file points ..."<<endl;
    try
    {
        char line[1024];
        string token;
        stringstream str;
        float not_used;

        for(int i=0; i<points.size(); i++)
        {
            Point3D &pt = points[i];
            int num;
            ifs.getline(line, sizeof(line)) ;//PATCH

            ifs.getline(line, sizeof(line)) ;//position
            str.str(line);
            str.clear();
            str>>pt.x;
            str>>pt.y;
            str>>pt.z;

            ifs.getline(line, sizeof(line)) ;//normal
            str.str(line);
            str.clear();
            str>>not_used;
            str>>not_used;
            str>>not_used;

            ifs.getline(line, sizeof(line));
            ifs.getline(line, sizeof(line));//num images visible in
            str.str(line);
            str.clear();
            str>>num;

            assert(num > 0);

            ifs.getline(line, sizeof(line));//image index
            str.str(line);
            str.clear();

            for(int j=0; j<num; ++j)
            {
                int idx;
                str>>idx;
                pt.visible_in.push_back(idx);
            }

            ifs.getline(line, sizeof(line));//possible visible in
            str.str(line);
            str.clear();
            str>>num;

            ifs.getline(line, sizeof(line));//image index
            str.str(line);
            str.clear();

            for(int j=0; j<num; ++j)
            {
                int idx;
                str>>idx;
                pt.visible_in.push_back(idx);
            }

            ifs.getline(line, sizeof(line)); // blank line

            if(ifs.eof())
            {
                 cerr << "LoadPMVSPatch(): Premature end of file" << endl;
                 exit(0);
            }
        }

    }catch(exception e)
	{
		cerr<<e.what()<<endl;
		exit(1);
	}
	std::cout<<"Parse PATCH file points successfully!"<<std::endl;
}
