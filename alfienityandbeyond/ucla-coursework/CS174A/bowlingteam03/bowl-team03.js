// Canvas/shader program
var program; 
var gl;

//  Input Global Variables
var gameMode = 1;
var ballColor = 0;
var rotateScene = 0;
var toggleScene = 0;
var translateBall = 0;
var lrBall = 0;
var bowlInterval = 0;
var pinInterval = 0;
var rotateSceneON = 0;
var rollBallON = 0;
var changeCamera = 0;
var scoreCounter=0;
var livesCounter=6;
var begin=0;

// Image globals
var pinsImage;
var bluewallImage;
var guttersImage;
var bowlinglaneImage;
var neonbowlbgImage;
var greenbgImage;
var orangebgImage;
var bowlingleaguesbgImage;
var neonpinsImage;

// Uniform Location Variables
var modelViewMatrixLoc;
var projectionMatrixLoc;
var cameraViewMatrixLoc;
var normalMatrixLoc;

var drawIndexLoc; 

var ambientProductLoc;
var diffuseProductLoc;
var specularProductLoc;

var uAlphaLoc;

// Transformations
var rotationMatrix = mat4();
var cameraViewMatrix = mat4();
var normalMatrix;

// Object Matrices
var lWallMatrix, rWallMatrix;

var mlgutterMatrix, mrgutterMatrix, lgutterMatrix, rgutterMatrix;

var backWallMatrix;
var ceilingMatrix;

var mLaneMatrix, rLaneMatrix, lLaneMatrix;

var backLightMatrix;

var mubMatrix, rubMatrix, lubMatrix;
var mlbMatrix, rlbMatrix, llbMatrix;

var hPinMatrix;
var slPinMatrix, srPinMatrix;
var tlPinMatrix, tmPinMatrix, trPinMatrix;
var fllPinMatrix, flPinMatrix, frPinMatrix, frrPinMatrix;

var sl2PinMatrix, sr2PinMatrix;
var tl2PinMatrix, tm2PinMatrix, tr2PinMatrix;
var fll2PinMatrix, fl2PinMatrix, fr2PinMatrix, frr2PinMatrix;

var ballMatrix;

//kirby and eve matrices, vars
var kirby = 0;
var eve = 0
var k=0;
var x=0;
var y=0;
var backswing = 0;
var backswingCounter = 0;
var kirbyBodyMatrix, kirbyLArmMatrix, kirbyRArmMatrix;
var kirbyLFootMatrix, kirbyRFootMatrix;
var origKirbyBody, origKirbyLArm, origKirbyRArm, origKirbyLFoot, origKirbyRFoot;
var eveBodyMatrix, eveRArmMatrix, eveLArmMatrix, eveHeadMatrix;
var origEveBody, origEveRA, origEveLA, origEveHead;

//score, game modes
var scoreElement;
var scoreNode;
var gameModeElement;
var gameModeNode;
var livesElement;
var livesNode;

// Cube Set-up
var vBuffer;
var cBuffer;
var nBuffer;
var tBuffer;
var icBuffer;
var cubeColors;

// Shader Attributes
var vPosition;
var vColor;
var vTexCoord;
var vNormal;

// Bowling Ball Set-up
var numTimesToSubdivide = 3;
var indexG = 0;

var pointsArray = [];
var vGBuffer;
var normalsArray = [];
var nGBuffer;

var va = vec4(0.0, 0.0, -1.0,1);
var vb = vec4(0.0, 0.942809, 0.333333, 1);
var vc = vec4(-0.816497, -0.471405, 0.333333, 1);
var vd = vec4(0.816497, -0.471405, 0.333333,1);

var lightPosition = vec4(0.0, 1.0, 0.0, -150.0); // (0, 1.0, 0, 5)
var lightAmbient = vec4(0.2, 0.2, 0.2, 1.0 );
var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );
var lightSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );

var materialAmbient = vec4( 1.0, 0.0, 1.0, 1.0);
var materialDiffuse = vec4( 1.0, 0.8, 0.0, 1.0);
var materialSpecular = vec4( 0.0, 0.0, 0.0, 1.0);
var materialShininess = 20.0;

var ambientProductS, diffuseProductS, specularProduct;
var ambientProductW, diffuseProductW;
var ambientProductT, diffuseProductT;
var ambientProductO, diffuseProductO;
var ambientProductB, diffuseProductB;

//some vars (meesh)
var modelt_ball;
var modelt_pin;
var pin_array = [];
var model_array = [];
var A = 1.0;
var mode1_throw = 0;
var hit_pin = [0,0,0,0,0,0,0,0,0,0];

var hit_pin2 = [0,0,0,0,0,0,0,0,0,0];
var pin2_array = [];
var model2_array = [];
var mode2_throw = 0;
//for mode3 (meesh_3)
var mode3_array = [];
var ballpoint = vec4(0, 0, 0, 1);
var pin_dir = [];
var left_x = -10.2; //this is the x of the left bumper
var right_x = 10.2; //this is the x of the right bumper
var org_ball = mult(translate(0.0, -5.75, 80), scale(3.0, 3.0, 3.0));
var p_c = [];
var p_speed = [];
var mode3_white = [];
var mode3_red = [];
var go = 1;
var playagain = 0;
var counter_3 = 0;
var model4_array = [];


//inverse function (meesh)
function inverse( m ) 
{
if ( !m.matrix ) { throw "attempt to invert non matrix"; }

var result = mat4();
var n11 = m[ 0 ][ 0 ], n12 = m[ 0 ][ 1 ], n13 = m[ 0 ][ 2 ], n14 = m[ 0 ][ 3 ]
var n21 = m[ 1 ][ 0 ], n22 = m[ 1 ][ 1 ], n23 = m[ 1 ][ 2 ], n24 = m[ 1 ][ 3 ];
var n31 = m[ 2 ][ 0 ], n32 = m[ 2 ][ 1 ], n33 = m[ 2 ][ 2 ], n34 = m[ 2 ][ 3 ];
var n41 = m[ 3 ][ 0 ], n42 = m[ 3 ][ 1 ], n43 = m[ 3 ][ 2 ], n44 = m[ 3 ][ 3 ];
result[ 0 ][ 0 ] = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
result[ 0 ][ 1 ] = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
result[ 0 ][ 2 ] = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
result[ 0 ][ 3 ] = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;
result[ 1 ][ 0 ] = n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44;
result[ 1 ][ 1 ] = n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44;
result[ 1 ][ 2 ] = n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44;
result[ 1 ][ 3 ] = n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34;
result[ 2 ][ 0 ] = n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44;
result[ 2 ][ 1 ] = n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44;
result[ 2 ][ 2 ] = n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44;
result[ 2 ][ 3 ] = n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34;
result[ 3 ][ 0 ] = n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43;
result[ 3 ][ 1 ] = n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43;
result[ 3 ][ 2 ] = n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43;
result[ 3 ][ 3 ] = n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33;
var one_over_determinant = 1.0 / (n11 * result[ 0 ][ 0 ] + n21 * result[ 0 ][ 1 ] + n31 * result[ 0 ][ 2 ] + n41 * result[ 0 ][ 3 ] );
return mult (result, mat4( one_over_determinant ) );
}

//collision detection (meesh)-rudimentary(with one pin)
function collision_check(m1, m2){
    inversem1 = inverse(m1);
    inversem2 = inverse(m2);
    for( var i=0; i<indexG; i+=1)
    {
        //point =  mult_vec(m2, pointsArray[i]);
        //point = mult_vec(inversem1, point);
        addpoint = mult(inversem1, m2);
        point = mult_vec(addpoint, pointsArray[i]);
        distance = (point[0]*point[0]) + (point[1]*point[1]) + (point[2]*point[2])
        if(distance <= 1)
            return 1;
    }
    for( var i=0; i<indexG; i+=1)
    {
        addpoint = mult(inversem2, m1);
        point = mult_vec(addpoint, pointsArray[i]);
        distance = (point[0]*point[0]) + (point[1]*point[1]) + (point[2]*point[2])
        if(distance <= 1)
            return 1;
    }
    return 0;
}

