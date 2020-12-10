#include "Boid.h"
#include "Flock.h"

// =============================================== //
// ======== Flock Functions from Flock.h ========= //
// =============================================== //

Flock::Flock()
{
}


int Flock::getSize()
{
    return flock.size();
}

Boid Flock::getBoid(int i)
{
    return flock[i];
}

void Flock::addBoid(Boid b)
{
    flock.push_back(b);
}

void Flock::addObstacle(Boid b)
{
	obstacles.push_back(b);
}

void Flock::addTarget(Boid b)
{
	targets.push_back(b);
}

// Runs the run function for every boid in the flock checking against the flock
// itself. Which in turn applies all the rules to the flock.
void Flock::flocking(double sep, double ali, double coh) 
{
    for(unsigned int i = 0; i < flock.size(); i++)
	{
		flock[i].setForceGains(sep, ali, coh);
        flock[i].run(flock, obstacles, targets);
	}
}
