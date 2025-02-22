# Fox Gnome Human Interface library (foxGHI)  
-22/02/2025-

*Content:*
  1. [General info](#1-general-info)
  2. [Compilation and installation](#2-compilation-and-installation)
  3. [Known errors and bugs](#3-known-errors-and-bugs)
  4. [The project state and plans for the future](#4-project-state-and-plans-for-the-futhure)
  5. [Author and project licence](#5-Author-and-project-licencion)
  6. [Internet](#6-internet)

_Img.1: An FoxGHI window examles_
<p align="center"><img src="doc/images/screenshot.png?raw=true" width="85%"/>  
  

## 1. GENERAL INFO:
This very small library extends the FOX GUI framework with several additional classes with the help of which
you can use top-level windows without decoration with the so-called Header bar.

The Header bar is a small bar at the top of the window that integrates the properties of the title bar,
including major control buttons such as iconify, maximize, restore, close window, and
possibly another. It also enables movement with the window using the mouse. Just like the title bar of the window can
display the app name and some additional text. It also provides space for tool buttons,
different indicators and the like, basically almost any widget can be used. Often Header bar
also contains a button with a roll-up main menu of the application.

FoxGHI offers several standard options in FOX Registers, through which you can influence behavior and 
appearance of most widgets in this library. They are grouped into the "FoxGHI" group and the name 
of the option consists of the object identifier and the property name, separated by a dot. The settings 
can be seen in the illustrative screenshot of the project. The options are as follows:
 * Window.EnableBorder - Enables/disables bordering of the window with a thin black line
 * Window.SelfControl - Enables/disables the window state management
 * Window.WMControl - Enables/disables Window manager framing (including window status handling)
 * Header.EnableColorize - Enables/disables GUI coloring of Header bar child
 * Header.BaseColorOffset - Sets the amount of dimming of the header bar bass color (in %). The range
                            is from 0 to 100, with 0 disabling dimming. The default setting is 20.
 * Header.TitleFont - Uses the set font to display the title bar, if enabled
 * Header.SubTitleFont - The specified font will be used to display the additional text of the main title, 
                           if enabled and set.
 * Controller.Hidden - Show/hide the window button controls on the HeaderBar 
 
To facilitate library configuration, FoxGHI provides a ControlPanel class that implements a GUI wrapper 
FoxGHI configuration. ControlPanel is designed to be easily integrated into any project 
using FoxGHI, or, if the developer deems it appropriate, it can be used in a standalone 
configuration utility. An example of how to work with this class is the FoxGHICP program in the utility directory 
project directory. This small utility is thus also provided as an independent configuration tool in the style 
FOX Control Panel. 

_Img.2: The FoxGHICP - FoxGHI Control Panel utility_
<p align="center"><img src="doc/images/ControlPanel.png?raw=true"/>  

The goal of this library is not to create a complete "Gnome 3-Like style“ for Fox, only to implement it
some - in my opinion - innovative and interesting techniques from this environment, that I want alone to 
use in my own projects. At this time Primary, Secondary Window (FXPrimaryWindow, FXSecondaryWindow), 
Header bar (FXWindowHeader), Window Control Panel (FXWindowController) and FoxGHI Settings wrapper 
(ControllPanel) are implemented.

As stated above, the goal of this library is not to duplicate Gnome 3, but to implement those
object, I am trying to start from the Gnome 3 Standard "GHI - Gnome Human Interface", according to this one
the library also got its name.

Please note that the library is currently under development and may change at any time, although there is a 
certain effort to prevent this from happening, however, this cannot be guaranteed at this time
 
## 2. COMPILATION AND INSTALLATION:
*Dependecies:*
  [Foxtoolkit 1.7.84](http://fox-toolkit.org/ftp/fox-1.7.84.tar.gz)

*Aditional dependencies for compilation:*
  cmake >= 3.10
  
After downloading the project from GitHub (and possibly unzipping it), go to the folder with the project and enter the following command sequence:
```
  mkdir build
  cd build && cmake .. 
  make
  sudo make install
```
After successfully compiling and building the project, the resulting library and header files will be installed into the
directory /opt/foxghi/0.4/

## 3. KNOWN ERRORS AND BUGS
* 18/05/2023 - Disfunct the "maximize" button - status fixed, closed
* 19/01/2023 - Some WMs show a forbidden decorative frame if the application icon is set - status open
    
## 4. PROJECT STATE AND PLANS FOR THE FUTHURE
Actual version: 25.02 0.5.0.0 ALPHA

FoxGHI currently implements the basic, intended functionality - i.e. autonomous top-level window with
an integrated headerbar in the style of Gnome 3. However, there is still room for improvement. For 
that reason please keep in mind that the project is still under development and may contain bugs and 
may change over time.


### 21/05/2023 Change of the default installation directory
From this version, FoxGHI will default to the directory install/path/foxghi/MAJOR.MINOR/, i.e. no subdirectory with the development version will be added,
which caused problems with library settings in ld.cache when updating development or patch versions

### 20/05/2023 Side Bar widget implementation is postponed indefinitely

### 28/05/2023 Fixed function of the window maximize button
Fixed the unpleasant bug of the non-functioning window maximization button, which appeared in some WMs.
It turned out that this functionality is influenced by the decorative attributes of the FXTopWindow class.  

### 02/03/2023 Presets for classic window decoration
The FXPrimaryWindow class allows you to define the FXTopWindow class flags, that will be used when 
activating the classic window management.  

### 09/10/2022 Basic concept of FoxGHI setup completed
FoxGHI now provides the ability to set the behavior of individual widgets within this library. Of 
course, more options will be added as the library is developed. The plan is to add a formulary class, 
whose to change the behavior of FoxGHI directly in the application. This form will be used for create 
a separate utility for setting up FoxGHI aka FOX Control Panel.  

### 18/10/2022 The control panel is almost finished
It remains to sort out the default values and how the CP class will be available in the library  

### 29/10/2022 Implementation of FXGHI_ControlPanel class completed 
The class providing the GUI for setting FoxGHI properties is finished and integrated into the library. Now
will only add any configuration options as the project progresses. With this class
FoxGHICP configuration utility has also been completed. I am therefore removing this item from the list of planned development goals.  

### 30/10/2022 Include basic concept of docking boxes
Added horizontal panel class, designed for creating small complex widgets (Boxes) to 
Header Bar. Its use is intended as a grouping of several similar elements with a similar focus 
(e.g. toolboxes) or standalone widgets where it is convenient to use some kind of docking base (e.g. 
menu).  

### 22/11/2022 Matching class names and corresponding files with GHI and Foxtoolkit (within limits)  

### 20/11/2024 Adding a project version to the library
Expanding the options for setting the Header bar color (darkening) in Foxlib registers.

### It will be in the near future  
  1) Completed Header Bar colorization setup in FXGHI::ControllPanel class
  2) Predefined basic FoxGHI setting profiles
  3) Create a documentations for this library
  4) Examples and tests
 

## 5. AUTHOR AND PROJECT LICENCION:
Copyright (C) 2019 - 2022 Pavel Šafařík <drakarax@seznam.cz>
All rights reseved.

This file is part of foxGHI.

FoxGHI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at 
your option) any later version.

foxGHI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with foxGHI. If not, see 
<https://www.gnu.org/licenses/>.

## 6. INTERNET
  * [Foxtoolkit home page](http://fox-toolkit.org/)
  * [Oxygen KDE icons theme, used in the FoxGHICP utility](https://github.com/KDE/oxygen-icons)
  * [Gnome Human Interace Guidelines](https://developer.gnome.org/hig/)
  * [Author's blog (CZ)](http://bfuplusplus.blogspot.cz/)

