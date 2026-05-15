//
// Created by gabriel on 13.05.26.
//

#include<Windows/FXDesktopWidget.h>
#ifndef WIN32
  #include <X11/Xlib.h>
  #include <X11/Xatom.h>

  #define DISPLAY( ) { static_cast<Display*>(getApp( )->getDisplay( ) ) }
#endif

using namespace FX;
namespace FXGHI {
FXDEFMAP( FXDesktopWidget ) FDW_MAP[ ] = {
  FXMAPFUNC( SEL_CONFIGURE, 0, FXDesktopWidget::onConfigure ),
};
FXIMPLEMENT( FXDesktopWidget, FXMainWindow, FDW_MAP, ARRAYNUMBER( FDW_MAP ) )

FXDesktopWidget::FXDesktopWidget()
{
  m_allowMode = false;
  m_instanceId = getClassName( );
  InitBaseDefaults( );
}

FXDesktopWidget::FXDesktopWidget( FXApp* app, const FXString& name, FXint x, FXint y, FXint w, FXint h )
               : FXMainWindow( app, name, nullptr, nullptr, DECOR_NONE, x, y, w, h, 0, 0, 0, 0, 0, 0 )
{
  m_allowMode = false;
  m_instanceId = getClassName( );
  
  m_position.x = x;
  m_position.y = y;
  m_size.w     = w;
  m_size.h     = h;
  m_GeomtryChanged = false;

  InitBaseDefaults( );
}

FXDesktopWidget::~FXDesktopWidget( )
{

}

void FXDesktopWidget::create( )
{
  FXMainWindow::create( );
  LoadGeometry( );
  ApplyMode( false );
}

FXbool FXDesktopWidget::close(FXbool notify)
{
  SaveGeometry( );
  return FXMainWindow::close( notify );
}

long FXDesktopWidget::onConfigure( FXObject *sender, FXSelector sel, void *data )
{
  long result = FXMainWindow::onConfigure( sender, sel, data );
  CheckGeometry( ); // FIXME: only in allow mode???
  return result;
}

void FXDesktopWidget::setWidgetType( FXDesktopWidgetType type )
{
  if( m_widgetType != type ) {
    m_widgetType = type;
    if( id( ) ) { ApplyX11Hints( ); }
  }
}

void FXDesktopWidget::SetWindowMode( FXDesktopWidgetMode mode )
{
  if( m_mode != mode ) {
    if( mode == DESKTOP_WIDGET_MODE_WINDOW && !m_allowMode ) { return; }
    m_mode = mode;
    if( id( ) ) { ApplyMode( ); }
  }
}

void FXDesktopWidget::setSkipTaskbar( FXbool value )
{
  if( m_skipTaskbar != value ) {
    m_skipTaskbar = value;
    if( id( ) ) { ApplyX11Hints( ); }
  }
}

void FXDesktopWidget::setSkipPager( FXbool value )
{
  if( m_skipPager != value ) {
    m_skipPager = value;
    if( id( ) ) { ApplyX11Hints( ); }
  }
}

void FXDesktopWidget::setSticky( FXbool value )
{
  if( m_sticky != value ) {
    m_sticky = value;
    if( id( ) ) { ApplyX11Hints( ); }
  }
}

void FXDesktopWidget::setAbove( FXbool value )
{
  if( m_above != value  ) {
    m_above = value;
    if( value ) { m_below = false; }
    if( id( ) ) { ApplyX11Hints( ); }
  }
}

void FXDesktopWidget::setBelow( FXbool value )
{
  if( m_below != value ) {
    m_below = value;
    if( value ) { m_above = false; }
    if( id( ) ) { ApplyX11Hints( ); }
  }
}

void FXDesktopWidget::ApplyX11Hints( )
{
#ifndef WIN32
  if( !id( ) || !getApp( ) || !getApp( )->getDisplay( ) ) return;

  switch( m_widgetType ) {
    case DESKTOP_WIDGET_DESKTOP:
      SetX11WindowType( "_NET_WM_WINDOW_TYPE_DESKTOP" );
      break;

    case DESKTOP_WIDGET_DOCK:
      SetX11WindowType( "_NET_WM_WINDOW_TYPE_DOCK" );
      break;

    case DESKTOP_WIDGET_UTILITY:
      SetX11WindowType( "_NET_WM_WINDOW_TYPE_UTILITY" );
      break;

    case DESKTOP_WIDGET_NORMAL:
    default:
      SetX11WindowType( "_NET_WM_WINDOW_TYPE_NORMAL" );
      break;
  }

  if( m_skipTaskbar ) AddX11State("_NET_WM_STATE_SKIP_TASKBAR");
  else                RemoveX11State("_NET_WM_STATE_SKIP_TASKBAR");

  if( m_skipPager )   AddX11State("_NET_WM_STATE_SKIP_PAGER");
  else                RemoveX11State("_NET_WM_STATE_SKIP_PAGER");

  if( m_sticky )      AddX11State("_NET_WM_STATE_STICKY");
  else                RemoveX11State("_NET_WM_STATE_STICKY");

  if( m_above )       AddX11State("_NET_WM_STATE_ABOVE");
  else                RemoveX11State("_NET_WM_STATE_ABOVE");

  if( m_below )       AddX11State("_NET_WM_STATE_BELOW");
  else                RemoveX11State("_NET_WM_STATE_BELOW");

  XFlush( DISPLAY( ) );
#endif
}

void FXDesktopWidget::SetX11WindowType(const char* atomName)
{
#ifndef WIN32
  Display* dpy  = DISPLAY( );
  Atom property = XInternAtom( dpy, "_NET_WM_WINDOW_TYPE", False );
  Atom value    = XInternAtom( dpy, atomName, False );

  XChangeProperty(
    dpy,
    id( ),
    property,
    XA_ATOM,
    32,
    PropModeReplace,
    reinterpret_cast<const unsigned char*>( &value ), //(unsigned char*)&value,
    1
  );
#endif
}

void FXDesktopWidget::AddX11State( const char* atomName )
{
#ifndef WIN32
  Display* dpy = DISPLAY( );
  Atom property = XInternAtom( dpy, "_NET_WM_STATE", False );
  Atom state    = XInternAtom( dpy, atomName, False );

  Atom atoms[32];
  int count = 0;

  Atom actualType;
  int actualFormat;
  unsigned long nitems, bytesAfter;
  unsigned char* data = nullptr;

  if( XGetWindowProperty(
      dpy,
      id( ),
      property,
      0,
      32,
      False,
      XA_ATOM,
      &actualType,
      &actualFormat,
      &nitems,
      &bytesAfter,
      &data
    ) == Success && data ) {

    Atom* oldAtoms = reinterpret_cast<Atom*>( data ); //(Atom*)data;

    for( unsigned long i = 0; i < nitems && count < 32; ++i ) {
      atoms[ count++ ] = oldAtoms[ i ];
      if( oldAtoms[ i ] == state ) {
        XFree( data );
        return;
      }
    }

    XFree( data );
  }

  if( count < 32 ) {
    atoms[ count++ ] = state;
  }

  XChangeProperty(
    dpy,
    (Window)id(),
    property,
    XA_ATOM,
    32,
    PropModeReplace,
    reinterpret_cast<const unsigned char*>( atoms ),
    count
  );
#endif
}

void FXDesktopWidget::RemoveX11State( const char* atomName )
{
#ifndef WIN32
  Display* dpy = DISPLAY( );
  Atom property = XInternAtom( dpy, "_NET_WM_STATE", False );
  Atom state    = XInternAtom( dpy, atomName, False );

  Atom atoms[32];
  int count = 0;

  Atom actualType;
  int actualFormat;
  unsigned long nitems, bytesAfter;
  unsigned char* data = nullptr;

  if( XGetWindowProperty(
      dpy,
      id( ),
      property,
      0,
      32,
      False,
      XA_ATOM,
      &actualType,
      &actualFormat,
      &nitems,
      &bytesAfter,
      &data
    ) == Success && data ) {

    Atom* oldAtoms = reinterpret_cast<Atom*>( data );

    for( unsigned long i = 0; i < nitems && count < 32; ++i ) {
      if( oldAtoms[ i ] != state ) {
        atoms[ count++ ] = oldAtoms[ i ];
      }
    }

    XFree( data );
  }

  XChangeProperty(
    dpy,
    id(),
    property,
    XA_ATOM,
    32,
    PropModeReplace,
    reinterpret_cast<const unsigned char*>( atoms ),
    count
  );
#endif
}

void FXDesktopWidget::ApplyMode( FXbool remap )
{
  FXbool was_shown = shown( );

  if( was_shown && remap ) { hide( ); }

  if ( m_mode == DESKTOP_WIDGET_MODE_WIDGET ) {
    setLockModeDefaults( );
    setDecorations( m_widgetDecor );
  }
  else {
    setUnlockModeDefaults( );
    setDecorations( m_windowDecor );
  }

  if( id( ) ) { ApplyX11Hints( ); }
  if( was_shown && remap ) { show( ); }
}

void FXDesktopWidget::InitBaseDefaults( )
{
  // Widget mode
  m_mode = DESKTOP_WIDGET_MODE_WIDGET;
  m_widgetDecor = DECOR_NONE;
  m_windowDecor = DECOR_BORDER | DECOR_RESIZE | DECOR_TITLE;

  // Window properties
  m_widgetType = DESKTOP_WIDGET_UTILITY;
  m_skipTaskbar = true;
  m_skipPager = true;
  m_sticky = true;
  m_above = false;
  m_below = false;
}

void FXDesktopWidget::setLockModeDefaults( )
{
  m_widgetType = DESKTOP_WIDGET_UTILITY;
  m_skipTaskbar = true;
  m_skipPager = true;
  m_sticky = true;
  m_above = false;
  m_below = true;
}

void FXDesktopWidget::setUnlockModeDefaults( )
{
  m_widgetType = DESKTOP_WIDGET_NORMAL;
  m_skipTaskbar = false;
  m_skipPager = false;
  m_sticky = false;
  m_above = false;
  m_below = false;
}

void FXDesktopWidget::CheckGeometry( )
{
  m_position.x = getX( );
  m_position.y = getY( );
  m_size.w     = getWidth( );
  m_size.h     = getHeight( );

  m_GeomtryChanged = true;
}


void FXDesktopWidget::LoadGeometry( )
{
  if( getApp( )->reg( ).existingSection( m_instanceId ) ) {
    m_position.x = getApp( )->reg( ).readIntEntry( m_instanceId, "X", 0 );
    m_position.y = getApp( )->reg( ).readIntEntry( m_instanceId, "Y", 0 );
    m_size.w     = getApp( )->reg( ).readIntEntry( m_instanceId, "Width", DEFAULT_WIDGET_WIDTH );
    m_size.h     = getApp( )->reg( ).readIntEntry( m_instanceId, "Height", DEFAULT_WIDGET_HEIGHT );

    setX( m_position.x );
    setY( m_position.y );
    setWidth( m_size.w );
    setHeight( m_size.h );

    m_GeomtryChanged = false;
  }
}

void FXDesktopWidget::SaveGeometry( )
{
  if( m_GeomtryChanged ) {
    getApp( )->reg( ).writeIntEntry( m_instanceId, "X", m_position.x );
    getApp( )->reg( ).writeIntEntry( m_instanceId, "Y", m_position.y );
    getApp( )->reg( ).writeIntEntry( m_instanceId, "Width", m_size.w );
    getApp( )->reg( ).writeIntEntry( m_instanceId, "Height", m_size.h );

    m_GeomtryChanged = false;
  }
}

}
