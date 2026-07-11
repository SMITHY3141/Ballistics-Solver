# Ballistics-Solver

A ballistics calculator for intercepting moving targets with linear-drag projectiles. Iteratively solves for firing conditions using a 3D newton-raphson method.

Assumes that the drag acting on a projectile is proportional to its own velocity (i.e. v[n+1] = v[n] * (1 - drag)), and it updates discretely.
Factors in gravity, target velocity, target position, projectile speed, linear wind, and drag.

The solver makes use of explicit analytical equations for projectile position, but it could also be solved numerically.

Won't go into the full derivation, but an explicit solution for projectile position can be found by treating the velocity as a geometric sequence, and the resulting position as a geometric series.
Giving:
b\left(t\right)=k\frac{1-k^{t}}{d}

s_{x}\left(a,\ p,\ t\right)=\left(b\left(t\right)\cdot v_{0}\cos\left(a\right)\cos\left(p\right)+\ w_{c}w.x\cdot\frac{t-b\left(t\right)}{d}\right)d_{t}
s_{y}\left(a,\ p,\ t\right)=\left(b\left(t\right)\cdot v_{0}\sin\left(a\right)\cos\left(p\right)+\ w_{c}w.y\cdot\frac{t-b\left(t\right)}{d}\right)d_{t}
s_{z}\left(a,\ p,\ t\right)=\left(b\left(t\right)\cdot v_{0}\sin\left(p\right)-0.5\frac{t-b\left(t\right)}{d}\right)d_{t}

From this partial derivatives of position with respect to time, azimuth, elevation can be derived.
These derivatives are used to converge on a solution in the newton-raphson solver.