//Matrix*vector function (meesh)
function mult_vec(M, v)
{
    v_4 = v.length == 4 ? v : vec4( v, 0 ); 
    
    v_new = vec4();
    v_new[0] = dot( M[0], v_4 );
    v_new[1] = dot( M[1], v_4 );
    v_new[2] = dot( M[2], v_4 );
    v_new[3] = dot( M[3], v_4 );
    return v_new;
}

//functions for mode3 (meesh_3)
var ball_back = 0;
function moveback(m){
    newpoint = mult_vec(m, ballpoint);
    if(newpoint[2] >= 80){ 
         ball_back = 0;
         rollBallON = 0;
         translateBall = 0.0;
     lrBall = 0.0;
     m = mult(translate(newpoint[0], -5.75, 80), scale(3.0, 3.0, 3.0));
    }
    else{
        for(i = 1; i <= 10; i++){
            m = mult( translate(0.0, 0.0, 1.0), m);
            newpoint = mult_vec(m, ballpoint);
            if(newpoint[2] >= 80)
                break;
        }
    }
    return m;
}


function work(n){
    if(collision_check(modelt_ball, mode3_array[n]) == 0){
        slide(n);
    }
    else{ //collision
        if(ball_back == 0){
            p_c[n] = 4;
            if(p_speed[n] != 5)
                p_speed[n] = 1 + p_speed[n]; 
            mode3_white[n] = 1;
            reset_pin_pos(n);
            ball_back = 1;
			counter_3 += 1;
            drawSpheres(toggleScene);
        }
    }
}



function reset_pin_pos(n){
    mode3_array[n] = model4_array[n];
}

function set_color(n){ //HERE
    if(p_c[n] == 0){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductT));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductT));
    }
    if(p_c[n] == 1){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductO));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductO));
    }
    if(p_c[n] == 2){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductB));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductB));
    }
    if(p_c[n] == 3){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductP));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductP));
    }
    if(p_c[n] == 4){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
    }
    if(p_c[n] == 5){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductR));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductR));
    }
    
}

var line = 0;
function slide(n){
	set_color(n);
	newpoint = mult_vec(mode3_array[n], ballpoint);
	if(newpoint[2] > 75 || mode3_red[n] == 1){
		if(mode3_red[n] == 0){
			p_c[n] = 5;
			mode3_array[n] = mult(translate(8.0, 3, 80- line), scale(0.5, 0.5, 0.5));
			mode3_red[n] = 1;
			line+=4;
			livesCounter--;
			 if(livesCounter==-1)
			{
				livesCounter=6;
				scoreCounter=0;
				reset_scene(3);
				go = 0;
			}
		}
		drawSpheres(toggleScene);	
	}
	else{
		if(checkforstop(mode3_array[n], pin_dir[n]) == 1){ //checking to see if pin has hit the 'bumpers'
		if(pin_dir[n] == 1)
			pin_dir[n] = 0;
		else
			pin_dir[n] = 1;
		drawSpheres(toggleScene);
		mode3_array[n] = mult( translate(0.0, 0.0, 8.0), mode3_array[n]);
		}
		else{
			roll(pin_dir[n],n, p_speed[n]);
			drawSpheres(toggleScene);
		}
	}
}



function checkforstop(p, p_dir){
    newpoint = mult_vec(p, ballpoint);
    if(p_dir == 1){
        if(newpoint[0] > right_x)
            return 1;
    }
    if(p_dir == 0){
        if(newpoint[0] < left_x)
            return 1;
    }
    return 0;
}

