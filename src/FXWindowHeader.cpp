#include<fox-1.7/xincs.h>
#include "FXWindowHeader.h"
#define DISPLAY( app ) ( ( Display* ) ( app->getDisplay( ) ) )
using namespace FXGHI;

namespace FXGHI {
// Event map and object implementation
FXDEFMAP( FXWindowHeader ) FXWindowHeaderMap[] = {
  FXMAPFUNC( SEL_PAINT,             0, FXWindowHeader::onPaint ),
  FXMAPFUNC( SEL_MOTION,            0, FXWindowHeader::onMotion ),
  FXMAPFUNC( SEL_LEFTBUTTONPRESS,   0, FXWindowHeader::onLeftBtnPress ),
  FXMAPFUNC( SEL_LEFTBUTTONRELEASE, 0, FXWindowHeader::onLeftBtnRelease ),
};
FXIMPLEMENT( FXWindowHeader, FXHorizontalFrame, FXWindowHeaderMap, ARRAYNUMBER( FXWindowHeaderMap ) )

/**************************************************************************************************/
 FXWindowHeader::FXWindowHeader( FXTopWindow *parent, const FXString &text, FXObject *tgt, FXSelector sel, FXuint opts,
				 FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs )
               : FXHorizontalFrame( parent, opts, x, y, w, h, pl, pr, pt, pb, hs, vs )
 {
   m_parent = parent;
   m_opts   = opts;

   this->enable( );
   this->setTarget( tgt );
   this->setSelector( sel );

   // Window mouse grab and moving
   m_dragged   = false;
   m_mmp.set( 0, 0 );

   // Title text
   m_stext          = text;
   m_sfnt           = this->getApp( )->getNormalFont( );
   m_tfnt           = new FXFont( getApp( ), m_sfnt->getFontDesc( ) );
   FXFontDesc _fdes = m_tfnt->getFontDesc( );
   _fdes.size       = 100;
   _fdes.weight     = FXFont::Bold;
   m_tfnt->setFontDesc( _fdes   );

   // Header bar colorize
   FXint clr_offset = 30;
   FXColor clr = getBackColor( );
   clr -= FXRGB( clr_offset, clr_offset, clr_offset );
   setBackColor( clr );
 }

FXWindowHeader::~FXWindowHeader( )
{ }

void FXWindowHeader::create( )
{
  FXHorizontalFrame::create( );
  m_tfnt->create( );

  recolorize( );
}

void FXWindowHeader::setTitle( const FXString &text )
{
  m_parent->setTitle( text );
  UpdateTitle( );
}

void FXWindowHeader::setText( const FXString &text )
{
  m_stext = text;
  UpdateTitle( );
}

void FXWindowHeader::layout( )
{
/* Calculate position to the headerBar text, with change to top-level window */
  FXHorizontalFrame::layout( );

  FXString t_text = this->getTitle( );
  m_tlenght  = m_tfnt->getTextWidth( t_text );
  m_stlenght = m_tfnt->getTextWidth( this->getText( ) );

  FXint wb_height = getHeight( );
  FXint wb_width  = getWidth( );
  FXint ft_height = m_tfnt->getFontHeight( );
  FXint pw        = wb_width / 2;
  FXint _width    = 0;
  FXint _left     = 0;
  FXint _right    = 0;

  // Corection a parent width, in depending on the title ( or subtitle) width
  for( FXWindow *ch = getFirst( ); ch != NULL; ch = ch->getNext( ) ) {
    if( ch ) { 
      int x = ch->getX( );
      int w = ch->getWidth( );

      _width += w + DEFAULT_SPACING;
      if ( _right == 0 ) {
        if ( x + w < pw ) { _left = _width; } else { _right = x; }
      }
    }  
  }
  wb_width -= _width;

  _width += ( m_tlenght >= m_stlenght ? m_tlenght : m_stlenght ) + 2* DEFAULT_SPACING;
 
  if ( _width > getParent( )->getWidth( ) ) {
    getParent( )->setWidth( _width );
  }
  
  // Recalc Titile position
  
  pw = _left + _right / 2;
  if( m_stext.empty( ) ) {
    m_tcoord.set( pw - ( m_tlenght / 2 ), wb_height / 2 + ft_height / 3 );
  }
  else {
    FXint offset = wb_height / 4 + getPadTop( );
    m_tcoord.set( pw - ( m_tlenght / 2 ),  offset );
    m_scoord.set( pw - ( m_stlenght / 2 ), wb_height - offset + 3 * ( ft_height / 4 ) );
  }


  std::cout << "_width      : " << _width << std::endl;
  std::cout << "parent width: " << getParent( )->getWidth( ) << std::endl;
}

void FXWindowHeader::recolorize( )
{
  // Colorize all childerns
  for( FXWindow *w = getFirst( ); w != NULL; w = w->getNext( ) )
  {
  	if( w ) { w->setBackColor( getBackColor( ) ); }
  }
}

/**************************************************************************************************/


long FXWindowHeader::onPaint( FXObject *sender, FXSelector sel, void *data )
{
  /* Reapint the Header bar */
  long resh = FXHorizontalFrame::onPaint( sender, sel, data );
  FXDCWindow dc( this );

  /* Drawing the haeder bar tetxs (top-level window title and subtitle - if any) */
  dc.setForeground( getApp()->getForeColor( ) );
  dc.setFont( m_tfnt );

  dc.drawText( m_tcoord.x, m_tcoord.y, m_parent->getTitle( ) );
  if( !m_stext.empty( ) ) {
    dc.setFont( m_sfnt );
    dc.drawText( m_scoord.x, m_scoord.y, m_stext );
  }

  /* Paint the Header bar bottom separator */
  FXint h = getHeight( ) - 1;
  FXint w = getWidth( ) ;
  FXint c_offset = 40;
  FXColor clr = getBackColor( ) - FXRGB( c_offset, c_offset, c_offset );

  dc.setForeground( clr );
  dc.drawLine ( 0, h , w, h  );

  return resh;
}

long FXWindowHeader::onLeftBtnPress( FXObject *sender, FXSelector sel, void *data )
{
  /* Grab to top-level window if is the left mouse button pressed in header bar space */
  long res = 0;

  if( m_opts & WHEADER_DELEGATE ) {
	FXObject  *target   = getTarget( );
    FXSelector selector = getSelector( );

	if( target ) { target->tryHandle( this, FXSEL( SEL_LEFTBUTTONPRESS, selector ), data ); }
  }
  else {
    flags &= ~FLAG_TIP;
    handle( this, FXSEL( SEL_FOCUS_SELF, 0 ), data );
    if( isEnabled( ) ) {
      grab( );

      FXEvent *e = static_cast<FXEvent*>( data );
      m_mmp.set( e->root_x, e->root_y );
      m_dragged = true;

      /// FXIME HEADER_01: Test of maximize window true:  m_parent->restore( )

      res = 1;
    }
  }
  return res;
}


long FXWindowHeader::onLeftBtnRelease( FXObject *sender, FXSelector sel, void *data )
{
  /* Ungab the top-level window if is the left mouse button released */
  long res = 0;

  if( m_opts & WHEADER_DELEGATE ) {
	FXObject  *target   = getTarget( );
    FXSelector selector = getSelector( );

	if( target ) { target->tryHandle( this, FXSEL( SEL_LEFTBUTTONRELEASE, selector ), data ); }
  }
  else {
    if( isEnabled( ) ) {
      ungrab();

      m_dragged = false;
      m_mmp.set( 0, 0 );

      res = 1;
    }
  }

  return res;
}

long FXWindowHeader::onMotion( FXObject *sender, FXSelector sel, void *data )
{
  /* if is the top-level window grabed, move with him */
  /// FIXME HEADER_02 : This method of window moving is very strong on complexy WM
  FXEvent *e  = static_cast<FXEvent*>( data );
  long    res = 0;
  FXPoint mpos;

  if( m_dragged && e->moved ) {
      mpos.set( m_parent->getX( ) + ( e->root_x - m_mmp.x ), m_parent->getY( ) + ( e->root_y - m_mmp.y ) );
      m_mmp.set( e->root_x, e->root_y );

      //std::cout << mpos.x << "x" << mpos.y << ";;" << e->root_x << "x" << e->root_y << "\n";
      m_parent->move( mpos.x, mpos.y );  //XMoveWindow( DISPLAY( getApp( ) ), m_parent->id( ), mpos.x, mpos.y );
      res = 1;
  }
  else { res = FXHorizontalFrame::onMotion( sender, sel, data ); }

  return res;
}

/**************************************************************************************************/
void FXWindowHeader::UpdateTitle( )
{
  /* Aktualize and redraiw Header bar in changes titles text */

  layout( );
  update( );
  repaint( );
}

} /* FXGHI */

/*** END *****************************************************************************************/
