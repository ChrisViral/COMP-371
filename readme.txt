Christophe Savard
40017812
COMP-317 WW
Assignment 1
Feburary 8th 2018

===== Compilation Information =====

Compiled using Visual Studio 2017 (15.5.5), using the visual studio compilation tools v141, on Windows 10.
GLEW, GLFW, and GLM have been configured to be in the project folder for compilation, for both lib and header files.
Header files should be in ./Include, lib files should be in ./Lib, and glew32.dll in ./A1, with the code files.
A compiled binary for Windows is also given in ./Compiled, along with the necessary shader files.

===== Controls =====

Space - Displace horse at random on the 100x100 grid
Home  - Returns horse and camera to default positions
Esc   - Closes the GL window

U - Scale horse up by adding a factor of 0.1
J - Scale horse down by removing a factor of 0.1 (clamped to stay greater than 0)

W - Move horse upwards one grid unit (Z-)
S - Move horse downwards one grid unit (Z+)
A - Move horse left one grid unit (X-)
D - Move horse right one grid unit (X+)

shift + W - Angle horse upwards 5 degrees (Z axis rotation)
shift + S - Angle horse downwards 5 degrees (Z axis rotation)
shift + A - Angle horse left 5 degrees (Y axis rotation)
shift + D - Angle horse right 5 degrees (Y axis rotation)

NOTES: The expected controls for the direction arrows were not very clear, so I implemented them how I thought they made sense
Up    - Move the camera forward one grid unit (Z-)
Down  - Move the camera backward one grid unit (Z+)
Left  - Move the camera left one grid unit (X-)
Right - Move the camera right one grid unit (X+)

P - Change polygons rendering mode to points
T - Change polygons rendering mode to triangles
L - Change polygons rendering mode to lines


===== Mouse controls =====

Right button hold  - Pans camera by sliding side to side
Middle button hold - Tilts camera by sliding up and down (Clamped to -89 to 89 degrees)
Left button hold   - Zooms camera by sliding up and down (Zooms up to a distance of 0.1)