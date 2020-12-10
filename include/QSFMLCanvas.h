#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H
#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>

#include <iostream>
#include "Flock.h"
#include "Boid.h"
#include "Pvector.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "QSFMLCanvas.h"


class QSFMLCanvas : public QWidget
{
Q_OBJECT
public:
	explicit QSFMLCanvas(QWidget* parent = Q_NULLPTR);
	virtual ~QSFMLCanvas();
	
	virtual void showEvent(QShowEvent*);
	virtual QPaintEngine* paintEngine() const;
	virtual void paintEvent(QPaintEvent*);
	
private Q_SLOTS:
	void updateSeparation(int k);
	void updateAlignment(int k);
	void updateCohesion(int k);
	void onReset();
	void onStart(bool enabled);
	void updateParameters(int desiredDistance, int fowAlignment, int fowCohesion);
	
private:
	sf::RenderWindow mWindow;
	
	double kSeparation;
	double kAlignment;
	double kCohesion;
	
	int kDesiredDistance;
	int kFowAlignment;
	int kFowCohesion;
	
	Flock flock;
	float boidsSize;
	vector<sf::CircleShape> shapes;
	vector<sf::CircleShape> obstacle_shape;
	vector<sf::CircleShape> target_shape;
	
	void Render();
	void HandleInput();
	
	QTimer myTimer;
	bool   myInitialized;
	bool mEnabled;
};
#endif // QSMLCANVAS_H
