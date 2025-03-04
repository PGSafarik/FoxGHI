/**************************************************************************************************
* FXPrimaryWindow                                                                                       *
*                                                                                                 *
* Základní definice Top-level okna ve stylu Gnome3. Lze pouzit jako primarni, nebo zaklad pro     *
* sekundarni okno.                                                                                *
* Copyryght (C) 2019 - 2021 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef __SIMPLEMAIN_
#define __SIMPLEMAIN_
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
//! #include<fox-1.7/fx.h>
#include "Core.h"
#include "Widgets.h"


namespace FXGHI {

class FXPrimaryWindow : public FXTopWindow {
FXDECLARE( FXPrimaryWindow )
  FXuint      w_opts; // Window system and controll options;
  FXuint      w_grab; // Value of the grab Flags
  FXPoint     w_last; // Point for save last mouse position
  FXRectangle w_rect; // Rectangle represend the window area using for resize calculate

  FXWindowHeader     *w_header;		  // The window header widget
  FXWindowController *w_controller;	// The window controller widget

  FXIcon *w_menuic;	   // Standard menu icon;
  FXIcon *w_omenuic;   // Overflov menu icon;

  // Configurations
  FXbool w_border;        // If true, this window draw border
  FXbool w_SelfControl;   // If true, allows handling of window resizing and moved by mouse dragging 
  FXbool w_WMControl;     // True value enabled a classical window decoiration and hendlig by Window Manager (Check the documentation - when it's ready ;)
  FXuint w_WMDecor;       // FOX Decorations flags usage if enabled WM decorations 
 
public:
  FXPrimaryWindow( FXApp *app, const FXString &title, FXIcon *ic = NULL, FXIcon *mi = NULL, FXuint opts = CONTROLS_NORMAL,
		         FXint x = 0, FXint y = 0, FXint w = 400, FXint h = 200,
		         FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING,
		         FXint hs = HV_SPACING2, FXint vs = HV_SPACING2  );
  FXPrimaryWindow( FXWindow *owner, const FXString &title, FXIcon *ic = NULL, FXIcon *mi = NULL, FXuint opts = CONTROLS_NORMAL,
		         FXint x = 0, FXint y = 0, FXint w = 400, FXint h = 200,
		         FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING,
		         FXint hs = HV_SPACING2, FXint vs = HV_SPACING2  );
  virtual ~FXPrimaryWindow( );

  ////////////////////////////////////////////////
  // Access methods
  //
  inline FXWindowHeader* getHeader( )            { return w_header; }
  FXIcon* getMenuIcon( FXbool overflov = false ) { return ( overflov ? w_omenuic : w_menuic ); }
  FXbool  isPrimary( )                           { return w_opts & WINDOW_MAIN; }
  
  ////////////////////////////////////////////////
  // Operations
  //
  virtual void   create( );
  virtual FXbool close( FXbool notify = false );
  void    setWMDecorations( FXuint opts ) { w_WMDecor = opts; }
  FXuint  getWMDecorations( )             { return w_WMDecor; }

  ////////////////////////////////////////////////
  // GUI messagess and handler
  //
  enum {
    ID_WINHEADER = FXTopWindow::ID_LAST, // Using for handled a window headerbar events
    ID_RECONFIGURE,
    ID_LAST
  };

  long onPaint( FXObject *sender, FXSelector sel, void *data );
  long onConfigure( FXObject *sender, FXSelector sel, void *data );
  long onLeftButtonPress( FXObject *sender, FXSelector sel, void *data );
  long onLeftButtonRelease( FXObject *sender, FXSelector sel, void *data );
  long onMotion( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data );

protected:
  FXPrimaryWindow( ) { }
  
  ///////////////////////////////////////////////
  // Helpers methods
  //
  FXuint Where( FXint pos_x, FXint pos_y );       // Get flag of the mouse grabing side
  void   Cursor_Change( );                        // Change with window moving or resizing
  void   Cursor_Revert( );                        // Change curzor on default
  void   Cursor_Set( FXDefaultCursor cursor_id ); // Change cursor
  void   RecalculateSize( );                        // Recalculte open window size

  virtual void ReadConfig( );
  virtual void WriteConfig( );
  //virtual void Configure( );

  ///////////////////////////////////////////////
  // Helpers flags
  //
  enum { 	// Grab flags ( the flags for mouse grabbing )
  	DRAG_NONE        = 0,
    DRAG_TOP         = 1,
    DRAG_BOTTOM      = 2,
    DRAG_LEFT        = 4,
    DRAG_RIGHT       = 8,
    DRAG_INVERTED    = 16,
    DRAG_TOPLEFT     = ( DRAG_TOP | DRAG_LEFT ),
    DRAG_TOPRIGHT    = ( DRAG_TOP | DRAG_RIGHT ),
    DRAG_BOTTOMLEFT  = ( DRAG_BOTTOM | DRAG_LEFT ),
    DRAG_BOTTOMRIGHT = ( DRAG_BOTTOM | DRAG_RIGHT ),
    DRAG_MOVE        = 32
  };
};

}      /* FX */
#endif /*__SIMPLEMAION_*/
