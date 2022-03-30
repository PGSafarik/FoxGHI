#include<fox-1.7/fx.h>
#include "FXPrimaryWindow.h"

#ifndef __PRIMARYMAIN_
#define __PRIMARYMAIN_

class FXMainPrimaryWindow : public FXPrimaryWindow {
FXDECLARE( FXMainPrimaryWindow )

  FXMainPrimaryWindow( const FXMainPrimaryWindow& );
  FXMainPrimaryWindow& operator =( const FXMainPrimaryWindow& );
public:
  FXMainPrimaryWindow( FXApp *app, const FXString &title, FXIcon *ic = NULL, FXIcon *mi = NULL, FXuint opts = CONTROLS_NORMAL,
		      FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0,
		      FXint pl = P_SPACING, FXint pr = P_SPACING, FXint pt = P_SPACING, FXint pb = P_SPACING,
		      FXint hs = HV_SPACING2, FXint vs = HV_SPACING2 );
  virtual ~FXMainPrimaryWindow( );

  ///////////////////////////////////////////////
  //
  //
  virtual void create( );


protected:
  FXMainPrimaryWindow( ) { }

};



#endif /* __PRIMARYMAIN_ */
