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

#include "FXHeaderBox.h" 

using namespace FXGHI;

namespace FXGHI {
/*** Base of boxes *******************************************************************************/


FXIMPLEMENT( FXHeaderBox, FXHorizontalFrame, NULL, 0 )

/*** Konstruction / destruction *******************************************************************/
FXHeaderBox::FXHeaderBox( FXWindowHeader *p, FXObject *tgt, FXSelector sel, FXuint opts, FXint pl, FXint pr, FXint hs )
                : FXHorizontalFrame( p, p->getBoxOpts( ) | opts, 0, 0, 0, 0,  
                  ( pl >= 0 ? pl : p->getBoxPl( ) ), ( pr >= 0 ? pr : p->getBoxPr( ) ), 0, 0,  
                  ( hs >= 0 ? hs : p->getBoxHs( ) ), 0 ) 
{
  m_parent   = p;
  m_separe   = false;
  m_nohide   = false;
  m_hidden   = false;
  m_colorize = true;

  //setTarget( tgt ? tgt : m_parent->getBoxTarget( ) );
  m_message = sel;
}

FXHeaderBox::~FXHeaderBox( )
{ }

void FXHeaderBox::create( )
{
  FXHorizontalFrame::create( );
  if( m_colorize ) { m_parent->recolorize( this ); }
}

/**************************************************************************************************/
long FXHeaderBox::onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data )
{
  m_parent->recolorize( this );

  return 1;
}

/**************************************************************************************************/
void FXHeaderBox::ReadConfig( )
{


}

void FXHeaderBox::WriteConfig( )
{


}

} /* FXGHI */
/*** END ******************************************************************************************/
