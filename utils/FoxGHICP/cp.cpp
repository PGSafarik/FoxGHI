/*************************************************************************
* cp.cpp; Copyright (c) 2022 by D.A.Tiger                                *
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

#include "cp.h" 

/**************************************************************************************************/
FXDEFMAP( GHI_ControlPanel ) CP_MAP[ ] = {
  FXMAPFUNC( SEL_COMMAND, GHI_ControlPanel::SELECT_FONT,      GHI_ControlPanel::onCmd_Select   ),
  FXMAPFUNC( SEL_COMMAND, GHI_ControlPanel::SETTINGS_SAVE,    GHI_ControlPanel::onCmd_Settings ),
  FXMAPFUNC( SEL_UPDATE,  GHI_ControlPanel::SETTINGS_SAVE,    GHI_ControlPanel::onUpd_Settings ),
  FXMAPFUNC( SEL_COMMAND, GHI_ControlPanel::SETTINGS_RESTORE, GHI_ControlPanel::onCmd_Settings ),
  FXMAPFUNC( SEL_UPDATE,  GHI_ControlPanel::SETTINGS_RESTORE, GHI_ControlPanel::onUpd_Settings ),
  FXMAPFUNC( SEL_COMMAND, GHI_ControlPanel::SETTINGS_DEFAULT, GHI_ControlPanel::onCmd_Settings ),
  FXMAPFUNC( SEL_COMMAND, GHI_ControlPanel::ID_CHANGE,        GHI_ControlPanel::onCmd_Update   )
};

FXIMPLEMENT( GHI_ControlPanel, FXVerticalFrame, CP_MAP, ARRAYNUMBER( CP_MAP ) )

/**************************************************************************************************/
GHI_ControlPanel::GHI_ControlPanel( FXComposite *p, FXObject *tgt, FXSelector sel, FXuint opts )
                : FXVerticalFrame( p, opts )  
{
   FXLabel *lh = new FXLabel( this, "Haeader bar", NULL, LABEL_NORMAL | LAYOUT_FILL_X );
   lh->setBackColor( getApp( )->getShadowColor( ) );
   FXMatrix *m = new FXMatrix( this, 3, MATRIX_BY_COLUMNS | LAYOUT_FILL_X );   
   new FXLabel( m, "Main title font", NULL, LABEL_NORMAL );
   htf_tfont = new FXTextField( m, 51, this, GHI_ControlPanel::ID_CHANGE, TEXTFIELD_NORMAL | LAYOUT_FILL_X ); 
   FXButton *tbtn = new FXButton( m, "...", NULL, this, GHI_ControlPanel::SELECT_FONT ); 
   tbtn->setUserData( htf_tfont );
   new FXLabel( m, "Subtitle font", NULL, LABEL_NORMAL );
   htf_sfont = new FXTextField( m, 51, this, GHI_ControlPanel::ID_CHANGE, TEXTFIELD_NORMAL | LAYOUT_FILL_X  ); 
   FXButton *sbtn = new FXButton( m, "...", NULL, this, GHI_ControlPanel::SELECT_FONT );
   sbtn->setUserData( htf_sfont );
   hcb_colorize = new FXCheckButton( this, "Header colorize", this, GHI_ControlPanel::ID_CHANGE );   

   FXLabel *lc = new FXLabel( this, "Controller", NULL, LABEL_NORMAL | LAYOUT_FILL_X ); 
   lc->setBackColor( getApp( )->getShadowColor( ) );
   ccb_hidden = new FXCheckButton( this, "Hide Controller", this, GHI_ControlPanel::ID_CHANGE );

   FXLabel *lw = new FXLabel( this, "Window", NULL, LABEL_NORMAL | LAYOUT_FILL_X );
   lw->setBackColor( getApp( )->getShadowColor( ) );
   wcb_border      = new FXCheckButton( this, "Enable window border", this, GHI_ControlPanel::ID_CHANGE );
   wcb_wmcontrol   = new FXCheckButton( this, "Enable WM frame", this, GHI_ControlPanel::ID_CHANGE );
   wcb_selfcontrol = new FXCheckButton( this, "Enable self control", this, GHI_ControlPanel::ID_CHANGE );

   target = tgt;
   message = sel;
   m_change = false;
}

GHI_ControlPanel::~GHI_ControlPanel( )
{


}


void GHI_ControlPanel::create( )
{
  readConfig( );
  m_change = false;

  FXVerticalFrame::create( );
  //Notify( );
}

