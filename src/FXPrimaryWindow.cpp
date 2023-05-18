/*************************************************************************
* FXPrimaryWindow.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger           *
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
#include "FXPrimaryWindow.h"

using namespace FXGHI;

#define DISPLAY( app ) ( ( Display* )( app->getDisplay( ) ) )

namespace FXGHI {

FXDEFMAP( FXPrimaryWindow ) PrimaryWindowMap[ ] = {
  FXMAPFUNC( SEL_PAINT,             0,                         FXPrimaryWindow::onPaint ),
  FXMAPFUNC( SEL_CONFIGURE,         0,                         FXPrimaryWindow::onConfigure ),
  FXMAPFUNC( SEL_LEFTBUTTONPRESS,   0,                         FXPrimaryWindow::onLeftButtonPress ),
  FXMAPFUNC( SEL_LEFTBUTTONPRESS,   FXPrimaryWindow::ID_WINHEADER,   FXPrimaryWindow::onLeftButtonPress ),
  FXMAPFUNC( SEL_LEFTBUTTONRELEASE, 0,                         FXPrimaryWindow::onLeftButtonRelease ),
  FXMAPFUNC( SEL_MOTION,            0,                         FXPrimaryWindow::onMotion ),
  FXMAPFUNC( SEL_CHANGED,           FXPrimaryWindow::ID_RECONFIGURE, FXPrimaryWindow::onCmd_Reconfigure)           
};
FXIMPLEMENT( FXPrimaryWindow, FXTopWindow, PrimaryWindowMap, ARRAYNUMBER( PrimaryWindowMap ) )

/**************************************************************************************************/
FXPrimaryWindow::FXPrimaryWindow( FXApp *app, const FXString &title, FXIcon *ic, FXIcon *mi, FXuint opts,
		       FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs  )
         : FXTopWindow( app, title, ic, mi, DECOR_RESIZE, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  #ifdef DEBUG 
  std::cout << "[DEBUG - FXPrimaryWindow::FXPrimaryWindow ] !!!Library is building in DEBUG MODE!!!\n";
  #endif

  w_opts = opts;
  w_WMDecor = DECOR_ALL;
  w_grab = DRAG_NONE;
  w_rect.set( 0, 0, 0, 0 );
  w_last.set( 0, 0 );
  w_header     = new FXWindowHeader( this, FXString::null, this, FXPrimaryWindow::ID_WINHEADER, WHEADER_STANDARD | WHEADER_DELEGATE );
  w_controller = new FXWindowController( w_header, w_opts );

  this->enable( );
  if( opts & WINDOW_CLIENTSIZE ) { RecalculateSize( ); }

  w_menuic  = new FXPNGIcon( getApp( ), window_menu_icdata );
  w_omenuic = new FXPNGIcon( getApp( ), overflow_menu_icdata );
}

FXPrimaryWindow::FXPrimaryWindow( FXWindow *owner, const FXString &title, FXIcon *ic, FXIcon *mi, FXuint opts,
		       FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs  )
         : FXTopWindow( owner, title, ic, mi, DECOR_RESIZE, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  w_opts = opts;
  w_grab = DRAG_NONE;
  w_WMDecor = DECOR_ALL;
  w_rect.set( 0, 0, 0, 0 );
  w_last.set( 0, 0 );
  w_header     = new FXWindowHeader( this, FXString::null, this, FXPrimaryWindow::ID_WINHEADER, WHEADER_STANDARD | WHEADER_DELEGATE  );
  w_controller = new FXWindowController( w_header, w_opts );

  this->enable( );
  if( opts & WINDOW_CLIENTSIZE ) { RecalculateSize( ); }

  w_menuic = new FXPNGIcon( getApp( ), window_menu_icdata );
  w_omenuic = new FXPNGIcon( getApp( ), overflow_menu_icdata );
}

FXPrimaryWindow::~FXPrimaryWindow( )
{ }

/**************************************************************************************************/
void FXPrimaryWindow::create( )
{
  ReadConfig( );

  if( w_WMControl ) {
    #ifdef DEBUG 
    std::cout << "[DEBUG - " <<  getClassName( ) << "::create( )]: Activate WM decorations " << w_WMDecor << std::endl;
    #endif 
    setDecorations( w_WMDecor );
  }

  FXTopWindow::create( );
  w_controller->create( );
  RecalculateSize( );

  if( ( w_opts & WINDOW_MAIN ) && xid ) {
	  FXApp *a = this->getApp( );
	  if( a->isInitialized( ) ) {
	    #ifndef WIN32
	    XSetCommand( DISPLAY( a ), xid, ( char** ) a->getArgv( ), a->getArgc( ) );
	    #endif 
	  }
  }
}

