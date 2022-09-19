#include<fox-1.7/fx.h>
#include"../include/fxghi.h"

#define WINDOW_PROPERTIES WINDOW_PRIMARY | CONTROL_ICONIFY | CONTROL_MAXIMIZE

/*** DECLARATION *********************************************************************************/
class ImageView : public FXGWindow {
FXDECLARE( ImageViewer )
  FXImageView     *m_view;
  FXVerticalFrame *m_fsbox;
  FXStatusBar     *m_stausbar;
  FXSplitter      *m_spliter;
  FXTextField     *m_filter;
  FXIconCache      m_icons;
  FXString         m_filename;
  FXRecentFiles    m_recent;

public:
  ImageView( FXApp *app );
  virtual ~ImageView( );

  /* Operations methods */
  virtual void create( );
  void LoadImageFile( const FXString &filename );
  void SaveImageFile( const FXString &filename );

  /* GUI Eventes messages */
  enum = {
    WIN_ABOUT = FXGWindow::ID_LAST,
    WIN_TITLE,
    WIN_QUIT,
    FS_OPEN,
    FS_SAVE,
    FS_FILELIST,
    FS_RECENTFILE,
    IMG_ROTATE_90,
    IMG_ROTATE_180,
    IMG_ROTATE_270,
    IMG_MIRROR_HOR,
    IMG_MIRROR_VER,
    IMG_MIRROR_BOTH,
    IMG_SCALE,
    IMG_CROP,
    ID_LAST
  };

  /* GUI Eventes handlers */
  long on_Cmd_Window( FXObject *sender, FXSelector sel, void *data );
  long on_Cmd_Filesystem( FXObject *sender, FXSelector sel, void *data );
  long on_Cmd_Image( FXObject *sender, FXSelector sel, void *data );
  long on_Upd_Image( FXObject *sender, FXSelector sel, void *data );

protected:
  ImageView( ) { }

};
/*** IMPLEMENT ***********************************************************************************/
FXDEFMAP( ImageView ) IMAGEVIEW_MAP[ ] = {
  FXMAPFUNCS( SEL_COMMAND, ImageView::WIN_ABOUT, ImageView::WIN_QUIT,     on_Cmd_Window ),
  FXMAPFUNCS( SEL_COMMAND, ImageView::FS_OPEN, ImageView::FS_RECENTFILE,  on_Cmd_Filesystem ),
  FXMAPFUNCS( SEL_COMMAND, ImageView::IMG_ROTATE_90, ImageView::IMG_CROP, on_Cmd_Image ),
  FXMAPFUNCS( SEL_COMMAND, ImageView::MG_ROTATE_90, ImageView::IMG_CROP,  on_Upd_Image )
};
FXIMPLEMENT( ImageView, FXGWindow, IMAGEVIEW_MAP, ARRAYNUMBER( IMAGEVIEW_MAP ) )

ImageView::ImageView( FXApp *app )
         : FXGWindow( app, "Fox-GHI ImageView", NULL, NULL, WINDOW_PROPERTIES )
{
  FXColorDialog *color_dlg = new FXColororDialog( this, "Colors" );
  m_statusbar = new FXStatusBar( this, LAYOUT_SIDE_BOTTOM | LAYOUT_FILL_X | STATUSBAR_WITH_DRAGCORNER );
  m_splitter  = new FXSplitter( this, LAYOUT_SIDE_TOP | LAYOUT_FILL_X | LAYOUT_FILL_Y | SPLITTER_TRACKING | SPLITTER_VERTICAL | SPLITTER_REVERSED );
  FXVerticalFrame *imagebox = new FXVerticalFrame( m_splitter, );
  imageview=new FXImageView( imagebox, NULL, NULL, 0, LAYOUT_FILL_X | LAYOUT_FILL_Y );
  m_fsbox = new FXVerticalFrame( m_splitter, );
  FXHorizontalFrame *filebar = new FXHorizontalFrame( m_fsbox, FRAME_SUNKEN | FRAME_THICK | LAYOUT_FILL_X, );


  new FXButton( filebar, "\t\t Up to directory", NULL, filelist,FXFileList::ID_DIRECTORY_UP, BUTTON_TOOLBAR | FRAME_RAISED | LAYOUT_FILL_Y  )

}

ImageView::~ImageView( )
{

}

void ImageView::create( )
{

}

void ImageView::LoadImageFile( const FXString &filename )
{

}

void ImageView::SaveImageFile( const FXString &filename )
{

}

long ImageView::on_Cmd_Window( FXObject *sender, FXSelector sel, void *data )
{

}

long ImageView::on_Cmd_Filesystem( FXObject *sender, FXSelector sel, void *data )
{

}

long ImageView::on_Cmd_Image( FXObject *sender, FXSelector sel, void *data )
{

}

long ImageView::on_Upd_Image( FXObject *sender, FXSelector sel, void *data )
{

}

/*** MAIN ****************************************************************************************/
int main( int argc, char **argv ) {
  FXApp app( "ImageView", "fox-desktop" );
  app.init( argc, argv );
  new ImageView( &app );
  app.create( );

  return app.run( );
}

/*** END *****************************************************************************************/
