///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

#include "images/applicationexit16.xpm"
#include "images/applicationexit32.xpm"
#include "images/cameraweb.xpm"
#include "images/helpabout16.xpm"
#include "images/mediaplaybackpause32.xpm"
#include "images/windowclose16.xpm"
#include "images/windowclose32.xpm"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 350,600 ), wxSize( 350,600 ) );
	
	m_menuBar = new wxMenuBar( 0 );
	m_menuFile = new wxMenu();
	wxMenuItem* m_menuItemWebcam;
	m_menuItemWebcam = new wxMenuItem( m_menuFile, wxID_ANY, wxString( wxT("Start webcam") ) , wxEmptyString, wxITEM_NORMAL );
	m_menuFile->Append( m_menuItemWebcam );
	
	wxMenuItem* m_menuItemStop;
	m_menuItemStop = new wxMenuItem( m_menuFile, wxID_CLOSEMENU, wxString( wxT("Stop webcam") ) , wxT("Close current file..."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_menuItemStop->SetBitmaps( wxBitmap( windowclose16_xpm ) );
	#elif defined( __WXGTK__ )
	m_menuItemStop->SetBitmap( wxBitmap( windowclose16_xpm ) );
	#endif
	m_menuFile->Append( m_menuItemStop );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menuFile->AppendSeparator();
	
	wxMenuItem* m_menuItemExit;
	m_menuItemExit = new wxMenuItem( m_menuFile, wxID_EXITMENU, wxString( wxT("Exit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Exit Demo Program..."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_menuItemExit->SetBitmaps( wxBitmap( applicationexit16_xpm ) );
	#elif defined( __WXGTK__ )
	m_menuItemExit->SetBitmap( wxBitmap( applicationexit16_xpm ) );
	#endif
	m_menuFile->Append( m_menuItemExit );
	
	m_menuBar->Append( m_menuFile, wxT("&File") );
	
	m_menuAbout = new wxMenu();
	wxMenuItem* m_menuItemAbout;
	m_menuItemAbout = new wxMenuItem( m_menuAbout, wxID_ANY, wxString( wxT("About") ) , wxT("Open 'About' dialog..."), wxITEM_NORMAL );
	#ifdef __WXMSW__
	m_menuItemAbout->SetBitmaps( wxBitmap( helpabout16_xpm ) );
	#elif defined( __WXGTK__ )
	m_menuItemAbout->SetBitmap( wxBitmap( helpabout16_xpm ) );
	#endif
	m_menuAbout->Append( m_menuItemAbout );
	
	m_menuBar->Append( m_menuAbout, wxT("&About") );
	
	this->SetMenuBar( m_menuBar );
	
	m_toolBar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	m_toolBar->AddTool( wxID_WEBCAMTOOL, wxT("tool"), wxBitmap( cameraweb_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Start webcam") );
	m_toolBar->AddTool( wxID_STOPTOOL, wxT("Close Webcam/File"), wxBitmap( windowclose32_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Stop webcam...") );
	m_toolBar->AddSeparator();
	m_toolBar->AddTool( wxID_PAUSETOOL, wxT("Pause"), wxBitmap( mediaplaybackpause32_xpm ), wxNullBitmap, wxITEM_CHECK, wxEmptyString, wxT("Pause tracking...") );
	m_toolBar->AddSeparator();
	m_toolBar->AddTool( wxID_EXITTOOL, wxT("Exit"), wxBitmap( applicationexit32_xpm ), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxT("Exit demo program...") );
	m_toolBar->Realize();
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	bSizer2->SetMinSize( wxSize( 0,0 ) ); 
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Video") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->AddGrowableCol( 3 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_labelDevice = new wxStaticText( this, wxID_ANY, wxT("Device"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelDevice->Wrap( -1 );
	fgSizer1->Add( m_labelDevice, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxALIGN_RIGHT, 5 );
	
	m_textDevice = new wxTextCtrl( this, wxID_ANY, wxT("/dev/video0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textDevice, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL, 5 );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxALL, 5 );
	
	m_labelWidth = new wxStaticText( this, wxID_ANY, wxT("Width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelWidth->Wrap( -1 );
	fgSizer1->Add( m_labelWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );
	
	m_textWidth = new wxTextCtrl( this, wxID_ANY, wxT("800"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textWidth, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_labelHeight = new wxStaticText( this, wxID_ANY, wxT("Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_labelHeight->Wrap( -1 );
	fgSizer1->Add( m_labelHeight, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textHeight = new wxTextCtrl( this, wxID_ANY, wxT("600"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_textHeight, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer1->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer1, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Output") ), wxVERTICAL );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText19 = new wxStaticText( this, wxID_ANY, wxT("File"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer10->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textOutFile = new wxTextCtrl( this, wxID_ANY, wxT("/home/balazs/out1.csv"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_textOutFile, 1, wxALL, 5 );
	
	sbSizer9->Add( bSizer10, 0, wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer9, 0, wxEXPAND, 5 );
	
	wxString m_radioBoxMethodChoices[] = { wxT("Snake"), wxT("Hough") };
	int m_radioBoxMethodNChoices = sizeof( m_radioBoxMethodChoices ) / sizeof( wxString );
	m_radioBoxMethod = new wxRadioBox( this, wxID_ANY, wxT("Method"), wxDefaultPosition, wxDefaultSize, m_radioBoxMethodNChoices, m_radioBoxMethodChoices, 2, wxRA_SPECIFY_COLS );
	m_radioBoxMethod->SetSelection( 0 );
	m_radioBoxMethod->SetFont( wxFont( 11, 74, 90, 92, false, wxT("Sans") ) );
	
	bSizer2->Add( m_radioBoxMethod, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Threshold") ), wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Thres"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer5->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textThreshold = new wxTextCtrl( this, wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	bSizer5->Add( m_textThreshold, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer6->Add( bSizer5, 0, wxEXPAND, 5 );
	
	bSizer8->Add( sbSizer6, 1, 0, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Blur") ), wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Value"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer9->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textBlur = new wxTextCtrl( this, wxID_ANY, wxT("5"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	bSizer9->Add( m_textBlur, 1, wxALL, 5 );
	
	sbSizer7->Add( bSizer9, 0, wxEXPAND, 5 );
	
	bSizer8->Add( sbSizer7, 1, 0, 5 );
	
	bSizer2->Add( bSizer8, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Snake") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 1, 6, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->AddGrowableCol( 3 );
	fgSizer3->AddGrowableCol( 5 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer3->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_textSnakeA = new wxTextCtrl( this, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer3->Add( m_textSnakeA, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer3->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSnakeB = new wxTextCtrl( this, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer3->Add( m_textSnakeB, 0, wxALL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("C"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	fgSizer3->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSnakeC = new wxTextCtrl( this, wxID_ANY, wxT("1.0"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer3->Add( m_textSnakeC, 1, wxALL, 5 );
	
	sbSizer4->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer4->AddGrowableCol( 1 );
	fgSizer4->AddGrowableCol( 3 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Window"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer4->Add( m_staticText13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSnakeWindow = new wxTextCtrl( this, wxID_ANY, wxT("15"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_textSnakeWindow, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Iterations"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer4->Add( m_staticText14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textSnakeIters = new wxTextCtrl( this, wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_textSnakeIters, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer4->Add( fgSizer4, 0, wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer4, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Hough") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer5->AddGrowableCol( 1 );
	fgSizer5->AddGrowableCol( 3 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("AccRes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer5->Add( m_staticText15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textHoughAccRes = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer5->Add( m_textHoughAccRes, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("MinDist"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer5->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textHoughMinDist = new wxTextCtrl( this, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer5->Add( m_textHoughMinDist, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer8->Add( fgSizer5, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgSizer6->AddGrowableCol( 1 );
	fgSizer6->AddGrowableCol( 3 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Canny"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer6->Add( m_staticText17, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textHoughCanny = new wxTextCtrl( this, wxID_ANY, wxT("50"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer6->Add( m_textHoughCanny, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Hough"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer6->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_textHoughHough = new wxTextCtrl( this, wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_PROCESS_ENTER );
	fgSizer6->Add( m_textHoughHough, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer8->Add( fgSizer6, 0, wxEXPAND, 5 );
	
	bSizer2->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ) );
	this->Connect( m_menuItemWebcam->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonWebcam ) );
	this->Connect( m_menuItemStop->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonStop ) );
	this->Connect( m_menuItemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonExit ) );
	this->Connect( m_menuItemAbout->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonAbout ) );
	this->Connect( wxID_WEBCAMTOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonWebcam ) );
	this->Connect( wxID_STOPTOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonStop ) );
	this->Connect( wxID_STOPTOOL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ) );
	this->Connect( wxID_PAUSETOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonPause ) );
	this->Connect( wxID_EXITTOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonExit ) );
	m_radioBoxMethod->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textThreshold->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textBlur->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::onTextBlur ), NULL, this );
	m_textSnakeA->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textSnakeB->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textSnakeB->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textSnakeC->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textSnakeWindow->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::onTextSnakeWindow ), NULL, this );
	m_textSnakeWindow->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textSnakeIters->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::udpateModel ), NULL, this );
	m_textHoughAccRes->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textHoughAccRes->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textHoughMinDist->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textHoughCanny->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textHoughCanny->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textHoughHough->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
}

MainFrameBase::~MainFrameBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonWebcam ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonStop ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonExit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::onButtonAbout ) );
	this->Disconnect( wxID_WEBCAMTOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonWebcam ) );
	this->Disconnect( wxID_STOPTOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonStop ) );
	this->Disconnect( wxID_STOPTOOL, wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ) );
	this->Disconnect( wxID_PAUSETOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonPause ) );
	this->Disconnect( wxID_EXITTOOL, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( MainFrameBase::onButtonExit ) );
	m_radioBoxMethod->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textThreshold->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textBlur->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::onTextBlur ), NULL, this );
	m_textSnakeA->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textSnakeB->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textSnakeB->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textSnakeC->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textSnakeWindow->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::onTextSnakeWindow ), NULL, this );
	m_textSnakeWindow->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textSnakeIters->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::udpateModel ), NULL, this );
	m_textHoughAccRes->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textHoughAccRes->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textHoughMinDist->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textHoughCanny->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
	m_textHoughCanny->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainFrameBase::onUpdateUI ), NULL, this );
	m_textHoughHough->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( MainFrameBase::updateModel ), NULL, this );
}

VideoFrameBase::VideoFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* b_mainSizer;
	b_mainSizer = new wxBoxSizer( wxVERTICAL );
	
	this->SetSizer( b_mainSizer );
	this->Layout();
}

VideoFrameBase::~VideoFrameBase()
{
}
