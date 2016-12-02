## Vectors in Python
# 
# When using a Notebook, remember to use shift-return to execute each cell.



### Set up Numpy and Matplotlib

import numpy as np 
#  import Numpy -- the matrix algebra module for Python

import matplotlib.pyplot as plt
#  Matplotlib = the Matlab-like plotting module for Python

# get_ipython().magic('matplotlib inline')
#  magic incantation that ensures all plot output is kept inline in this notebook

plt.rcParams['figure.figsize'] = (15.0, 10.0)
#  another incantation to set the default plot sizing



### Sample plot


n = 20;                                                                                                                                               
                                                                                                                                                      
t = np.linspace(0, 2 * np.pi, n);
#  n points in a linear sequence, starting at 0, ending at 2*pi                                                            
t = np.arange(n)* 2 * np.pi / n;                                                                                                                               
                                                                                                                                                      
x1 = np.cos(t);                                                                                                                                          
x2 = np.sin(t);                                                                                                                                          
                                                                                                                                                      
plt.plot(x1, x2, 'b.')
plt.axis('equal')
#  axis equal == make x and y axes the same scale (i.e., aspect ratio = 1.0)


### Fancier plot: draw vectors (arrows)for each point on the circle


plt.xlim(-2,2)
plt.ylim(-2,2)

plt.plot(x1, x2, 'b.')
plt.axis('equal')
                                                                                                                                                      
plt.hold(True)
#  hold on == "superimpose another plot on the current figure"                                                                     

for i in range(n):
   plt.arrow( 0,0, x1[i], x2[i], color='b' );
   # draw an arrow from (0,0)to v = (x1(i),x2(i))                                                                 

plt.hold(False)


### Define a function for plotting vectors, and make it even prettier


# function:  draw an arrow from (0,0)to v = (v1,v2)                                                                                                  
                                                                                                                                                      
def drawvector(v1, v2, c):
    plt.arrow(0,0, v1,v2, color=c )

# the MaxHeadSize option makes the arrow heads smaller                                                                                                
                                                                                                                                                      
plt.plot(x1, x2, 'b.')
plt.axis('equal')
                                                                                                                                                      
plt.hold()
for i in range(n):
   drawvector( x1[i], x2[i], 'b' );                                                                                                                   

plt.hold()



help(plt.arrow)



t = np.linspace(0, 2 * np.pi, n);                                                                                                                             
                                                                                                                                                      
x1 = np.cos(t);                                                                                                                                          
x2 = np.sin(t);                                                                                                                                          
                                                                                                                                                      
z = np.zeros(n);  # vector of n zeroes
                                                                                                                                                      
plt.plot(x1, x2, 'b.')
plt.axis('equal')
                                                                                                                                                      
plt.hold()
for i in range(n):
   plt.arrow( 0, 0, x1[i], x2[i], color='b', width=5e-4 )# thinner lines                                                                 
plt.hold()



### Now translate each vector in the circle by a linear transformation


x = [ x1 , x2 ];
np.shape(x)


A = np.array([[1.8, 0.6], [0.6, 0.7]]);  #  or any 2x2 matrix you want

Ax = A.dot(x)
np.shape(Ax)



Ax1 = Ax[0, :];
Ax2 = Ax[1, :];
np.shape(Ax2)
Ax2



plt.plot(x1,x2, 'b.')
plt.axis('equal')

plt.hold()
plt.plot(Ax1, Ax2, 'r.')

for i in range(n):
    plt.arrow( 0, 0,  x1[i],  x2[i], color='b', width=0.00075 )
    plt.arrow( 0, 0, Ax1[i], Ax2[i], color='r', width=0.00075 )

plt.hold()



plt.plot(x1,x2, 'b.')
plt.axis('equal')

plt.hold()

plt.plot(Ax1, Ax2, 'r.')

for i in range(n):
    plt.arrow( x1[i], x2[i], Ax1[i]-x1[i], Ax2[i]-x2[i], color='m', width=0.00075 )
# plot the change from x to A*x -- with magenta arrows

plt.hold()


### Fancy diagram...


A = np.array([[1.8, 0.6], [0.6, 0.7]])
n = 4

xtext  = [ '(1,0)', '(0,1)', '(-1,0)',  '(0,-1)'  ]
Axtext = [ '(a,c)', '(b,d)', '(-a,-c)', '(-b,-d)' ]

t = np.linspace(0, 2*np.pi, n)

x1 = np.cos(t)
x2 = np.sin(t)

x = np.array([ x1 , x2 ])
x


Ax = A.dot(x)# matrix multiplication
Ax


Ax1 = Ax[0, :]
Ax2 = Ax[1, :]

xmax = max( 1.5, abs(Ax1).max()+0.75 )
ymax = max( 1.5, abs(Ax2).max()+0.75 )
(xmax, ymax)
n



def drawvector(v,c,t,dx,dy):
    plt.arrow(0,0,v[0],v[1], color=c, width=0.00075)
    plt.text( v[0]+ dx, v[1]+ dy, t )

def drawtranslation(x1,x2,y1,y2,c):
    plt.arrow(x1,x2,(y1-x1),(y2-x2), color=c, width=0.0004)



plt.plot(x1,x2, 'b.')

