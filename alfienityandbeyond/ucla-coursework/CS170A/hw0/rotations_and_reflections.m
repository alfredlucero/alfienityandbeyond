
%% If you are running Octave, first run the following commands (inside Octave):
%% >>>  pkg install -forge symbolic   %  download and install symbolic package
%% >>>  pkg load symbolic             %  load functions from the symbolic package


syms phi theta   %  declare phi and theta to be symbolic variables

Rotation = @(t) [ cos(t) -sin(t) ; sin(t) cos(t) ]   %  define a function that returns a rotation matrix

%% Rotation = 
%% 
%%     @(t)[cos(t),-sin(t);sin(t),cos(t) ]

Rotation(theta)

%% ans =
%%  
%% [ cos(theta), -sin(theta) ]
%% [ sin(theta),  cos(theta) ]

Rotation(theta) * Rotation(-theta)

%% ans =
%%  
%% [ cos(theta)^2 + sin(theta)^2,                           0 ]
%% [                           0, cos(theta)^2 + sin(theta)^2 ]

simplify( Rotation(theta) * Rotation(-theta) )

%% ans =
%%  
%% [ 1, 0 ]
%% [ 0, 1 ]

simplify( Rotation(theta) * Rotation(theta) )

%% ans =
%%  
%% [ cos(2*theta), -sin(2*theta) ]
%% [ sin(2*theta),  cos(2*theta) ]

simplify( Rotation(theta) * Rotation(phi) )
 
%% ans =
%%  
%% [ cos(phi + theta), -sin(phi + theta) ]
%% [ sin(phi + theta),  cos(phi + theta) ]



Reflection = @(t) [ cos(t) sin(t) ; sin(t) -cos(t) ]   %  define a function that yields a reflection matrix

%% Reflection = 
%% 
%%     @(t)[cos(t),sin(t);sin(t),-cos(t) ]

Reflection(theta)

%% ans =
%%  
%% [ cos(theta),  sin(theta) ]
%% [ sin(theta), -cos(theta) ]

Reflection(theta) * Reflection(theta)

%% ans =
%%  
%% [ cos(theta)^2 + sin(theta)^2,                           0 ]
%% [                           0, cos(theta)^2 + sin(theta)^2 ]

simplify(ans)

%% ans =
%%  
%% [ 1, 0 ]
%% [ 0, 1 ]

Reflection(theta) * Reflection(phi)

%% ans =
%%  
%% [ cos(phi)*cos(theta) + sin(phi)*sin(theta), cos(theta)*sin(phi) - cos(phi)*sin(theta) ]
%% [ cos(phi)*sin(theta) - cos(theta)*sin(phi), cos(phi)*cos(theta) + sin(phi)*sin(theta) ]

simplify(ans)

%% ans =
%%  
%% [  cos(phi - theta), sin(phi - theta) ]
%% [ -sin(phi - theta), cos(phi - theta) ]

Rotation(theta - phi)

%% ans =
%%  
%% [  cos(phi - theta), sin(phi - theta) ]
%% [ -sin(phi - theta), cos(phi - theta) ]

simplify( Reflection(theta) * Reflection(phi)  -  Rotation(theta - phi) )

%% ans =
%%  
%% [ 0, 0 ]
%% [ 0, 0 ]
%%  

