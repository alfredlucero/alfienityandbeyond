// .\chrome.exe" --allow-file-access-from-files

var canvas;
var gl;
var progam;

var numTimesToSubdivide = 3;

var index = 0;
var indexG = 0;

var pointsArray = [];
var pointsGPArray = [];
var normalsArray = [];
var normalsGPArray = [];

var va = vec4(0.0, 0.0, -1.0,1);
var vb = vec4(0.0, 0.942809, 0.333333, 1);
var vc = vec4(-0.816497, -0.471405, 0.333333, 1);
var vd = vec4(0.816497, -0.471405, 0.333333,1);

var lightPosition = vec4(0.0, 1.0, 0.0, -5.0);
var lightAmbient = vec4(0.2, 0.2, 0.2, 1.0 );
var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );
var lightSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );

var materialAmbient = vec4( 1.0, 0.0, 1.0, 1.0);
var materialDiffuse = vec4( 1.0, 0.8, 0.0, 1.0);
var materialSpecular = vec4( 0.0, 0.0, 0.0, 1.0);
var materialShininess = 20.0;

// Holds different color values for each planet
var ambientProductS, diffuseProductS, specularProductS;
var ambientProductF, diffuseProductF;
var ambientProductG1, diffuseProductG1;
var ambientProductG2, diffuseProductG2, specularProductG2;
var ambientProductP, diffuseProductP;
var ambientLoc, diffuseLoc, specularLoc;

var modelViewMatrix, projectionMatrix;
var modelViewMatrixLoc, projectionMatrixLoc;
var cameraViewMatrix, cameraViewMatrixLoc;

var vPosition;
var vNormal;
var vBuffer;
var nBuffer;

var nGBuffer;
var vGBuffer;

var drawIndexLoc;
var drawIndex = 0;

var normalMatrix, normalMatrixLoc;

var changeRotationF = 0;
var changeRotationG1 = 0;
var changeRotationG2 = 0;
var changeRotationP = 0;

var orbitingPlanet = mat4();
var isFixed = 0;

function triangle(a, b, c, fs) {
	if (fs == 0 ){ // Flat Shading Set-Up
		var t1 = subtract(b, a);
		var t2 = subtract(c, a);
		var normal = normalize(cross(t2, t1));
		normal = vec4(normal);

		normalsArray.push(normal);
		normalsArray.push(normal);
		normalsArray.push(normal);

		pointsArray.push(a);
		pointsArray.push(b);
		pointsArray.push(c);

		index += 3;
	 }
	 else if (fs == 1) {// Gouraud Shading Set-Up
		pointsGPArray.push(a);
		pointsGPArray.push(b);
		pointsGPArray.push(c);

		// normals are vectors

		normalsGPArray.push(a[0],a[1], a[2], 0.0);
		normalsGPArray.push(b[0],b[1], b[2], 0.0);
		normalsGPArray.push(c[0],c[1], c[2], 0.0);

		indexG += 3;
	 }
}

function divideTriangle(a, b, c, count, fs) {
    if ( count > 0 ) {

        var ab = mix( a, b, 0.5);
        var ac = mix( a, c, 0.5);
        var bc = mix( b, c, 0.5);

        ab = normalize(ab, true);
        ac = normalize(ac, true);
        bc = normalize(bc, true);

        divideTriangle( a, ab, ac, count - 1, fs );
        divideTriangle( ab, b, bc, count - 1, fs );
        divideTriangle( bc, c, ac, count - 1, fs );
        divideTriangle( ab, bc, ac, count - 1, fs );
    }
    else {
        triangle( a, b, c, fs );
    }
}


function tetrahedron(a, b, c, d, n, fs) {
    divideTriangle(a, b, c, n, fs);
    divideTriangle(d, c, b, n, fs);
    divideTriangle(a, d, b, n, fs);
    divideTriangle(a, c, d, n, fs);
}



