/*************************************************************************
* FXWindowHeader.cpp; Copyright (c) 2019 - 2022 by D.A.Tiger             *
*                                                                        *
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


#include "Widgets/FXWindowHeader.h"
#define DISPLAY( app ) ( ( Display* ) ( app->getDisplay( ) ) )
using namespace FXGHI;

namespace FXGHI {
// Event map and object implementation
FXDEFMAP( FXWindowHeader ) FXWindowHeaderMap[] = {
  FXMAPFUNC( SEL_PAINT,             0,                              FXWindowHeader::onPaint ),
  FXMAPFUNC( SEL_CONFIGURE,         0,                              FXWindowHeader::onConfigure ),
  FXMAPFUNC( SEL_MOTION,            0,                              FXWindowHeader::onMotion ),
  FXMAPFUNC( SEL_LEFTBUTTONPRESS,   0,                              FXWindowHeader::onLeftBtnPress ),
  FXMAPFUNC( SEL_LEFTBUTTONRELEASE, 0,                              FXWindowHeader::onLeftBtnRelease ),
  FXMAPFUNC( SEL_CHANGED,           FXWindowHeader::ID_RECONFIGURE, FXWindowHeader::onCmd_Reconfigure ) 
};
FXIMPLEMENT( FXWindowHeader, FXHorizontalFrame, FXWindowHeaderMap, ARRAYNUMBER( FXWindowHeaderMap ) )

/**************************************************************************************************/
FXWindowHeader::FXWindowHeader( FXTopWindow *parent, const FXString &text, FXObject *tgt, FXSelector sel, FXuint opts,
				         FXint x, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb, FXint hs, FXint vs )
               : FXHorizontalFrame( parent, opts, x, y, w, h, pl, pr, pt, pb, hs, vs )
{
  this->enable( );
  this->setTarget( tgt );
  this->setSelector( sel );
  m_parent = parent;
  m_opts   = opts;

  m_box_tgt  = NULL;
  m_box_opts = 0;
  m_box_pl   = pl;
  m_box_pr   = pr;
  m_box_hs   = hs;

  // Header style
  m_clrOffset    = 0;
  m_sepClrOffset = 0;
  m_separate     = true;
  m_colorize     = true;

  // Window mouse grab and moving
  m_dragged   = false;
  m_mmp.set( 0, 0 );

  // Title text
  m_tvisible      = true;
  m_stext         = text;
  m_tfnt = m_sfnt = NULL;
}

FXWindowHeader::~FXWindowHeader( )
{ }

