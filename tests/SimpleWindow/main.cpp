#include<fox-1.7/fx.h>
#include<fxghi.h>

int main(int argc, char **argv) {
  FXApp a( "FXGHI_SimpleWindow", "fox-desktop" );
  a.init( argc, argv );

  FXGWindow *win = new FXGWindow( &a, "Simple FoxGHI Window" );
  win->getHeader( )->setText( "Hello World!" ); 
  new FXButton( win->getHeader( ), "\t\t TEST Button", win->getMenuIcon( ), NULL, 0 );
  
  a.create( );
  win->show( PLACEMENT_SCREEN );

  return a.run( );
}