function roll(roll_dir, pin_n, num){
    if (roll_dir == 0){ //left
        if(num == 0) //slow
            mode3_array[pin_n] = mult( translate(-0.8, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 1) //medium
            mode3_array[pin_n] = mult( translate(-1.0, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 2) //fast
            mode3_array[pin_n] = mult( translate(-1.5, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 3) //faster
            mode3_array[pin_n] = mult( translate(-2.0, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 4) //faster
            mode3_array[pin_n] = mult( translate(-2.5, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 5) //O_O
            mode3_array[pin_n] = mult( translate(-4.0, 0.0, 0.0), mode3_array[pin_n]);
        
    }
    else{ //right
        if(num == 0) //slow
            mode3_array[pin_n]= mult( translate(0.8, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 1) //medium
            mode3_array[pin_n] = mult( translate(1.0, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 2) //fast
            mode3_array[pin_n] = mult( translate(1.5, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 3) //faster
            mode3_array[pin_n] = mult( translate(2.0, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 4) //faster
            mode3_array[pin_n] = mult( translate(2.5, 0.0, 0.0), mode3_array[pin_n]);
        if(num == 5) //O_O
            mode3_array[pin_n] = mult( translate(4.0, 0.0, 0.0), mode3_array[pin_n]);
    }
}
//end of mode 3 functions






    
function triangle(a, b, c) {
     // Gouraud Shading Set-Up
        pointsArray.push(a);
        pointsArray.push(b);
        pointsArray.push(c);

        normalsArray.push(a[0],a[1], a[2], 0.0);
        normalsArray.push(b[0],b[1], b[2], 0.0);
        normalsArray.push(c[0],c[1], c[2], 0.0);

        indexG += 3;
}

function divideTriangle(a, b, c, count) {
    if ( count > 0 ) {

        var ab = mix( a, b, 0.5);
        var ac = mix( a, c, 0.5);
        var bc = mix( b, c, 0.5);

        ab = normalize(ab, true);
        ac = normalize(ac, true);
        bc = normalize(bc, true);

        divideTriangle( a, ab, ac, count - 1 );
        divideTriangle( ab, b, bc, count - 1 );
        divideTriangle( bc, c, ac, count - 1 );
        divideTriangle( ab, bc, ac, count - 1 );
    }
    else {
        triangle( a, b, c );
    }
}


function tetrahedron(a, b, c, d, n) {
    divideTriangle(a, b, c, n);
    divideTriangle(d, c, b, n);
    divideTriangle(a, d, b, n);
    divideTriangle(a, c, d, n);
}


function configureTexture( image ) {
    texture = gl.createTexture();
    gl.bindTexture( gl.TEXTURE_2D, texture );
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true); 
    gl.texImage2D( gl.TEXTURE_2D, 0, gl.RGB, 
         gl.RGB, gl.UNSIGNED_BYTE, image );
    gl.generateMipmap( gl.TEXTURE_2D );
    gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, 
                      gl.LINEAR ); //gl.LINEAR_MIPMAP_LINEAR );
    gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR );
        
    gl.uniform1i(gl.getUniformLocation(program, "texture"), 0);
}

window.onload = function init()
{
    var canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    //
    //  Configure WebGL
    //
    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 );
    gl.enable(gl.DEPTH_TEST); 

    //  Load shaders and initialize attribute buffers

    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    // Retrieve uniforms' locations
    modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix");
    projectionMatrixLoc = gl.getUniformLocation(program, "projectionMatrix");
    cameraViewMatrixLoc = gl.getUniformLocation(program, "cameraViewMatrix");
    normalMatrixLoc = gl.getUniformLocation(program, "normalMatrix");
    drawIndexLoc = gl.getUniformLocation(program, "drawIndex");
    ambientProductLoc = gl.getUniformLocation(program, "ambientProduct");
    diffuseProductLoc = gl.getUniformLocation(program, "diffuseProduct");
    specularProductLoc = gl.getUniformLocation(program, "specularProduct");
	uAlphaLoc = gl.getUniformLocation(program, "uAlpha");
	
    // Retrieve image IDs
    pinsImage = document.getElementById("pinsImage");
    darkwallImage = document.getElementById("darkwallImage");
    ceilingImage = document.getElementById("ceilingImage");
    bluewallImage = document.getElementById("bluewallImage");
    guttersImage = document.getElementById("guttersImage");
    bowlinglaneImage = document.getElementById("bowlinglaneImage");
    neonbowlbgImage = document.getElementById("neonbowlbgImage");
    greenbgImage = document.getElementById("greenbgImage");
    orangebgImage = document.getElementById("orangebgImage");
    bowlingleaguesbgImage = document.getElementById("bowlingleaguesbgImage");
    neonpinsImage = document.getElementById("neonpinsImage");

    scoreElement = document.getElementById("score");
    scoreNode = document.createTextNode("");
    scoreElement.appendChild(scoreNode);
    
    livesElement = document.getElementById("lives");
    livesNode = document.createTextNode("");
    livesElement.appendChild(livesNode);

    gameModeElement = document.getElementById("gameMode");
    gameModeNode = document.createTextNode("");
    gameModeElement.appendChild(gameModeNode);

    // Default view
    var projectionMatrix = perspective(45, canvas.width/canvas.height, 0.1, 1000); 
    //meesh_3_camera
	  cameraViewMatrix = mult( translate(0.0, 2.0, -130.0), rotate(10, [1, 0, 0]));
    //cameraViewMatrix = translate(0.0, 0.0, -100.0);
    
    gl.uniformMatrix4fv(projectionMatrixLoc, false, flatten(projectionMatrix));
    gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix));
    
    // Bowling Ball Colors
    ambientProductS = mult(lightAmbient, materialAmbient);
    diffuseProductS = mult(lightDiffuse, materialDiffuse);
    specularProduct = mult(lightSpecular, materialSpecular);

    ambientProductW = mult(lightAmbient, vec4(1.0, 1.0, 1.0, 1.0));
    diffuseProductW = mult(lightDiffuse, vec4(1.0, 1.0, 1.0, 1.0));

    ambientProductT = mult(lightAmbient, vec4(0.0, 0.75, 0.45, 1.0));
    diffuseProductT = mult(lightDiffuse, vec4(0.0, 0.75, 0.45, 1.0));

    ambientProductO = mult(lightAmbient, vec4(0.8, 0.4, 0.25, 1.0));
    diffuseProductO = mult(lightDiffuse, vec4(0.8, 0.4, 0.25, 1.0));

    ambientProductB = mult(lightAmbient, vec4(0.0, 0.5, 0.75, 1.0));
    diffuseProductB = mult(lightDiffuse, vec4(0.0, 0.5, 0.75, 1.0));
    
    ambientProductP = mult(lightAmbient, vec4(1.0, 0.2, 0.75, 1.0));
    diffuseProductP = mult(lightDiffuse, vec4(0.8, 0.3, 0.75, 1.0));

    ambientProductR = mult(lightAmbient, vec4(0.5, 0, 0, 1.0));
    diffuseProductR = mult(lightDiffuse, vec4(0.5, 0, 0, 1.0));
    
    gl.uniform4fv(ambientProductLoc, flatten(ambientProductS));
    gl.uniform4fv(diffuseProductLoc,flatten(diffuseProductS));
    gl.uniform4fv(specularProductLoc,flatten(specularProduct));
    gl.uniform4fv(gl.getUniformLocation(program,
       "lightPosition"),flatten(lightPosition));
    gl.uniform1f(gl.getUniformLocation(program,
       "shininess"),materialShininess);
    
    // Bowling Ball Gouraud Shading Set-up
    tetrahedron(va, vb, vc, vd, numTimesToSubdivide);
    
    vGBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vGBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);
    
    
    vNormal = gl.getAttribLocation( program, "vNormal" );
    gl.enableVertexAttribArray( vNormal);
    nGBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, nGBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(normalsArray), gl.STATIC_DRAW );
    gl.vertexAttribPointer( vNormal, 4, gl.FLOAT, false, 0, 0 );
    
    
    // Cube indices
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
    
    // Cube Vertices
    
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
    
    vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.enableVertexAttribArray(vPosition);
    vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer);
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW);
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    
    // Cube Texture
        var textureCoords = [
            // Front face
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            // Back face
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,
            // Top face
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            // Bottom face
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,
            1.0, 0.0,
            // Right face
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
            0.0, 0.0,
            // Left face
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
        ];
    vTexCoord = gl.getAttribLocation( program, "vTexCoord" );
    gl.enableVertexAttribArray( vTexCoord );
    tBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, tBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(textureCoords), gl.STATIC_DRAW );
    
    gl.vertexAttribPointer( vTexCoord, 2, gl.FLOAT, false, 0, 0 );
    
    // Set up default object transformations:
    
    lWallMatrix = mult(translate(-45.0, 11.5, -25.0), scale(5.0, 20.0, 100.0)); // Left Wall
    rWallMatrix = mult(translate(45.0, 11.5, -25.0), scale(5.0, 20.0, 100.0)); // Right Wall
    
    mlgutterMatrix = mult(translate(-12.5, -9.0, -25.0), scale(1.0, 1.0, 100.0)); // Middle Left Gutter
    mrgutterMatrix = mult(translate(12.5, -8.75, -25.0), scale(1.0, 1.0, 100.0)); // Middle Right Gutter
    lgutterMatrix = mult(translate(-37.5, -9.0, -25.0), scale(1.0, 1.0, 100.0)); // Left Gutter
    rgutterMatrix = mult(translate(37.5, -9.0, -25.0), scale(1.0, 1.0, 100.0)); // Right Gutter

    backWallMatrix = mult(translate(0.0, 11.5, -121.0), scale(40.0, 20.0, 0.0)); // Back Wall
    ceilingMatrix = mult(translate(0.0, 32.5, -25.0), scale(40.0, 0.0, 100.0)); // Ceiling
    
    mLaneMatrix = mult(translate(0.0, -8.75, -25.0), scale(10.0, 0.0, 100.0)); // Middle Lane
    rLaneMatrix = mult(translate(25.0, -8.75, -25.0), scale(10.0, 0.0, 100.0)); // Right Lane
    lLaneMatrix = mult(translate(-25.0, -8.75, -25.0), scale(10.0, 0.0, 100.0)); // Left Lane

    backLightMatrix = mult(translate(0.0, 21.5, -100.0), scale(10.0, 5.0, 10.0)); // Back Light (Bowling Sign)
    
    mubMatrix = mult(translate(0.0, 12.5, -120.0), scale(10.0, 5.0, 0.0)); // Middle Upper Back Wall
    rubMatrix = mult(translate(25.0, 12.5, -120.0), scale(10.0, 5.0, 0.0)); // Right Upper Back Wall
    lubMatrix = mult(translate(-25.0, 12.5, -120.0), scale(10.0, 5.0, 0.0)); // Left Upper Back Wall
    mlbMatrix = mult(translate(0.0, 2.5, -120.0), scale(10.0, 5.0, 0.0));   // Middle Lower Back Wall
    rlbMatrix = mult(translate(25.0, 2.5, -120.0), scale(10.0, 5.0, 0.0)); // Right Lower Back Wall
    llbMatrix = mult(translate(-25.0, 2.5, -120.0), scale(10.0, 5.0, 0.0)); // Left Lower Back Wall
    
	//Mode 3 Set-up
    hPinMatrix = mult(translate(0.0, -3.75, -100), scale(1.0, 5.0, 1.0));   // Head Pin
    modelt_pin = hPinMatrix; //(meesh)
    slPinMatrix =  mult(hPinMatrix, translate(2.0, 0.0, 10.0)); // Second Left Pin
    srPinMatrix = mult(hPinMatrix, translate(-4.0, 0.0, 3.0));  // Second Right Pin
    trPinMatrix = mult(hPinMatrix, translate(9.0, 0.0, 1.0)); // Third Right Pin
    tmPinMatrix = mult(hPinMatrix, translate(5.0, 0.0, 60.0)); // Third Middle Pin
    tlPinMatrix =  mult(hPinMatrix, translate(4.0, 0.0, 22.0)); // Third Left Pin
    fllPinMatrix = mult(hPinMatrix, translate(-1.0, 0.0, 25.0)); // Fourth Far Left Pin
    flPinMatrix = mult(hPinMatrix, translate(-6.0, 0.0, 40.0)); // Fourth Left Pin
    frPinMatrix = mult(hPinMatrix, translate(6.0, 0.0, 40.0));  // Fourth Right Pin
    frrPinMatrix = mult(hPinMatrix, translate(-9.0, 0.0, 50.0));    // Fourth Far Right Pin
    model4_array.push(hPinMatrix, slPinMatrix, srPinMatrix, trPinMatrix, tmPinMatrix, tlPinMatrix, fllPinMatrix, flPinMatrix, frPinMatrix, frrPinMatrix);
    mode3_array.push(hPinMatrix, slPinMatrix, srPinMatrix, trPinMatrix, tmPinMatrix, tlPinMatrix, fllPinMatrix, flPinMatrix, frPinMatrix, frrPinMatrix);
	
	
    // Mode 1 Pin Set-up
    hPinMatrix = mult(translate(0.0, -3.75, -100), scale(1.0, 5.0, 1.0));   // Head Pin
    modelt_pin = hPinMatrix; //(meesh)
    slPinMatrix =  mult(hPinMatrix, translate(30.0, 0.0, 155.0)); // Second Left Pin
    srPinMatrix = mult(hPinMatrix, translate(-30.0, 0.0, 155.0));  // Second Right Pin
    trPinMatrix = mult(hPinMatrix, translate(0.0, 0.0, 140.0)); // Third Right Pin
    tmPinMatrix = mult(hPinMatrix, translate(-25.0, 0.0, 115.0)); // Third Middle Pin
    tlPinMatrix =  mult(hPinMatrix, translate(0.0, 0.0, 100.0)); // Third Left Pin
    fllPinMatrix = mult(hPinMatrix, translate(25.0, 0.0, 115.0)); // Fourth Far Left Pin
    flPinMatrix = mult(hPinMatrix, translate(-16.0, 0.0, 80.0)); // Fourth Left Pin
    frPinMatrix = mult(hPinMatrix, translate(16.0, 0.0, 40.0));  // Fourth Right Pin
    frrPinMatrix = mult(hPinMatrix, translate(0.0, 0.0, 50.0));    // Fourth Far Right Pin
	pin_array.push(hPinMatrix, slPinMatrix, srPinMatrix, trPinMatrix, tmPinMatrix, tlPinMatrix, fllPinMatrix, flPinMatrix, frPinMatrix, frrPinMatrix);
    model_array.push(hPinMatrix, slPinMatrix, srPinMatrix, trPinMatrix, tmPinMatrix, tlPinMatrix, fllPinMatrix, flPinMatrix, frPinMatrix, frrPinMatrix);
	//mode3_array.push(hPinMatrix, slPinMatrix, srPinMatrix, trPinMatrix, tmPinMatrix, tlPinMatrix, fllPinMatrix, flPinMatrix, frPinMatrix, frrPinMatrix);
    for(i=0; i<10; i++){
          mode3_white.push(0);
      }
      
    for(i=0; i<10; i++){
		      mode3_red.push(0);
	    }
    
    pin_dir.push(1, 0, 1, 0, 1, 0, 1, 0, 1, 0);
    //sliding pin color initializer
     
      rand1 = Math.floor(Math.random() * 4);
      for(i = 0; i < 10; i++){
          p_c.push(rand1);
      }
    
      //sliding pin speed initializer
      for(i = 0; i < 10; i++){
          rand2 = Math.floor(Math.random() * 3);
          p_speed.push(rand2);
      }
    //^(meeshic_3)
    
    
    // Mode 2 Pin Set-up
    sl2PinMatrix =  mult(hPinMatrix, translate(-2.0, 0.0, -2.0));   // Second Left Pin
    sr2PinMatrix = mult(sl2PinMatrix, translate(4.0, 0.0, 0.0));    // Second Right Pin
    tr2PinMatrix = mult(sr2PinMatrix, translate(2.0, 0.0, -2.0)); // Third Right Pin
    tm2PinMatrix = mult(tr2PinMatrix, translate(-4.0, 0.0, 0.0)); // Third Middle Pin
    tl2PinMatrix =  mult(tm2PinMatrix, translate(-4.0, 0.0, 0.0)); // Third Left Pin
    fll2PinMatrix = mult(tl2PinMatrix, translate(-2.0, 0.0, -2.0)); // Fourth Far Left Pin
    fl2PinMatrix = mult(fll2PinMatrix, translate(4.0, 0.0, 0.0)); // Fourth Left Pin
    fr2PinMatrix = mult(fl2PinMatrix, translate(4.0, 0.0, 0.0));    // Fourth Right Pin
    frr2PinMatrix = mult(fr2PinMatrix, translate(4.0, 0.0, 0.0));   // Fourth Far Right Pin
    pin2_array.push(hPinMatrix, sl2PinMatrix, sr2PinMatrix, tr2PinMatrix, tm2PinMatrix, tl2PinMatrix, fll2PinMatrix, fl2PinMatrix, fr2PinMatrix, frr2PinMatrix);
    model2_array.push(hPinMatrix, sl2PinMatrix, sr2PinMatrix, tr2PinMatrix, tm2PinMatrix, tl2PinMatrix, fll2PinMatrix, fl2PinMatrix, fr2PinMatrix, frr2PinMatrix);
    
    // Model Character Set-up
    kirbyBodyMatrix = mult(translate(-6, -2, 83), scale(4, 4, 4));
    kirbyLArmMatrix = mult(translate(-9.5, -2.5, 83),mult(rotate(-50, [0, 2, 1]), scale(0.5, 2.0, 1.0)));
    kirbyRArmMatrix = mult(translate(-2, -2.5, 83),mult(rotate(75, [0, 2, 1]), scale(0.5, 2.0, 1.0)));
    kirbyLFootMatrix = mult(translate(-7.5, -6, 83),mult(rotate(-45, [0, 1, 0]), scale(2, 1, 1)));
    kirbyRFootMatrix = mult(translate(-4.5, -6, 83),mult(rotate(45, [0, 1, 0]), scale(2, 1, 1)));
    origKirbyBody = kirbyBodyMatrix;
    origKirbyLArm = kirbyLArmMatrix;
    origKirbyRArm = kirbyRArmMatrix;
    origKirbyLFoot = kirbyLFootMatrix;
    origKirbyRFoot = kirbyRFootMatrix;

    eveBodyMatrix = mult(translate(-5, 0, 83), scale(3.0, 6.0, 3.0));
    eveLArmMatrix = mult(translate(-7.5, .5, 83),mult(rotate(-50, [0, 2, 1]), scale(0.5, 5.0, 1.0)));
    eveRArmMatrix = mult(translate(-2.5, .5, 83),mult(rotate(75, [0, 2, 1]), scale(0.5, 5.0, 1.0)));
    eveHeadMatrix = mult(translate(-5, 3.5, 83.5), scale(2.5, 2.0, 2.0));
    origEveBody = eveBodyMatrix;
    origEveLA = eveLArmMatrix;
    origEveRA = eveRArmMatrix;
    origEveHead = eveHeadMatrix;
    
    // Bowling Ball Set-up
    ballMatrix = mult(translate(0.0, -5.75, 80), scale(3.0, 3.0, 3.0)); // Bowling Ball
    modelt_ball = ballMatrix;
        
    tick();
}

    function trans_disappear(){ //(meesh)
        //amb_blue = mult(lightAmbient, vec4(0.0, 0.5, 0.75, A));
        diff_blue = mult(lightDiffuse, vec4(0.0, 0.5, 0.75, A));
        //spec_blue = mult(vec4(1.0, 1.0, 1.0, A), materialSpecular);
        
        //gl.uniform4fv(ambientProductLoc, flatten(amb_blue));
        gl.uniform4fv(diffuseProductLoc, flatten(diff_blue));
        //gl.uniform4fv(specularProductLoc,flatten(spec_blue));
        drawSpheres(toggleScene);
        A-=0.05;
        reset_pin_traits();
    }
    
    function reset_pin_traits(){
        //gl.uniform4fv(ambientProductLoc, flatten(ambientProductB));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductB));
        //gl.uniform4fv(specularProductLoc,flatten(specularProduct));
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
    }
    
    function reset_pin_colors(){
        gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
    }
    
    function twist_up(num, mode){
        if (mode == 1) {
            pin_array[num] = mult(pin_array[num], rotate(30, [0.0, 1.0, 0.0]));
            pin_array[num] = mult(translate(0,2,0), pin_array[num]);
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(pin_array[num]));
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductB));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductB));
            drawSpheres(toggleScene);
            reset_pin_colors();
            hit_pin[num] = 1;
        } else if (mode == 2) {
            pin2_array[num] = mult(pin2_array[num], rotate(30, [0.0, 1.0, 0.0]));
            pin2_array[num] = mult(translate(0,2,0), pin2_array[num]);
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(pin2_array[num]));
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductB));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductB));
            drawSpheres(toggleScene);
            reset_pin_colors();
            hit_pin2[num] = 1;
        }
    }
    
