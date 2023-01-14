/**************************************************************************************************
* WINDOW HEADER BAR                                                                               *
* FXWindowHeader                                                                                  *
*                                                                                                 *
* Ovladaci prvek a spravce layoutu ve stylu Gnome 3, ktery poskutuje top-level oknu bez dekoraci  *
* moznost ovladani pozice, okenni titulek a zaroven funguje jako prostor pro ovladaci prvky okna. *
* Prostor prvku se pouziva jako tez vyceucelovy toolbar, kam je mozno zasadit temer jakykoliv     *
* ovladaci prvek. Dalsi informace viz dokumentace.                                                *
* Copyryght (C) 2019 - 2022 P.G.Safarik alias D.A.Tiger                                           *
**************************************************************************************************/
#ifndef __GNOME3_HEADER_
#define __GNOME3_HEADER_
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
#include<iostream>
#include<fox-1.7/fx.h>
#include "fxghi_defs.h"

namespace FXGHI {

//#define DEFAULT_DISTANCE 10                                               // Standard bounds distace
//#define S_HEAD FRAME_NONE | LAYOUT_TOP | LAYOUT_SIDE_TOP | LAYOUT_FILL_X  // Standard header options

class FXWindowHeader : public FXHorizontalFrame {
FXDECLARE( FXWindowHeader )
  FXTopWindow *m_parent; // Ukazatel na rodicovske okno

  FXuint  m_opts;      // Window HeaderBar options flags
  FXColor m_sepcolor;  // Color of the bottom separator
  FXColor m_backcolor; // Backcolor for header bar   

  // Moving
  FXbool  m_dragged; // Priznak zachyceni okna mysi
  FXPoint m_mmp;     // Ulozena pozice mysi (Memory Mouse Position)
  FXPoint m_mwp;     // Ulozena pozice okna (Memory Window Position)

  // Text of bar
  FXPoint   m_tcoord;           // Pozice pro vykresleni titlku
  FXPoint   m_scoord;           // Pozice pro vykresleni subtitulku
  FXString  m_stext;            // Subtitulek
  FXString  m_fntspec_title;    //  
  FXString  m_fntspec_subtitle; //
  FXFont   *m_tfnt;             // Font titulku
  FXFont   *m_sfnt;             // Font subtitulku
  FXint     m_tlenght;          // Delka titulku
  FXint     m_stlenght;         // Delka subtitulku

  // For Children
  FXObject *m_box_tgt;     // ukazatel na objekt urceny jako univerzalni prijemce GUI zprav
  FXuint    m_box_opts;    // Seznam voleb, ktere mohou byt vyuzity pro jednotne stylovani potomku
  FXint     m_box_pl;      // Doporuceny odstup mezi prvky : Levy okraj 
  FXint     m_box_pr;      // Doporuceny odstup mezi prvky : Pravy okraj
  FXint     m_box_hs;      // Doporuceny odstup mezi prvky : Mezery
  
  // Config
  FXbool m_colorize;         // 0 = off; > 0 = base_color + colorize   
  

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
  FXString  getText( ) const                      { return m_stext;                  }
  FXbool    hasText( )                            { return getText( ).empty( );      }
  void      setText( const FXString &text ); 
  FXFont*   getTitleFont( )                       { return m_tfnt; }
  void      setTitleFont( const FXString &spec );
  FXFont*   getSubtitleFont( )                    { return m_sfnt; }
  void      setSubtitleFont( const FXString &spec );
                    

  FXObject* getBoxTarget( )                  { return ( m_box_tgt ? m_box_tgt : m_parent ); }
  void      setBoxTarget( FXObject *target ) { m_box_tgt = target; }
  FXuint    getBoxOpts( )                    { return m_box_opts; }
  void      setBoxOpts( FXuint opts )        { m_box_opts = opts; }
  
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
#endif /*__GNOME3_HEADER_ */
