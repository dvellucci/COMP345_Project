# COMP345_Project

Project for advanced program design with C++ (COMP 345) Concordia.

Steps to install:

When the project is loaded in Visual Studio 17 (in debug mode), right click on the solution and go to properties -> C/C++ -> General.
In the field "additional include Directories", enter ..\SFML\include

Then on the left, go to Linker -> General.
In the field Additional Library Directories, enter the path ..\SFML\lib\static-std

Then go to linker -> input.
In the additional dependencies field, enter these 5 dependencies:
sfml-graphics-s-d.lib;
sfml-window-s-d.lib;
sfml-system-s-d.lib;
freetype.lib;
jpeg.lib;
opengl32.lib;
winmm.lib;

If your visual studio is enabled to x64, change it to x86 at the top. In the properties panel, make sure the configuration is in debug mode. 