function fix_sidelanes(mode){
    /*if (mode == 1)
    {
            // LEFT LANE PINS
            // 1st Pin
        var moveLeft = translate(-25.0, 0.0, 0.0);
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,hPinMatrix)));
        drawSpheres(toggleScene);
    
        // 2nd Row Pins: L/R
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,slPinMatrix)));
        drawSpheres(toggleScene);

        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,srPinMatrix)));
        drawSpheres(toggleScene);
    
        // 3rd Row Pins: R/M/L
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,trPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,tmPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,tlPinMatrix)));
        drawSpheres(toggleScene);
    
        // 4th Row Pins: LL/L/R/RR
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,fllPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,flPinMatrix)));    
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,frPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,frrPinMatrix)));
        drawSpheres(toggleScene);
    
        // RIGHT LANE PINS
        // 1st Pin
        var moveRight = translate(25.0, 0.0, 0.0);
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,hPinMatrix)));
        drawSpheres(toggleScene);
    
        // 2nd Row Pins: L/R
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,slPinMatrix)));
        drawSpheres(toggleScene);

        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,srPinMatrix)));
        drawSpheres(toggleScene);
    
        // 3rd Row Pins: R/M/L
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,trPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,tmPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,tlPinMatrix)));
        drawSpheres(toggleScene);
    
        // 4th Row Pins: LL/L/R/RR
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,fllPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,flPinMatrix)));   
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,frPinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,frrPinMatrix)));
        drawSpheres(toggleScene);
     } else if (mode == 2) {*/
        // LEFT LANE PINS
        // 1st Pin
        var moveLeft = translate(-25.0, 0.0, 0.0);
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,hPinMatrix)));
        drawSpheres(toggleScene);
    
        // 2nd Row Pins: L/R
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,sl2PinMatrix)));
        drawSpheres(toggleScene);

        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,sr2PinMatrix)));
        drawSpheres(toggleScene);
    
        // 3rd Row Pins: R/M/L
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,tr2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,tm2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,tl2PinMatrix)));
        drawSpheres(toggleScene);
    
        // 4th Row Pins: LL/L/R/RR
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,fll2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,fl2PinMatrix)));   
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,fr2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveLeft,frr2PinMatrix)));
        drawSpheres(toggleScene);
    
        // RIGHT LANE PINS
        // 1st Pin
        var moveRight = translate(25.0, 0.0, 0.0);
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,hPinMatrix)));
        drawSpheres(toggleScene);
    
        // 2nd Row Pins: L/R
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,sl2PinMatrix)));
        drawSpheres(toggleScene);

        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,sr2PinMatrix)));
        drawSpheres(toggleScene);
    
        // 3rd Row Pins: R/M/L
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,tr2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,tm2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,tl2PinMatrix)));
        drawSpheres(toggleScene);
    
        // 4th Row Pins: LL/L/R/RR
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,fll2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,fl2PinMatrix)));  
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,fr2PinMatrix)));
        drawSpheres(toggleScene);
    
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(moveRight,frr2PinMatrix)));
        drawSpheres(toggleScene);
    //}
}
    
    function reset_scene(mode){
        if (mode == 1) // Reset first scene: spread out pins & for third? meesh_3
        {
			gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
			gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(hPinMatrix));
            pin_array[0] = hPinMatrix;
            drawSpheres(toggleScene);
    
            // 2nd Row Pins: L/R
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(slPinMatrix));
            pin_array[1] = slPinMatrix;
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(srPinMatrix));
            pin_array[2] = srPinMatrix;
            drawSpheres(toggleScene);
    
            // 3rd Row Pins: R/M/L
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(trPinMatrix));
            pin_array[3] = trPinMatrix;
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tmPinMatrix));
            pin_array[4] = tmPinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tlPinMatrix));
            pin_array[5] = tlPinMatrix;
            drawSpheres(toggleScene);
    
            // 4th Row Pins: LL/L/R/RR
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fllPinMatrix));
            pin_array[6] = fllPinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(flPinMatrix));   
            pin_array[7] = flPinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(frPinMatrix));
            pin_array[8] = frPinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(frrPinMatrix));
            pin_array[9] = frrPinMatrix;
            drawSpheres(toggleScene);
        } else if (mode == 2) { // Reset second scene: standard bowling
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(hPinMatrix));
            pin2_array[0] = hPinMatrix;
            drawSpheres(toggleScene);
    
            // 2nd Row Pins: L/R
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(sl2PinMatrix));
            pin2_array[1] = sl2PinMatrix;
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(sr2PinMatrix));
            pin2_array[2] = sr2PinMatrix;
            drawSpheres(toggleScene);
    
            // 3rd Row Pins: R/M/L
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tr2PinMatrix));
            pin2_array[3] = tr2PinMatrix;
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tm2PinMatrix));
            pin2_array[4] = tm2PinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tl2PinMatrix));
            pin2_array[5] = tl2PinMatrix;
            drawSpheres(toggleScene);
    
            // 4th Row Pins: LL/L/R/RR
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fll2PinMatrix));
            pin2_array[6] = fll2PinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fl2PinMatrix));  
            pin2_array[7] = fl2PinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fr2PinMatrix));
            pin2_array[8] = fr2PinMatrix;
            drawSpheres(toggleScene);
    
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(frr2PinMatrix));
            pin2_array[9] = frr2PinMatrix;
            drawSpheres(toggleScene);
        }  else if(mode == 3){
            for(i=0; i<10; i++){
               gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(model4_array[i]));
              pin_array[i] = model4_array[i];
              drawSpheres(toggleScene);
            }
		}
    }

