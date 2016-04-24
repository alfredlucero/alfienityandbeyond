
var gl;
var points;
 
var NumPoints = 5000;

//	Input Global Variables
var changeRotation = 0;
var changeFov = 50;
var changeHeading = 0.0;
var changeYPos = 0.0;
var moveFB = 0.0;
var moveLR = 0;
var toggle = 0;
var color1Index = 0;
var color2Index = 1;
var color3Index = 2;
var color4Index = 3;
var color5Index = 4;
var color6Index = 5;
var color7Index = 0;
var color8Index = 1;
var colorCycle = 0;
var changeScale = 1.0;

// Color Globals
var red = [];
var yellow = [];
var green = [];
var magenta = [];
var blue = [];
var cyan = [];


// projection -> camera -> model -> position
var mvMatrixLoc;
var pvMatrixLoc;
var cvMatrixLoc;
var pvMatrix = mat4();
var cvMatrix = mat4();

// Transformations
var translationMatrix;
var rotationMatrix;
var scaleMatrix;

var program; // Holds shader programs

// Cube Set-up
var vBuffer;
var vPosition;
var cBuffer;
var vColor;

var c2Buffer;
var c3Buffer;
var c4Buffer;
var c5Buffer;
var c6Buffer;
var c7Buffer;
var c8Buffer;

// Outline Set-up
var lvBuffer;
var lcBuffer;
var iBuffer;

// Crosshair Set-up
var ccColor;
var ciBuffer;
var cvBuffer;

var cubeColors;
var icBuffer;

 var crosshair = [
	-1.0, 0.0, -1.0,
	1.0, 0.0, -1.0,
	0.0, 1.0, -1.0,
	0.0, -1.0, -1.0
];

 var vertices = [
       // Front face
      -1.0, -1.0,  1.0,		
       1.0, -1.0,  1.0,
       1.0,  1.0,  1.0,
      -1.0,  1.0,  1.0,

      // Back face
      -1.0, -1.0, -1.0,
      -1.0,  1.0, -1.0,
       1.0,  1.0, -1.0,
       1.0, -1.0, -1.0,

      // Top face
      -1.0,  1.0, -1.0,
      -1.0,  1.0,  1.0,
       1.0,  1.0,  1.0,
       1.0,  1.0, -1.0,

      // Bottom face
      -1.0, -1.0, -1.0,
       1.0, -1.0, -1.0,
       1.0, -1.0,  1.0,
      -1.0, -1.0,  1.0,

      // Right face
       1.0, -1.0, -1.0,
       1.0,  1.0, -1.0,
       1.0,  1.0,  1.0,
       1.0, -1.0,  1.0,

      // Left face
      -1.0, -1.0, -1.0,
      -1.0, -1.0,  1.0,
      -1.0,  1.0,  1.0,
      -1.0,  1.0, -1.0
    ];

	// Array of different vec4 colors
	 var vertexColors = [
        vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
        vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
        vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
        vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
        vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
        vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
    ];

