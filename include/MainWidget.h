#ifndef MAIN_WIDGET_H_
#define MAIN_WIDGET_H_

#include <QWidget>

#include <QLabel>
#include <QSlider>
#include "QSFMLCanvas.h"
#include <QPushButton>
#include <QTextEdit>

class MainWidget : public QWidget
{
	Q_OBJECT
public:
	explicit MainWidget(QWidget* parent = Q_NULLPTR);
	virtual ~MainWidget();
	
private Q_SLOTS:
	void onStartButtonClicked();
	void onResetButtonClicked();
	
private:
	QSFMLCanvas* 	mCanvas;
	QSlider*		mSeparationSlider;
	QSlider*		mAlignmentSlider;
	QSlider*		mCohesionSlider;
	QPushButton*	mStartButton;
	QPushButton*	mResetButton;
	
	QTextEdit*		mDesiredSeparation;
	QTextEdit*		mFieldOfVisionAlignment;
	QTextEdit*		mFieldOfVisionCohesion;
};
#endif // QSMLCANVAS_H
