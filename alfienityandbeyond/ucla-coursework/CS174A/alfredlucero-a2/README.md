ID:604251044 alfredlucero-a2

I implemented the solar system using phong, gouraud, and flat shading as shown in the
examples given in the book and simply had condition variables within the vertex/fragment
shaders to instruct the program when to shade a planet in a certain manner. Affecting the
colors properly involved trial-and-error with the RGB values and further updating per 
planet during the render process. I also modified the triangle,divideTriangles, and tetrahedron
functions to include another parameter so that it can tell when to create vertices for flat or 
smooth shading as requested of the design. In addition, I moved the light position away from 
the origin and created a solid yellow sphere in order to represent the sun as the point light 
source, whereas the four distinct planets orbited around this sun with varying speeds,
colors, and shading strategies. I then adjusted the camera coordinates to look down at a 30 degree
angle from above the sun to the orbiting planets, and I made sure to implement the keyboard 
controls similar to the first assignment to move around and reset the camera view. 

Here is a brief overview of the appropriate shading techniques employed:
Flat Shading: one normal per color, one normal per primitive, in vertex shader
Gouraud Shading: three normals per primitive, one color per fragment, in vertex shader
Phong Shading: three normals per primitive, one color per fragment, in fragment shader

Due to flat shading and gouraud shading occurring in the vertex shader, I had to pass in
condition floats in order to check whether or not to use flat or gouraud shading, and had to
adjust the uniform and varying variables to account for phong shading in the vertex shaders.
Basic if-else-statements and some rearranging and copying of variables/methods did the trick nicely.

Some issues:
-Left and Right Arrow Key in changing heading not totally correct as it rotates azimuth around Y axis
when it starts off already rotated down 30 degrees on the x axis.
-Possible lighting issues/not completely accurate?

Extra Credit:
-Managed code development and submission using CS174A GitHub repository
-Added a moon orbiting around one of the planets