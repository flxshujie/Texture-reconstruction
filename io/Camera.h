#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp>

/**Due to the bundler have do the process of calibrating of these images, we do not consider of the
    parameters of aspect ratio and the distort ratio****/
class Camera
{
    public:
            /**
			 * @brief constructor, set some default values.
			 */
            Camera();
            /**
			 * @brief set the external matrix of the cam, all the related info. will automatically update.
			 *
			 * @param src input external matrix.
			 */
			void setExtMat(const cv::Mat& src);
			/**
			 * @brief set the internal matrix of the cam, all the related info. will automatically update.
			 *
			 * @param src input internal matrix.
			 */
			void setIntMat(const cv::Mat& src);
			inline bool isCamValid(void) const {return mIsValid;}
			inline void setValid(void) {mIsValid = true;}
			/**
			 * @brief project a 3d point (world coordinate) to the image.
			 *
			 * @param pt3d 3d point
			 *
			 * @return 2d point
			 */
			inline cv::Point2f project(cv::Point3f pt3d) const;
			// output APIs
			// these set of methods should AVOID be used directly in the reconstruction stage, they serve as the base methods for other higher end methods, such as computing homograph.
			inline const cv::Mat& getR(void) const {return mR;}
			inline const cv::Mat& getT(void) const {return mt;}
			inline float getFocLen(void) const {return mFocLen;}
			inline const cv::Mat& getExtMat(void) const {return mExtMat;}
			inline const cv::Mat& getIntMat(void) const {return mIntMat;}
			inline const cv::Mat& getPrjMat(void) const {return mPrjMat;}
			inline cv::Vec3f getPrincipal(void) const {return mPrincipal;}
			inline cv::Point3f getCamCenter(void) const {return mCamCenter;}
			inline bool isValid(void) const {return mIsValid;}

			/**
			 * @brief update project matrix
			 */
			inline void updatePrjMat(void)
			{
				mPrjMat = mIntMat * mExtMat;
			}
			/**
			 * @brief update rotation and translation matrix
			 */
			void updateRt(void);
			/**
			 * @brief update camera center
			 */
			void updateCamCenter(void);
			/**
			 * @brief update principal point
			 */
			void updatePrincipal(void);
			/**
			 * @brief update focal length
			 */
			void updateFocalLen(void);
			/**
			 * @brief should be called immediately after updateRt
			 */
			void updateRInv(void);
			/**
			 * @brief should be called immediately after setIntMat
			 */
			void updateIntMatInv(void);


    private:
            /**
			 * @brief focal length
			 * written if setIntMat() is called
			 */
			float mFocLen;
			/**
			 * @brief external matrix 3 * 4
			 * written if setExtMat() is called
			 */
			cv::Mat mExtMat;
			/**
			 * @brief internal matrix 3 * 3
			 * written if setIntMat() is called
			 */
			cv::Mat mIntMat;
			/**
			 * @brief project matrix, 3* 4
			 * written if setIntMat() or setExtMat() is called
			 */
			cv::Mat mPrjMat;
			/**
			 * @brief principal direction, directed towards the front of the camera
			 * written if setExtMat() is called
			 * Ref. MVG pp. 154, 161
			 */
			cv::Vec3f mPrincipal;
			/**
			 * @brief camera optical center
			 * written if setExtMat() is called
			 */
			cv::Point3f mCamCenter;
			/**
			 * @brief rotation matrix, 3 * 3
			 * written if setExtMat() is called
			 */
			cv::Mat mR;
			/**
			 * @brief translation 3 * 1
			 * written if setExtMat() is called
			 */
			cv::Mat mt;

			/**
			 * @brief whether the camera is successfully calibrated by sfm system.
			 * written if setValid() is called
			 */
			bool mIsValid;
};

//---------------------------------------------------------------
	// implementation
cv::Point2f Camera::project(cv::Point3f pt3d) const
{

    cv::Point2f p2;
    const float* pPrjMat = (const float*)mPrjMat.data;
    cv::Point3f prjPt;
    prjPt.x = pPrjMat[0] * pt3d.x + pPrjMat[1] * pt3d.y + pPrjMat[2] * pt3d.z + pPrjMat[3];
    prjPt.y = pPrjMat[4] * pt3d.x + pPrjMat[5] * pt3d.y + pPrjMat[6] * pt3d.z + pPrjMat[7];
    prjPt.z = pPrjMat[8] * pt3d.x + pPrjMat[9] * pt3d.y + pPrjMat[10] * pt3d.z + pPrjMat[11];

    if(prjPt.z < 1e-6)
    {
        p2.x = -1;
        p2.y = -1;
    }
    else
    {
        p2.x = prjPt.x / prjPt.z ;
        p2.y = prjPt.y / prjPt.z ;
    }
    return p2;
}
#endif
