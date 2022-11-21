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

#include<fox-1.7/fx.h>
#include<fxghi.h>

int main(int argc, char **argv) {
  FXApp a( "FXGHI_SimpleWindow", "fox-desktop" );
  a.init( argc, argv );

  FXPrimaryWindow *win = new FXPrimaryWindow( &a, "Simple FoxGHI Window" );
  win->getHeader( )->setText( "Hello World!" ); 
  new FXButton( win->getHeader( ), "\t\t TEST Button", win->getMenuIcon( ), NULL, 0, BUTTON_TOOLBAR );
  
  a.create( );
  win->show( PLACEMENT_SCREEN );

  return a.run( );
}
