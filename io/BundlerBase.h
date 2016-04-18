#ifndef BUNDLERBASE_H
#define BUNDLERBASE_H
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
// ---------------------------------------------------------------
// basic definitions

/**
 * @brief This structure is NOT for the end user. It is based on the bundler output. The class Bundler should convert this structure to the camera class which is for the sake of end user (i.e. other classes).
 */

class Camera;

class Bundler
{
    public:
        Bundler(std::string&);
        virtual ~Bundler();
       /**
        * @brief get camera class for image[idx]
        *
        * @param idx image index
        *
        * @return  camera class
        */
        Camera const& getCam(size_t idx) const;
       /**
        * @brief return the pointer to the camera[idx], used by Photo class to maintain the camera info. for each image.
        *
        * @param idx the camera index
        *
        * @return the pointer to the idx-th camera.
        */
        Camera const* getCamPtr(size_t idx) const;
       /**
        * @brief get image name (dir)
        *
        * @param idx image index
        *
        * @return image name
        */
        inline std::string getImgName(size_t idx) const;
       /**
        * @brief get the input number of images
        *
        * @return number of input images
        */
        inline size_t getNumImg(void) const {return mNumImg;}
       /**
        * @brief after construct the class, call this function to read the bundler output file. Any error while parsing the file will throw an IoException and terminate the entire program.
        */
        void readData(void);
       /**
        * @brief parse bundler.out file
        */

        virtual void parseBundlerOut(void);

       /**
        * @brief parse the meta data (header) of the bundler output
        */
        void parseMeta(std::ifstream& fs);
       /**
        * @brief parse the camera info. from bundler output
        */
        virtual void parseCamera(std::ifstream& fs);
       /**
        * @brief parse image list.txt file
        */
        void parseImgList(void);




    protected:
        /**
         * @brief all the information collected from bundler, used in the Photo class (by constant pointer)
         */
        std::vector<Camera> mCameras;
        /**
         * @brief bundler file directory, used to init this class.
         * this directory just include to bin
         */
        std::string mBundlerDir;
        /**
         * @brief image names use later
         */
        std::vector<std::string> mImgNames;
        /**
         * @brief the used image index of the input image
         */
        std::vector<int> numIdx;
        /**
         * @brief number of images
         */
        size_t mNumImg;
        size_t mNumFea;

};

std::string Bundler::getImgName(size_t idx) const
{
    return mImgNames[idx];
}

#endif // BUNDLERBASE_H
