# Fox Gnome Human Interface library (foxGHI)  
-08/09/2022-

*Content:*
  1. General info
  2. Compilation and installation
  3. Known errors and bugs
  4. The project state and plans for the future
  5. Author and project licencion
  6. Internet
  
<p align="center"><img src="doc/images/01.png?raw=true" width="49%" />  

## 1. GENERAL INFO:
This very small library extends the FOX GUI Framework with several additional classes with the help of which
you can use top-level windows without decoration with the so-called Header bar.

The Header bar is a small bar at the top of the window that integrates the properties of the title bar,
including major control buttons such as iconify, maximize, restore, close window, and
possibly another. It also enables movement with the window using the mouse. Just like the title bar of the window can
display the app name and some additional text. It also provides space for tool buttons,
different indicators and the like, basically almost any widget can be used. Often Header bar
also contains a button with a roll-up main menu of the application.

The goal of this library is not to create a complete „Gnome 3-Like style“ for Fox, only to implement it
some - in my opinion - innovative and interesting techniques from this environment. At this time
Simple Window (FXGWindow), Header bar (FXWindowHeader) and Window Control Panel (FXWindowController) are implemented.

As stated above, the goal of this library is not to duplicate Gnome 3, but to implement those
object, I am trying to start from the Gnome 3 Standard "GHI - Gnome Human Interface", according to this one
the library also got its name.

Please note that the library is currently under development and may change at any time, although there is a 
certain effort to prevent this from happening, however, this cannot be guaranteed at this time



## 2. COMPILATION AND INSTALLATION:
*Dependecies:*
  [Foxtoolkit 1.7.76](http://fox-toolkit.org/ftp/fox-1.7.76.tar.gz)

*Aditional dependencies for kompilation:*
  cmake >= 3.10
  
After downloading the project from Github (and possibly unzipping it), go to the folder with the project and enter the following command sequence:
'''
  mkdir build
  cd build && cmake .. 
  make
  sudo make install
'''
After successfully compiling and building the project, the resulting library and header files will be installed into the
address book /opt/foxGHI/0.1/1/

## 3. KNOWN ERRORS AND BUGS
*  10/09/2022 - Disfunct the "maximize" button - opened
   On some WMs and DEs (eg Gnome, Cinnamon) the maximize button may not work. Probably it is a 
   faulty communication between the application and WM, or an error in the WM settings.
    
## 4. PROJECT STATE AND PLANS FOR THE FUTHURE
FoxGHI currently implements the basic, intended functionality - i.e. autonomous top-level window with
an integrated headerbar in the style of Gnome 3. However, there is still room for improvement. For 
that reason please keep in mind that the project is still under development and may contain bugs and 
may change over time.

It will be in the near future
  1) Create a documentations for this library
  2) Examples and tests
  3) Versioned
  4) integration boxes for FXWindowHeader

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
  * [Foxtoolkitu home page](http://fox-toolkit.org/)
  * [Gnome Human Interace Guidelines](https://developer.gnome.org/hig/)
  * [Autor's blog (CZ)](http://bfuplusplus.blogspot.cz/)
