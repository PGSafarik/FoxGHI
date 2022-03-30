#include "FXGDialogBox.h"

using namespace FXGHI;

namespace FXGHI {
FXDEFMAP( FXGDialogBox ) DialogBoxMap[ ] = {
  FXMAPFUNC( SEL_CLOSE,   0,                       FXGDialogBox::onCmdCancel ),
  FXMAPFUNC( SEL_COMMAND, FXGDialogBox::ID_CLOSE,  FXGDialogBox::onCmdCancel ),
  FXMAPFUNC( SEL_COMMAND, FXGDialogBox::ID_ACCEPT, FXGDialogBox::onCmdAccept ),
  FXMAPFUNC( SEL_CHORE,   FXGDialogBox::ID_CANCEL, FXGDialogBox::onCmdCancel ),
  FXMAPFUNC( SEL_TIMEOUT, FXGDialogBox::ID_CANCEL, FXGDialogBox::onCmdCancel ),
  FXMAPFUNC( SEL_COMMAND, FXGDialogBox::ID_CANCEL, FXGDialogBox::onCmdCancel ),
};
FXIMPLEMENT( FXGDialogBox, FXGWindow, DialogBoxMap, ARRAYNUMBER( DialogBoxMap ) )
/**************************************************************************************************/

FXGDialogBox::FXGDialogBox( FXApp* a, const FXString &name, FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs )
            : FXGWindow( a, name, NULL, NULL, opts, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  this->getAccelTable( )->addAccel( MKUINT( KEY_Escape, 0 ), this, FXSEL( SEL_COMMAND, ID_CANCEL ) );
}

FXGDialogBox::FXGDialogBox( FXWindow* owner, const FXString &name, FXuint opts, FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs )
            : FXGWindow( owner, name, NULL, NULL, opts, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  this->getAccelTable( )->addAccel( MKUINT( KEY_Escape, 0 ), this, FXSEL( SEL_COMMAND, ID_CANCEL ) );
}

/**************************************************************************************************/
FXuint FXGDialogBox::execute( FXuint placement )
{
  this->create( );
  this->show( placement );
  this->getApp( )->refresh( );
  return this->getApp( )->runModalFor( this );
}

/**************************************************************************************************/
long FXGDialogBox::onCmdAccept( FXObject*, FXSelector, void* )
{
  this->getApp( )->stopModal( this, true );
  this->hide( );
  return 1;
}

long FXGDialogBox::onCmdCancel( FXObject*, FXSelector, void* )
{
  this->getApp( )->stopModal( this, false );
  this->hide( );
  return 1;
}

} /* FXGHI */
/*** END ******************************************************************************************/