function playGame1(){
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(hPinMatrix));
    if(collision_check(modelt_ball, model_array[0]) == 1 || hit_pin[0] == 1) //collision check (meesh)
        twist_up(0, gameMode);
    else
        drawSpheres(toggleScene);
    
    // 2nd Row Pins: L/R
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(slPinMatrix));
    if(collision_check(modelt_ball, model_array[1]) == 1 || hit_pin[1] == 1) //collision check (meesh)
        twist_up(1, gameMode);
    else
        drawSpheres(toggleScene);

    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(srPinMatrix));
    if(collision_check(modelt_ball, model_array[2]) == 1 || hit_pin[2] == 1) //collision check (meesh)
        twist_up(2, gameMode);
    else
        drawSpheres(toggleScene);
    
    // 3rd Row Pins: R/M/L
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(trPinMatrix));
    if(collision_check(modelt_ball, model_array[3]) == 1 || hit_pin[3] == 1) //collision check (meesh)
        twist_up(3, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tmPinMatrix));
    if(collision_check(modelt_ball, model_array[4]) == 1 || hit_pin[4] == 1) //collision check (meesh)
        twist_up(4, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tlPinMatrix));
    if(collision_check(modelt_ball, model_array[5]) == 1 || hit_pin[5] == 1) //collision check (meesh)
        twist_up(5, gameMode);
    else
        drawSpheres(toggleScene);
    
    // 4th Row Pins: LL/L/R/RR
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fllPinMatrix));
    if(collision_check(modelt_ball, model_array[6]) == 1 || hit_pin[6] == 1) //collision check (meesh)
        twist_up(6, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(flPinMatrix));   
    if(collision_check(modelt_ball, model_array[7]) == 1 || hit_pin[7] == 1) //collision check (meesh)
        twist_up(7, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(frPinMatrix));
    if(collision_check(modelt_ball, model_array[8]) == 1 || hit_pin[8] == 1) //collision check (meesh)
        twist_up(8, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(frrPinMatrix));
    if(collision_check(modelt_ball, model_array[9]) == 1 || hit_pin[9] == 1) //collision check (meesh)
        twist_up(9, gameMode);
    else
        drawSpheres(toggleScene);

    var counter=0;
    for(var i=0; i<hit_pin.length; i++)
    {
        if(hit_pin[i]==1)
        {
            counter++;
        }
    }
    scoreCounter=counter;
}

