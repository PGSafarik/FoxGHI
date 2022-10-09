/*************************************************************************
* FXGWindow.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger           *
*                                                                        *
* This program is free software: you can redistribute it and/or modify   *
* it under the terms of the GNU Lesser General Public License as         *
* published by the Free Software Foundation, either version 3 of the     *
* License, or (at your option) any later version.                        *
*                                                                        *
* This program is distributed in the hope that it will be useful,        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of         *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
* GNU General Public License for more details.                           *
*                                                                        *
* You should have received a copy of the GNU General Public License      *
* along with this program.  If not, see <https://www.gnu.org/licenses/>. *
*************************************************************************/
#include<fox-1.7/xincs.h>
#include "FXGWindow.h"

using namespace FXGHI;

#define DISPLAY( app ) ( ( Display* )( app->getDisplay( ) ) )

namespace FXGHI {

FXDEFMAP( FXGWindow ) PrimaryWindowMap[ ] = {
  FXMAPFUNC( SEL_PAINT,             0,                       FXGWindow::onPaint ),
  FXMAPFUNC( SEL_LEFTBUTTONPRESS,   0,                       FXGWindow::onLeftButtonPress ),
  FXMAPFUNC( SEL_LEFTBUTTONPRESS,   FXGWindow::ID_WINHEADER, FXGWindow::onLeftButtonPress ),
  FXMAPFUNC( SEL_LEFTBUTTONRELEASE, 0,                       FXGWindow::onLeftButtonRelease ),
  FXMAPFUNC( SEL_MOTION,            0,                       FXGWindow::onMotion )
};
FXIMPLEMENT( FXGWindow, FXTopWindow, PrimaryWindowMap, ARRAYNUMBER( PrimaryWindowMap ) )

/**************************************************************************************************/
FXGWindow::FXGWindow( FXApp *app, const FXString &title, FXIcon *ic, FXIcon *mi, FXuint opts,
		       FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs  )
         : FXTopWindow( app, title, ic, mi, DECOR_RESIZE , x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  #ifdef DEBUG 
  std::cout << "[ DEBUG - FXGWindow::FXGWindow ] !!!Library is building in DEBUG MODE!!!\n";
  #endif

  w_opts = opts;
  w_grab = DRAG_NONE;
  w_rect.set( 0, 0, 0, 0 );
  w_last.set( 0, 0 );
  w_header     = new FXWindowHeader( this, FXString::null, this, FXGWindow::ID_WINHEADER, WHEADER_STANDARD | WHEADER_DELEGATE );
  w_controller = new FXWindowController( w_header, w_opts );

  this->enable( );
  if( opts & WINDOW_CLIENTSIZE ) { RecalculateSize( ); }

  w_menuic = new FXPNGIcon( getApp( ), window_menu_icdata );
}

FXGWindow::FXGWindow( FXWindow *owner, const FXString &title, FXIcon *ic, FXIcon *mi, FXuint opts,
		       FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs  )
         : FXTopWindow( owner, title, ic, mi, DECOR_RESIZE , x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  w_opts = opts;
  w_grab = DRAG_NONE;
  w_rect.set( 0, 0, 0, 0 );
  w_last.set( 0, 0 );
  w_header     = new FXWindowHeader( this, FXString::null, this, FXGWindow::ID_WINHEADER, WHEADER_STANDARD | WHEADER_DELEGATE  );
  w_controller = new FXWindowController( w_header, w_opts );

  this->enable( );
  if( opts & WINDOW_CLIENTSIZE ) { RecalculateSize( ); }

  w_menuic = new FXPNGIcon( getApp( ), window_menu_icdata );
}

FXGWindow::~FXGWindow( )
{  
  //WriteConfig( );
}

/**************************************************************************************************/
void FXGWindow::create( )
{
  ReadConfig( );

  if( w_WMControl ) {
    setDecorations( DECOR_ALL );
  }

  FXTopWindow::create( );
  w_controller->create( );
  RecalculateSize( );

  if( ( w_opts & WINDOW_PRIMARY ) && xid ) {
	  FXApp *a = this->getApp( );
	  if( a->isInitialized( ) ) {
	    #ifndef WIN32
	    XSetCommand( DISPLAY( a ), xid, ( char** ) a->getArgv( ), a->getArgc( ) );
	    #endif // WIN32
	  }
  }
}

FXbool FXGWindow::close( FXbool notify )
{
  // Reimplement from FXTopWindow so that this function accept a primary FXGWindow like the FXMainWidow
  FXWindow *window;
  FXbool    quit = true;
  FXbool    resh = false;

  // Ask target if desired
  if( !notify || !target || !target->tryHandle( this, FXSEL( SEL_CLOSE, message ), NULL ) ) {
    // Target will receive no further messages from us
    setTarget( NULL );
    setSelector( 0 );

    // If there was another main level window still visible, that's all we do
    for( window = getRoot( )->getFirst( ); window; window = window->getNext( ) ) {
      if( window != this && window->isMemberOf( FXMETACLASS( FXGWindow ) ) ) {
		  // If is the chcked window signed as primary, no closing this aplication...
	      if( dynamic_cast<FXGWindow*>( window )->isPrimary( ) ) {
		      // I don't like jumping
		      quit = false;
		      break;
	      }
      }
    }

    // We've just hidden the last remaining top level window:- quit the application
    if( quit ) { getApp( )->handle( this, FXSEL( SEL_COMMAND, FXApp::ID_QUIT ), NULL ); }

    // Self destruct
    delete this;

    // Was closed
    resh = true;
  }

  return resh;
}


/*************************************************************************************************/
long FXGWindow::onPaint( FXObject *sender, FXSelector sel, void *data )
{
  /* Rendering of the line window border. Without it, it would look "sprawling" */
  long r = FXTopWindow::onPaint( sender, sel, data );
  
  if( w_border ) {
    FXDCWindow dc( this );
    dc.setForeground( FXRGB( 0, 0, 0 ) );
    dc.drawRectangle( 0, 0, this->getWidth( ) - 1, this->getHeight( ) - 1 );
  }

  return r;
}

long FXGWindow::onLeftButtonPress( FXObject *sender, FXSelector sel, void *data )
{
  /* Grab this window of left mouse button */
  long resh = 0;

  flags &= ~FLAG_TIP;
  handle( this, FXSEL( SEL_FOCUS_SELF, 0 ), data );

  if( isEnabled( ) && w_SelfControl ) {
	  FXEvent *event = static_cast<FXEvent*>( data );
    grab( );

    if( FXSELID( sel ) == FXGWindow::ID_WINHEADER ) { w_grab = DRAG_MOVE; }
    else { w_grab = Where( event->win_x, event->win_y ); }

    w_rect.set( getX( ), getY( ), getWidth( ), getHeight( ) );
    w_last.set( event->root_x, event->root_y );

    Cursor_Change( );

	  resh = 1;
  }

  return resh;
}

long FXGWindow::onLeftButtonRelease( FXObject *sender, FXSelector sel, void *data )
{
  /* Ungrab this window of left mouse button */
  long resh = 0;

  if( isEnabled( ) && w_SelfControl ) {
	  
	  if( w_grab != DRAG_NONE ) {
      ungrab( ); 
	    //position( w_rect.x, w_rect.y, w_rect.w, w_rect.h );
	    w_grab = DRAG_NONE;
	    w_last.set( 0, 0 );
	    w_rect.set( 0, 0, 0, 0 );
	    Cursor_Change( );
	  }

    resh = 1;
  }

  return resh;
}

long FXGWindow::onMotion( FXObject *sender, FXSelector sel, void *data )
{
  long res = 0;

  if( w_grab != DRAG_NONE ) {
    FXEvent *event = static_cast<FXEvent*>( data );

    // Calculate the cursor position differention
    FXPoint offset( w_last.x - event->root_x, w_last.y - event->root_y );
    w_last.set( event->root_x, event->root_y );

    // Calculate for window position, if sending window header
    if( w_grab & DRAG_MOVE ) {
	    w_rect.x -= offset.x;
	    w_rect.y -= offset.y;
    }
    else {
      // Calculate window resize values on top and bottom side
      if( w_grab & DRAG_TOP ) {
	      w_rect.y = w_rect.y - offset.y;
        w_rect.h = w_rect.h + offset.y;
      }
      else if( w_grab & DRAG_BOTTOM ) {
  	    w_rect.h = w_rect.h - offset.y;
      }

      // Window resize values on right and left side
      if( w_grab & DRAG_LEFT ) {
  	    w_rect.x = w_rect.x - offset.x;
  	    w_rect.w = w_rect.w + offset.x;
      }
      else if( w_grab & DRAG_RIGHT ) {
  	    w_rect.w = w_rect.w - offset.x;
      }
    }

    // Set window size and position
    position( w_rect.x, w_rect.y, w_rect.w, w_rect.h );
  }

  return res;
}
/*************************************************************************************************/
FXuint FXGWindow::Where( FXint pos_x, FXint pos_y )
{
  FXuint s = DRAG_NONE;
  if( !( w_opts & WINDOW_STATIC ) ) {
    if( pos_x < getPadLeft( ) )                   { s |= DRAG_LEFT; }
    if( getWidth( ) - getPadRight( ) <= pos_x )   { s |= DRAG_RIGHT; }
    if( pos_y < getPadTop( ) )                    { s |= DRAG_TOP; }
    if( getHeight( ) - getPadBottom( ) <= pos_y ) { s |= DRAG_BOTTOM; }
  }

  return s;
}

void FXGWindow::Cursor_Change( )
{
  switch( w_grab ) {
    case DRAG_TOP :
    case DRAG_BOTTOM:
		Cursor_Set( DEF_DRAGH_CURSOR );
		break;
    case DRAG_LEFT :
    case DRAG_RIGHT:
		Cursor_Set( DEF_DRAGV_CURSOR );
		break;
    case DRAG_TOPLEFT :
    case DRAG_BOTTOMRIGHT:
		Cursor_Set( DEF_DRAGTL_CURSOR );
		break;
    case DRAG_TOPRIGHT :
    case DRAG_BOTTOMLEFT:
		Cursor_Set( DEF_DRAGTR_CURSOR );
		break;
	  case DRAG_MOVE:
		Cursor_Set( DEF_MOVE_CURSOR );
		break;
    default:
	  Cursor_Revert( );
  }
}

void FXGWindow::Cursor_Revert( )
{
  Cursor_Set( DEF_ARROW_CURSOR );
}

void FXGWindow::Cursor_Set( FXDefaultCursor cursor_id )
{
  FXCursor *cursor = getApp( )->getDefaultCursor( cursor_id );
  setDefaultCursor( cursor );
  setDragCursor( cursor );
}

void FXGWindow::RecalculateSize( )
{
  FXint width  = getPadLeft( ) + getPadRight( ) + getWidth( );
  FXint height = getPadTop( ) + getPadBottom( ) + getVSpacing( ) + getHeight( ) + w_header->getHeight( );

  this->resize( width, height );
}

void FXGWindow::ReadConfig( )
{
  FXString cf_prefix = CFG_WIDOW_PREFIX;  
   
  if ( getApp( )->reg( ).used( ) < 1 ) { getApp( )->reg( ).read( ); }  

   w_border      = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".EnableBorder", true );
   w_SelfControl = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".SelfControl",  true );
   w_WMControl   = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".WMControl",    false );

   #ifdef DEBUG 
   std::cout << "[DEBUG - FXGWindow::ReadConfig] border: "                 << w_border      << std::endl;
   std::cout << "[DEBUG - FXGWindow::ReadConfig] Window selfcontrol: "     << w_SelfControl << std::endl;
   std::cout << "[DEBUG - FXGWindow::ReadConfig] Window Manager control: " << w_WMControl << std::endl;
   #endif

}

void FXGWindow::WriteConfig( )
{
  FXString cf_prefix = CFG_WIDOW_PREFIX; 

  getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".EnableBorder", w_border );
  getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".SelfControl",  w_SelfControl );
  getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".WMControl",    w_WMControl );

}


} /* FXGHI */
/*** END ******************************************************************************************/