void FXWindowHeader::create( )
{
  ReadConfig( );

  // Vertical center all childerns widgets at Y axis
  for( FXWindow *w = getFirst( ); w != NULL; w = w->getNext( ) ) {
    FXuint hints = w->getLayoutHints( );
    if ( !( hints & LAYOUT_CENTER_Y  ) ) { w->setLayoutHints( hints | LAYOUT_CENTER_Y ); }
  }

  // Header bar colorize
  if( m_colorize ) {
    m_backcolor = ColorIntensityCorrection( getApp( )->getBaseColor( ), m_clrOffset );
    m_sepcolor  = ColorIntensityCorrection( getApp( )->getBorderColor(  ), m_sepClrOffset );

    setBackColor( m_backcolor );
  }
  else { 
    m_sepcolor = getApp( )->getBorderColor( ); 
    setBackColor( getApp( )->getBaseColor( ) );
  }

  // Creating
  FXHorizontalFrame::create( );
  
  // Set header title fonts
  setTitleFont( m_fntspec_title );
  setSubtitleFont( m_fntspec_subtitle );
  UpdateTitle( );

  // Colorized children for this frame
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

void FXWindowHeader::setTitleFont( const FXString &spec )
{
  if( m_tfnt ) { delete m_tfnt; }
  m_tfnt = CreateFont( spec );
}

void FXWindowHeader::setSubtitleFont( const FXString &spec )
{
  if( m_sfnt ) { delete m_sfnt; }
  m_sfnt = CreateFont( spec );
}


void FXWindowHeader::layout( )
{
/* Calculate position to the headerBar text, with change to top-level window */
  FXHorizontalFrame::layout( );

  m_tlenght  = m_tfnt->getTextWidth( this->getTitle( ) );  // Length of title string
  m_stlenght = m_tfnt->getTextWidth( this->getText( ) );   // Length of subtitle string (aka window text)

  FXint wb_height = getHeight( );             // Height of the Header bar
  FXint wb_width  = getWidth( );              // Width of the Header bar
  //std::cout << "W:" << wb_width << std::endl;
  //std::cout << "H:" << wb_height << std::endl;

  FXint pw        = wb_width / 2;             // Auxiliary variable
  FXint ft_height = m_tfnt->getFontHeight( ); // Length of the used text font
  FXint _width    = 0;                        // Required width WH (i.e. length of all children + spaces + length of longest title text)
  FXint _left     = 0;                        // Auxiliary variable: Total length of all descendants on the left side of the panel
  FXint _right    = 0;                        // Auxiliary variable: The position on the X axis where widgets (descendants of the panel) start on the right 

  // Corection a parent width, in depending on the title ( or subtitle) width and check size empty 
  // space for widow title  
  FXint i = 0;

  for( FXWindow *ch = getFirst( ); ch != NULL; ch = ch->getNext( ) ) { // Pro vsechny potomky
    if( ch ) {                                                         // Pokud skutecne existuje
      i++;  
      int x = ch->getX( );                                             // Pozice potomka v ose X
      int w = ch->getWidth( );                                         // Sirka potomka    

      _width += w + DEFAULT_SPACING;                                   // K pozadovane sirce panelu prictem sirku widgetu a odstup mezi widgety
      if ( _right == 0 ) {                                             // Dokud nezacalo pocitani widgetu zprava
        if ( x + w < pw ) { _left = _width; } else { _right = x; }     // Pokud pozice widgetu a jeho sirka nepresahne polovinu sirky baneru,   --
                                                                       // sirka na levo je rovna celkove sirce. V opacnem pripade si ulozime    --
                                                                       // pozici widgetu na pravou stranu. Timto postupem je urcen prostor mezi --
                                                                       // potomky urceny pro texty titulku.  
      }
    }
  }
/*
  _width += ( m_tlenght >= m_stlenght ? m_tlenght : m_stlenght ) + 2 * DEFAULT_SPACING; // K pozadovane sice panelu prictem nejdelsi z obou radku titulku

  if ( _width > getParent( )->getWidth( ) ) {  // Pokud pozadovana sirka presahne celkovou sirku potomka (top-lewel okna)
    getParent( )->setWidth( _width );          // Nastvime sirku potomka shodnou se sirkou panelu
  }
*/
  // Recalc Titile position
  if( m_tvisible ) {
    pw = _left + _right / 2;                                                 // Urcime stred prostoru pro titulek
    if( m_stext.empty( ) ) {                                                 // Pokud neni nastaven subtitulek
      m_tcoord.set( pw - ( m_tlenght / 2 ), wb_height / 2 + ft_height / 4 ); // Umistime titulek do stredu
    } 
    else {                                                                                 //
      //! FXint offset = wb_height / 4 + padtop + border;                                         // Odstup z vrchu
      FXint offset = ft_height / 2;
      FXint beg = offset + padtop + border;
      m_tcoord.set( pw - ( m_tlenght  / 2 ), beg );                                     // Vypocet pozice prvniho radku
      m_scoord.set( pw - ( m_stlenght / 2 ),  beg + offset + vspacing * 2);             // Vypocet pozice druheho radku

    }
  }
}

void FXWindowHeader::_recolorize( FXWindow *w )
{
  if( w ) { w->setBackColor( getBackColor( ) ); }
}

void FXWindowHeader::recolorize( FXWindow *target )
{
  if( m_colorize ) {
    FXWindow *t = ( target ? target : this );

    // Colorize all childerns
    for( FXWindow *w = t->getFirst( ); w != NULL; w = w->getNext( ) )
    {
  	  _recolorize( w );
    }
  }
}

FXint FXWindowHeader::getDefaultHeight( ) 
{
  FXint value = 0;
  FXint m = FXHorizontalFrame::getDefaultHeight( );  // Default height for Horizontal frame
  FXint fh = m_tfnt->getFontHeight( );               // Height for used font

  if ( m_tvisible ) {
    value = ( !getText( ).empty( ) ? m_scoord.y + fh : fh );
    value = ( value > m ) ? value : m;
  }
  else { value = m; }

  std::cout << "Horizonatal Frame default Height: " << m << std::endl;
  std::cout << "Header Bar default Height: " << value << std::endl;

  return value;
}

FXint FXWindowHeader::getDefaultWidth() {
  return FXHorizontalFrame::getDefaultWidth( );
}


/**************************************************************************************************/
long FXWindowHeader::onPaint( FXObject *sender, FXSelector sel, void *data )
{
  /* Reapint the Header bar */
  long resh = FXHorizontalFrame::onPaint( sender, sel, data );
  FXDCWindow dc( this );

  /* Drawing the haeder bar tetxs (top-level window title and subtitle - if any) */
  if( m_tvisible ) {
    dc.setForeground( getApp()->getForeColor( ) );
    dc.setFont( m_tfnt );

    dc.drawText( m_tcoord.x, m_tcoord.y, m_parent->getTitle( ) );
    if( !m_stext.empty( ) ) {
      dc.setFont( m_sfnt );
      dc.drawText( m_scoord.x, m_scoord.y, m_stext );
    }
  }

  /* Paint the Header bar bottom separator */
  if( m_separate ) {
    FXint h = getHeight( ) - 1;
    FXint w = getWidth( );
    dc.setForeground( m_sepcolor );
    dc.drawLine ( 0, h , w, h  );
  }

  return resh;
}

long FXWindowHeader::onConfigure( FXObject *sender, FXSelector sel, void *data )
{

  /* handler for a FXWindow configure type notify */
  //#ifdef DEBUG 
  //std::cout << "[DEBUG - FXPrimaryWindow::onCmd_Reconfigure]: Configure Handler for " << getClassName( ) <<  std::endl;
  //#endif
  
  FXHorizontalFrame::onConfigure( sender, sel, data );
  for( FXWindow *ch = getFirst( ); ch != NULL; ch = ch->getNext( ) ) {
    ch->handle( this, FXSEL( SEL_CONFIGURE, 0), NULL ); 
  }
  layout( );
  
  return 1;
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

     
      m_parent->move( mpos.x, mpos.y );  //XMoveWindow( DISPLAY( getApp( ) ), m_parent->id( ), mpos.x, mpos.y );
      res = 1;
  }
  else { res = FXHorizontalFrame::onMotion( sender, sel, data ); }

  return res;
}