window.onload = function init()
{
    var canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //
    //  Initialize our data for the Sierpinski Gasket
    //

    //
    //  Configure WebGL
    //
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 );	// Clear the canvas to black background
	gl.enable(gl.DEPTH_TEST); // enable z-buffer for depth


	// Default transformations
	rotationMatrix = rotate(0, [0.0, 1.0, 0.0]);
	scaleMatrix = scale([1.0,1.0,1.0], 0, 0);
	translationMatrix = translate(0.0,0.0,-10.0);
	changeFov *= (960/540);
	pvMatrix = perspective(changeFov, 960/540, 0.1, 1000); // Situate to camera coordinates
	cvMatrix = translationMatrix;
	mvMatrix = mult(translationMatrix, mult(rotationMatrix, scaleMatrix));

    //  Load shaders and initialize attribute buffers

    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    // Load the data into the GPU
	// Retrieve uniforms' locations
    mvMatrixLoc = gl.getUniformLocation(program, "mvMatrix");
	pvMatrixLoc = gl.getUniformLocation(program, "pvMatrix");
	cvMatrixLoc = gl.getUniformLocation(program, "cvMatrix");
	
	/*
	// Cube Color
	cBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
    for (var j=0; j < 14; j++) {
        red = red.concat(vec4(1.0,0.0,0.0,1.0));
		yellow =  yellow.concat(vec4( 1.0, 1.0, 0.0, 1.0 ));
        green = green.concat(vec4( 0.0, 1.0, 0.0, 1.0 ));
        blue = blue.concat(vec4( 0.0, 0.0, 1.0, 1.0 ));
        magenta = magenta.concat(vec4( 1.0, 0.0, 1.0, 1.0 ));
        cyan = cyan.concat(vec4( 0.0, 1.0, 1.0, 1.0 ));
      }
    gl.bufferData(gl.ARRAY_BUFFER, flatten(red), gl.STATIC_DRAW);
    cBuffer.itemSize = 4;
    cBuffer.numItems = 14;
	
	// Cube2 Color
	c2Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c2Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(yellow), gl.STATIC_DRAW);

	// Cube3 Color
	c3Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c3Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(blue), gl.STATIC_DRAW);

	// Cube4 Color
	c4Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c4Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(green), gl.STATIC_DRAW);

	// Cube5 Color
	c5Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c5Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(magenta), gl.STATIC_DRAW);

	// Cube6 Color
	c6Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c6Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(cyan), gl.STATIC_DRAW);

	// Cube7 Color
	c7Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c7Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(red), gl.STATIC_DRAW);

	// Cube8 Color
	c8Buffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, c8Buffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(yellow), gl.STATIC_DRAW);

	gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
	*/
	
	cBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
	cubeColors = [];
	for (var i = 0; i < 24; i++)
		cubeColors = cubeColors.concat(vec4(1.0, 1.0, 1.0, 1.0));
	gl.bufferData(gl.ARRAY_BUFFER, flatten(cubeColors), gl.STATIC_DRAW);
	cBuffer.itemSize = 4;
	cBuffer.numItems = 24;
	
	// Outline Color

	lcBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	var lineColors = [];
	for (var i = 0; i < 24; i++) {
        lineColors = lineColors.concat(vec4(0.0, 0.0, 0.0, 1.0));
    }
	gl.bufferData( gl.ARRAY_BUFFER, flatten(lineColors), gl.STATIC_DRAW );
	lcBuffer.itemSize = 4;
	lcBuffer.numItems = 24;
	
	vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );

    // Associate out shader variables with our data buffer

	// Outline indices
	iBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);
	var indices = [
		0,1, 1,2, 2,3, 0,3,
		4,5, 5,6, 6,7, 4,7,
		8,9, 9,10, 10,11, 8,11,
		12,13, 13,14, 14,15, 12,15,
		16,17, 17,18, 18,19, 16,19,
		20,21, 21,22, 22,23, 20,23
	];
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(indices), gl.STATIC_DRAW);

	icBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, icBuffer);
	var cubeIndices = [
		0, 1, 2,      0, 2, 3,    
            4, 5, 6,      4, 6, 7,    
            8, 9, 10,     8, 10, 11,  
            12, 13, 14,   12, 14, 15,
            16, 17, 18,   16, 18, 19, 
            20, 21, 22,   20, 22, 23  
    ];
	gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(cubeIndices), gl.STATIC_DRAW);
	icBuffer.itemSize = 1;
	icBuffer.numItems = 36;
	
	// Outline vertices
	lvBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW);
	
	
	/*
	// Crosshair Color
	ccColor = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, ccColor);
	var crosshairColors = [];
	for (var i = 0; i < 4; i++) {
        crosshairColors = crosshairColors.concat(vec4(1.0, 1.0, 1.0, 1.0));
    }
	gl.bufferData( gl.ARRAY_BUFFER, flatten(crosshairColors), gl.STATIC_DRAW );

	// Crosshair indices
	ciBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ciBuffer);
	var cIndices = [
		0,1,
		2,3
	];
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint8Array(cIndices), gl.STATIC_DRAW);

	cvBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cvBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(crosshair), gl.STATIC_DRAW);
	*/
	// Cube
	vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW);
	
    vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mvMatrix));
	gl.uniformMatrix4fv(pvMatrixLoc, false, flatten(pvMatrix));
	gl.uniformMatrix4fv(cvMatrixLoc, false, flatten(cvMatrix));

	// Based on certain key presses, affect the rendering in various ways.
	document.onkeydown = function handleKeyDown(event) {
    // You can uncomment the next line to find out each key's code
	//alert(event.keyCode);

    if (event.keyCode == 37) {
        // Left Arrow Key: control the heading (azimuth) of the camera
		decreaseHeading();
    } else if (event.keyCode == 38) {
        // Up Arrow Key: control position of camera along the Y-axis
		decreaseY();
    } else if (event.keyCode == 39) {
        // Right Arrow Key: control the heading (azimuth) of the camera
		increaseHeading();
    } else if (event.keyCode == 40) {
        // Down Arrow Key: control position of camera along the Y-axis
		increaseY();
    } else if (event.keyCode == 67) {
		// 'c' Key: cycle the colors between the cube faces
		colorCycle = 1;
	} else if (event.keyCode == 73) {
		// 'i' Key: go forward relative to the camera's current heading
		moveForward();
	} else if (event.keyCode == 74) {
		// 'j' Key: go left relative to the camera's current heading
		moveLeft();
	} else if (event.keyCode == 75) {
		// 'k' Key: go right relative to the camera's current heading
		moveRight();
	} else if (event.keyCode == 77) {
		// 'm' Key: go backward relative to the camera's current heading
		moveBackward();
	} else if (event.keyCode == 82) {
		// 'r' Key: reset the view to the start position
		changeFov = 50;
		changeYPos = 0.0;
		changeHeading = 0;
	} else if (event.keyCode == 78) {
		// 'n' Key: make the horizontal field-of-view narrower
		narrowFov();
	} else if (event.keyCode == 87) {
		// 'w' Key: make the horizontal field-of-view wider
		widenFov();
	} else if (event.keyCode == 187) {
		// '+' Key: toggles display of an orthographic projection of a cross hair centered over your scene
		if (!toggle)
			toggle = 1;
		else
			toggle = 0;
	}
}
    render();
}


