/**************************************************************************************************
* FXWindowController.h                                                                              *
*                                                                                                 *
* A box in the Header Bar controlling the state of the parent top-level window (iconification,    *
* closing, maximizing, etc...)                                                                    *
* Copyryght (C) 2019 - 2025 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef FXGHI_CONTROLLER_H
#define FXGHI_CONTROLLER_H

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
#include "Core.h"
#include "FXWindowHeader.h"

namespace FXGHI {

class FXWindowController : public FXObject {
FXDECLARE( FXWindowController )
  FXWindowHeader *m_parent;  // Pointer on the HeaderBar

  FXButton *m_closeBtn;      // Window close button
  FXButton *m_maximizeBtn;   // Window Maximize button
  FXButton *m_iconifyBtn;    // Window minimize/iconify button
  
  FXVerticalSeparator *m_sep; // The Controller content separator 

  FXIcon *ic_close;     // Close button icon
  FXIcon *ic_iconify;   // Iconify/minimize button icon
  FXIcon *ic_maximize;  // Maximalize button icon
  FXIcon *ic_restore;   // Restore button icon

  // Configurations
  FXbool m_hidden;       // Hidden controller buttons 

public :
  FXWindowController( FXWindowHeader *p, FXuint opts = CONTROLS_NORMAL );
  virtual ~FXWindowController( );

  ////////////////////////////////////////////////
  // Access
  //
  FXuint getOptions( ) { return 0; }
  void   setOptions( FXuint opts ) { }
  FXbool isHidden( ) { return m_hidden; } 

  ////////////////////////////////////////////////
  // Operations
  //
  virtual void create( );
  void show( );
  void hide( );

  ////////////////////////////////////////////////
  // Gui events
  //
  enum {
    WIN_MAXIMIZE = 1,
    ID_RECONFIGURE,
    ID_LAST
  };
  long onCmd_WinMaximize( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data );

protected:
  FXWindowController( ) { }

  virtual void ReadConfig( );
  virtual void WriteConfig( );
  
};

}      /* FXGHI */
#endif /* FXGHI_CONTROLLER_H */
