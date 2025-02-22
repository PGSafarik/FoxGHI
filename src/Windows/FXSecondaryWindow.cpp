/*************************************************************************
* FXSecondaryWindow.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger               *
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
#include "Windows/FXSecondaryWindow.h"

using namespace FXGHI;

namespace FXGHI {
FXDEFMAP( FXSecondaryWindow ) DialogBoxMap[ ] = {
  FXMAPFUNC( SEL_CLOSE,   0,                       FXSecondaryWindow::onCmdCancel ),
  FXMAPFUNC( SEL_COMMAND, FXSecondaryWindow::ID_CLOSE,  FXSecondaryWindow::onCmdCancel ),
  FXMAPFUNC( SEL_COMMAND, FXSecondaryWindow::ID_ACCEPT, FXSecondaryWindow::onCmdAccept ),
  FXMAPFUNC( SEL_CHORE,   FXSecondaryWindow::ID_CANCEL, FXSecondaryWindow::onCmdCancel ),
  FXMAPFUNC( SEL_TIMEOUT, FXSecondaryWindow::ID_CANCEL, FXSecondaryWindow::onCmdCancel ),
  FXMAPFUNC( SEL_COMMAND, FXSecondaryWindow::ID_CANCEL, FXSecondaryWindow::onCmdCancel ),
};
FXIMPLEMENT( FXSecondaryWindow, FXPrimaryWindow, DialogBoxMap, ARRAYNUMBER( DialogBoxMap ) )
/**************************************************************************************************/

FXSecondaryWindow::FXSecondaryWindow( FXApp* a, const FXString &name, FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs )
            : FXPrimaryWindow( a, name, NULL, NULL, opts, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  this->getAccelTable( )->addAccel( MKUINT( KEY_Escape, 0 ), this, FXSEL( SEL_COMMAND, ID_CANCEL ) );
}

FXSecondaryWindow::FXSecondaryWindow( FXWindow* owner, const FXString &name, FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs )
            : FXPrimaryWindow( owner, name, NULL, NULL, opts, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  this->getAccelTable( )->addAccel( MKUINT( KEY_Escape, 0 ), this, FXSEL( SEL_COMMAND, ID_CANCEL ) );
}

/**************************************************************************************************/
FXuint FXSecondaryWindow::execute( FXuint placement )
{
  this->create( );
  this->show( placement );
  this->getApp( )->refresh( );
  return this->getApp( )->runModalFor( this );
}

/**************************************************************************************************/
long FXSecondaryWindow::onCmdAccept( FXObject*, FXSelector, void* )
{
  this->getApp( )->stopModal( this, true );
  this->hide( );
  return 1;
}

long FXSecondaryWindow::onCmdCancel( FXObject*, FXSelector, void* )
{
  this->getApp( )->stopModal( this, false );
  this->hide( );
  return 1;
}

} /* FXGHI */
/*** END ******************************************************************************************/
