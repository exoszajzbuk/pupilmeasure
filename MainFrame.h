////////////////////////////////////////////////////////////////////////////////
// Filename: MainFrame.h
// Author:   Balazs KOVACS
// Year:     2010
//
// Description: Header of MainFrame class.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MainFrame__
#define __MainFrame__

// others
#include "PupilMeasure.h"
#include "VideoFrame.h"

// forward declarations
class VideoFrame;


////////////////////////////////////////////////////////////
// Class:        MainFrame
// Derived from: MainFrameBase
//
// Description: MainFrame class handles most of GUI calls
//              and events.
////////////////////////////////////////////////////////////
class MainFrame
    : public MainFrameBase
{
public:
    // default constructor
	MainFrame(wxWindow* parent, PupilMeasure* model);

protected:
    // button/menu events
    void    onButtonWebcam(wxCommandEvent& event);
    void    onButtonStop(wxCommandEvent& event);
    void    onButtonPause(wxCommandEvent& event);
    void    onButtonExit(wxCommandEvent& event);
    void    onButtonAbout(wxCommandEvent& event);
    
    // textctrl events
   	void	onTextBlur(wxCommandEvent& event);
   	void	onTextSnakeWindow(wxCommandEvent& event);

    // update UI
    void    onUpdateUI(wxUpdateUIEvent& event);
    
    // update model
    void	updateModel(wxCommandEvent& event);

    // idle event handler for rendering
    void    onIdle(wxIdleEvent& event);

private:
    // variables
    PupilMeasure*   m_model;        	// pointer to model
    VideoFrame*     m_resultFrame;  	// pointer to video window
    VideoFrame*     m_leftEyeFrame;		// left-eye frame
    VideoFrame*     m_rightEyeFrame;	// right-eye frame

    // methods
    void        activateRenderLoop(bool on);    // activating render-loop
    
    // get wxString values
    int			getIntValue(wxString p_str);
    double		getDoubleValue(wxString p_str);
};

#endif
