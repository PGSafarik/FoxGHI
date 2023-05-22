/*************************************************************************
* main.cpp; Copyright (c) 2022 by D.A.Tiger                                *
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

#include <fox-1.7/fx.h>
#include <fxghi.h>
//#include "cp.h"
#include "icons.h"

/*** UTILS ****************************************************************************************/


/*** WINDOW CLASS **********************************************************************************/
class Config : public FXPrimaryWindow {
FXDECLARE( Config )
  FXIcon *ics_small[ 9 ];
  FXIcon *ics_big[ 2 ];

public :
  Config( FXApp *a );
  virtual ~Config( );

  /* operations */
  virtual void create( );
  
protected :
  Config( ) { }

};

/**************************************************************************************************/
FXDEFMAP( Config ) CFGW_MAP[ ] = { };
FXIMPLEMENT( Config, FXPrimaryWindow, NULL, 0 )

/**************************************************************************************************/
Config::Config( FXApp *a )
      : FXPrimaryWindow( a, "FoxGHI Control Panel", NULL, NULL, CONTROLS_STATIC | WINDOW_MAIN | WINDOW_STATIC , 0, 0, 550, 250  ) 
{
  // Applications static iconspack (Oxygen)
  ics_big[ 0 ] = new FXPNGIcon( getApp( ), save22 );
  ics_big[ 1 ] = new FXPNGIcon( getApp( ), refresh22 );

  ics_small[ 0 ] = new FXPNGIcon( getApp( ), about16 );
  ics_small[ 1 ] = new FXPNGIcon( getApp( ), configure16 );
  ics_small[ 2 ] = new FXPNGIcon( getApp( ), default16 );
  ics_small[ 3 ] = new FXPNGIcon( getApp( ), exit16 );
  ics_small[ 4 ] = new FXPNGIcon( getApp( ), font16 );
  ics_small[ 5 ] = new FXPNGIcon( getApp( ), help16 );
  ics_small[ 6 ] = new FXPNGIcon( getApp( ), revert16 );
  ics_small[ 7 ] = new FXPNGIcon( getApp( ), save16 );
  ics_small[ 8 ] = new FXPNGIcon( getApp( ), refresh16 );  

  // Set Window icons
  //setIcon( ics_small[ 1 ] ); // FIXME GHICP_001: WM's incompatible behavior (or bug). See FXPrimaryWindow_001.
  
  // Set subtitle text
  getHeader( )->setText( ( getApp( )->getAppName( ) + " : " + getApp( )->getVendorName( ) ) );  

  // Create control panel frame
  GHI_ControlPanel *control = new GHI_ControlPanel( this, this, Config::ID_RECONFIGURE );  

  // Create menu
  FXMenuPane *MyMenu = new FXMenuPane( this );
  new FXMenuCommand( MyMenu, "Save",    ics_small[ 7 ], control, GHI_ControlPanel::SETTINGS_SAVE );
  new FXMenuCommand( MyMenu, "Restore", ics_small[ 8 ], control, GHI_ControlPanel::SETTINGS_RESTORE );
  new FXMenuCommand( MyMenu, "Default",         NULL,   control, GHI_ControlPanel::SETTINGS_DEFAULT );
  new FXMenuCommand( MyMenu, "Full decoration", NULL,   control, GHI_ControlPanel::SETTINGS_WINMNG );
  new FXMenuSeparator( MyMenu );
  new FXMenuCommand( MyMenu, "Help",    ics_small[ 5 ], NULL, 0 );
  new FXMenuCommand( MyMenu, "About",   ics_small[ 0 ], NULL, 0 );
  new FXMenuSeparator( MyMenu );
  new FXMenuCommand( MyMenu, "Exit",    ics_small[ 3 ], getApp( ), FXApp::ID_QUIT );
  
  // Control buttons for Window Header
  new FXMenuButton( getHeader( ), "\t\t Menu", getMenuIcon( ), MyMenu ); 
  new FXVerticalSeparator( getHeader( ) );
  new FXButton( getHeader( ), "\t\t Ulozit",  ics_big[ 0 ], control, GHI_ControlPanel::SETTINGS_SAVE,    BUTTON_TOOLBAR | LAYOUT_LEFT );
  new FXButton( getHeader( ), "\t\t Obnovit", ics_big[ 1 ], control, GHI_ControlPanel::SETTINGS_RESTORE, BUTTON_TOOLBAR | LAYOUT_LEFT );
}

Config::~Config( )
{ }

void Config::create( )
{
  FXPrimaryWindow::create( );
  show( PLACEMENT_SCREEN );
}

/*** MAIN *****************************************************************************************/
  
int main( int argc, char **argv ) {
  FXString appvendor = "FOX-DESKTOP";
  FXString appname   = "ControlPanel";

  for( FXint i = 0; i != argc; i++ ) {
	    if( strcmp( argv[ i ], "--vendor" ) == 0 ) {
	    i++;
	    appvendor = argv[ i ];
	  }
	    if( strcmp( argv[ i ], "--name" ) == 0 ) {
	    i++;
	    appname = argv[ i ];
	  }
	}

  //FXApp app( "ControlPanel", "FOX-DESKTOP" );
  FXApp app( appname, appvendor );
  app.init( argc, argv );
  new Config( &app );
  app.create( );

  return app.run( );
}
