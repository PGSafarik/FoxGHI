/*************************************************************************
* FXWindowControll.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger           *
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

#include"FXWindowController.h"
#include<iostream>

using namespace FXGHI;

namespace FXGHI {

FXDEFMAP( FXWindowController ) WindowController[ ] = {
  FXMAPFUNC( SEL_COMMAND, FXWindowController::WIN_MAXIMIZE,   FXWindowController::onCmd_WinMaximize ),
  FXMAPFUNC( SEL_CHANGED, FXWindowController::ID_RECONFIGURE, FXWindowController::onCmd_Reconfigure )
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

  m_sep = new FXVerticalSeparator( m_parent, SEPARATOR_GROOVE|LAYOUT_FILL_Y | LAYOUT_RIGHT );
}

FXWindowController::~FXWindowController( )
{ }

/*************************************************************************************************/
void FXWindowController::create( )
{
  ReadConfig( );

  ic_close->create( );
  ic_maximize->create( );
  ic_iconify->create( );
  ic_restore->create( );

  if( m_hidden ) { this->hide( ); }
}

void FXWindowController::show( )
{
  if( m_closeBtn )    { m_closeBtn->show( ); }
  if( m_maximizeBtn ) { m_maximizeBtn->show( ); }
  if( m_iconifyBtn )  { m_iconifyBtn->show( ); }
  m_sep->show( );
}

void FXWindowController::hide( )
{
  if( m_closeBtn ) { m_closeBtn->hide( ); }
  if( m_maximizeBtn ) { m_maximizeBtn->hide( ); }
  if( m_iconifyBtn ) { m_iconifyBtn->hide( ); }
  m_sep->hide( );
}


long FXWindowController::onCmd_WinMaximize( FXObject *sender, FXSelector sel, void *data )
{
  FXTopWindow *win = m_parent->getTopWindow( );
    
  if( win && win->isMaximized( ) ) {
	  if ( win->restore( ) ) { m_maximizeBtn->setIcon( ic_maximize ); }
  }
  else { 
    if ( win->maximize( true ) ) { m_maximizeBtn->setIcon( ic_restore ); } 
  }
  m_maximizeBtn->update( );
  
  return 1;
}

long FXWindowController::onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data ) 
{
  #ifdef DEBUG 
  std::cout << "[DEBUG - FXGWindowController::onCmd_Reconfigure] "  << std::endl;
  #endif

  ReadConfig( );
  ( isHidden( ) ? hide( ) : show( ) );
  
  return 1;
}

void FXWindowController::ReadConfig( )
{
  FXString cf_prefix = CFG_CONTROLLER_PREFIX;  
  m_hidden = m_parent->getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".Hidden", false );

  #ifdef DEBUG 
  std::cout << "[DEBUG - FXWindowController::ReadConfig] Hidden:  "    << m_hidden << std::endl;
  //std::cout << "[ DEBUG - Object::ReadConfig] Value entry:  " << entry << std::endl;
  #endif
}

void FXWindowController::WriteConfig( )
{
  FXString cf_prefix = CFG_CONTROLLER_PREFIX;
  m_parent->getApp( )->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".Hidden", m_hidden );
     
}

} /* FXGHI */

/*** END *****************************************************************************************/
