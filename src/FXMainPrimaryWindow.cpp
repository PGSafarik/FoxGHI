#include "FXMainPrimaryWindow.h"
#include<fox-1.7/xincs.h>

#define DISPLAY( app ) ( ( Display* )( app->getDisplay( ) ) )
/*
FXDEFMAP( FXMainPrimaryWindow ) WindowSimpleMainMap[ ] = {
  FXMAPFUNC( SEL_PAINT, 0, FXMainPrimaryWindow::onPaint )
};*/
FXIMPLEMENT( FXMainPrimaryWindow, FXPrimaryWindow, NULL, 0 )

/**************************************************************************************************/
FXMainPrimaryWindow::FXMainPrimaryWindow( FXApp *app, const FXString &title, FXIcon *ic, FXIcon *mi, FXuint opts,
		      FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs  )
                  : FXPrimaryWindow( app, title, ic, mi, DECOR_RESIZE, x, y, w, h, pl, pr, pt, pb, hs, vs )
{ }

FXMainPrimaryWindow::~FXMainPrimaryWindow( )
{ }

/**************************************************************************************************/
void FXMainPrimaryWindow::create( )
{
  FXTopWindow::create( );
  if( xid ) {
	FXApp *app = this->getApp( );
	if( app->isInitialized( ) ) {
       #ifndef WIN32
       XSetCommand( DISPLAY( app ), xid, (char**) app->getArgv( ), app->getArgc( ) );
       #endif // WIN32
	}
  }
}