window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 ); // Clear to black background

    gl.enable(gl.DEPTH_TEST); // Z-Buffer enabled

    //
    //  Load shaders and initialize attribute buffers
    //
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

	// Set up different colors for planets
    ambientProductS = mult(lightAmbient, materialAmbient);
    diffuseProductS = mult(lightDiffuse, materialDiffuse);
    specularProductS = mult(lightSpecular, materialSpecular);

	ambientProductF = mult(lightAmbient, vec4(1.0, 1.0, 1.0, 1.0));
    diffuseProductF = mult(lightDiffuse, vec4(1.0, 1.0, 1.0, 1.0));

	ambientProductG1 = mult(lightAmbient, vec4(0.0, 0.75, 0.45, 1.0));
    diffuseProductG1 = mult(lightDiffuse, vec4(0.0, 0.75, 0.45, 1.0));

    ambientProductG2 = mult(lightAmbient, vec4(0.8, 0.4, 0.25, 1.0));
    diffuseProductG2 = mult(lightDiffuse, vec4(0.8, 0.4, 0.25, 1.0));
    specularProductG2 = mult(lightSpecular, vec4(0.0, 0.0, 0.0, 1.0));

	ambientProductP = mult(lightAmbient, vec4(0.0, 0.5, 0.75, 1.0));
    diffuseProductP = mult(lightDiffuse, vec4(0.0, 0.5, 0.75, 1.0));

	drawIndex = 0;
	// Set-up flat shading arrays
    tetrahedron(va, vb, vc, vd, numTimesToSubdivide, drawIndex);
	drawIndex++;
	// Set-up gouraud shading arrays
	tetrahedron(va, vb, vc, vd, numTimesToSubdivide, drawIndex);
	drawIndex++;

	// Flat Normal Buffer
    nBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, nBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(normalsArray), gl.STATIC_DRAW );

	// Gouraud Normal Buffer
	nGBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, nGBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(normalsGPArray), gl.STATIC_DRAW );

    vNormal = gl.getAttribLocation( program, "vNormal" );
    gl.vertexAttribPointer( vNormal, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vNormal);

	// Flat Vertex Buffer
    vBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);

	// Gouraud Vertex Buffer
	vGBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vGBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsGPArray), gl.STATIC_DRAW);

    vPosition = gl.getAttribLocation( program, "vPosition");
    gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vPosition);

    modelViewMatrixLoc = gl.getUniformLocation( program, "modelViewMatrix" );
    projectionMatrixLoc = gl.getUniformLocation( program, "projectionMatrix" );
    normalMatrixLoc = gl.getUniformLocation( program, "normalMatrix" );
	cameraViewMatrixLoc = gl.getUniformLocation( program, "cameraViewMatrix" );
	cameraViewMatrix = mult(rotate(30, [1.0, 0.0, 0.0]), translate(0.0, -3.0, 20.0));
	gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix));


	drawIndexLoc = gl.getUniformLocation( program, "drawIndex" );

	ambientLoc = gl.getUniformLocation(program, "ambientProduct");
	diffuseLoc = gl.getUniformLocation(program, "diffuseProduct");
	specularLoc = gl.getUniformLocation(program, "specularProduct");

    gl.uniform4fv( ambientLoc,flatten(ambientProductS) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductS) );
    gl.uniform4fv( specularLoc,flatten(specularProductS) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "lightPosition"),flatten(lightPosition) );
    gl.uniform1f( gl.getUniformLocation(program,
       "shininess"),materialShininess );

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
	} else if (event.keyCode == 73) {
		// 'i' Key: go forward relative to the camera's current heading
		moveForward();
	} else if (event.keyCode == 74) {
		// 'j' Key: go left relative to the camera's current heading
		moveLeft();
	} else if (event.keyCode == 75) {
		// 'k' Key: go right relative to the camera's current heading
		moveRight();
	} else if (event.keyCode == 82) {
		// 'r' Key: reset the view to the start position
		cameraViewMatrix = mult(rotate(30, [1.0, 0.0, 0.0]), translate(0.0, -3.0, 20.0));
	} else if (event.keyCode == 77){
		// 'm' Key: go backward relative to the camera's current heading
		moveBackward();
	}
}

    tick();
}


