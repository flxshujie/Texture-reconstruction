#include "Camera.h"
#include <cmath>

using namespace std;
using namespace cv;

Camera::Camera()
:mIsValid(false)
,mFocLen(0.0)
,mExtMat(3, 4, CV_32FC1, Scalar::all(0))
,mIntMat(3, 3, CV_32FC1, Scalar::all(0))
,mR(3, 3, CV_32FC1, Scalar::all(0))
,mt(3, 1, CV_32FC1, Scalar::all(0))
,mPrjMat(3, 4, CV_32FC1, Scalar::all(0))
{
}

void Camera::setExtMat(const cv::Mat& src)
{
    this->mExtMat = src.clone();
    updateRt();
    updatePrjMat();
	updateCamCenter();
	updatePrincipal();
}

void Camera::setIntMat(const cv::Mat& src)
{
    this->mIntMat = src.clone();
    updatePrjMat();
	updateFocalLen();
	updatePrincipal();
}

void Camera::updateRt(void)
{
    mR = mExtMat(cv::Range(0, 3), cv::Range(0, 3));
    mt = mExtMat(cv::Range(0, 3), cv::Range(3, 4));
}

void Camera::updateCamCenter(void)
{
    Mat camC = -mR.inv() * mt ;
    mCamCenter.x = camC.at<float>(0,0);
	mCamCenter.y = camC.at<float>(1,0);
	mCamCenter.z = camC.at<float>(2,0);
}

void Camera::updatePrincipal(void)
{
	//reference MVG pp160-pp161
	mPrincipal[0] = mPrjMat.at<float>(2,0);
	mPrincipal[1] = mPrjMat.at<float>(2,1);
	mPrincipal[2] = mPrjMat.at<float>(2,2);
}

void Camera::updateFocalLen(void)
{
	float f1 = mIntMat.at<float>(0,0);
	float f2 = mIntMat.at<float>(1,1);

	mFocLen = (f1 + f2) / 2.0f;
}
