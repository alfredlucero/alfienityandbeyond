import numpy as np
from sympy import *

# This imports many useful functions, like sin(), cos(), etc.
# They can be used without having to give a module name.

phi, theta = symbols('phi theta')  #  declare phi and theta to be symbolic variables

Rotation = lambda t: np.matrix([[cos(t), -sin(t)], [sin(t), cos(t)]])

Rotation(theta)

matrix_simplify = np.vectorize(simplify)

matrix_simplify( Rotation(theta) * Rotation(-theta) )

matrix_simplify( Rotation(theta) * Rotation(+theta) )

Rotation(theta) * Rotation(phi)

matrix_simplify( Rotation(theta) * Rotation(phi) )

Reflection = lambda t: np.matrix([[cos(t), sin(t)], [sin(t), -cos(t)]])

Reflection(theta)

matrix_simplify( Reflection(theta) * Reflection(theta) )

Reflection(theta) * Reflection(phi)

Rotation(theta - phi)

matrix_simplify( Reflection(theta) * Reflection(phi)  -  Rotation(theta - phi) )


#  >>> Rotation = lambda t: np.matrix([[cos(t), -sin(t)], [sin(t), cos(t)]])
#  >>> 
#  >>> Rotation(theta)
#  matrix([[cos(theta), -sin(theta)],
#          [sin(theta), cos(theta)]], dtype=object)
#  >>> 
#  >>> matrix_simplify = np.vectorize(simplify)
#  >>> 
#  >>> matrix_simplify( Rotation(theta) * Rotation(-theta) )
#  matrix([[1, 0],
#          [0, 1]], dtype=object)
#  >>> 
#  >>> matrix_simplify( Rotation(theta) * Rotation(+theta) )
#  matrix([[cos(2*theta), -sin(2*theta)],
#          [sin(2*theta), cos(2*theta)]], dtype=object)
#  >>> 
#  >>> Rotation(theta) * Rotation(phi)
#  matrix([[-sin(phi)*sin(theta) + cos(phi)*cos(theta),
#           -sin(phi)*cos(theta) - sin(theta)*cos(phi)],
#          [sin(phi)*cos(theta) + sin(theta)*cos(phi),
#           -sin(phi)*sin(theta) + cos(phi)*cos(theta)]], dtype=object)
#  >>> 
#  >>> matrix_simplify( Rotation(theta) * Rotation(phi) )
#  matrix([[cos(phi + theta), -sin(phi + theta)],
#          [sin(phi + theta), cos(phi + theta)]], dtype=object)
#  >>> 
#  >>> Reflection = lambda t: np.matrix([[cos(t), sin(t)], [sin(t), -cos(t)]])
#  >>> 
#  >>> Reflection(theta)
#  matrix([[cos(theta), sin(theta)],
#          [sin(theta), -cos(theta)]], dtype=object)
#  >>> 
#  >>> matrix_simplify( Reflection(theta) * Reflection(theta) )
#  matrix([[1, 0],
#          [0, 1]], dtype=object)
#  >>> 
#  >>> Reflection(theta) * Reflection(phi)
#  matrix([[sin(phi)*sin(theta) + cos(phi)*cos(theta),
#           sin(phi)*cos(theta) - sin(theta)*cos(phi)],
#          [-sin(phi)*cos(theta) + sin(theta)*cos(phi),
#           sin(phi)*sin(theta) + cos(phi)*cos(theta)]], dtype=object)
#  >>> 
#  >>> Rotation(theta - phi)
#  matrix([[cos(phi - theta), sin(phi - theta)],
#          [-sin(phi - theta), cos(phi - theta)]], dtype=object)
#  >>> 
#  >>> matrix_simplify( Reflection(theta) * Reflection(phi)  -  Rotation(theta - phi) )
#  matrix([[0, 0],
#          [0, 0]], dtype=object)
#  >>> 
