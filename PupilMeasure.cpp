////////////////////////////////////////////////////////////////////////////////
// Filename: PupilMeasure.cpp
// Author:   Balazs KOVACS
// Year:     2010
//
// Description: Imlementation of PupilMeasure class.
//
////////////////////////////////////////////////////////////////////////////////

// STL
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <time.h>

// OpenCV
#include <cv.h>
#include <highgui.h>

// other
#include "PupilMeasure.h"

// namespaces
using namespace std;
using namespace cv;

// macros
#define PT_THRES 5

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: PupilMeasure
//
// Description: PupilMeasure class default constructor
////////////////////////////////////////////////////////////
PupilMeasure::PupilMeasure()
{
    // default options
    m_capturing = false;
    m_paused = false;

    // fps init
    m_timePrev = 0;
    m_timeNow = 0;
}



////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: loadVideoFile
//
// Description: This method loads a video file and sets
//              corresponding variables.
////////////////////////////////////////////////////////////
bool PupilMeasure::startWebcam(string device, int width, int height, string outFile)
{
    // init webcam
    m_wcam = new WebCamera(device, width, height);
    //m_classifier = new CascadeClassifier("haarcascade_eye.xml");
    
    // set filename
    m_outFile = outFile;

    // initally detect
    m_detect = true;
    m_redetect = 0;

    // initialize and start capturing
    if (!m_capturing)
    {
        m_wcam->Init();
        m_wcam->StartCapturing();

        m_capturing = true;
    }
    
    // initialize snake contour
    initSnakeContour(m_eyeWidth/2, m_eyeHeight/2, m_eyeWidth<m_eyeHeight?m_eyeWidth/2:m_eyeHeight/2, 15, 0);
    initSnakeContour(m_eyeWidth/2, m_eyeHeight/2, m_eyeWidth<m_eyeHeight?m_eyeWidth/2:m_eyeHeight/2, 15, 1);
    
    // ================
    // LOGGING
    m_startTime = getTime();
	
	// get date
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer [80];
	time (&rawtime);
  	timeinfo = localtime (&rawtime);
	strftime(buffer,80,"%c.",timeinfo);
    
    // open log file
	ofstream logfile(m_outFile.c_str(), ios::app);

	// insert log header
	std::string method = m_method==0?"SNAKE":"HOUGH";
    logfile << method <<" measurement -- started at " << buffer << "\n";
    
    // close log file
    logfile.close();
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: closeVideoFile
//
// Description: This method closes the actually loaded
//              video file.
////////////////////////////////////////////////////////////
void PupilMeasure::stopWebcam()
{
    // stop capturing and close
    if (m_capturing)
    {
        m_wcam->StopCapturing();
        m_wcam->Close();

        m_capturing = false;
    }
}


int clamp(double x)
{
    int r = x;      /* round to nearest */

    if (r < 0)         return 0;
    else if (r > 255)  return 255;
    else               return r;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: processNextFrame
//
// Description: This method processes the next frame in
//              video using the private variables to
//              determine what to do. (e.g. process
//              method, thresholding, blurring, etc).
////////////////////////////////////////////////////////////
bool PupilMeasure::processNextFrame()
{
    // grabs next frame
    cv::Mat img = grabFrame();
    	
	// eye positions
	int padding = 5;
	int eyeY = padding+m_eyeHeight/2+(int)((getHeight()-(padding*2+m_eyeHeight))*m_eyeVPos/100);
	int leftEyeX = padding+m_eyeWidth/2+(int)((getWidth()/2-(padding*2+m_eyeWidth))*m_eyeHPos/100);
	int rightEyeX = getWidth()/2+padding+m_eyeWidth/2+(int)((getWidth()/2-(padding*2+m_eyeWidth))*(100-m_eyeHPos)/100);

	// render left-eye frame
	rectangle(
		img,
		Point(leftEyeX-m_eyeWidth/2, eyeY-m_eyeHeight/2),
		Point(leftEyeX+m_eyeWidth/2, eyeY+m_eyeHeight/2),
		Scalar(255,0,0),
		1, 8, 0
	);
	
	// render right-eye frame
	rectangle(
		img,
		Point(rightEyeX-m_eyeWidth/2, eyeY-m_eyeHeight/2),
		Point(rightEyeX+m_eyeWidth/2, eyeY+m_eyeHeight/2),
		Scalar(255,0,0),
		1, 8, 0
	);
	
    // extract eye regions
    cv::Mat tmp, leftEye, leftEyeProc, rightEye, rightEyeProc;
    tmp = img(cv::Rect(leftEyeX-m_eyeWidth/2, eyeY-m_eyeHeight/2, m_eyeWidth, m_eyeHeight));
    tmp.copyTo(leftEye);

    tmp = img(cv::Rect(rightEyeX-m_eyeWidth/2, eyeY-m_eyeHeight/2, m_eyeWidth, m_eyeHeight));
    tmp.copyTo(rightEye);
    
    // process eye regions
    leftEyeProc = processEye(leftEye, 0);
    rightEyeProc = processEye(rightEye, 1);

    // render current fps to image
    std::ostringstream o;
    o << "FPS: " << getCurrentFPS();
    cv::putText(img, o.str(), Point(getWidth()-100, 13), FONT_HERSHEY_PLAIN, 1.0, Scalar(0,255,0), 2);

    // notify videoframe
    m_actualFrame.setImage(img);
    m_actualFrame.setChanged(true);
       
    // notify left-eye frame
    //cv::Mat leftEyeBig;
    //resize(leftEyeProc, leftEyeBig, Size(), 2, 2);
    m_leftEyeFrame.setImage(leftEyeProc);
    m_leftEyeFrame.setChanged(true);

    // notify left-eye frame
    //cv::Mat rightEyeBig;
    //resize(rightEyeProc, rightEyeBig, Size(), 2, 2);
    m_rightEyeFrame.setImage(rightEyeProc);
    m_rightEyeFrame.setChanged(true);

    // save time values
    m_timePrev = m_timeNow;
    m_timeNow = getTime();
    
    // ===============
    // LOGGING
	
	// elapsed time
	double time = (m_timeNow - m_startTime)/1000000000;
    
    // open log file
	ofstream logfile(m_outFile.c_str(), ios::app);

	// log time, frame number and results
    logfile << m_frameNum++ << ";" << time << ";results\n";
    
    // HOUGH/SNAKE specific logging
    
    // close log file
    logfile.close();
    
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: processEye
//
// Description: This method initializes snake contour
//              to given position (in a circle).
////////////////////////////////////////////////////////////
cv::Mat PupilMeasure::processEye(cv::Mat p_img, int p_eye)
{
   	// ***===***===***===***===***===***===***===***===***===***===***===***===
    // OPENCV code here
    
	// frames
    cv::Mat grey, thr, blur, out;
    IplImage snakeimg;
    
	CvPoint* snakeContour;
	int snakeContourLength;
    
    // result vectors
    if (p_eye == 0)
    {
    	snakeContour = m_snakeContourLeft;
		snakeContourLength = m_snakeContourLeftLength;
    }
    else if (p_eye == 1)
    {
		snakeContour = m_snakeContourRight;
		snakeContourLength = m_snakeContourRightLength;
    }
    vector<Vec3f> circles;

    cvtColor(p_img, grey, CV_RGB2GRAY);

    // if there's no previous image
    if (m_prevImage.empty())
    {
        //std::cout << "empty" << std::endl;
        m_prevImage = grey;
    }
    
	// thresholding
	if (m_threshold == -1)
	{
		// disable thresholding
		thr = grey;
	}
	else
	{
		// thresholding image
		threshold(
			grey,               // input image
			thr,                // output image
			m_threshold,	    // threshold value
			255,				// replace value
			THRESH_BINARY		// thresholding method
		);
	}

	// blurring
	if (m_blur == -1)
	{
		blur = thr;
	}
	else
	{
		// if blurring is on, process
		GaussianBlur(
			thr,					// input image
			blur,					// output image
			Size(m_blur,m_blur),	// Gaussian kernel-size
			0,						// sigmaX 
			0,						// sigmaY, default=0
			BORDER_DEFAULT			// borderType
		);
	}
	
	// setting out image
	cvtColor(blur, out, CV_GRAY2RGB);
	
	// process eye contour/position
	if (m_method == 0)
	{
		// ====================
		// Active Contour model
		
		// reinit if needed
		reInitSnakeContour(20, p_eye);

		// get IplImage
		snakeimg = IplImage(blur);
		
		// set termination criteria
		CvTermCriteria termCrit;
		termCrit.epsilon = 5;
		termCrit.max_iter = m_snakeIters;
		termCrit.type = CV_TERMCRIT_ITER;
		
		// parameters
		float snakeA = (float)m_snakeA;
		float snakeB = (float)m_snakeB;
		float snakeC = (float)m_snakeC;

		// snake interation
		cvSnakeImage(
			&snakeimg,                          // input image
			snakeContour,                       // contour
			snakeContourLength,                 // contour length
			&snakeA,							// alpha
 			&snakeB,							// beta
			&snakeC,							// gamma
			CV_VALUE,							// single values
			Size(m_snakeWindow,m_snakeWindow),	// snake kernel
			termCrit,							// termination crit.
			0									// calc. gradient
		);
	
		// write back results
		if (p_eye == 0)
		{
    		m_snakeContourLeft = snakeContour;
			m_snakeContourLeftLength = snakeContourLength;
		}
		else if (p_eye == 1)
		{
    		m_snakeContourRight = snakeContour;
			m_snakeContourRightLength = snakeContourLength;		
		}
		
		// draw results
		for (size_t i = 0; i < snakeContourLength; i++)
		{
			// points
			circle(
				out,
				snakeContour[i],
				3,
				Scalar(0,255,0),
				-1,
				7,
				0
			);

			// line segments
			if (i > 0)
			{
				// draw line segments
				line(
					out,
					snakeContour[i],
					snakeContour[i-1],
					Scalar(255,0,0),
					1,
					8,
					0
				);
			}
		}

		// draw last line segment
		line(
			out,
			snakeContour[0],
			snakeContour[snakeContourLength-1],
			Scalar(255,0,0),
			1,
			8,
			0
		);
	}
	else
	{
		// ====================
		// Hough-transform
		HoughCircles(
			blur,					// input image
			circles,				// output vector of found circles
			CV_HOUGH_GRADIENT,		// the '21HT' method
			m_houghAccRes,			// accumulator resolution
			m_houghMinDist,			// minimum distance between circles
			m_houghCanny,			// param1 (Canny-parameter)
			m_houghHough,			// param2, default=100
			0,						// minimum radius, default=0
            0						// maximum radius, default=0
		);
		
		// draw detected circles
		for(size_t i = 0; i < circles.size(); i++)
		{
			Point center(
				cvRound(circles[i][0]), 
				cvRound(circles[i][1])
			);
			int radius = cvRound(circles[i][2]);

			// draw the circle center
			circle(out, center, 3, Scalar(0,255,0), -1, 7, 0);

			// draw the circle outline
			circle(out, center, radius, Scalar(255,0,0), 1, 8, 0);
		}
	}
	
	return out;

    // ***===***===***===***===***===***===***===***===***===***===***===***===
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: initSnakeContour
//
// Description: This method initializes snake contour
//              to given position (in a circle).
////////////////////////////////////////////////////////////
void PupilMeasure::initSnakeContour(int x0, int y0, int r, int num, int p_eye)
{

    // set proper elements
    if (p_eye == 0)
    {
    	if (m_snakeContourLeft != NULL)
    	{
    		delete m_snakeContourLeft;
    	}

	    // create contour
		m_snakeContourLeft = new CvPoint[num];
    	m_snakeContourLeftLength = num;

		// set points to a circle
		double deg = 360/num;
		double rad = deg * (M_PI/180);

		for (int i = 0; i < num; i++)
		{
		    int x = (int)(x0 + r*cos(i*rad));
		    int y = (int)(y0 + r*sin(i*rad));

		    if (x > m_eyeWidth)
		    {
		        x = m_eyeWidth;
		    }

		    if (x < 0)
		    {
		        x = 0;
		    }

		    if (y > m_eyeHeight)
		    {
		        y = m_eyeHeight;
		    }

		    if (y < 0)
		    {
		        y = 0;
		    }

		    m_snakeContourLeft[i].x = x;
		    m_snakeContourLeft[i].y = y;
		}
	}
	else if (p_eye == 1)
	{
    	if (m_snakeContourRight != NULL)
    	{
    		delete m_snakeContourRight;
    	}

	    // create contour
		m_snakeContourRight = new CvPoint[num];
    	m_snakeContourRightLength = num;

		// set points to a circle
		double deg = 360/num;
		double rad = deg * (M_PI/180);

		for (int i = 0; i < num; i++)
		{
		    int x = (int)(x0 + r*cos(i*rad));
		    int y = (int)(y0 + r*sin(i*rad));

		    if (x > m_eyeWidth)
		    {
		        x = m_eyeWidth;
		    }

		    if (x < 0)
		    {
		        x = 0;
		    }

		    if (y > m_eyeHeight)
		    {
		        y = m_eyeHeight;
		    }

		    if (y < 0)
		    {
		        y = 0;
		    }

		    m_snakeContourRight[i].x = x;
		    m_snakeContourRight[i].y = y;
		}
	}
    
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: initSnakeContour
//
// Description: This method checks if snake contour
//              needs to be reinitialized, and
//              reinitializes it if needed.
////////////////////////////////////////////////////////////
void PupilMeasure::reInitSnakeContour(int thres, int p_eye)
{
	// switch contours
	CvPoint* snakeContour;
	int snakeContourLength;
	
	if (p_eye == 0)
	{
		snakeContour = m_snakeContourLeft;
		snakeContourLength = m_snakeContourLeftLength;
	}
	else if (p_eye == 1)
	{
		snakeContour = m_snakeContourRight;
		snakeContourLength = m_snakeContourRightLength;	
	}

	std::cout << "reinit\n";

    // temporary variables
    int x_min = m_eyeWidth;
    int x_max = 0;
    int x_sum = 0;

    int y_min = m_eyeHeight;
    int y_max = 0;
    int y_sum = 0;

    // calculate 'bounding box'
    for (int i = 0; i < snakeContourLength; i++)
    {
        int x = snakeContour[i].x;
        int y = snakeContour[i].y;

        if (x > x_max)
        {
            x_max = x;
        }
        
        if (x < x_min)
        {
            x_min = x;
        }

        if (y > y_max)
        {
            y_max = y;
        }
        
        if (y < y_min)
        {
            y_min = y;
        }

        x_sum += x;
        y_sum += y;
    }

    double x_avg = x_sum / snakeContourLength;
    double y_avg = y_sum / snakeContourLength;

    if ((x_max - x_min) < thres && (y_max - y_min) < thres)
    {
    	std::cout << "KELL\n";
        // reinit contour
        initSnakeContour(m_eyeWidth/2, m_eyeHeight/2, m_eyeWidth<m_eyeHeight?m_eyeWidth/2:m_eyeHeight/2, 15, p_eye);
        std::cout << "kesz\n";
    }

}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: grabFrame
//
// Description: grabs a new frame from webcam
////////////////////////////////////////////////////////////
cv::Mat PupilMeasure::grabFrame()
{
    const unsigned char *buffer = NULL;
    buffer = (const unsigned char*)m_wcam->NextFrame();

    int Y0, Y1, Cb, Cr;            /* gamma pre-corrected input [0;255] */
    int ER0,ER1,EG0,EG1,EB0,EB1;    /* output [0;255] */
    double r0,r1,g0,g1,b0,b1;             /* temporaries */
    double y0,y1, pb, pr;
    unsigned height = 0, width = 0;

	width = getWidth();
	height = getHeight();

    unsigned char bufferOut[width*height*3];

    int k = 0;

    for (unsigned i = 0; i < height; i++)
    {
	    for(unsigned j = 0; j < width / 2; j++)
	    {
	        Y0 = *(buffer++);
	        Cb = *(buffer++);
	        Y1 = *(buffer++);
	        Cr = *(buffer++);

	        y0 = (255 / 219.0) * (Y0 - 16);
	        y1 = (255 / 219.0) * (Y1 - 16);
	        pb = (255 / 224.0) * (Cb - 128);
	        pr = (255 / 224.0) * (Cr - 128);

	        // Generate first pixel
	        r0 = y0 + 1.402 * pr;
	        g0 = y0 - 0.344 * pb - 0.714 * pr;
	        b0 = y0 + 1.772 * pb;

	        // Generate next pixel - must reuse pb & pr as 4:2:2
	        r1 = y1 + 1.402 * pr;
	        g1 = y1 - 0.344 * pb - 0.714 * pr;
	        b1 = y1 + 1.772 * pb;

    	    ER0 = clamp (r0);
	        ER1 = clamp (r1);
	        EG0 = clamp (g0);
	        EG1 = clamp (g1);
	        EB0 = clamp (b0);
	        EB1 = clamp (b1);

            bufferOut[k++] = (unsigned char)ER0;
            bufferOut[k++] = (unsigned char)EG0;
            bufferOut[k++] = (unsigned char)EB0;
            bufferOut[k++] = (unsigned char)ER1;
            bufferOut[k++] = (unsigned char)EG1;
            bufferOut[k++] = (unsigned char)EB1;
        }
    }

     // convert to opencv matrix
    cv::Mat img = cv::Mat(height, width, CV_8UC3, (unsigned char*)bufferOut);
    return img;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: getTime
//
// Description: This method returns current time in
//              nanoseconds.
////////////////////////////////////////////////////////////
double PupilMeasure::getTime()
{
    // structure to store time in
    struct timespec time;

    // get current time from monotonic clock
    clock_gettime(CLOCK_MONOTONIC, &time);

    return ((time.tv_sec * 1000000000)+time.tv_nsec);
}



////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: getCapturing
////////////////////////////////////////////////////////////
bool PupilMeasure::getCapturing()
{
    return m_capturing;
}



////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: getWidth
//
// Description: This method returns the video width.
////////////////////////////////////////////////////////////
int PupilMeasure::getWidth()
{
    return m_wcam->GetWidth();
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: getWidth
//
// Description: This method returns the video height.
////////////////////////////////////////////////////////////
int PupilMeasure::getHeight()
{
    return m_wcam->GetHeight();
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: getCurrentFPS
//
// Description: This method returns the current FPS
//              calculated from previous and current
//              time.
////////////////////////////////////////////////////////////
double PupilMeasure::getCurrentFPS()
{
    double fps = 1000/((m_timeNow-m_timePrev)/1000000);
    return fps>0?fps:0.0;
}



////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: pointSortPredicate
//
// Description: adfasdf
////////////////////////////////////////////////////////////
bool PupilMeasure::pointSortPredicate(const cv::Point2f& left, const cv::Point2f& right)
{
    return left.x < right.x;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setEyeWidth/getEyeWidth
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setEyeWidth(int p_eyeWidth)
{
    m_eyeWidth = p_eyeWidth;
}

int PupilMeasure::getEyeWidth()
{
    return m_eyeWidth;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setEyeHeight/getEyeHeight
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setEyeHeight(int p_eyeHeight)
{
    m_eyeHeight = p_eyeHeight;
}

int PupilMeasure::getEyeHeight()
{
    return m_eyeHeight;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setEyeHPos/getEyeHPos
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setEyeHPos(int p_eyeHPos)
{
    m_eyeHPos = p_eyeHPos;
}

int PupilMeasure::getEyeHPos()
{
    return m_eyeHPos;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setEyeVPos/getEyeVPos
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setEyeVPos(int p_eyeVPos)
{
    m_eyeVPos = p_eyeVPos;
}

int PupilMeasure::getEyeVPos()
{
    return m_eyeVPos;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setMethod/getMethod
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setMethod(int p_method)
{
    m_method = p_method;
}

int PupilMeasure::getMethod()
{
    return m_method;
}

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setThreshold/getThreshold
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setThreshold(int p_threshold)
{
    m_threshold = p_threshold;
}

int PupilMeasure::getThreshold()
{
    return m_threshold;
}

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setBlur/getBlur
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setBlur(int p_blur)
{
	if (p_blur < 0)
	{
		m_blur = 1;
	}
	else if (p_blur%2 == 0)
	{
		m_blur = p_blur-1;
	}
	else
	{
		m_blur = p_blur;
	}
}

int  PupilMeasure::getBlur()
{
    return m_blur;
}

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setSnakeA/getSnakeA
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setSnakeA(double p_snakeA)
{
	m_snakeA = p_snakeA;
}

double PupilMeasure::getSnakeA()
{
	return m_snakeA;
}
        

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setSnakeB/getSnakeB
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setSnakeB(double p_snakeB)
{
	m_snakeB = p_snakeB;
}

double PupilMeasure::getSnakeB()
{
	return m_snakeA;
}

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setSnakeC/getSnakeC
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setSnakeC(double p_snakeC)
{
	m_snakeC = p_snakeC;
}

double PupilMeasure::getSnakeC()
{
	return m_snakeC;
}

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: getSnakeWindow/getSnakeWindow
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setSnakeWindow(int p_snakeWindow)
{
	if (p_snakeWindow == 0)
	{
		m_snakeWindow = 1;
	}
	else if (p_snakeWindow%2 == 0)
	{
		m_snakeWindow = p_snakeWindow-1;
	}
	else
	{
		m_snakeWindow = p_snakeWindow;
	}
}

int PupilMeasure::getSnakeWindow()
{
	return m_snakeWindow;
}
        
        
////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setSnakeIters/getSnakeIters
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setSnakeIters(int p_snakeIters)
{
	m_snakeIters = p_snakeIters;
}

int PupilMeasure::getSnakeIters()
{
	return m_snakeIters;
}

////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setHoughAccRes/getHoughAccRes
//
// Description: adfasdf
////////////////////////////////////////////////////////////
void PupilMeasure::setHoughAccRes(int p_houghAccRes)
{
	m_houghAccRes = p_houghAccRes;
}

int PupilMeasure::getHoughAccRes()
{
	return m_houghAccRes;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setHoughMinDist/getHoughMinDist
//
// Description: adfasdf
////////////////////////////////////////////////////////////        
void PupilMeasure::setHoughMinDist(int p_houghMinDist)
{
	m_houghMinDist = p_houghMinDist;
}

int PupilMeasure::getHoughMinDist()
{
	return m_houghMinDist;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setHoughCanny/getHoughCanny
//
// Description: adfasdf
////////////////////////////////////////////////////////////        
void PupilMeasure::setHoughCanny(int p_houghCanny)
{
	m_houghCanny = p_houghCanny;
}

int PupilMeasure::getHoughCanny()
{
	return m_houghCanny;
}


////////////////////////////////////////////////////////////
// Class name:  PupilMeasure
// Method name: setHoughHough/getHoughHough
//
// Description: adfasdf
////////////////////////////////////////////////////////////        
void PupilMeasure::setHoughHough(int p_houghHough)
{
	m_houghHough = p_houghHough;
}

int PupilMeasure::getHoughHough()
{
	return m_houghHough;
}