function render() {
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

	var mvMatrix = mat4();

	// Crosshair
	// if toggled on, create a orthographic crosshair
	// if toggled off, remove it

	if (toggle)
	{
		var addOrtho = ortho(-30.0, 30.0, -30.0, 30.0, 0.1, 1000);
		gl.uniformMatrix4fv(pvMatrixLoc, false, flatten(mult(addOrtho, translate(0.0, 0.0, -30.0))));
		gl.uniformMatrix4fv(cvMatrixLoc, false, flatten(mat4()));
		gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mat4()));

		gl.bindBuffer(gl.ARRAY_BUFFER, cvBuffer);
		gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

		gl.bindBuffer(gl.ARRAY_BUFFER, ccColor);
		gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

		gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, ciBuffer);

		gl.drawElements( gl.LINES, 4, gl.UNSIGNED_BYTE, 0 );
	}

	// Set up perspective projection
	pvMatrix = perspective(changeFov, 960/540, 0.1, 1000);


	 // gl.uniformMatrix4fv(pvMatrixLoc, false, flatten(mult(addPersp, mult(translate(0.0, changeYPos, -40.0), rotate(changeHeading, [0.0, 1.0, 0.0])))));
	gl.uniformMatrix4fv(pvMatrixLoc, false, flatten(pvMatrix));
	//gl.uniformMatrix4fv(pvMatrixLoc, false, flatten(mult(translate(0.0, changeYPos, -40.0), mult(rotate(changeHeading, [0.0, 1.0, 0.0]),addPersp))));
	// gl.uniformMatrix4fv(pvMatrixLoc, false, flatten(mult(rotate(changeHeading, [0.0, 1.0, 0.0]), mult(translate(0.0, changeYPos, -40.0),addPersp))));

	// Set up camera
	gl.uniformMatrix4fv(cvMatrixLoc, false, flatten(mult(rotate(changeHeading, [0.0,1.0,0.0]), translate(0.0, changeYPos, -40.0 + moveFB))));
	
	// Cube 1
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
	if (colorCycle)
	{
		swapIndex(color1Index);
		color1Index++;
		if (color1Index == 6)
			color1Index = 0;
	}

	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, icBuffer);
	
	rotationMatrix = rotate(changeRotation, [0.0, 1.0, 0.0]);
	if (changeScale >= 2.0)
		changeScale = 1.0;
	scaleMatrix = scale([5.0, 10.0, 20.0], 0, 0);
	translationMatrix = translate(10.0 + moveLR, 10.0, 10.0);
	mvMatrix = mult(translationMatrix, mult(rotationMatrix, scaleMatrix));

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mvMatrix));
	
	gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_BYTE, 0);
	
