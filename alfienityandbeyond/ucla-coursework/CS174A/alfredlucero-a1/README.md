604251044 alfredlucero-a1

For Assignment 1, I built off of the gasket template provided in class and created
eight cubes using a single sequential triangle strip (EXTRA CREDIT) and the same data. Each cube 
would be created with a different color using different color buffers and set variables
holding the color vectors. In handling keyboard inputs, I would use document.onkeydown
and have conditions checking for certain event keycodes pertaining to left arrow key, right
arrow key, etc. Then, certain global variables would be affected that are used in transformations
for translating, rotating, projecting in different ways (ortho and perspective). MV.js proved
helpful for matrix multiplications and vector creation, and the ordering of transformations proved
critical in handling the changes in heading, fov, y position, etc.

I ran into some issues with handling the camera and moving forward and backward in which the objects
would only move forward towards the camera in a certain way rather than wherever the camera is.
Also, for handling the horizontal field of view I decided to find it by considering the ratio of 
width/height to be equal to fovx/fovy and altered the perspective function accordingly (initial fov is 50 * (960/540)).

Other completed extra credit opportunities:

-Using quaternions for navigation: rotations in MV.js already handle this
-Drawing a cube using a single sequential triangle strip from the same data
-Manage your code development and submission using CS174A GitHub repository (check commit history).
-Rotating cube in 60 RPM, scaling by 0.01 per frame (1.0 -> 2.0 -> 1.0), smooth (not by ten percent though)