function playGame2() {
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(hPinMatrix));
    if(collision_check(modelt_ball, model2_array[0]) == 1 || hit_pin2[0] == 1) //collision check (meesh)
        twist_up(0, gameMode);
        //trans_disappear();
    else
        drawSpheres(toggleScene);
    
    // 2nd Row Pins: L/R
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(sl2PinMatrix));
    if(collision_check(modelt_ball, model2_array[1]) == 1 || hit_pin2[1] == 1) //collision check (meesh)
        twist_up(1, gameMode);
    else
        drawSpheres(toggleScene);

    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(sr2PinMatrix));
    if(collision_check(modelt_ball, model2_array[2]) == 1 || hit_pin2[2] == 1) //collision check (meesh)
        twist_up(2, gameMode);
    else
        drawSpheres(toggleScene);
    
    // 3rd Row Pins: R/M/L
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tr2PinMatrix));
    if(collision_check(modelt_ball, model2_array[3]) == 1 || hit_pin2[3] == 1) //collision check (meesh)
        twist_up(3, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tm2PinMatrix));
    if(collision_check(modelt_ball, model2_array[4]) == 1 || hit_pin2[4] == 1) //collision check (meesh)
        twist_up(4, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(tl2PinMatrix));
    if(collision_check(modelt_ball, model2_array[5]) == 1 || hit_pin2[5] == 1) //collision check (meesh)
        twist_up(5, gameMode);
    else
        drawSpheres(toggleScene);
    
    // 4th Row Pins: LL/L/R/RR
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fll2PinMatrix));
    if(collision_check(modelt_ball, model2_array[6]) == 1 || hit_pin2[6] == 1) //collision check (meesh)
        twist_up(6, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fl2PinMatrix));  
    if(collision_check(modelt_ball, model2_array[7]) == 1 || hit_pin2[7] == 1) //collision check (meesh)
        twist_up(7, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(fr2PinMatrix));
    if(collision_check(modelt_ball, model2_array[8]) == 1 || hit_pin2[8] == 1) //collision check (meesh)
        twist_up(8, gameMode);
    else
        drawSpheres(toggleScene);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(frr2PinMatrix));
    if(collision_check(modelt_ball, model2_array[9]) == 1 || hit_pin2[9] == 1) //collision check (meesh)
        twist_up(9, gameMode);
    else
        drawSpheres(toggleScene);

    var counter=0;
    for(var i=0; i<hit_pin2.length; i++)
    {
        if(hit_pin2[i]==1)
        {
            counter++;
        }
    }
    scoreCounter=counter;
}

function playGame3(){
    for(i = 0; i < (mode3_array.length); i++){
        gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mode3_array[i]));
        work(i);
    }
    //    var counter=0;
    //for(var i=0; i<mode3_white.length; i++)
    //{
    //    if(mode3_white[i]==1)
    //    {
    //        counter++;
    //    }
    //}
    scoreCounter=counter_3;
}