FXbool FXPrimaryWindow::close( FXbool notify )
{
  /* Close this window */
  // Reimplement from FXTopWindow so that this function accept a primary FXPrimaryWindow like the FXMainWidow
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
      if( window != this && window->isMemberOf( FXMETACLASS( FXPrimaryWindow ) ) ) {
		  // If is the chcked window signed as primary, no closing this aplication...
	      if( dynamic_cast<FXPrimaryWindow*>( window )->isPrimary( ) ) {
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
long FXPrimaryWindow::onPaint( FXObject *sender, FXSelector sel, void *data )
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

long FXPrimaryWindow::onLeftButtonPress( FXObject *sender, FXSelector sel, void *data )
{
  /* Grab this window of left mouse button, begin on move or resize this window */
  long resh = 0;

  flags &= ~FLAG_TIP;
  handle( this, FXSEL( SEL_FOCUS_SELF, 0 ), data );

  if( isEnabled( ) && w_SelfControl ) {
	  FXEvent *event = static_cast<FXEvent*>( data );

    if( FXSELID( sel ) == FXPrimaryWindow::ID_WINHEADER ) { w_grab = DRAG_MOVE; }
    else { w_grab = Where( event->win_x, event->win_y ); }

    if( w_grab != DRAG_NONE ) {   
      grab( );
      w_rect.set( getX( ), getY( ), getWidth( ), getHeight( ) );
      w_last.set( event->root_x, event->root_y );

      Cursor_Change( );
    }

	  resh = 1;
  }
  return resh;
}

long FXPrimaryWindow::onLeftButtonRelease( FXObject *sender, FXSelector sel, void *data )
{
  /* Ungrab this window of left mouse button, end of move or resize this window */
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

long FXPrimaryWindow::onMotion( FXObject *sender, FXSelector sel, void *data )
{
  /* Moving the window */
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

long FXPrimaryWindow::onConfigure( FXObject *sender, FXSelector sel, void *data )
{
  /* handler for a FXWindow configure type notify */
  // #ifdef DEBUG 
  // std::cout << "[DEBUG - FXPrimaryWindow::onCmd_Reconfigure]: Configure Handler for " << getClassName( ) <<  std::endl;
  // #endif

  FXTopWindow::onConfigure( sender, sel, data );
  w_controller->handle( this, FXSEL( SEL_CONFIGURE, 0 ), NULL );
  w_header->handle( this, FXSEL( SEL_CONFIGURE, 0 ), NULL );
  
  return 1;
}

long FXPrimaryWindow::onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data )
{
  /* request to change window settings */
  #ifdef DEBUG 
  std::cout << "[DEBUG - FXPrimaryWindow::onCmd_Reconfigure] " << getClassName( )  << std::endl;
  #endif
  
  ReadConfig( );
  setDecorations( ( w_WMControl ? w_WMDecor : DECOR_RESIZE  ) );

  w_controller->tryHandle( this, FXSEL( SEL_CHANGED, FXWindowController::ID_RECONFIGURE ), NULL );
  w_header->tryHandle(     this, FXSEL( SEL_CHANGED, FXWindowHeader::ID_RECONFIGURE ),     NULL );

  return 1;
}


/*************************************************************************************************/
FXuint FXPrimaryWindow::Where( FXint pos_x, FXint pos_y )
{
  /* Check out exactly where the window is captured by the mouse (from FXWM)*/
  FXuint s = DRAG_NONE;
  if( !( w_opts & WINDOW_STATIC ) ) {
    if( pos_x < getPadLeft( ) )                   { s |= DRAG_LEFT; }
    if( getWidth( ) - getPadRight( ) <= pos_x )   { s |= DRAG_RIGHT; }
    if( pos_y < getPadTop( ) )                    { s |= DRAG_TOP; }
    if( getHeight( ) - getPadBottom( ) <= pos_y ) { s |= DRAG_BOTTOM; }
  }

  return s;
}

void FXPrimaryWindow::Cursor_Change( )
{
  /* Determine the necessary mouse cursor change (from FXWM) */
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

void FXPrimaryWindow::Cursor_Revert( )
{
  /* Return the to default mouse cursor (from FXWM) */
  Cursor_Set( DEF_ARROW_CURSOR );
}

void FXPrimaryWindow::Cursor_Set( FXDefaultCursor cursor_id )
{
  /* Set the mouse cursor (from FXWM) */ 
  FXCursor *cursor = getApp( )->getDefaultCursor( cursor_id );
  setDefaultCursor( cursor );
  setDragCursor( cursor );
}

void FXPrimaryWindow::RecalculateSize( )
{
  FXint width  = getPadLeft( ) + getPadRight( ) + getWidth( );
  FXint height = getPadTop( ) + getPadBottom( ) + getVSpacing( ) + getHeight( ) + w_header->getHeight( );

  this->resize( width, height );
}

void FXPrimaryWindow::ReadConfig( )
{
  FXString cf_prefix = CFG_WINDOW_PREFIX;  
   
  if ( getApp( )->reg( ).used( ) < 1 ) { getApp( )->reg( ).read( ); } 

   w_border      = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".EnableBorder", true );
   w_SelfControl = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".SelfControl",  true );
   w_WMControl   = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".WMControl",    false );

   #ifdef DEBUG 
   std::cout << "[DEBUG - FXPrimaryWindow::ReadConfig] border: "                 << w_border      << std::endl;
   std::cout << "[DEBUG - FXPrimaryWindow::ReadConfig] Window selfcontrol: "     << w_SelfControl << std::endl;
   std::cout << "[DEBUG - FXPrimaryWindow::ReadConfig] Window Manager control: " << w_WMControl << std::endl;
   #endif

}

void FXPrimaryWindow::WriteConfig( )
{
  FXString cf_prefix = CFG_WINDOW_PREFIX; 

  getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".EnableBorder", w_border );
  getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".SelfControl",  w_SelfControl );
  getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".WMControl",    w_WMControl );

}


} /* FXGHI */
/*** END ******************************************************************************************/
