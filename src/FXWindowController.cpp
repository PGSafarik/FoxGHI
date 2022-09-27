#include"FXWindowController.h"
#include<iostream>

using namespace FXGHI;

namespace FXGHI {

FXDEFMAP( FXWindowController ) WindowController[ ] = {
  FXMAPFUNC( SEL_COMMAND, FXWindowController::WIN_MAXIMIZE, FXWindowController::onCmd_WinMaximize )
};
FXIMPLEMENT( FXWindowController, FXObject, WindowController, ARRAYNUMBER( WindowController ) )

/*************************************************************************************************/
FXWindowController::FXWindowController( FXWindowHeader *p, FXuint opts )
{

  m_parent = p;
  FXTopWindow *win = m_parent->getTopWindow( );

  ic_close    = new FXGIFIcon( win->getApp( ), winclose );
  ic_iconify  = new FXGIFIcon( win->getApp( ), winminimize );
  ic_maximize = new FXGIFIcon( win->getApp( ), winmaximize );
  ic_restore  = new FXGIFIcon( win->getApp( ), winrestore );

  m_maximizeBtn = NULL;
  m_iconifyBtn  = NULL;

  m_closeBtn    = new FXButton( m_parent, "\t Close Window", ic_close, win,  FXTopWindow::ID_CLOSE, FRAME_NONE | LAYOUT_RIGHT | LAYOUT_CENTER_Y );
  if( opts & CONTROL_MAXIMIZE ) {
    m_maximizeBtn = new FXButton( m_parent, "\t Maximize Window", ic_maximize, this, FXWindowController::WIN_MAXIMIZE, FRAME_NONE | LAYOUT_RIGHT | LAYOUT_CENTER_Y );
  }
  if( opts & CONTROL_ICONIFY  ) {
    m_iconifyBtn = new FXButton( m_parent, "\t Iconify Window", ic_iconify, win, FXTopWindow::ID_MINIMIZE, FRAME_NONE | LAYOUT_RIGHT | LAYOUT_CENTER_Y );
  }

  new FXVerticalSeparator( m_parent, SEPARATOR_GROOVE|LAYOUT_FILL_Y | LAYOUT_RIGHT );
}

FXWindowController::~FXWindowController( )
{ }

/*************************************************************************************************/
void FXWindowController::create( )
{
  ic_maximize->create( );
  ic_restore->create( );
}

long FXWindowController::onCmd_WinMaximize( FXObject *sender, FXSelector sel, void *data )
{
  FXTopWindow *win = m_parent->getTopWindow( );
  
  if( win && win->isMaximized( ) ) {
	  if ( win->restore( ) ) { m_maximizeBtn->setIcon( ic_maximize ); }
  }
  else {
    /// FIXME 001: In some wm/environments (e.g. gnome) it doesn't work, win->maximize( ) behaves like win->restore( ). Find out why
	  if ( win->maximize( true ) ) { m_maximizeBtn->setIcon( ic_restore ); }
  }
  
  m_maximizeBtn->update( );
  return 1;
}

} /* FXGHI */

/*** END *****************************************************************************************/
