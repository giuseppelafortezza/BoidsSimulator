#include "Pvector.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <mutex>

#ifndef BOID_H_
#define BOID_H_

const int window_height = 900;
const int window_width = 1200;

// The Boid Class
//
// Attributes
//  bool predator: flag that specifies whether a given boid is a predator.
//  Pvector location: Vector that specifies a boid's location.
//  Pvector velocity: Vector that specifies a boid's current velocity.
//  Pvector acceleration: Vector that specifies a boid's current acceleration.
//  float maxSpeed: Limits magnitude of velocity vector.
//  float maxForce: Limits magnitude of acceleration vector. (F = m*a!)
//
// Methods
//  applyForce(Pvector force): Adds the given vector to acceleration
//
//  Pvector Separation(vector<Boid> Boids): If any other boids are within a
//      given distance, Separation computes a a vector that distances the
//      current boid from the boids that are too close.
//
//  Pvector Alignment(vector<Boid> Boids): Computes a vector that causes the
//      velocity of the current boid to match that of boids that are nearby.
//
//  Pvector Cohesion(vector<Boid> Boids): Computes a vector that causes the
//      current boid to seek the center of mass of nearby boids.

class Boid
{
public:
    Boid();
    Boid(float x, float y);
    Boid(float x, float y, bool predCheck);
	
	
	Pvector location;
	Pvector velocity;
	
    void applyForce(Pvector force);
    
    //Functions involving SFML and visualisation linking
    Pvector seek(Pvector v);
	void run(vector <Boid> b, vector <Boid> o, vector <Boid> t);
    void update();
	void flock(vector <Boid> b, vector <Boid> o, vector <Boid> t);
    void borders();
    float angle(Pvector v);
	
	void setForceGains(double separ, double align, double cohes);
	
private:
	// Three Laws that boids follow
	Pvector Separation(vector<Boid> Boids);
	Pvector Alignment(vector<Boid> Boids);
	Pvector Cohesion(vector<Boid> Boids);
	
	Pvector Attractive(vector<Boid> Targets);
	Pvector Repulsive(vector<Boid> Obstacles);
	
	
private:
	bool predator;
	Pvector acceleration;
	float maxSpeed;
	float maxForce;
	
private:
	double kSeparation;
	double kAlignment;
	double kCohesion;
	
	double kAttractive;
	double kRepulsive;
};

#endif
