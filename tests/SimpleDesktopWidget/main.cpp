/*************************************************************************
* This program is free software: you can redistribute it and/or modify   *
* it under the terms of the GNU General Public License as published by   *
* the Free Software Foundation, either version 3 of the License, or      *
* (at your option) any later version.                                    *
*                                                                        *
* This program is distributed in the hope that it will be useful,        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of         *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
* GNU General Public License for more details.                           *
*                                                                        *
* You should have received a copy of the GNU General Public License      *
* along with this program.  If not, see <https://www.gnu.org/licenses/>. *
*************************************************************************/

/*************************************************************************
* main.cpp                                                               *
*                                                                        *
* Example 01 - Simple main Window with FoxGHI                            *
* Copyright (c) 10/09/2022 D.A.Tiger <drakarax@seznam.cz>                *
*************************************************************************/
#include<iostream>
#include<fox-1.7/fx.h>
#include<fxghi.h>

#define DEFAULT_POS_X 200
#define DEFAULT_POS_Y 150

class DesktopWidget : public FXDesktopWidget {
FXDECLARE( DesktopWidget )
  FXButton *m_close_btn;
  FXButton *m_config_btn;
  FXLabel  *m_display;

public:
  DesktopWidget( FXApp *a, const FXString& title );
  virtual ~DesktopWidget( );

  /* Acess methods */

  /* Operations */
  void create( ) override;

  /* GUI Messageges & handlers */
  enum {
    ID_EXIT = FXDesktopWidget::ID_LAST,
    ID_CONFIGURE,
    ID_TIME,
    ID_LAST
  };

  long onCmd_Quit( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Configure( FXObject *sender, FXSelector sel, void *data );
  long onTimer( FXObject *sender, FXSelector sel, void *data );

protected:
  DesktopWidget( ) { }
//  void ReadWindowGeometry( );
//  void WriteWindowGeometry( );
};

/**************************************************************************************************/
FXDEFMAP( DesktopWidget ) DW_MAP[ ] = {
  FXMAPFUNC( SEL_COMMAND, DesktopWidget::ID_EXIT, DesktopWidget::onCmd_Quit )
};

FXIMPLEMENT( DesktopWidget, FXDesktopWidget, DW_MAP, ARRAYNUMBER( DW_MAP ) )

DesktopWidget::DesktopWidget( FXApp *a, const FXString &title )
              : FXDesktopWidget( a, title, DEFAULT_POS_X, DEFAULT_POS_Y )
{
  //ReadWindowGeometry( );

  FXHorizontalFrame *frame = new FXHorizontalFrame( this, FRAME_NONE | LAYOUT_FILL_X, 0, 0, 0, 0,  0, 0, 0, 0,  0, 0 );
  m_close_btn = new FXButton( frame, "Close", NULL, this, ID_EXIT, BUTTON_TOOLBAR | LAYOUT_RIGHT );
  m_config_btn = new FXButton( frame, "Config", NULL, NULL, 0, BUTTON_TOOLBAR | LAYOUT_RIGHT );
  FXHorizontalFrame *timer = new FXHorizontalFrame( this, FRAME_NONE | LAYOUT_FILL );
  m_display = new FXLabel( timer, "Hello World!", NULL, LABEL_NORMAL | LAYOUT_FILL | JUSTIFY_CENTER_X | JUSTIFY_CENTER_Y );
}

DesktopWidget::~DesktopWidget( )
{

}

void DesktopWidget::create( )
{
  FXDesktopWidget::create( );
  show( PLACEMENT_SCREEN );
}
/*
void DesktopWidget::ReadWindowGeometry( )
{
  FXPoint pos;
  FXSize  size;

  pos.x = getApp( )->reg( ).readIntEntry( "Window", "X", DEFAULT_POS_X );
  pos.y = getApp( )->reg( ).readIntEntry( "Window", "Y", DEFAULT_POS_Y );
  size.w = getApp( )->reg( ).readIntEntry( "Window", "Width", DEFAULT_WIDGET_WIDTH );
  size.h = getApp( )->reg( ).readIntEntry( "Window", "Height", DEFAULT_WIDGET_HEIGHT );

  setX( pos.x );
  setY( pos.y );
  setWidth( size.w );
  setHeight( size.h );
}

void DesktopWidget::WriteWindowGeometry( )
{
  FXPoint pos;
  FXSize  size;

  pos.x = getX( );
  pos.y = getY( );
  size.w = getWidth( );
  size.h = getHeight( );

  getApp( )->reg( ).writeIntEntry( "Window", "X", pos.x );
  getApp( )->reg( ).writeIntEntry( "Window", "Y", pos.y );
  getApp( )->reg( ).writeIntEntry( "Window", "Width", size.w );
  getApp( )->reg( ).writeIntEntry( "Window", "Height", size.h );
}
*/
long DesktopWidget::onCmd_Quit(FXObject *sender, FXSelector sel, void *data)
{
   if( FXMessageBox::question( this, MBOX_YES_NO,"Quit", "Do you want to quit?" ) == MBOX_CLICKED_YES ) {
     getApp( )->exit( );
   }
   return 1;
}

/**************************************************************************************************/
int main(int argc, char **argv) {
  FXApp a( "FXGHI_SimpleDesktopWidget", "fox-desktop" );
  a.init( argc, argv );
  std::cout << FXGHI::Version::PROJECT_NAME << ": " << FXGHI::Version::FULLVERSION_STRING <<  std::endl;
  
  DesktopWidget *win = new DesktopWidget( &a, "Simple FoxGHI Window" );

  a.create( );
  return a.run( );
}
