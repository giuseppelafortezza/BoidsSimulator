#include "QSFMLCanvas.h"
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif
#include <iostream>


bool target = false;
bool obstacle = false;

QSFMLCanvas::QSFMLCanvas(QWidget* parent)
	: QWidget(parent)
	, boidsSize(3.0)
	, myInitialized(false)
	, kSeparation(1.0)
	, kAlignment(1.0)
	, kCohesion(1.0)
	, kDesiredDistance(100)
	, kFowAlignment(50)
	, kFowCohesion(100)
	, mEnabled(false)
{
	// Setup some states to allow direct rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	// Set strong focus to enable keyboard events to be received
	setFocusPolicy(Qt::StrongFocus);
	
	
	//Create flock
	for(int i = 0; i < 50; i++)
	{
		Boid b(width() / 2, height() / 2); // Starts all boids in the center of the screen
		sf::CircleShape shape(8, 3);
		
		// Changing the Visual Properties of the shape
		// shape.setPosition(b.location.x, b.location.y); // Sets position of shape to random location that boid was set to.
		shape.setPosition(width(), height()); // Testing purposes, starts all shapes in the center of screen.
		shape.setOutlineColor(sf::Color(0,255,0));
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1);
		shape.setRadius(boidsSize);
		
		// Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
		flock.addBoid(b);
		shapes.push_back(shape);
	}
}


QSFMLCanvas::~QSFMLCanvas()
{
	
}

void QSFMLCanvas::updateParameters(int desiredDistance, int fowAlignment, int fowCohesion)
{
	
}

void QSFMLCanvas::updateSeparation(int k)
{
	kSeparation = double(k);
}


void QSFMLCanvas::updateAlignment(int k)
{
	kAlignment = double(k);
}


void QSFMLCanvas::updateCohesion(int k)
{
	kCohesion = double(k);
}


void QSFMLCanvas::showEvent(QShowEvent*)
{
	if(!myInitialized)
	{
		// Under X11, we need to flush the commands sent to the server to ensure that
		// SFML will get an updated view of the windows
		#ifdef Q_WS_X11
		//XFlush(QX11Info::display());
		#endif
		
		mWindow.create(winId());
		
		connect(&myTimer, SIGNAL(timeout()), this, SLOT(repaint()));
		myTimer.setInterval(50);
		myTimer.start();
		
		myInitialized = true;
	}
}


void QSFMLCanvas::onStart(bool enabled)
{
	mEnabled = enabled;
}

void QSFMLCanvas::onReset()
{
	shapes.clear();

}



QPaintEngine* QSFMLCanvas::paintEngine() const
{
	return 0;
}


void QSFMLCanvas::paintEvent(QPaintEvent*)
{
	if(true == mEnabled)
	{
		HandleInput();
		Render();
	}
}


void QSFMLCanvas::HandleInput()
{
	sf::Event event;
	while(mWindow.pollEvent(event))
	{
		// "close requested" event: we close the window
		// Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)
		if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) ||
			(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X))
		{
			mWindow.close();
		}
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		std::cout << "Add target" << std::endl;
		target = true;
		
		int sizeObj = 20;
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(mWindow);
		Boid b(mouseCoords.x -sizeObj/2, mouseCoords.y -sizeObj/2, false);
		b.setForceGains(kSeparation, kAlignment, kCohesion);
		sf::CircleShape shape(30,4);
		
		// Changing visual properties of newly created boid
		shape.setPosition(mouseCoords.x -sizeObj/2, mouseCoords.y -sizeObj/2);
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineColor(sf::Color::Green);
		shape.setOutlineThickness(1);
		shape.setRadius(sizeObj);
		
		// Adds newly created boid and shape to their respective data structure
		flock.addTarget(b);
		target_shape.push_back(shape);
		
		// New Shape is drawn
		mWindow.draw(target_shape[target_shape.size()-1]);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		std::cout << "Add obstacle" << std::endl;
		obstacle = true;
		
		int sizeObj = 20;
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(mWindow);
		Boid b(mouseCoords.x -sizeObj/2, mouseCoords.y -sizeObj/2, false);
		b.setForceGains(kSeparation, kAlignment, kCohesion);
		sf::CircleShape shape(100,100);
		
		// Changing visual properties of newly created boid
		shape.setPosition(mouseCoords.x -sizeObj/2, mouseCoords.y -sizeObj/2);
		shape.setFillColor(sf::Color::White);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1);
		shape.setRadius(sizeObj);
		
		// Adds newly created boid and shape to their respective data structure
		flock.addObstacle(b);
		obstacle_shape.push_back(shape);
		
		// New Shape is drawn
		mWindow.draw(obstacle_shape[obstacle_shape.size()-1]);
	}
	
	// Check for mouse click, draws and adds boid to flock if so.
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		// Gets mouse coordinates, sets that as the location of the boid and the shape
		sf::Vector2i mouseCoords = sf::Mouse::getPosition(mWindow);

		
		Boid b(mouseCoords.x, mouseCoords.y, false);
		b.setForceGains(kSeparation, kAlignment, kCohesion);
		sf::CircleShape shape(10,3);

		// Changing visual properties of newly created boid
		shape.setPosition(mouseCoords.x, mouseCoords.y);
		shape.setOutlineColor(sf::Color(255, 255, 0));
		shape.setFillColor(sf::Color(255, 255, 0));
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1);
		shape.setRadius(boidsSize);

		// Adds newly created boid and shape to their respective data structure
		flock.addBoid(b);
		shapes.push_back(shape);

		// New Shape is drawn
		mWindow.draw(shapes[shapes.size()-1]);
	}
}


void QSFMLCanvas::Render()
{
	mWindow.clear();
	
	for (unsigned int i = 0; i < obstacle_shape.size(); i++)
	{
		mWindow.draw(obstacle_shape[i]);
	}
	
	for (unsigned int i = 0; i < target_shape.size(); i++)
	{
		mWindow.draw(target_shape[i]);
	}
	
	
	// Draws all of the Boids out, and applies functions that are needed to update.
	for (unsigned int i = 0; i < shapes.size(); i++)
	{
		mWindow.draw(shapes[i]);
		
// 		cout << "Boid "<< i <<" Coordinates: (" << shapes[i].getPosition().x << ", " << shapes[i].getPosition().y << ")" << endl;
// 		cout << "Boid Code " << i << " Location: (" << flock.getBoid(i).location.x << ", " << flock.getBoid(i).location.y << ")" << endl;
		
		// Matches up the location of the shape to the boid
		shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);
		
		// Calculates the angle where the velocity is pointing so that the triangle turns towards it.
		float theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
		shapes[i].setRotation(theta);
		
		// Prevent boids from moving off the screen through wrapping
		// If boid exits right boundary
		if (shapes[i].getPosition().x > width())
			shapes[i].setPosition(shapes[i].getPosition().x - width(), shapes[i].getPosition().y);
		// If boid exits bottom boundary
		if (shapes[i].getPosition().y > height())
			shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - height());
		// If boid exits left boundary
		if (shapes[i].getPosition().x < 0)
			shapes[i].setPosition(shapes[i].getPosition().x + width(), shapes[i].getPosition().y);
		// If boid exits top boundary
		if (shapes[i].getPosition().y < 0)
			shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + height());
	}
	
	// Applies the three rules to each boid in the flock and changes them accordingly.
	flock.flocking(kSeparation, kAlignment, kCohesion);
	
	mWindow.display();
}
