////////////////////////////////////////////////////////////////////////////////
// Filename: PupilMeasure.h
// Author:   Balazs KOVACS
// Year:     2010
//
// Description: Header of PupilMeasure class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __PupilMeasure__
#define __PupilMeasure__

// STL
#include <string.h>
#include <time.h>
#include <vector>

// OpenCV
#include <cv.h>
#include <highgui.h>

// others
#include "OwnCVImage.h"
#include "Webcamera.h"



////////////////////////////////////////////////////////////
// Class:       PupilMeasure
//
// Description: PupilMeasure gives the model of tracking
//              for the GUI.
////////////////////////////////////////////////////////////
class PupilMeasure
{
    public:
        // default constructor
        PupilMeasure();

        // start and stop webcam
        bool startWebcam(std::string device, int width, int height, std::string outFile);
        void stopWebcam();

        // process actual or next frame
        bool processNextFrame();
        
        // processEye
        cv::Mat processEye(cv::Mat p_mat);

        // actual image
        OwnCVImage m_actualFrame;
		OwnCVImage m_leftEyeFrame;
        OwnCVImage m_rightEyeFrame;

        // ==========
        // INFOS
       
        // get video width, height and capture status
        int getWidth();
        int getHeight();
        bool getCapturing();
        
        // get/set for eye frames
        void setEyeWidth(int p_eyeWidth);
        int getEyeWidth();
        void setEyeHeight(int p_eyeHeight);
        int getEyeHeight();
        void setEyeHPos(int p_eyeHPos);
        int getEyeHPos();
        void setEyeVPos(int p_eyeVPos);
        int getEyeVPos();
        
        // get/set method
        void setMethod(int p_method);
        int getMethod();
        
        // get/set threshold and blur
        void setThreshold(int p_threshold);
        int getThreshold();
        void setBlur(int p_blur);
        int getBlur();
        
        // get/set Snake params
        void setSnakeA(double p_snakeA);
        double getSnakeA();
        
        void setSnakeB(double p_snakeB);
        double getSnakeB();
        
        void setSnakeC(double p_snakeC);
        double getSnakeC();
        
        void setSnakeWindow(int p_snakeWindow);
        int getSnakeWindow();
        
        void setSnakeIters(int p_snakeIters);
        int getSnakeIters();
        
        // get/set Hough params
        void setHoughAccRes(int p_houghAccRes);
        int getHoughAccRes();
        
        void setHoughMinDist(int p_houghMinDist);
        int getHoughMinDist();
        
        void setHoughCanny(int p_houghCanny);
        int getHoughCanny();
        
        void setHoughHough(int p_houghHough);
        int getHoughHough();

        // get original and current fps
        double getCurrentFPS();

        // get actual time
        double getTimeAct();
        
    private:
        // webcamera object
        WebCamera*	        m_wcam;
        cv::Mat             m_prevImage;

        // haar classifier
        cv::CascadeClassifier* m_classifier;
        bool    m_detect;
        std::vector<cv::Rect> detected;
        int     m_eyesize;
        int     m_redetect;

        // grabs frame
        cv::Mat grabFrame();

        // is capturing, and paused
        bool m_capturing;
        bool m_paused;
        
        // output file name
        std::string m_outFile;
        
        // times and frames
        double m_startTime;
        int m_frameNum;

		// eye frames
		int m_eyeWidth;
		int m_eyeHeight;
		int m_eyeHPos;
		int m_eyeVPos;

		// process method
		int m_method;
		
		// threshold/blur
		int m_threshold;
		int m_blur;
		
		// snake parameters
		double m_snakeA;
		double m_snakeB;
		double m_snakeC;
		int m_snakeWindow;
		int m_snakeIters;
		
		CvPoint* m_snakeContourLeft;
        int m_snakeContourLeftLength;
        
        CvPoint* m_snakeContourRight;
        int m_snakeContourRightLength;
        
        std::vector<cv::Vec3f> m_circlesLeft;
        std::vector<cv::Vec3f> m_circlesRight;
        
        void initSnakeContour(int x0, int y0, int r, int num, int p_eye);
        void reInitSnakeContour(int thres, int p_eye);
		
		// hough parameters
		int m_houghAccRes;
		int m_houghMinDist;
		int m_houghCanny;
		int m_houghHough;

        // time variables
        double m_timePrev;
        double m_timeNow;

        // get actual time in nanoseconds
        double getTime();

        // point vectors
        std::vector<cv::Point2f> m_prevPoints;
        std::vector<cv::Point2f> m_points;
        
        // sort predicate        
        static bool pointSortPredicate(const cv::Point2f &left, const cv::Point2f &right);

        // process eyes
        cv::Mat processEye(cv::Mat eye, int p_eye);

};

#endif
