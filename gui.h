///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/radiobox.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_CLOSEMENU 1000
#define wxID_EXITMENU 1001
#define wxID_WEBCAMTOOL 1002
#define wxID_STOPTOOL 1003
#define wxID_PAUSETOOL 1004
#define wxID_EXITTOOL 1005

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menuBar;
		wxMenu* m_menuFile;
		wxMenu* m_menuAbout;
		wxToolBar* m_toolBar;
		wxStaticText* m_labelDevice;
		wxTextCtrl* m_textDevice;
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText5;
		wxStaticText* m_labelWidth;
		wxTextCtrl* m_textWidth;
		wxStaticText* m_labelHeight;
		wxTextCtrl* m_textHeight;
		wxStaticText* m_staticText19;
		wxTextCtrl* m_textOutFile;
		wxRadioBox* m_radioBoxMethod;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_textThreshold;
		wxStaticText* m_staticText9;
		wxTextCtrl* m_textBlur;
		wxStaticText* m_staticText10;
		wxTextCtrl* m_textSnakeA;
		wxStaticText* m_staticText11;
		wxTextCtrl* m_textSnakeB;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_textSnakeC;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_textSnakeWindow;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_textSnakeIters;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_textHoughAccRes;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_textHoughMinDist;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_textHoughCanny;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_textHoughHough;
		wxStatusBar* m_statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void onButtonWebcam( wxCommandEvent& event ) { event.Skip(); }
		virtual void onButtonStop( wxCommandEvent& event ) { event.Skip(); }
		virtual void onButtonExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void onButtonAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void onButtonPause( wxCommandEvent& event ) { event.Skip(); }
		virtual void updateModel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTextBlur( wxCommandEvent& event ) { event.Skip(); }
		virtual void onTextSnakeWindow( wxCommandEvent& event ) { event.Skip(); }
		virtual void udpateModel( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("PupilMeasure"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 350,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~MainFrameBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class VideoFrameBase
///////////////////////////////////////////////////////////////////////////////
class VideoFrameBase : public wxFrame 
{
	private:
	
	protected:
	
	public:
		
		VideoFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCAPTION|wxTAB_TRAVERSAL );
		~VideoFrameBase();
	
};

#endif //__gui__