long FXWindowHeader::onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data )
{
  ReadConfig( );

  // Header bar colorize
  if( m_colorize ) {
    // Calculate and set colors tint
    m_backcolor = ColorIntensityCorrection( getApp( )->getBaseColor( ), m_clrOffset );
    m_sepcolor  = ColorIntensityCorrection( getApp( )->getBorderColor( ), m_sepClrOffset );

    setBackColor( m_backcolor );
    }
  else { 
    m_sepcolor = getApp( )->getBorderColor( ); 
    setBackColor( getApp( )->getBaseColor( ) );
  }


  // Update title
  setTitleFont( m_fntspec_title );
  setSubtitleFont( m_fntspec_subtitle );
  UpdateTitle( );

  // Colorized children for this frame
  recolorize( );

  return 1;
}

/**************************************************************************************************/
void FXWindowHeader::UpdateTitle( )
{
  /* Aktualize and redraiw Header bar in changes titles text */
  if( m_tfnt ) {
    layout( );
    update( );
    repaint( );
  }
}

void FXWindowHeader::ReadConfig( )
{
  FXString cf_prefix = CFG_HEADER_PREFIX;
  FXString fntspec_base;

  if ( getApp( )->reg( ).used( ) < 1 ) { getApp( )->reg( ).read( ); }
  fntspec_base = getApp( )->getNormalFont( )->getFont( );

  m_tvisible         = getApp( )->reg( ).readBoolEntry(   CFG_FXGHI, cf_prefix + ".ShowTitle",       true );
  m_colorize         = getApp( )->reg( ).readBoolEntry(   CFG_FXGHI, cf_prefix + ".EnableColorized", true );
  m_fntspec_title    = getApp( )->reg( ).readStringEntry( CFG_FXGHI, cf_prefix + ".TitleFont",       fntspec_base.text( ) );
  m_fntspec_subtitle = getApp( )->reg( ).readStringEntry( CFG_FXGHI, cf_prefix + ".SubTitleFont",    fntspec_base.text( ) );
  m_separate         = getApp( )->reg( ).readBoolEntry(   CFG_FXGHI, cf_prefix + ".EnableSeparator", true );

  m_clrOffset    = static_cast<FXfloat>( getApp( )->reg( ).readRealEntry( CFG_FXGHI, cf_prefix + ".BaseColorOffset", -0.85 ) );
  m_sepClrOffset = static_cast<FXfloat>( getApp( )->reg( ).readRealEntry( CFG_FXGHI, cf_prefix + ".SepColorOffset",  0.45 ) );

  #ifdef DEBUG
  std::cout << "[DEBUG - FXWindowHeader::ReadConfig] Enable colorize:  "              << m_colorize << std::endl;
  std::cout << "[DEBUG - FXWindowHeader::ReadConfig] Title Font:  "                   << m_fntspec_title.text( )  << std::endl;
  std::cout << "[DEBUG - FXWindowHeader::ReadConfig] Subtitle Font:  "                << m_fntspec_subtitle.text( )  << std::endl;
  std::cout << "[DEBUG - FXWindowHeader::ReadConfig] Frame base color offset: "       << m_clrOffset  << std::endl;
  std::cout << "[DEBUG - FXWindowHeader::ReadConfig] Separator shadow color offset: " << m_sepClrOffset  << std::endl;
  #endif
}

