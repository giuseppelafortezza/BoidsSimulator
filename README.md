# Boids Simulator

This project attempts to simulate flocking behavior, through the creation of simple entities called boids. Boids, which exist on a two-dimensional plane, function through three simple rules -- alignment, cohesion, and separation.

- Alignment causes boids to match velocity of nearby boids.
- Cohesion causes boids to seek the center of mass of the nearest clump of boids.
- Separation prevents boids from getting too close to each other.

These three simple rules cause complex behavior to emerge, which is what makes the boid simulation interesting. The algorithm was originally formulated by Craig Reynolds in the 1980s.

## Dependencies 
In order to build the simulator you need to install qt5 and cmake
- Ubuntu / Debian-based distros: `sudo apt-get install qt5-default cmake build-essential`

## Building the simulator
Create a direcotry called `build`
Then `cd` into the `build` folder and run `make` to produce an executable file called `BoidsGui`.

## Running the simulation
Move into the `build` folder and execute the simulator `./BoidsGui`.

You can see a GUI with sliders on the right. Press `START` to run the simulation.

You can add additional obstacles pressing the key `O` on the keyboard.
