/**************************************************************************************************
* FXWindowHeader.h                                                                                *
*                                                                                                 *
* Ovladaci prvek a spravce layoutu ve stylu Gnome 3, ktery poskutuje top-level oknu bez dekoraci  *
* moznost ovladani pozice, okenni titulek a zaroven funguje jako prostor pro ovladaci prvky okna. *
* Prostor prvku se pouziva jako tez vyceucelovy toolbar, kam je mozno zasadit temer jakykoliv     *
* ovladaci prvek. Dalsi informace viz dokumentace.                                                *
* Copyryght (C) 2019 - 2022 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef FXGHI_WINDOWHEADER_H
#define FXGHI_WINDOWHEADER_H

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
#include "Core.h"

namespace FXGHI {

class FXWindowHeader : public FXHorizontalFrame {
FXDECLARE( FXWindowHeader )
  FXTopWindow *m_parent; // Pointer of the parent window 

  FXuint  m_opts;      // Window HeaderBar options flags
  FXColor m_sepcolor;  // Color of the bottom separator
  FXColor m_backcolor; // Backcolor for header bar   

  // Moving 
  FXbool  m_dragged; // Flag of mouse dragged  
  FXPoint m_mmp;     // Memory Mouse Position
  FXPoint m_mwp;     // Memory Window Position

  // Title text of the Header bar
  FXbool    m_tvisible;         // Flag of the Title enabled
  FXPoint   m_tcoord;           // Position of the title drawing 
  FXPoint   m_scoord;           // Position of the subtitle 
  FXString  m_stext;            // Subtitle ( Second text of the window )
  FXString  m_fntspec_title;    // Specifications of the title font 
  FXString  m_fntspec_subtitle; // Specifications of the subtitle font
  FXFont   *m_tfnt;             // The title font object
  FXFont   *m_sfnt;             // The subtitle font object
  FXint     m_tlenght;          // Length of the title
  FXint     m_stlenght;         // Length of the subtitle

  // For Children widgets layout managment
  FXObject *m_box_tgt;     // Pointer of a univerzal target on GUI messagess 
  FXuint    m_box_opts;    // List of a options, List of options that can be used for uniform styling of descendants
  FXint     m_box_pl;      // Recommended spacing between elements: Left margin
  FXint     m_box_pr;      // Recommended spacing between elements: Right margin
  FXint     m_box_hs;      // Recommended spacing between elements: Spaces
  
  // Config
  FXbool m_separate;         // true = drawing a separator line at the bottom side of this bar
  FXbool m_colorize;         // 0 = off; > 0 = base_color + colorize   
  FXint  m_clrOffset;        //Base color offset - Color difference from the window's base color

public:
  FXWindowHeader( FXTopWindow *parent, const FXString &text = FXString::null, FXObject *tgt = NULL, FXSelector sel = 0,  FXuint opts = WHEADER_STANDARD,
		 FXint x = 0, FXint y = 0, FXint w = 0, FXint h = 0,
		 FXint pl = DEFAULT_DISTANCE, FXint pr = DEFAULT_DISTANCE, FXint pt = DEFAULT_DISTANCE, FXint pb = DEFAULT_DISTANCE,
		 FXint hs = DEFAULT_SPACING, FXint vs = DEFAULT_SPACING );
  virtual ~FXWindowHeader( );

  ////////////////////////////////////////////////
  // Access methods
  //
  FXTopWindow* getTopWindow( ) { return m_parent; }

  FXIcon*   getMiniIcon( )                        { return m_parent->getMiniIcon( ); }
  void      setMiniIcon( FXIcon *mic )            { m_parent->setMiniIcon( mic );    }
  FXIcon*   getIcon( )                            { return m_parent->getIcon( );     }
  void      setIcon( FXIcon *ic )                 { m_parent->setIcon( ic );         }
  FXString  getTitle( ) const                     { return m_parent->getTitle( );    }
  FXbool    hasTitle( )                           { return getTitle( ).empty( );     }
  void      setTitle( const FXString &text );  
  FXString  getText( ) const                      { return m_stext;               }
  FXbool    hasText( )                            { return getText( ).empty( );      }
  void      setText( const FXString &text ); 
  FXFont*   getTitleFont( )                       { return m_tfnt; }
  void      setTitleFont( const FXString &spec );
  FXFont*   getSubtitleFont( )                    { return m_sfnt; }
  void      setSubtitleFont( const FXString &spec );
  FXbool    isTitleVisible( )                     { return m_tvisible; }
  void      setTitleVisible( FXbool value )       { m_tvisible = value; }
  void      setSeparating( FXbool value )         { m_separate = value; }
  FXbool    getSeparating( )                      { return m_separate; }
                    
  FXObject* getBoxTarget( )                  { return ( m_box_tgt ? m_box_tgt : m_parent ); }
  void      setBoxTarget( FXObject *target ) { m_box_tgt = target; }
  FXuint    getBoxOpts( )                    { return m_box_opts; }
  void      setBoxOpts( FXuint opts )        { m_box_opts = opts; }
  
  FXint getDefaultHeight( );
  FXint getBoxPl( )             { return m_box_pl;  }
  void  setBoxPl( FXint value ) { m_box_pl = value; }
  FXint getBoxPr( )             { return m_box_pr; }
  void  setBoxPr( FXint value ) { m_box_pr = value; }
  FXint getBoxHs( )             { return m_box_hs; }
  void  setBoxHs( FXint value ) { m_box_hs = value; }

  ////////////////////////////////////////////////
  // Operations
  //
  virtual void create( );
  virtual void layout( );
  void         _recolorize( FXWindow *w ); 
  void         recolorize( FXWindow *target = NULL );

  ////////////////////////////////////////////////
  // GUI events and handlers
  //
  enum {
    ID_RECONFIGURE = FXHorizontalFrame::ID_LAST,
    ID_LAST
  };

  long onPaint( FXObject *sender, FXSelector sel, void *data );
  long onConfigure( FXObject *sender, FXSelector sel, void *data );
  long onLeftBtnPress( FXObject *sender, FXSelector sel, void *data );
  long onLeftBtnRelease( FXObject *sender, FXSelector sel, void *data );
  long onMotion( FXObject *sender, FXSelector sel, void *data );
  long onCmd_Reconfigure( FXObject *sender, FXSelector sel, void *data );

protected:
  FXWindowHeader( ) { }
  void UpdateTitle( );
  FXFont *CreateFont( const FXString &spec );

  virtual void ReadConfig( );
  virtual void WriteConfig( );
  
};

}      /* FXGHI */
#endif /*FXGHI_WINDOWHEADER_H */
