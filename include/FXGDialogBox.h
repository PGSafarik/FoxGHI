/**************************************************************************************************
* FXGDialogBox	                                                                                  *
*                                                                                                 *
* Základní Dialogove okno.                                                                        *
* Copyryght (C) 2019 - 2022 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef __DIALOGBOX_H
#define __DIALOGBOX_H
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
#include<fox-1.7/fx.h>

#include "FXGHI_defs.h"
#include "FXGWindow.h"

namespace FXGHI {

class FXGDialogBox : public FXGWindow {
  FXDECLARE( FXGDialogBox )

  FXGDialogBox( const FXDialogBox& );
  FXGDialogBox& operator = ( const FXDialogBox& );
public:
  FXGDialogBox(FXApp* a,        const FXString &name, FXuint opts = WINDOW_STATIC, FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0, FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING, FXint hs = HV_SPACING2, FXint vs = HV_SPACING2 );
  FXGDialogBox(FXWindow* owner, const FXString &name, FXuint opts = WINDOW_STATIC, FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0, FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING, FXint hs = HV_SPACING2, FXint vs = HV_SPACING2 );

  ////////////////////////////////////////////////
  // Operations
  //
  virtual FXuint execute( FXuint placement=PLACEMENT_CURSOR );

  ////////////////////////////////////////////////
  // GUI events and handlers
  //
  enum {
    ID_CANCEL=FXTopWindow::ID_LAST,     /// Closes the dialog, cancel the entry
    ID_ACCEPT,                          /// Closes the dialog, accept the entry
    ID_LAST
  };

  long onCmdAccept( FXObject*, FXSelector, void* );
  long onCmdCancel( FXObject*, FXSelector, void* );

protected:
  FXGDialogBox( ){ }
};

}      /* FXGHI */
#endif /* __DIALOGBOX_H */
/*** END ******************************************************************************************/
