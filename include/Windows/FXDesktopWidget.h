//
// Created by gabriel on 13.05.26.
//

#ifndef FXGHI_FXDESKTOPWIDGET_H
#define FXGHI_FXDESKTOPWIDGET_H

#include <fox-1.7/fx.h>
//#include <X11/Xlib.h>

namespace FXGHI {
#define DEFAULT_WIDGET_WIDTH 200
#define DEFAULT_WIDGET_HEIGHT 100

  enum FXDesktopWidgetType {
    DESKTOP_WIDGET_NORMAL,
    DESKTOP_WIDGET_DESKTOP,
    DESKTOP_WIDGET_DOCK,
    DESKTOP_WIDGET_UTILITY
  };

  enum FXDesktopWidgetMode {
    DESKTOP_WIDGET_MODE_WIDGET,   // bez dekorací, sticky, skip taskbar
    DESKTOP_WIDGET_MODE_WINDOW    // normální okno, dekorace, taskbar
  };

  class FXDesktopWidget : public FXMainWindow {
    FXDECLARE(FXDesktopWidget)

    // Widget Properties
    FXString m_instanceId;
    FXDesktopWidgetType m_widgetType;
    FXbool m_skipTaskbar; // true -> Nezobrazovat v seznamu oken na plose
    FXbool m_skipPager;   // true -> nezobrazivat na strankovaci ploch
    FXbool m_sticky;      // true -> zobrazit na vsech dostupnych plochach
    FXbool m_above;       // true -> bude drzeno NAD beznymi okny
    FXbool m_below;       // true -> bude drzeno POD beznymi okny

    // Widget mode
    FXDesktopWidgetMode m_mode;
    FXuint m_widgetDecor;
    FXuint m_windowDecor;
    FXbool m_allowMode;

    // Widget Geometry
    FXPoint m_position;
    FXSize  m_size;
    FXbool  m_GeomtryChanged;

    // Transparency support
    /* in process */

  public:
    FXDesktopWidget( FXApp* app, const FXString& name, FXint x = 0, FXint y = 0, FXint w = DEFAULT_WIDGET_WIDTH, FXint h = DEFAULT_WIDGET_HEIGHT );
    virtual ~FXDesktopWidget();

    /* Access methods */
    const FXString& getInstanceId( ) const { return m_instanceId; }
    void setInstanceId( const FXString& id ) { m_instanceId = id; }
    void setWidgetType( FXDesktopWidgetType type );
    FXDesktopWidgetType getWidgetType( ) const { return m_widgetType; }
    void SetWindowMode( FXDesktopWidgetMode mode );
    FXDesktopWidgetMode getWindowtMode( ) const { return m_mode; }
    void EnableWidgetMode( FXbool allow ) { m_allowMode = allow; }
    void setSkipTaskbar( FXbool value );
    FXbool getSkipTaskbar( ) const { return m_skipTaskbar; }
    void setSkipPager( FXbool value );
    FXbool getSkipPager( ) const { return m_skipPager; }
    void setSticky( FXbool value );
    FXbool getSticky( ) const { return m_sticky; }
    void setAbove( FXbool value );
    FXbool getAbove( ) const { return m_above; }
    void setBelow( FXbool value );
    FXbool getBelow( ) const { return m_below; }

    /* Operations */
    void create() override;
    FXbool close( FXbool notify = false );

    /* GUI Messagess & handlers*/
    long onConfigure( FXObject*, FXSelector, void* );

  protected:
    FXDesktopWidget();

    //Display* GetDisplay( ) const { return static_cast<Display*>( getApp( )->getDisplay( ) ); }
    void     SetX11WindowType( const char* atomName );
    void     AddX11State( const char* atomName );
    void     RemoveX11State( const char* atomName );
    void     ApplyX11Hints( );
    void     InitBaseDefaults( );
    virtual void setLockModeDefaults( );    // Lock => Widget
    virtual void setUnlockModeDefaults( );  // Unlock => Normal window ;)
    virtual void ApplyMode( FXbool remap = true );
    void     LoadGeometry( );
    void     SaveGeometry( );
    void     CheckGeometry( );
};

}

#endif //FXGHI_FXDESKTOPWIDGET_H
