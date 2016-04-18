#include "Camera.h"
#include "BundlerBase.h"
#include <stdexcept>


Bundler::Bundler(string &dir)
:mNumImg(0)
{
    this->mBundlerDir = dir ;
}

void
Bundler::readData(void)
{
    // list.txt file
	parseImgList();

	// bundler.out file
	parseBundlerOut();
}

Camera const& Bundler::getCam(size_t idx) const
{
    return mCameras[idx];
}

Camera const* Bundler::getCamPtr(size_t idx) const
{
    return &(mCameras[idx]);
}


void Bundler::parseCamera(std::ifstream& fs)
{
    std::cout<<"1.Start to parse Bundler Camera..."<<std::endl;
    mCameras.resize(mNumImg);
    for(int i=0; i<mNumImg; ++i)
    {
        Camera camera;
        camera.setValid();
        float tmp[15];
        if(fs != NULL)
        {
            for(int j=0; j<15; ++j)
                fs>>tmp[j];
        }
        Mat matExt(3, 4, CV_32FC1);
        Mat matInt(3, 3, CV_32FC1);

        Mat Img = imread(mImgNames[i]);
        Point2f p2;
        p2.x = Img.cols / 2.f - 0.5 ;
        p2.y = Img.rows / 2.f - 0.5 ;
        // fill Internal matrix

        matInt.at<float>(0,0) = tmp[0]; matInt.at<float>(0,1) = 0.0   ; matInt.at<float>(0,2) = p2.x ;
        matInt.at<float>(1,0) = 0.0   ; matInt.at<float>(1,1) = tmp[0]; matInt.at<float>(1,2) = p2.y ;
        matInt.at<float>(2,0) = 0.0   ; matInt.at<float>(2,1) = 0.0   ; matInt.at<float>(2,2) = 1.0  ;

        matExt.at<float>(0,0) =  tmp[3]; matExt.at<float>(0,1) =  tmp[4] ; matExt.at<float>(0,2) =  tmp[5] ;
        matExt.at<float>(1,0) = -tmp[6]; matExt.at<float>(1,1) = -tmp[7] ; matExt.at<float>(1,2) = -tmp[8] ;
        matExt.at<float>(2,0) = -tmp[9]; matExt.at<float>(2,1) = -tmp[10]; matExt.at<float>(2,2) = -tmp[11];

        matExt.at<float>(0,3) = tmp[12];matExt.at<float>(1,3)  = -tmp[13]; matExt.at<float>(2,3) = -tmp[14];

        camera.setExtMat(matExt);
        camera.setIntMat(matInt);
        mCameras.push_back(camera);
    }
    std::cout<<"2.Parse Bundler Camera successfully!..."<<std::endl;
}

void Bundler::parseImgList(void)
{
    std::cout<<"1.Start to parse img.txt file..."<<std::endl;
    try
    {
        string imgLName = mBundlerDir + "/imgs.txt";
        ifstream f2(imgLName.c_str());
        mImgNames.clear();
        if(f2.is_open())
        {
            while(!f2.eof())
            {
                string imgDir;
                f2>>imgDir;
                if(!imgDir.empty())
                    mImgNames.push_back(imgDir);
            }
            mNumImg = mImgNames.size();
        }
        f2.close();
    }
    catch(exception e)
    {
        cerr<<e.what()<<endl;
		exit(0);
    }
    cout<<"2.parse img.txt successfully"<<endl;
}

void Bundler::parseMeta(std::ifstream& fs)
{
    std::cout<<"1. Parsing Bundler meta ..."<<std::endl;
    try
    {
        char head[256]="";
        fs.getline(head,sizeof(head));//head
        if(fs.eof()||head[17]!='3')
            cout<<"The function parseMeta() encounters wrong meta structure!";
        fs>>mNumImg;
    }
    catch(exception e)
    {
        cerr<<e.what()<<endl;
        exit(1);
    }
    std::cout<<"2.Parsing Bundler meta done..."<<std::endl;
}

void Bundler::parseBundlerOut(void)
{
    std::cout<<"1.Start to parse bundler.out file..."<<std::endl;
    try
    {
        std::string bundlerName = mBundlerDir + "/bundle.rd.out";
        ifstream f1(bundlerName.c_str());
        if ( f1.is_open())
        {
            parseMeta(f1);
            parseCamera(f1);
        }
        else
            cout<<"File open failed!";
        f1.close();
    }
    catch (exception e)
	{
		cerr<<e.what()<<endl;
		//getchar();
		exit(1);
	}
	std::cout<<"2.Parse bundler.out file successfully!"<<std::endl;
}

Bundler::~Bundler()
{

}
