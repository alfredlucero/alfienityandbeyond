ID:604251044 alfredlucero-a3 

I modified the given textureCube1.html and textureCube1.js files in order to apply
two square images (pikachu.png and tomodachi.png, 256 x 256) onto two cubes. 
I applied basic transformations by using projection (perspective), camera, and model
matrices that involve rotations, translations, and scaling, and for simple visibility,
I placed the cubes side by side and had to orient the textures so that it starts
out right side up (before it would be upside down). 

In order to handle tri-linear and nearest-neighbor filtering, I simply
had to alter the options of texParameteri function within configureTexture function 
for min and mag (gl.NEAREST/gl.NEAREST or gl.LINEAR_MIPMAP_LINEAR/gl.LINEAR). To produce
the effect of zooming out, I had to alter the texture coordinates so that they would maintain
the aspect ratio while shrinking and repeating to fill up each cube face. In addition,
I mirrored previous assignments for the 'i' and 'o' keys to bring the camera nearer
or farer away from the cubes. 

EXTRA CREDIT:
1. 'r' key properly rotates the cubes around the X and Y axes with varying speeds.
2. I set up the 't' key but realized I would have to alter the starting texCoords 
in a fashion that would affect the setup/bigger portion of the original program. 
Instead I just had the texture go around in a circle applying sin and cos.
3. 's' scrolls in sinusoidal fashion left to right with repeating textures.
