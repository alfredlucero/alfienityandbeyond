

var canvas;
var gl;

var numVertices  = 36;

var texSize = 64;

var program;

var pointsArray = [];
var colorsArray = [];
var texCoordsArray1 = [];
var texCoordsArray2 = [];

var texture;
var pikachuImage;
var tomodachiImage;

var texCoord1 = [
    vec2(0, 0),	
    vec2(0, 1.0),	
    vec2(1.0, 1.0),	
    vec2(1.0, 0)
];

var texCoord2 = [
    vec2(0, 0),	
    vec2(0, 2.0),	
    vec2(2.0, 2.0),	
    vec2(2.0, 0)
];

var vertices = [
    vec4( -0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5,  0.5,  0.5, 1.0 ),
    vec4( 0.5,  0.5,  0.5, 1.0 ),
    vec4( 0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5, -0.5, -0.5, 1.0 ),
    vec4( -0.5,  0.5, -0.5, 1.0 ),
    vec4( 0.5,  0.5, -0.5, 1.0 ),
    vec4( 0.5, -0.5, -0.5, 1.0 )
];

var vertexColors = [
    vec4( 0.0, 0.0, 0.0, 1.0 ),  // black
    vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
    vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
    vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    vec4( 0.0, 1.0, 1.0, 1.0 ),  // white
    vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
];    

var xAxis = 0;
var yAxis = 1;
var zAxis = 2;
var axis = xAxis;
var theta = [0.0, 0.0, 0.0];

var cameraViewMatrix;
var rotationMatrix1;
var rotationMatrix2;
var rotationON = 0;
var changeRotation1 = 0;
var changeRotation2 = 0;
var scrollON = 0;
var rotateTexON = 0;

var modelViewMatrixLoc;
var projectionMatrixLoc;
var cameraViewMatrixLoc;
var cubeLoc;
var timeLoc;
var scrollLoc;
var thetaLoc;
var rotateTexLoc;

function configureTexture( image, texfilter ) {
    texture = gl.createTexture();
    gl.bindTexture( gl.TEXTURE_2D, texture );
    gl.pixelStorei(gl.PACK_ALIGNMENT, true); // gl.UNPACK_FLIP_Y_WEBGL
    gl.texImage2D( gl.TEXTURE_2D, 0, gl.RGB, 
         gl.RGB, gl.UNSIGNED_BYTE, image );
	if (texfilter == 0) {
		gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, 
                      gl.NEAREST );
		gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST );
    } else {
		gl.generateMipmap( gl.TEXTURE_2D );
		gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, 
                      gl.LINEAR_MIPMAP_LINEAR );
		gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR );
	}
		
    gl.uniform1i(gl.getUniformLocation(program, "texture"), 0);
}


function quad(a, b, c, d) {
     pointsArray.push(vertices[a]); 
     colorsArray.push(vertexColors[a]); 
     texCoordsArray1.push(texCoord1[0]);
	 texCoordsArray2.push(texCoord2[0]);
     
	 pointsArray.push(vertices[b]); 
     colorsArray.push(vertexColors[a]);
     texCoordsArray1.push(texCoord1[1]); 
	 texCoordsArray2.push(texCoord2[1]);

     pointsArray.push(vertices[c]); 
     colorsArray.push(vertexColors[a]);
     texCoordsArray1.push(texCoord1[2]);
	 texCoordsArray2.push(texCoord2[2]);
   
     pointsArray.push(vertices[a]); 
     colorsArray.push(vertexColors[a]);
     texCoordsArray1.push(texCoord1[0]);
	 texCoordsArray2.push(texCoord2[0]);

     pointsArray.push(vertices[c]); 
     colorsArray.push(vertexColors[a]);
     texCoordsArray1.push(texCoord1[2]);
     texCoordsArray2.push(texCoord2[2]);	 

     pointsArray.push(vertices[d]); 
     colorsArray.push(vertexColors[a]);
     texCoordsArray1.push(texCoord1[3]);
	 texCoordsArray2.push(texCoord2[3]);
}


function colorCube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}