plt.axis('equal')
plt.xlabel('translation by A of individual unit vectors is shown with magenta arrows')
plt.hold()

for i in range(n):
   drawtranslation( x1[i], x2[i],  Ax1[i], Ax2[i], 'm' )
   plt.text( (x1[i]+Ax1[i])*0.57, (x2[i]+Ax2[i])*0.57, 'A', color='m' )
   drawvector(  x[:,i], 'b',  xtext[i], x1[i]*0.25-0.15, x2[i]*0.15  )
   drawvector( Ax[:,i], 'r', Axtext[i], x1[i]*0.25-0.15, x2[i]*0.15  )

plt.text(  1.36, 1.35, 'A = [ a b ]', horizontalalignment='right')
plt.text(  1.36, 1.20, '    [ c d ]', horizontalalignment='right')

plt.xlim(-xmax, xmax)#  These xlim and ylim commands should be at the end
plt.ylim(-ymax, ymax)#   in order to suppress auto-scaling

plt.hold()


### Vector Projection


u = np.array([7.68, 2.24])

v = np.array([3, 4])

lambda_ = (u.dot(v))/ (u.dot(u))   #  = length of projection of v onto u

vector_projection_of_v_onto_u  =  lambda_ * u
vector_projection_of_v_onto_u


### Fancy diagram...


u = np.array([7.68, 2.24])
v = np.array([3, 4])
origin = np.array([0, 0])

plt.plot(np.array([-1, 8]), np.array([0, 0]))  # x-axis
plt.hold()
plt.plot(np.array([0, 0]),  np.array([-1,5]))  # y-axis

plt.axis('equal')
         
plt.text(6.1,2.7, ('u  =  [%4.2f, %4.2f]' % (u[0],u[1])))
plt.text(3.1,4.2, ('v  =  [%4.2f, %4.2f]' % (v[0],v[1])))
plt.title('projection of v onto u')

lambda_ = (u.dot(v))/ (u.dot(u))
w = lambda_ * u

def drawvector(o,v,c):
    plt.arrow(o[0], o[1], v[0], v[1], color=c, width=0.0002 )

drawvector( origin, u, 'r' )
drawvector( origin, v, 'b' )
drawvector( w,    v-w, 'm' )

plt.text(2.0,5.0, ('lambda  =  ( <u,v> / <u,u> )=  %4.2f' % lambda_))
plt.text(4.0,0.9, ('w  =  lambda  u  =  %4.2f  u'% lambda_))
plt.text(4.0,0.5, ('w  =  [%4.2f, %4.2f]' % (w[0], w[1])))
plt.text(3.7,2.5, '3')
plt.text(2.4,1.0, '4')
plt.text(1.4,2.5, '5')

epsilon = 0.03
drawvector( origin+epsilon, w+epsilon, 'm'  )

plt.axis([-1, 9, -1, 6])# this must go last; otherwise the plot is resized automatically
plt.hold()


### Vector Length (and Norm)


u = np.array( [7.6, 2.24] )

print(('length of u =? %f' % u.dot(u)))
print(('norm of u = %f' % np.linalg.norm(u)))



v = np.array( [3, 4] )

print(('length of v =? %f' % v.dot(v)))
print(('norm of v = %f' % np.linalg.norm(v)))


### Incorrect mathematical definition of vector norm
# 
# $$norm(v)~=~ <v,v> ~=~ v' * v ~=~ \sum_{i=1}^n ~ \overline{v_i} ~ v_i ~$$
# 
# Why isn't this definition right?

### Discretized Functions


n = 100;
x = np.linspace(0, 4*np.pi, n);  #  x  =  vector of samples

f = np.sin                       #  f  =  sin
fx = np.sin(x);                  #  fx is a discretized version of f

plt.plot( x, fx, 'b.-' )
plt.show()


### Multiple views (subplots)


n = 100
x = np.linspace(0, 4 * np.pi, n)#  x  =  vector of samples

f = np.sin                        #  f  =  sin
fx = np.sin(x)#  fx = discretized f

plt.subplot(3,1, 1)#  1st of 3 plots
plt.plot( x, fx, 'b.-' )

plt.subplot(3,1, 2)#  2nd of 3 plots
plt.plot( x[:-1], np.diff(fx), 'r.-')

plt.subplot(3,1, 3)#  3rd of 3 plots
deltax = x[1] - x[0]

plt.plot( x, fx, 'b.-', x[:-1], np.diff(fx)/ deltax, 'r.-')
plt.show()


### Rotations


def Rotation(t):
     return np.array([[ np.cos(t), -np.sin(t)], [np.sin(t), np.cos(t)]])
    #  a function that returns a rotation matrix

theta = np.pi/2

R_theta = Rotation(theta)

R_theta



R_theta_minus_theta = Rotation(theta).dot( Rotation(-theta) )

R_theta_minus_theta



R_theta_plus_theta = Rotation(theta).dot( Rotation(theta) )

R_theta_plus_theta



R_two_theta = Rotation(2 * theta)

R_two_theta



phi = np.pi/4

R_theta_phi = Rotation(theta).dot( Rotation(phi) )

R_theta_phi



R_theta_plus_phi = Rotation(theta + phi)

R_theta_plus_phi