function render() {

    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    modelViewMatrix = mat4(); // lookAt(eye, at , up);
    projectionMatrix = perspective(55, 960/540, 0.1, 1000); // ortho(left, right, bottom, ytop, near, far);
    normalMatrix = [
        vec3(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2]),
        vec3(modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2]),
        vec3(modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2])
    ];

    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(modelViewMatrix, mult(translate(0.0, 0.0, -20.0), scale(2.0, 2.0, 2.0)))));
    gl.uniformMatrix4fv(projectionMatrixLoc, false, flatten(projectionMatrix) );
    gl.uniformMatrix3fv(normalMatrixLoc, false, flatten(normalMatrix) );
	gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix));

	// Set up for flat shading

	gl.bindBuffer( gl.ARRAY_BUFFER, nBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(normalsArray), gl.STATIC_DRAW );
	gl.vertexAttribPointer( vNormal, 4, gl.FLOAT, false, 0, 0 );
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);
	gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);

	gl.uniform4fv( ambientLoc,flatten(ambientProductS) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductS) );
    gl.uniform4fv( specularLoc,flatten(specularProductS) );

	// Draw SUN: point light source location: complete solid yellow by choice
	var sunMatrix = mult(modelViewMatrix, translate(0.0, 0.0, -20.0));
	gl.uniform1f(drawIndexLoc, 0.0);
    for( var i=0; i<index; i+=3)
        gl.drawArrays( gl.TRIANGLES, i, 3 );

	// Draw first orbiting planet: Flat Shading
	// Icy white, faceted, diamond-like, medium-low complexity

	gl.uniform4fv( ambientLoc,flatten(ambientProductF) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductF) );

	gl.uniform1f(drawIndexLoc, 1.0);
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(sunMatrix,mult(rotate(changeRotationF,[0.0, 1.0, 0.0]),translate(5.0, 0.0, 0.0)))));
	for (var i = 0; i < index; i+= 3)
		gl.drawArrays(gl.TRIANGLES, i, 3 );

	// Set up for Gouraud shading
	gl.bindBuffer( gl.ARRAY_BUFFER, nGBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(normalsGPArray), gl.STATIC_DRAW );
	gl.vertexAttribPointer( vNormal, 4, gl.FLOAT, false, 0, 0 );
	gl.bindBuffer(gl.ARRAY_BUFFER, vGBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(pointsGPArray), gl.STATIC_DRAW );
	gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);

	gl.uniform4fv( ambientLoc,flatten(ambientProductG1) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductG1) );

	// Draw second orbiting planet: Gouraud Shading
	// Swampy, watery green planet with medium-low complexity, specular highlight
	gl.uniform1f(drawIndexLoc, 2.0);
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(sunMatrix ,mult(rotate(changeRotationG1,[0.0, 1.0, 0.0]),translate(7.5, 0.0, 0.0)))));
	for (var i = 0; i < indexG; i+= 3)
		gl.drawArrays(gl.TRIANGLES, i, 3 );

	// Draw fourth orbiting planet: Gouraud Shading
	// Mud covered planet, brownish-orange with dull appearance, medium-high complexity, no specular highlight

	gl.uniform4fv( ambientLoc,flatten(ambientProductG2) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductG2) );
	gl.uniform4fv( specularLoc,flatten(specularProductG2) );

	orbitingPlanet = mult(sunMatrix,mult(rotate(changeRotationG2,[0.0, 1.0, 0.0]),translate(15.0,0.0, 0.0)));

	gl.uniform1f(drawIndexLoc, 2.5);
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(orbitingPlanet));
	for (var i = 0; i < indexG; i+= 3)
		gl.drawArrays(gl.TRIANGLES, i, 3 );

	// Draw orbiting moon around fourth planet
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(orbitingPlanet, mult(rotate(changeRotationF, [0.0, 1.0, 0.0]), mult(translate(5.0, 0.0, 0.0), scale(0.5, 0.5, 0.5))))));
	gl.uniform4fv( ambientLoc,flatten(ambientProductG1) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductG1) );
	for (var i = 0; i < indexG; i+= 3)
		gl.drawArrays(gl.TRIANGLES, i, 3 );

	// Draw third orbiting planet: Phong Shading
	// Clam smooth water with high complexity and specular highlight

	gl.uniform4fv( ambientLoc,flatten(ambientProductP) );
    gl.uniform4fv( diffuseLoc,flatten(diffuseProductP) );
	gl.uniform4fv( specularLoc,flatten(specularProductS) );


	gl.uniform1f(drawIndexLoc, 3.0);
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(sunMatrix,mult(rotate(changeRotationP,[0.0, 1.0, 0.0]),mult(translate(10.0, 0.0, 0.0), scale(1.0, 1.0, 1.0))))));
	for (var i = 0; i < indexG; i+= 3)
		gl.drawArrays(gl.TRIANGLES, i, 3 );

	changeRotationF += 2;
	changeRotationG1 += 1.5;
	changeRotationP += 1.25;
	changeRotationG2 += 2.5;

}

function tick() {
	requestAnimFrame(tick)
	render();
}

function increaseY(){
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.25, 0.0));
}

function decreaseY(){
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, -0.25, 0.0));
}

function increaseHeading(){
	cameraViewMatrix = mult(cameraViewMatrix, rotate(1, [0.0, 1.0, 0.0]));
}

function decreaseHeading(){
	cameraViewMatrix = mult(cameraViewMatrix, rotate(-1, [0.0, 1.0, 0.0]));
}

function moveLeft(){
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.25, 0.0, 0.0));
}

function moveRight(){
	cameraViewMatrix = mult(cameraViewMatrix, translate (-0.25, 0.0, 0.0));
}

function moveBackward() {
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, -0.25));
}

function moveForward() {
	cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, 0.25));
}
