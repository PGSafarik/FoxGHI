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
#ifndef FXGHI_CP_H
#define FXGHI_CP_H

/*************************************************************************
* ControlPanel.h                                                         *
*                                                                        *
* Declaration of the FoxGHI Control Panel                                *
* Copyright (c) 2022 - 2025 D.A.Tiger <drakarax@seznam.cz>               *
*************************************************************************/
#include<Core.h>

class GHI_ControlPanel : public FXVerticalFrame {
FXDECLARE( GHI_ControlPanel )  
   // Header
   FXTextField   *htf_tfont;
   FXTextField   *htf_sfont; 
   FXCheckButton *hcb_colorize;
   FXCheckButton *hcb_title;
   FXCheckButton *hcb_separator;

   // Window
   FXCheckButton *wcb_wmcontrol;
   FXCheckButton *wcb_selfcontrol;
   FXCheckButton *wcb_border;
   // Controller
   FXCheckButton *ccb_hidden;
    
   // internal data
   FXbool             m_change;
   FXStringDictionary m_back;    // Original values backup
   //FXStringDictionary m_def;   // Default values

public :
  GHI_ControlPanel( FXComposite *p, FXObject *tgt = NULL, FXSelector sel = 0, FXuint opts = FRAME_NONE | LAYOUT_FILL );
  ~GHI_ControlPanel( );

  /* Access methods */
  FXbool hasBackup( ) { return !m_back.empty( ); } 
  FXbool isChange( )  { return m_change; }
  
  /* Operations */
  virtual void create( );

  virtual void readConfig( );
  virtual void writeConfig( );

  /* GUI Messages & Handlers */
  enum {
    SETTINGS_SAVE = FXVerticalFrame::ID_LAST, // Save changes
    SETTINGS_RESTORE,                         // Restore to previous state
    SETTINGS_DEFAULT,                         // Default profile ( remove the all settings)
    SETTINGS_WINMNG,                          // Active full window management and decoration profile
    SELECT_FONT,                              // Dialog for select font
    ID_CHANGE,                                // Notify of change settings widget
    ID_LAST,                                  // ...
  };
  long onCmd_Select( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Settings( FXObject *sender, FXSelector sel, void *data );
  long onUpd_Settings( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Update( FXObject *sender, FXSelector sel, void *data );

protected :
  GHI_ControlPanel( ) { }

  /* Helpers methods */
  void Notify( FXuint t = SEL_CHANGED ) { if( target ) { target->tryHandle( this, FXSEL( t, message ), NULL ); } } 
};

#endif /* FXGHI_CP_H */
