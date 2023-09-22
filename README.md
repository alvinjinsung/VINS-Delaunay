# VINS-Delaunay
Performed Delaunay traingulation using the feature points obtained from VINS-Fusion pipeline

Also performed Delaunay refinement algorithm to renomve accute triangles (angle < 25 degree)

## Reference
* VINS-Fusion: https://github.com/HKUST-Aerial-Robotics/VINS-Fusion
* Dealunay traingulation: https://github.com/Bl4ckb0ne/delaunay-triangulation

## VINS-Fusion
VINS-Fusion is a popular VIO SLAM algorithm which uses vision and inertial data to perform SLAM

Basic pipeline can be described as follows

1) Initialization (Visual only SfM, IMU preintegration, Visual-Inertial alignment)
2) Tightly couple preintegrated IMU measurement and feature observations
3) Loop closure and pose graph reuse

Throughout the process, VIO system extracts keypoints and match the keypoints to perform odeometry estimation

## Delaunay traingulation
Delaunay triangulation for a given set P of discrete points is a triangulation DT(P) such that no point in P is inside the circumcircle of any triangle in DT(P)

Bowyer Watson algorithm is used here (https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm)

## Delaunay refinement
Delaunay refinement is a process to to remove skinny traingles from Delaunay triangulation

Ruppert's algorithm is used here (https://www.sciencedirect.com/science/article/pii/S0196677485710218, https://en.wikipedia.org/wiki/Delaunay_refinement)