function render() {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    var modelViewMatrix = mat4();
    rotationMatrix = rotate(rotateScene, [0.0, 1.0, 0.0]);
    normalMatrix = [
        vec3(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2]),
        vec3(modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2]),
        vec3(modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2])
    ];

    gameModeNode.nodeValue=gameMode;

    // Set up camera/normals
    gl.uniformMatrix4fv(cameraViewMatrixLoc, false, flatten(cameraViewMatrix));
    gl.uniformMatrix3fv(normalMatrixLoc, false, flatten(normalMatrix));
    
    /* CUBES */
    gl.uniform1f(drawIndexLoc, 0.0);
    // MIDDLE LANE
	// Draw with transparency for pseudo reflection
	gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
	gl.enable(gl.BLEND);
	gl.disable(gl.DEPTH_TEST);
	gl.uniform1f(uAlphaLoc, 0.5);
    
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    /*
    gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    */
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, icBuffer);
    
    gl.enableVertexAttribArray(vTexCoord);
    configureTexture(bowlinglaneImage);
    
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mLaneMatrix));
    drawCubes(toggleScene);
    
    // RIGHT LANE 
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(rLaneMatrix));
    drawCubes(toggleScene);
    
    // LEFT LANE
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(lLaneMatrix));
    drawCubes(toggleScene);
	
	
	// CEILING
    configureTexture(ceilingImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(ceilingMatrix));
    drawCubes(toggleScene);
	
     
	// MIDDLE LANE REFLECTION
	gl.uniform1f(uAlphaLoc, 0.25);
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(translate(0.0, -0.01, 0.0), mLaneMatrix)));
	drawCubes(toggleScene);
	
	// RIGHT LANE REFLECTION
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(translate(0.0,-0.01, 0.0), rLaneMatrix)));
	drawCubes(toggleScene);
	
	// LEFT LANE REFLECTION
	gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mult(translate(0.0, -0.01, 0.0), lLaneMatrix)));
	drawCubes(toggleScene);

	gl.disable(gl.BLEND);
	gl.enable(gl.DEPTH_TEST);
	
	// Draw the rest normally
	gl.uniform1f(uAlphaLoc, 1.0);
	
	// RIGHT WALL
    configureTexture(bluewallImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(rWallMatrix));
    drawCubes(toggleScene);
    
    // LEFT WALL
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(lWallMatrix));
    drawCubes(toggleScene);
    
    // MIDDLE RIGHT GUTTER
    configureTexture(guttersImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mrgutterMatrix));
    drawCubes(toggleScene);
    
    // MIDDLE LEFT GUTTER
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mlgutterMatrix));
    drawCubes(toggleScene);
    
    // FAR LEFT GUTTER
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(lgutterMatrix));
    drawCubes(toggleScene);
    
    // FAR RIGHT GUTTER
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(rgutterMatrix));
    drawCubes(toggleScene);
    
    // BACK WALL
    configureTexture(darkwallImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(backWallMatrix));
    drawCubes(toggleScene);
    
    // BACK LIGHT 
    configureTexture(neonbowlbgImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(backLightMatrix));
    drawCubes(toggleScene);
    
    // MIDDLE UPPER BACK WALL
    configureTexture(greenbgImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mubMatrix));
    drawCubes(toggleScene);
    
    // MIDDLE LOWER BACK WALL
    configureTexture(orangebgImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(mlbMatrix));
    drawCubes(toggleScene);
    
    // RIGHT UPPER BACK WALL
    configureTexture(bowlingleaguesbgImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(rubMatrix));
    drawCubes(toggleScene);
    
    // LEFT UPPER BACK WALL
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(lubMatrix));
    drawCubes(toggleScene);
    
    // RIGHT LOWER BACK WALL
    configureTexture(neonpinsImage);
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(rlbMatrix));
    drawCubes(toggleScene);
    
    // LEFT LOWER BACK WALL
    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(llbMatrix));
    drawCubes(toggleScene);
    
    /* BOWLING PINS */
    gl.disableVertexAttribArray(vTexCoord);
    gl.uniform1f(drawIndexLoc, 1.0);
    gl.bindBuffer(gl.ARRAY_BUFFER, nGBuffer);
    gl.vertexAttribPointer(vNormal, 4, gl.FLOAT, false, 0, 0);
    gl.bindBuffer(gl.ARRAY_BUFFER, vGBuffer);
    gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);

    gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
    gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
    
    //gl.uniform4fv(ambientProductLoc, flatten(ambientProductB));
    //gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductB));
    
    // MIDDLE LANE PINS
    // 1st Pin
    // Play specific game mode
    if (gameMode == 1) {
        playGame1();
        scoreNode.nodeValue=scoreCounter;
        livesNode.nodeValue="";
        fix_sidelanes(gameMode);
    } else if (gameMode == 2) {
        playGame2();
        scoreNode.nodeValue=scoreCounter;
        livesNode.nodeValue="";
        fix_sidelanes(gameMode);
    }
    else if(gameMode == 3){ //meesh_3
        if(go == 1){
          if(playagain == 1){
            mode3_white=[0,0,0,0,0,0,0,0,0,0];
            mode3_red=[0,0,0,0,0,0,0,0,0,0];
			counter_3 = 0;
            rand1 = Math.floor(Math.random() * 4);
          for(i = 0; i < 10; i++){
              p_c[i] = (rand1);
          }
    
          //sliding pin speed initializer
          for(i = 0; i < 10; i++){
              rand2 = Math.floor(Math.random() * 3);
              p_speed[i] = (rand2);
          }
          }
          playGame3();
          playagain = 0;
        }
        else{ //reset the scene and wait for go to become 1
          reset_scene(3);
          for(i=0; i<10; i++)
            mode3_array[i] = model4_array[i];
          playagain = 1;
        }
        scoreNode.nodeValue=scoreCounter;
    livesNode.nodeValue="Lives: " + livesCounter;
    gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
        gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
        fix_sidelanes(gameMode);
      }
    
    if((kirby && !rollBallON) || (eve && !rollBallON))
    {
        if(kirby)
        {
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductP));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductP));
            
            //body
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(kirbyBodyMatrix));
            drawSpheres(toggleScene);

            //right arm
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(kirbyRArmMatrix));
            drawSpheres(toggleScene);

            //left arm
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(kirbyLArmMatrix));
            drawSpheres(toggleScene);

            //feet 
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductR));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductR));
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(kirbyRFootMatrix));
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(kirbyLFootMatrix));
            drawSpheres(toggleScene);
        }
        else if(eve)
        {
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(eveBodyMatrix));
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(eveRArmMatrix));
            drawSpheres(toggleScene);

            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(eveLArmMatrix));
            drawSpheres(toggleScene);

            //gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(eveHeadMatrix));
            //drawSpheres(toggleScene);

        }
    }
    
    
    /* BOWLING BALL */
    switch(ballColor) { // Alternate Bowling Ball Colors
        case 0:
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductS));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductS));
            break;
        case 1:
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductW));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductW));
            break;
        case 2:
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductT));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductT));
            break;
        case 3:
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductO));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductO));
            break;
        case 4:
            gl.uniform4fv(ambientProductLoc, flatten(ambientProductB));
            gl.uniform4fv(diffuseProductLoc, flatten(diffuseProductB));
            break;
    }
    
    // Handle rolling the ball
    if (!rollBallON)
    {
        if (bowlInterval == 0)  // Wait for timer before returning ball to default position
        {
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(ballMatrix));
            drawSpheres(toggleScene);
        } else {
            bowlInterval -= 1;
        }
    } else {
        if (translateBall >= 200.0) // If bowling ball reaches the end, set timer interval before it returns and reset position of ball
        {
            rollBallON = 0;
            translateBall = 0.0;
            lrBall = 0.0;
            bowlInterval = 30;
            ballMatrix = mult(translate(0.0, -5.75, 80), scale(3.0, 3.0, 3.0));
            modelt_ball = ballMatrix; //(meesh)
            if(mode1_throw == 3) {
                hit_pin = [0,0,0,0,0,0,0,0,0,0]; //reset pin locations
                reset_scene(1);
                mode1_throw = 0;
                scoreCounter = 0;
            } else if (mode2_throw == 2) {
                hit_pin2 = [0,0,0,0,0,0,0,0,0,0]; //reset pin locations
                reset_scene(2);
                mode2_throw = 0;
                scoreCounter = 0;
            }
            
            if(kirby){
                kirbyRFootMatrix = origKirbyRFoot;
                kirbyLFootMatrix = origKirbyLFoot;
                kirbyRArmMatrix = origKirbyRArm;
                kirbyLArmMatrix = origKirbyLArm;
                kirbyBodyMatrix = origKirbyBody;
            } else if(eve) {
                eveBodyMatrix = origEveBody;
                eveHeadMatrix = origEveHead;
                eveLArmMatrix = origEveLA;
                eveRArmMatrix = origEveRA;
            }
        } else { // Bowling ball rolls down the lane
                if(ball_back == 0){
                    ballMatrix = mult(mult(translate(0.0, 0.0, -4.0),ballMatrix), rotate(-0.5, [1.0, 0.0, 0.0]));
                    modelt_ball = ballMatrix;
                    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(ballMatrix));
                    drawSpheres(toggleScene);
            
                    translateBall += 4.0;
                }
              else{
                    ballMatrix = moveback(ballMatrix);
                    modelt_ball = ballMatrix;
                    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(ballMatrix));
                    drawSpheres(toggleScene);
              }
      }
    }
    if (changeCamera) // Change camera to ball perspective if toggled
        cameraViewMatrix = translate(lrBall, 2.5, -90.0 + translateBall);

    if(backswing)
    {
      
      y=0.01-x^2;
      if(backswingCounter<3)//2
      {
          x-=0.01;
          ballMatrix = mult(mult(translate(0.0, y, x),ballMatrix), rotate(-0.5, [1.0, 0.0, 0.0]));
          if(kirby)
              kirbyRArmMatrix = mult(mult(translate(0.0, 0.5, 0.01), kirbyRArmMatrix), mult(rotate(50, [0, 1, 7]), scale(1,1,1)));
          if(eve)
              eveRArmMatrix = mult(mult(translate(0.0, 0.2, -0.01), eveRArmMatrix), mult(rotate(-10, [0, 1, 7]), scale(1,1,1)));
          backswingCounter++;
      }
      else if(backswingCounter<6)//5
      {
          backswingCounter++;
      }
      else if(backswingCounter<9)//7
      {
          x+=0.01;
          ballMatrix = mult(mult(translate(0.0, -y, -x),ballMatrix), rotate(0.5, [1.0, 0.0, 0.0]));
          if(kirby)
              kirbyRArmMatrix = mult(mult(translate(0.0, -0.5, -0.01),kirbyRArmMatrix), mult(rotate(0.5, [1.0, 0.0, 0.0]), scale(1,1,1)));            
          if(eve)
              eveRArmMatrix = mult(mult(translate(0.0, -0.5, -0.01),eveRArmMatrix), mult(rotate(0.5, [1.0, 0.0, 0.0]), scale(1,1,1)));  
          backswingCounter++;
      }
      else 
      {
          rollBallON=1;
          backswingCounter=0;
          backswing=0;
      }
  }
    
}

