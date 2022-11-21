/**************************************************************************************************
* FXGHI_Defs                                                                                      *
*                                                                                                 *
* Preddefinovane konstanty a ridici priznaky.                                                     *
* Copyryght (C) 2019 - 2021 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef __GHI_DEFS_
#define __GHI_DEFS_
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
#include "icons.h"

namespace FXGHI {
/*** WINDOW CONTROLLER ***************************************************************************/
enum WinControllerFlags {
  NOSEPARATING       = 0x00000010,	// No create separator for this box
  CONTROL_ICONIFY    = 0x00000020,	// Minimize / iconify window button
  CONTROL_MAXIMIZE   = 0x00000040	// Maximize window button
  //CONTROL_FULLSCREEN = 0x00000040,
};
#define CONTROLS_NORMAL CONTROL_MAXIMIZE | CONTROL_ICONIFY
#define CONTROLS_STATIC CONTROL_ICONIFY

/*** WINDOW HEADER BAR ***************************************************************************/
enum WinHeaderFlags {
  WHEADER_DELEGATE = 0x00100000	// Delegate Maximixe notifikation on Header parent
};
#define DEFAULT_DISTANCE 10 														// Standard bounds distace
#define WHEADER_STANDARD FRAME_NONE | LAYOUT_TOP | LAYOUT_SIDE_TOP | LAYOUT_FILL_X 	// Standard header options

/*** WINDOW FLAGS ********************************************************************************/
enum {
  WINDOW_MAIN       = 0x00100000,	// Flag defined a primary window
  WINDOW_CLIENTSIZE = 0x00200000,	// Enter the window size is size for client space in this window
  WINDOW_STATIC     = 0x00400000	// Disable window resizing
};
#define P_SPACING         3	// 5
#define HV_SPACING2       2	// 2

/*** CONFIGURATIONS *******************************************************************************/
#define CFG_FXGHI             "FoxGHI"
#define CFG_WINDOW_PREFIX     "Window"
#define CFG_HEADER_PREFIX     "Header" 
#define CFG_CONTROLLER_PREFIX "Controller"
#define CFG_BOXES_PREFIX      "Box"

}      /* FXGHI       */
#endif /* __GHI_DEFS_ */

/*** END *****************************************************************************************/