void FXWindowHeader::WriteConfig( )
{
  FXString cf_prefix = CFG_HEADER_PREFIX;  
  getApp( )->reg( ).writeBoolEntry(   CFG_FXGHI, cf_prefix + ".ShowTitle",       m_tvisible );
  getApp( )->reg( ).writeBoolEntry(   CFG_FXGHI, cf_prefix + ".EnableColorized", m_colorize ); 
  getApp( )->reg( ).writeRealEntry(   CFG_FXGHI, cf_prefix + ".BaseColorOffset", static_cast<FXdouble>( m_clrOffset ) );
  getApp( )->reg( ).writeRealEntry(   CFG_FXGHI, cf_prefix + ".SepColorOffset",  static_cast<FXdouble>( m_sepClrOffset ) );
  getApp( )->reg( ).writeStringEntry( CFG_FXGHI, cf_prefix + ".TitleFont",   m_fntspec_title.text( ) );
  getApp( )->reg( ).writeStringEntry( CFG_FXGHI, cf_prefix + ".SubTitleFont",m_fntspec_subtitle.text( ) );
  getApp( )->reg( ).writeBoolEntry(   CFG_FXGHI, cf_prefix + ".EnableSeparator", m_separate );
}

FXFont* FXWindowHeader::CreateFont( const FXString &spec )
{
   FXFont *fnt = new FXFont( getApp( ), spec );
   fnt->create( );
   return fnt;
}

FXColor FXWindowHeader::ColorIntensityCorrection( FXColor clr, FXfloat offset )
{
  FXint nr, ng, nb;

  const FXfloat r = static_cast<FXfloat>( FXREDVAL( clr ) );
  const FXfloat g = static_cast<FXfloat>( FXREDVAL( clr ) );
  const FXfloat b = static_cast<FXfloat>( FXREDVAL( clr ) );

  if( offset > 0 ) { // tint (lightening)
    nr = r + ( 255 - r ) * offset;
    ng = g + ( 255 - g ) * offset;
    nb = b + ( 255 - b ) * offset;
  }
  else { // shadow (darkening)
    offset = -offset;
    nr = r * offset;
    ng = g * offset;
    nb = b * offset;
  }

  return FXRGB( nr, ng, nb );
}

} /* FXGHI */

/*** END *****************************************************************************************/
