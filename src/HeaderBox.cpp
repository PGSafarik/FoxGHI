/*************************************************************************
* HeaderBox.cpp; Copyright (c) 2022 by D.A.Tiger                         *
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

#include "HeaderBox.h" 

using namespace FXGHI;

namespace FXGHI {
/*** Base of boxes *******************************************************************************/


FXIMPLEMENT( FXGHI_HeaderBox, FXHorizontalFrame, NULL, 0 )

/*** Konstruction / destruction *******************************************************************/
FXGHI_HeaderBox::FXGHI_HeaderBox( FXWindowHeader *p, FXObject *tgt, FXSelector sel, FXuint opts, FXint pl, FXint pr, FXint hs )
                : FXHorizontalFrame( p, p->getBoxOpts( ) | opts, 0, 0, 0, 0,  
                  ( pl >= 0 ? pl : p->getBoxPl( ) ), ( pr >= 0 ? pr : p->getBoxPr( ) ), 0, 0,  
                  ( hs >= 0 ? hs : p->getBoxHs( ) ), 0 ) 
{
  m_parent = p;
  m_separe = false;
  m_nohide = false;
  m_hidden = false;

  //setTarget( tgt ? tgt : m_parent->getBoxTarget( ) );
  m_message = sel;
}

FXGHI_HeaderBox::~FXGHI_HeaderBox( )
{ }

void FXGHI_HeaderBox::create( )
{
  FXHorizontalFrame::create( );
  m_parent->recolorize( this );
}

/**************************************************************************************************/
long FXGHI_HeaderBox::onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data )
{
  m_parent->recolorize( this );

  return 1;
}

/**************************************************************************************************/
void FXGHI_HeaderBox::ReadConfig( )
{


}

void FXGHI_HeaderBox::WriteConfig( )
{


}

} /* FXGHI */
/*** END ******************************************************************************************/
