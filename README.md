# Ballistics-Solver

A ballistics calculator for intercepting moving targets with linear-drag projectiles. Iteratively solves for firing conditions using a multi-dimensional newton-raphson method (to find what set of launch conditions produces zero error).

Has also been implemented in desmos for a graphical view https://www.desmos.com/3d/5zz8pbzmjr

Assumes that the drag acting on a projectile is proportional to its own velocity (i.e. y'' = g - d * y', where g is gravity, d is drag coeff).
Factors in gravity, target velocity, target position, projectile speed, and drag.

The solver makes use of explicit analytical equations for projectile position, but it could also be solved numerically.

Won't go into the full derivation, but an explicit solution for projectile position can be found by laplace transform.
Giving:
$s_{x}\left(a,\ p,\ t\right)=\ \frac{v_{0}\cos\left(a\right)\cos\left(p\right)}{d}\left(1-e^{-dt}\right)$ 
$s_{y}\left(a,\ p,\ t\right)=\frac{v_{0}\sin\left(a\right)\cos\left(p\right)}{d}\left(1-e^{-dt}\right)$ 
$s_{z}\left(a,\ p,\ t\right)=\frac{g}{d}\left(\frac{e^{-dt}}{d}+t-\frac{1}{d}\right)+\frac{v_{0}\sin\left(p\right)}{d}\left(1-e^{-dt}\right)$  

where t is the time in seconds, d is drag, a is azimuth angle, p is elevation angle, t is time after launch.

we specifically try solve for the launch condition that drives the miss vector to 0 (i.e. the root of the error vector).
$s_{x}\left(a,\ p,\ t\right)-T_{x}\left(t\right)=0$
$s_{y}\left(a,\ p,\ t\right)-T_{y}\left(t\right)=0$
$s_{z}\left(a,\ p,\ t\right)-T_{z}\left(t\right)=0$

From these equations partial derivatives of error with respect to time, azimuth, and elevation can be derived.
These derivatives are used to converge on a solution in the newton-raphson solver.
