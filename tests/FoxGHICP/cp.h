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

#ifndef __CP_H
#define __CP_H
/*************************************************************************
* cp.h                                                                   *
*                                                                        *
* Deklarace FoxGHI Control Panel                                         *
* Copyright (c) 10/10/2022 D.A.Tiger <drakarax@seznam.cz>                *
*************************************************************************/
#include<iostream>
#include<fox-1.7/fx.h>
#include<fxghi.h>


class GHI_ControlPanel : public FXVerticalFrame {
FXDECLARE( GHI_ControlPanel )  
   // Header
   FXTextField   *htf_tfont;
   FXTextField   *htf_sfont; 
   FXCheckButton *hcb_colorize;
   // Window
   FXCheckButton *wcb_wmcontrol;
   FXCheckButton *wcb_selfcontrol;
   FXCheckButton *wcb_border;
   // Controller
   FXCheckButton *ccb_hidden;

public :
  GHI_ControlPanel( FXComposite *p, FXuint opts = FRAME_NONE | LAYOUT_FILL );
  ~GHI_ControlPanel( );

  /* Operations */
  virtual void create( );

  virtual void readConfig( );
  virtual void writeConfig( );

  /* GUI Messages & Handlers */
  enum {
    SETTINGS_SAVE = FXVerticalFrame::ID_LAST,
    SELECT_FONT,
    ID_LAST,
  };
  long onCmd_Select( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Settings( FXObject *sender, FXSelector sel, void *data );

protected :
  GHI_ControlPanel( ) { }

};

#endif
