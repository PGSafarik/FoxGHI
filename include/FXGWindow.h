/**************************************************************************************************
* FXGWindow                                                                                       *
*                                                                                                 *
* Základní definice Top-level okna ve stylu Gnome3. Lze pouzit jako primarni, nebo zaklad pro     *
* sekundarni okno.                                                                                *
* Copyryght (C) 2019 - 2021 P.G.Safarik alias D.A.Tiger GNU GPL v3                                *
**************************************************************************************************/
#ifndef __SIMPLEMAIN_
#define __SIMPLEMAIN_
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
#include<fox-1.7/fx.h>
#include "FXGHI_defs.h"
#include "FXWindowHeader.h"
#include "FXWindowController.h"

namespace FXGHI {

class FXGWindow : public FXTopWindow {
FXDECLARE( FXGWindow )
  FXuint      w_opts; // Window system and controll options;
  FXuint      w_grab; // Value of the grab Flags
  FXPoint     w_last; // Point for save last mouse position
  FXRectangle w_rect; // Rectangle represend the window area using for resize calculate

  FXWindowHeader     *w_header;		// The window header widget
  FXWindowController *w_controller;	// The window controller widget

  FXIcon *w_menuic;	// Standard menu icon;

public:
  FXGWindow( FXApp *app, const FXString &title, FXIcon *ic = NULL, FXIcon *mi = NULL, FXuint opts = CONTROLS_NORMAL,
		      FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0,
		      FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING,
		      FXint hs = HV_SPACING2, FXint vs = HV_SPACING2  );
  FXGWindow( FXWindow *owner, const FXString &title, FXIcon *ic = NULL, FXIcon *mi = NULL, FXuint opts = CONTROLS_NORMAL,
		      FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0,
		      FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING,
		      FXint hs = HV_SPACING2, FXint vs = HV_SPACING2  );
  virtual ~FXGWindow( );

  ////////////////////////////////////////////////
  // Access methods
  //
  inline FXWindowHeader* getHeader( ) { return w_header; }
  FXIcon* getMenuIcon( )              { return w_menuic; }
  FXbool  isPrimary( )                { return w_opts & WINDOW_PRIMARY; }

  ////////////////////////////////////////////////
  // Operations
  //
  virtual void   create( );
  virtual FXbool close( FXbool notify = false );

  ////////////////////////////////////////////////
  // GUI messagess and handler
  //
  enum {
    ID_WINHEADER = FXTopWindow::ID_LAST, // Using for handled a window headerbar events
    ID_LAST
  };

  long onPaint( FXObject *sender, FXSelector sel, void *data );
  long onLeftButtonPress( FXObject *sender, FXSelector sel, void *data );
  long onLeftButtonRelease( FXObject *sender, FXSelector sel, void *data );
  long onMotion( FXObject *sender, FXSelector sel, void *data );

protected:
  FXGWindow( ) { }

  ///////////////////////////////////////////////
  // Helpers methods
  //
  FXuint Where( FXint pos_x, FXint pos_y );       // Get flag of the mouse grabing side
  void   Cursor_Change( );                        // Change with window moving or resizing
  void   Cursor_Revert( );                        // Change curzor on default
  void   Cursor_Set( FXDefaultCursor cursor_id ); // Change cursor
  void   RecalculateSize( );                        // Recalculte open window size

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