//	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);
	
	// Outline 1
	
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0 );
	
	/*
	// Cube 2

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(10.0 + moveLR, -10.0, 10.0), mult(rotationMatrix, scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c2Buffer);
	//gl.bufferData(gl.ARRAY_BUFFER, flatten(yellow), gl.STATIC_DRAW);
	if (colorCycle)
	{
		swapIndex(color2Index);
		color2Index++;
		if (color2Index == 6)
			color2Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 2
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Cube 3

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(10.0+moveLR, -10.0, -10.0), mult(rotationMatrix, scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c3Buffer);
	if (colorCycle)
	{
		swapIndex(color3Index);
		color3Index++;
		if (color3Index == 6)
			color3Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 3
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Cube 4

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(10.0+moveLR, 10.0, -10.0), mult(rotationMatrix, scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c4Buffer);
	if (colorCycle)
	{
		swapIndex(color4Index);
		color4Index++;
		if (color4Index == 6)
			color4Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 4
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Cube 5

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(-10.0+moveLR, 10.0, 10.0), mult(rotationMatrix,scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c5Buffer);
	if (colorCycle)
	{
		swapIndex(color5Index);
		color5Index++;
		if (color5Index == 6)
			color5Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 5
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Cube 6

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(-10.0+moveLR, -10.0, 10.0), mult(rotationMatrix,scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c6Buffer);
	if (colorCycle)
	{
		swapIndex(color6Index);
		color6Index++;
		if (color6Index == 6)
			color6Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 6
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Cube 7

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(-10.0+moveLR, -10.0, -10.0), mult(rotationMatrix, scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c7Buffer);
	if (colorCycle)
	{
		swapIndex(color7Index);
		color7Index++;
		if (color7Index == 6)
			color7Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 7
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Cube 8

	gl.uniformMatrix4fv(mvMatrixLoc, false, flatten(mult(translate(-10.0 + moveLR, 10.0, -10.0), mult(rotationMatrix, scaleMatrix))));

	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, c8Buffer);
	if (colorCycle)
	{
		swapIndex(color8Index);
		color8Index++;
		if (color8Index == 6)
			color8Index = 0;
	}
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 14);

	// Outline 8
	gl.bindBuffer(gl.ARRAY_BUFFER, lvBuffer);
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ARRAY_BUFFER, lcBuffer);
	gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );

	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);

	gl.drawElements( gl.LINES, 48, gl.UNSIGNED_BYTE, 0);

	// Adjust rotation and scaling
	changeRotation += 6;
	changeScale += 0.01;

	// Toggle color cycling
	if (colorCycle == 1)
		colorCycle = 0;
	*/
	requestAnimFrame(render);
}


function widenFov(){
	changeFov += 5;
}

function narrowFov(){
	changeFov -= 5;
}

function increaseY(){
	changeYPos += 0.25;
}

function decreaseY(){
	changeYPos -= 0.25;
}

function increaseHeading(){
	changeHeading += 1;
}

function decreaseHeading(){
	changeHeading -= 1;
}

function moveLeft(){
  moveLR += 0.25;
}

function moveRight(){
	moveLR -= 0.25;
}

function moveForward(){
	moveFB += 0.25;
}

function moveBackward(){
  moveFB -= 0.25;
}

function swapIndex(index) {
		index++;
		switch(index){
			case 1:
				gl.bufferData(gl.ARRAY_BUFFER, flatten(yellow), gl.STATIC_DRAW);
				break;
			case 2:
				gl.bufferData(gl.ARRAY_BUFFER, flatten(green), gl.STATIC_DRAW);
				break;
			case 3:
				gl.bufferData(gl.ARRAY_BUFFER, flatten(magenta), gl.STATIC_DRAW);
				break;
			case 4:
				gl.bufferData(gl.ARRAY_BUFFER, flatten(blue), gl.STATIC_DRAW);
				break;
			case 5:
				gl.bufferData(gl.ARRAY_BUFFER, flatten(cyan), gl.STATIC_DRAW);
				break;
			case 6:
				gl.bufferData(gl.ARRAY_BUFFER, flatten(red), gl.STATIC_DRAW);
				break;
		}
}
