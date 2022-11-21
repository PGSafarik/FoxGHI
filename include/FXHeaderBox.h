/**************************************************************************************************
* FXGHI                                                                                           *
*                                                                                                 *
* Compositor pro male boxiky, pouzivany nejcasteji jako toolbar v toplevel oknech. Obdoba menu v  *
* Gnome3 applikacich.                                                                             *
* Copyryght (C) 2017 - 2022 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef __HEDERBOX_H
#define __HEADERBOX_H
/*************************************************************************
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
#include <iostream>
#include <fox-1.7/fx.h>
#include "fxghi_defs.h"
#include "FXWindowHeader.h"

namespace FXGHI {

class FXHeaderBox : public FXHorizontalFrame {
FXDECLARE( FXHeaderBox )
  FXWindowHeader *m_parent; // Window header

  FXbool m_separe; // Separing this box
  FXbool m_nohide; // No hide this box, when is small space 
  FXbool m_hidden; // Indication hide this box

  FXSelector m_message; // GUI notifycation message

public:
  FXHeaderBox( FXWindowHeader *p, FXObject *tgt = NULL, FXSelector sel = 0, FXuint opts = LAYOUT_CENTER_Y, FXint pl = -1, FXint pr = -1, FXint hs = -1 );
  virtual ~FXHeaderBox( );

  /* Operations */
  virtual void create( );
 
  /* Access Methods */
  FXWindowHeader* getBoxFrame( ) { return m_parent;  }
  FXbool getNohide( )            { return m_nohide;  }
  void setNohide( FXbool value ) { m_nohide = value; }
  FXbool getSepare( )            { return m_separe;  }
  void setSepare( FXbool value ) { m_separe = value; }

  /* GUI messages and handlers */
  enum {
    ID_RECONFIGURE = FXHorizontalFrame::ID_LAST,
    ID_LAST
  };
  long onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data );

protected:
  FXHeaderBox( ) { }

  virtual void ReadConfig( );
  virtual void WriteConfig( );
  
};

} /* FXGHI */
#endif /* __HEADERBOX_H */
