# Ballistics-Solver

A ballistics calculator for intercepting moving targets with linear-drag projectiles. Iteratively solves for firing conditions using a multi-dimensional newton-raphson method (to find what set of launch conditions produces zero error).

Has also been implemented in desmos for a graphical view [https://www.desmos.com/3d/5zz8pbzmjr](https://www.desmos.com/3d/nwblzd3r48)
<img width="482" height="450" alt="Screenshot 2026-07-16 at 2 13 36 am" src="https://github.com/user-attachments/assets/c52fa0b8-ceb0-44cf-9873-649f4addd9e6" />

Model assumes that the drag acting on a projectile is proportional to its own velocity (i.e. $y''=g-d\cdot y'$, where g is gravity, d is drag coeff).
Factors in gravity, target velocity, target position, projectile speed, and drag.

The solver makes use of explicit analytical equations for projectile position, but with modification it could also be solved numerically.

Won't go into the full derivation, but an explicit solution for projectile position can be found by the laplace transform.
Giving:<br>
$s_{x}\left(\theta,\ \phi,\ t\right)=\ \frac{v_{0}\cos\left(\theta\right)\cos\left(\phi\right)}{d}\left(1-e^{-dt}\right)$<br>
$s_{y}\left(\theta,\ \phi,\ t\right)=\frac{v_{0}\sin\left(\theta\right)\cos\left(\phi\right)}{d}\left(1-e^{-dt}\right)$<br>
$s_{z}\left(\theta,\ \phi,\ t\right)=\frac{g}{d}\left(\frac{e^{-dt}}{d}+t-\frac{1}{d}\right)+\frac{v_{0}\sin\left(\phi\right)}{d}\left(1-e^{-dt}\right)$<br>

where t is the time in seconds, d is drag, a is azimuth angle, p is elevation angle, t is time after launch.

we specifically try solve for the launch condition that drives the miss vector to 0 (i.e. the root of the error vector).<br>
$s_{x}\left(\theta,\ \phi,\ t\right)-T_{x}\left(t\right)=0$<br>
$s_{y}\left(\theta,\ \phi,\ t\right)-T_{y}\left(t\right)=0$<br>
$s_{z}\left(\theta,\ \phi,\ t\right)-T_{z}\left(t\right)=0$<br>

From these equations partial derivatives of error with respect to time, azimuth, and elevation can be derived.
These derivatives are used to converge on a solution in the newton-raphson solver.




EXAMPLE USAGE

% ./solver<br>  

CONDITIONS<br>
speed: 300 m/s<br>
drag: 0.05<br>
gravity: -9.8 m/s/s<br>
target: (1900, 500, 900) m<br>
velocity: (0, 0, 0) m/s<br>
max: 9<br>
desired error: 0 m<br>

SOLVING<br>
0: (0.257324, 0.429559, 8.93105), error: 338.62<br>
1: (0.257324, 0.597785, 9.79863), error: 44.0945<br>
2: (0.257324, 0.591436, 10.0317), error: 0.560407<br>
3: (0.257324, 0.591683, 10.0345), error: 0.000136479<br>
4: (0.257324, 0.591683, 10.0345), error: 0.00017531<br>
5: (0.257324, 0.591683, 10.0345), error: 0.000136479<br>
6: (0.257324, 0.591683, 10.0345), error: 0.00017531<br>
7: (0.257324, 0.591683, 10.0345), error: 0.000136479<br>
8: (0.257324, 0.591683, 10.0345), error: 0.00017531<br>
9: (0.257324, 0.591683, 10.0345), error: 0.000136479<br>

SOLUTION<br>
azimuth: 0.257324 rads<br>
elevation: 0.591683 rads<br>
time: 10.0345 s<br>
error: 0.000136479 m<br>

