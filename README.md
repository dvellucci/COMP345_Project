# COMP345_Project

Project for advanced program design with C++ (COMP 345) Concordia.

Steps to install:

When the project is loaded in Visual Studio 17, right click on the solution and go to properties -> C/C++ -> General.
In the field "additional include Directories", enter SFML\include

Then on the left, go to Linker -> General.
In the field Additional Library Directories, enter the path SFML\lib\static-std

Then go to linker -> input.
In the additional dependencies field, enter these 5 dependencies:
sfml-graphics-s.lib;
sfml-window-s.lib;
sfml-system-s.lib;
freetype.lib;
jpeg.lib;
opengl32.lib;
winmm.lib;

If your visual studio is enabled to x64, change it to x86 at the top. 