/* KEYBOARD INPUT 
/* Based on certain key presses, affect the rendering in various ways */
document.onkeydown = function handleKeyDown(event) {
    // alert(event.keyCode); 
    if(event.keyCode == 13){ 
        //enter key
        begin=1;
        document.getElementById('welcome').style.visibility='hidden'; 
		document.getElementById('welcome').style.display = 'none';
    }
    if(begin == 1){
    if (event.keyCode == 81) {
        // 'q' Key: control the heading (azimuth) of the camera
        decreaseHeading();
    } else if (event.keyCode == 87) {
        // 'w' Key: control position of camera along the Y-axis
        decreaseY();
    } else if (event.keyCode == 69) {
        // 'e' Key: control the heading (azimuth) of the camera
        increaseHeading();
    } else if (event.keyCode == 83) {
        // 's' Key: control position of camera along the Y-axis
        increaseY();
    } else if (event.keyCode == 90) {
        // 'z' Key: go forward relative to the camera's current heading
        moveForward();
    } else if (event.keyCode == 65) { 
        // 'a' Key: go left relative to the camera's current heading
        moveLeft();
    } else if (event.keyCode == 68) { 
        // 'd' Key: go right relative to the camera's current heading
        moveRight();
    } else if (event.keyCode == 82) {
        // 'r' Key: reset the view to the start position
        resetCamera();
    } else if (event.keyCode == 88){
        // 'x' Key: go backward relative to the camera's current heading
        moveBackward();
    } else if (event.keyCode == 73) {
        // 'i' Key: go forward relative to the camera's current heading
        moveForward();
    } else if (event.keyCode == 79){
        // 'o' Key: toggle drawing style options of the scene
        toggleScene++;
        if (toggleScene == 4)
            toggleScene = 0;
    }else if (event.keyCode == 89){
        //'y' Key: turn go to 1
        if(go==0)
            go=1;
        else if(go==1)
            go=0;
    } else if (event.keyCode == 67) {
        // 'c' Key: toggle bowling ball color
        ballColor++;
        if (ballColor == 5)
            ballColor = 0;
    } else if (event.keyCode == 38) {
        // Up Arrow Key: Roll the ball down the lane
      if (!rollBallON && translateBall == 0) 
      {
          backswing=1;
          if (gameMode == 1)
            mode1_throw++;
          else if (gameMode == 2)
            mode2_throw++;
          //rollBallON = 1;
      }
    } else if (event.keyCode == 40) {
        // Down Arrow Key: Change game mode
        gameMode++;
        if (gameMode == 4){
            gameMode = 1;
            mode1_throw = 0;
        } else if (gameMode == 2) {
            mode2_throw = 0;
        }
    } else if (event.keyCode == 37) {
        // Left Arrow Key: Move ball left
        ballMatrix = mult(ballMatrix, translate(-0.5, 0.0, 0.0));
        lrBall += 1.5;
        if((kirby && !rollBallON) || (eve && !rollBallON))
        {
        var left = lrBall * -1.0;
          if(kirby)
          {
              kirbyRArmMatrix = mult(translate(left, 0.0, 0.0), origKirbyRArm);
              kirbyLArmMatrix = mult(translate(left, 0.0, 0.0), origKirbyLArm);
              kirbyLFootMatrix = mult(translate(left, 0.0, 0.0), origKirbyLFoot);
              kirbyRFootMatrix = mult(translate(left, 0.0, 0.0), origKirbyRFoot);
              kirbyBodyMatrix = mult(translate(left, 0.0, 0.0),origKirbyBody);
          }   
          else if(eve)
          {
              eveBodyMatrix = mult(translate(left, 0.0, 0.0),origEveBody);
              eveLArmMatrix = mult(translate(left, 0.0, 0.0), origEveLA);
              eveRArmMatrix = mult(translate(left, 0.0, 0.0),origEveRA);
          }
        }
    } else if (event.keyCode == 39) {
        // Right Arrow Key: Move ball right
        ballMatrix = mult(ballMatrix, translate(0.5, 0.0, 0.0));
        lrBall -= 1.5;
        if((kirby && !rollBallON) || (eve && !rollBallON))
        {
            var right = lrBall * -1.0;
            if(kirby)
            {
              kirbyRArmMatrix = mult(translate(right, 0.0, 0.0), origKirbyRArm);
              kirbyLArmMatrix = mult(translate(right, 0.0, 0.0), origKirbyLArm);
              kirbyLFootMatrix = mult(translate(right, 0.0, 0.0), origKirbyLFoot);
              kirbyRFootMatrix = mult(translate(right, 0.0, 0.0), origKirbyRFoot);
              kirbyBodyMatrix = mult(translate(right, 0.0, 0.0),origKirbyBody);
            }   
            else if(eve)
            {
              eveBodyMatrix = mult(translate(right, 0.0, 0.0),origEveBody);
              eveLArmMatrix = mult(translate(right, 0.0, 0.0), origEveLA);
              eveRArmMatrix = mult(translate(right, 0.0, 0.0),origEveRA);
            }
        }
    } else if (event.keyCode == 80) {
        // 'p' Key: Change camera perspective to one above the bowling ball
        if (!changeCamera)
            changeCamera = 1;
        else
            changeCamera = 0;
    }
    else if (event.keyCode == 77) {
      // 'm' key: rotate between using nothing, kirby, eve
      k++;
      var j=k%3;
      if(j==0)
      {
          kirby=0;
          eve=0;
      }
      else if(j == 1)
      {
          kirby=1;
          eve=0;
      }
      else if(j == 2)
      {
          kirby=0;
          eve=1;
      }
  }
  }
}


function tick() {
    requestAnimFrame(tick)
    render();
}

// Draw all cube related objects with varying styles
function drawCubes( option ){
    if (option == 0)
        gl.drawElements(gl.TRIANGLES, 36, gl.UNSIGNED_BYTE, 0);
    else if (option == 1)
        gl.drawElements(gl.LINES, 36, gl.UNSIGNED_BYTE, 0);
    else if (option == 2)
        gl.drawElements(gl.LINE_LOOP, 36, gl.UNSIGNED_BYTE, 0);
    else
        gl.drawElements(gl.TRIANGLE_STRIP, 36, gl.UNSIGNED_BYTE, 0);
}

// Draw all sphere related objects with varying styles
function drawSpheres( option ){
    if (option == 0) {
        for (var i = 0; i < indexG; i+= 3)
            gl.drawArrays(gl.TRIANGLES, i, 3 );
    } else if (option == 1) {
        for (var i = 0; i < indexG; i+= 3)
            gl.drawArrays(gl.LINES, i, 3 );
    } else if (option == 2) {
        for (var i = 0; i < indexG; i+= 3)
            gl.drawArrays(gl.LINE_LOOP, i, 3 );
    } else {
        for (var i = 0; i < indexG; i+= 3)
            gl.drawArrays(gl.TRIANGLE_STRIP, i, 3 );
    }
}

/* CAMERA FUNCTIONS */
function increaseY(){
    cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.5, 0.0));
}

function decreaseY(){
    cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, -0.5, 0.0));
}

function increaseHeading(){
    cameraViewMatrix = mult(rotate(1, [0.0, 1.0, 0.0]), cameraViewMatrix);
}

function decreaseHeading(){
    cameraViewMatrix = mult(rotate(-1, [0.0, 1.0, 0.0]), cameraViewMatrix);
}

function moveLeft(){
    cameraViewMatrix = mult(cameraViewMatrix, translate(0.5, 0.0, 0.0));
}

function moveRight(){
    cameraViewMatrix = mult(cameraViewMatrix, translate (-0.5, 0.0, 0.0));
}

function moveBackward() {
    cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, -0.5));
}

function moveForward() {
    cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, 0.5));
}

function moveBackward() {
    cameraViewMatrix = mult(cameraViewMatrix, translate(0.0, 0.0, -0.5));
}

function resetCamera() {
    cameraViewMatrix = translate(0.0, 0.0, -100.0);
}