window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 );
    
    gl.enable(gl.DEPTH_TEST);

    //
    //  Load shaders and initialize attribute buffers
    //
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
    
    colorCube();

    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colorsArray), gl.STATIC_DRAW );
    
    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );

    var vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW );
    
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );
    
    tBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, tBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(texCoordsArray1), gl.STATIC_DRAW );
    
    var vTexCoord = gl.getAttribLocation( program, "vTexCoord" );
    gl.vertexAttribPointer( vTexCoord, 2, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vTexCoord );

	modelViewMatrixLoc = gl.getUniformLocation( program, "modelViewMatrix" );
    projectionMatrixLoc = gl.getUniformLocation( program, "projectionMatrix" );
	cameraViewMatrixLoc = gl.getUniformLocation( program, "cameraViewMatrix" );
	timeLoc = gl.getUniformLocation( program, "time" );
	thetaLoc = gl.getUniformLocation( program, "theta" ); 
	scrollLoc = gl.getUniformLocation( program, "scroll" );
	cubeLoc = gl.getUniformLocation( program, "cube" );
	rotateTexLoc = gl.getUniformLocation( program, "rotateTex" );
	
	var projectionMatrix = perspective(45, 960/540, 0.1, 1000);
	gl.uniformMatrix4fv(projectionMatrixLoc, false, flatten(projectionMatrix) );
	cameraViewMatrix = translate(0.0, 0.0, -5.0);
	gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix) );
	
    //
    // Initialize a texture
    //

    //var image = new Image();
    //image.onload = function() { 
     //   configureTexture( image );
    //}
    //image.src = "SA2011_black.gif"
	
	// if (!isPowerOfTow(image.width) || !isPowerOfTwo(
	
    pikachuImage = document.getElementById("pikachuImage");
	tomodachiImage = document.getElementById("tomodachiImage");
	gl.uniform3fv(thetaLoc, flatten(theta)); // Flip right side up
	
	// Based on certain key presses, affect the rendering in various ways.
	document.onkeydown = function handleKeyDown(event) {
    // You can uncomment the next line to find out each key's code
	//alert(event.keyCode);

	if (event.keyCode == 73) {
		// 'i' Key: go forward relative to the camera's current heading
		moveForward();
	} else if (event.keyCode == 79){
		// 'o' Key: go backward relative to the camera's current heading
		moveBackward();
	} else if (event.keyCode == 82) {
		// 'r' Key: toggle rotation of each cube
		if (!rotationON)
			rotationON = 1;
		else
			rotationON = 0;
	} else if (event.keyCode == 83) {
		// 's' Key: toggle continuous scrolling of the texture map on the pikachu cube
		if (!scrollON)
			scrollON = 1.0;
		else
			scrollON = 0.0;
		gl.uniform1f(scrollLoc, scrollON);
	} else if (event.keyCode == 84) {
		// 't' Key: toggle rotation of the texture map on the tomodachi cube
		if (!rotateTexON)
			rotateTexON = 1.0;
		else
			rotateTexON = 0.0;
		gl.uniform1f(rotateTexLoc, rotateTexON);
	}
}
	render();
}

var render = function(time){
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    
	gl.uniform1f(timeLoc, time);
    gl.uniform3fv(thetaLoc, flatten(theta));
	rotationMatrix1 = rotate(changeRotation1, [0.0, 1.0, 0.0]);
	rotationMatrix2 = rotate(changeRotation2, [1.0, 0.0, 0.0]);
	
	var modelViewMatrix = mat4();
	
	// Nearest-neighbor texture filtering cube
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(modelViewMatrix, mult(translate(2.0, 0.0, -10.0),mult(rotationMatrix1, scale(3.0, 3.0, 3.0))))));
	gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix));
	
	// Configure tomodachi texture with nearest-neighbor filtering
	gl.uniform1f(cubeLoc, 0.0);
	gl.bindBuffer( gl.ARRAY_BUFFER, tBuffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(texCoordsArray1), gl.STATIC_DRAW );
	configureTexture( tomodachiImage, 0 );
	
	gl.drawArrays( gl.TRIANGLES, 0, numVertices );
	
	
	// Tri-linear texture filtering cube
	gl.uniform1f(cubeLoc, 1.0);
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(modelViewMatrix, mult(translate(-2.0, 0.0, -10.0), mult(rotationMatrix2, scale(3.0, 3.0, 3.0))))));
	gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix));
	
	// Configure pikachu texture with tri-linear filtering
	gl.bindBuffer( gl.ARRAY_BUFFER, tBuffer );
	gl.bufferData( gl.ARRAY_BUFFER, flatten(texCoordsArray2), gl.STATIC_DRAW );
	configureTexture ( pikachuImage, 1 );
	
	gl.drawArrays( gl.TRIANGLES, 0, numVertices );
	
	if (rotationON) {
		changeRotation1 += 1;
		changeRotation2 += 0.5;
	}
	
	requestAnimFrame(render);
}

function moveBackward() {
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, -0.25));
}

function moveForward() {
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, 0.25));
}