/**************************************************************************************************/
void GHI_ControlPanel::readConfig( )
{
   if ( getApp( )->reg( ).used( ) < 1 ) { getApp( )->reg( ).read( ); }  
   FXString fntspec_base = getApp( )->getNormalFont( )->getFont( );   
   
   FXString cf_prefix = CFG_HEADER_PREFIX;
   FXbool   _colorize         = getApp( )->reg( ).readBoolEntry(   CFG_FXGHI, cf_prefix + ".EnableColorized", true );  
   FXString _fntspec_title    = getApp( )->reg( ).readStringEntry( CFG_FXGHI, cf_prefix + ".TitleFont",       fntspec_base.text( ) );
   FXString _fntspec_subtitle = getApp( )->reg( ).readStringEntry( CFG_FXGHI, cf_prefix + ".SubTitleFont",    fntspec_base.text( ) );
   htf_tfont->setText( _fntspec_title );
   htf_sfont->setText( _fntspec_subtitle );
   hcb_colorize->setCheck( _colorize );

   cf_prefix = CFG_CONTROLLER_PREFIX;
   FXbool _hidden = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".Hidden", false );
   ccb_hidden->setCheck( _hidden );

   cf_prefix = CFG_WINDOW_PREFIX;
   FXbool _border      = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".EnableBorder", true );
   FXbool _SelfControl = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".SelfControl",  true );
   FXbool _WMControl   = getApp( )->reg( ).readBoolEntry( CFG_FXGHI, cf_prefix + ".WMControl",    false );   
   wcb_wmcontrol->setCheck( _WMControl );
   wcb_selfcontrol->setCheck( _SelfControl );
   wcb_border->setCheck( _border );
}

void GHI_ControlPanel::writeConfig( )
{
  FXApp *a = getApp( );

  // Vytvoreni zalohy
  if( a->reg( ).existingSection( CFG_FXGHI ) ) { m_back = a->reg( ).at( CFG_FXGHI ); }
 
  FXString cf_prefix = CFG_HEADER_PREFIX;
  a->reg( ).writeBoolEntry(   CFG_FXGHI, cf_prefix + ".EnableColorized", hcb_colorize->getCheck( ) );
  a->reg( ).writeStringEntry( CFG_FXGHI, cf_prefix + ".TitleFont",       htf_tfont->getText( ).text( ) );
  a->reg( ).writeStringEntry( CFG_FXGHI, cf_prefix + ".SubTitleFont",    htf_sfont->getText( ).text( ) );

  cf_prefix = CFG_CONTROLLER_PREFIX;
  a->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".Hidden", ccb_hidden->getCheck( ) );

  cf_prefix = CFG_WINDOW_PREFIX;
  a->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".EnableBorder", wcb_border->getCheck( ) );
  a->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".SelfControl",  wcb_selfcontrol->getCheck( ) );
  a->reg( ).writeBoolEntry( CFG_FXGHI, cf_prefix + ".WMControl",    wcb_wmcontrol->getCheck( ) );

  a->reg( ).write( );
}

/**************************************************************************************************/
long GHI_ControlPanel::onCmd_Select( FXObject *sender, FXSelector sel, void *data )
{
  FXButton    *button = static_cast<FXButton*>( sender );
  FXTextField *field  = static_cast<FXTextField*>( button->getUserData( ) );

  FXFontDialog *dialog = new FXFontDialog( this, "Select font" );
  dialog->setFont( field->getText( ) );
  if( dialog->execute( ) ) { field->setText( dialog->getFont( ), true ); }
  
 return 1;
}

long GHI_ControlPanel::onCmd_Settings( FXObject *sender, FXSelector sel, void *data )
{
  FXuint id = FXSELID( sel );

  switch( id ) {
    case GHI_ControlPanel::SETTINGS_SAVE :
    {
      writeConfig( ); 
      m_change = false;
      Notify( );

      break;
    }
    case GHI_ControlPanel::SETTINGS_RESTORE :
    {
      if( !m_back.empty( ) )
      {
        if( FXMessageBox::question( this, MBOX_YES_NO, "Restore FoxGHI settings", "Do you really want to restore the original settings?" ) == MBOX_CLICKED_YES ) {
          getApp( )->reg( ).at( CFG_FXGHI ) = m_back;
          m_back.clear( );  
          readConfig( );
          m_change = true;
          Notify( );
          
        }  
      }
      else { FXMessageBox::warning( this, MBOX_OK, "Restore FoxGHI settings", "Unfortunately there is no data available for recovery." ); } 
      break; 
    }
    case GHI_ControlPanel::SETTINGS_DEFAULT :
    {
      if( FXMessageBox::question( this, MBOX_YES_NO, "Predefined FoxGHI settings", "Do you really want predefined settings?" ) == MBOX_CLICKED_YES ) {
        if( getApp( )->reg( ).existingSection( CFG_FXGHI ) ) { getApp( )->reg( ).deleteSection( CFG_FXGHI ); }
        readConfig( );
        m_change = true;
        Notify( );
      }
      break;
    }
  }


  return 1;
}

long GHI_ControlPanel::onUpd_Settings( FXObject *sender, FXSelector sel, void *data )
{
  FXWindow *actor = static_cast<FXWindow*>( sender );
  
  switch( FXSELID( sel ) ) {
    case GHI_ControlPanel::SETTINGS_SAVE : 
    { 
      m_change ? actor->enable( ) : actor->disable( ) ;
      break;
    }
    case GHI_ControlPanel::SETTINGS_RESTORE :  
    { 
      ( !m_back.empty( ) ) ? actor->enable( ) : actor->disable( ) ;
      break;
    }
  }

  return 1;
}

long GHI_ControlPanel::onCmd_Update( FXObject *sender, FXSelector sel, void *data )
{
  m_change = true;
  //Notify( );

  return 1; 
}

/*** END ******************************************************************************************/
