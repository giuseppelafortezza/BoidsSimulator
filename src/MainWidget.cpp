#include "MainWidget.h"

#include "QHBoxLayout"
#include "QVBoxLayout"

#include "Boid.h"

MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
	, mCanvas(Q_NULLPTR)
	, mSeparationSlider(Q_NULLPTR)
	, mAlignmentSlider(Q_NULLPTR)
	, mCohesionSlider(Q_NULLPTR)
	, mStartButton(Q_NULLPTR)
	, mResetButton(Q_NULLPTR)
	, mDesiredSeparation(Q_NULLPTR)
	, mFieldOfVisionAlignment(Q_NULLPTR)
	, mFieldOfVisionCohesion(Q_NULLPTR)
{
	mCanvas = new QSFMLCanvas();
	mCanvas->setFixedSize(window_width,window_height);
	
	
	mStartButton = new QPushButton("START");
	mStartButton->setCheckable(true);
	mResetButton = new QPushButton("RESET");
	
	mDesiredSeparation = new QTextEdit("100");
	mDesiredSeparation->setToolTip("Desired distance between boids");
	mFieldOfVisionAlignment = new QTextEdit("50");
	mFieldOfVisionAlignment->setToolTip("Field of view for alignment");
	mFieldOfVisionCohesion = new QTextEdit("1000");
	mFieldOfVisionCohesion->setToolTip("Field of view for cohesion");
	
	mSeparationSlider = new QSlider(Qt::Horizontal);
	mSeparationSlider->setMaximum(40);
	mSeparationSlider->setMinimum(0);
	mSeparationSlider->setValue(15);
	mSeparationSlider->setTickPosition(QSlider::TicksBothSides);
	mAlignmentSlider = new QSlider(Qt::Horizontal);
	mAlignmentSlider->setMaximum(5);
	mAlignmentSlider->setMinimum(0);
	mAlignmentSlider->setValue(3);
	mAlignmentSlider->setTickPosition(QSlider::TicksBothSides);
	mCohesionSlider = new QSlider(Qt::Horizontal);
	mCohesionSlider->setMaximum(10);
	mCohesionSlider->setMinimum(0);
	mCohesionSlider->setValue(1);
	mCohesionSlider->setTickPosition(QSlider::TicksBothSides);
	
	QObject::connect(mSeparationSlider, SIGNAL(sliderMoved(int)), mCanvas, SLOT(updateSeparation(int)));
	QObject::connect(mAlignmentSlider, SIGNAL(sliderMoved(int)), mCanvas, SLOT(updateAlignment(int)));
	QObject::connect(mCohesionSlider, SIGNAL(sliderMoved(int)), mCanvas, SLOT(updateCohesion(int)));
	
	QObject::connect(mStartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
	QObject::connect(mResetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
	QObject::connect(mStartButton, SIGNAL(clicked(bool)), mCanvas, SLOT(onStart(bool)));
	QObject::connect(mResetButton, SIGNAL(clicked()), mCanvas, SLOT(onReset()));
	
	QHBoxLayout* lHLayout = new QHBoxLayout();
	QVBoxLayout* lVLayout = new QVBoxLayout();
	lVLayout->addWidget(mStartButton);
	//lVLayout->addWidget(mResetButton);
// 	lVLayout->addSpacing(30);
// 	lVLayout->addWidget(mDesiredSeparation);
// 	lVLayout->addWidget(mFieldOfVisionAlignment);
// 	lVLayout->addWidget(mFieldOfVisionCohesion);
	lVLayout->addSpacing(80);
	lVLayout->addWidget(new QLabel("Separation"));
	lVLayout->addWidget(mSeparationSlider);
	lVLayout->addSpacing(30);
	lVLayout->addWidget(new QLabel("Alignment"));
	lVLayout->addWidget(mAlignmentSlider);
	lVLayout->addSpacing(30);
	lVLayout->addWidget(new QLabel("Cohesion"));
	lVLayout->addWidget(mCohesionSlider);
	lHLayout->addWidget(mCanvas);
	lHLayout->addLayout(lVLayout);
	setLayout(lHLayout);
}


MainWidget::~MainWidget()
{
	if(Q_NULLPTR != mStartButton)
	{
		QObject::disconnect(mStartButton, SIGNAL(clicked(bool)), mCanvas, SLOT(onStart(bool)));
		QObject::disconnect(mStartButton, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
		delete mStartButton;
		mStartButton = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mResetButton)
	{
		QObject::disconnect(mResetButton, SIGNAL(clicked()), mCanvas, SLOT(onReset()));
		QObject::disconnect(mResetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
		delete mResetButton;
		mResetButton = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mDesiredSeparation)
	{
		delete mDesiredSeparation;
		mDesiredSeparation = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mFieldOfVisionAlignment)
	{
		delete mFieldOfVisionAlignment;
		mFieldOfVisionAlignment = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mFieldOfVisionCohesion)
	{
		delete mFieldOfVisionCohesion;
		mFieldOfVisionCohesion = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mSeparationSlider)
	{
		QObject::disconnect(mSeparationSlider, SIGNAL(sliderMoved(int)), mCanvas, SLOT(updateSeparation(int)));
		delete mSeparationSlider;
		mSeparationSlider = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mAlignmentSlider)
	{
		QObject::disconnect(mAlignmentSlider, SIGNAL(sliderMoved(int)), mCanvas, SLOT(updateAlignment(int)));
		delete mAlignmentSlider;
		mAlignmentSlider = Q_NULLPTR;
	}
	
	if(Q_NULLPTR != mCohesionSlider)
	{
		QObject::disconnect(mCohesionSlider, SIGNAL(sliderMoved(int)), mCanvas, SLOT(updateCohesion(int)));
		delete mCohesionSlider;
		mCohesionSlider = Q_NULLPTR;
	}
}


void MainWidget::onStartButtonClicked()
{
	if(true == mStartButton->isChecked())
	{
		mStartButton->setText("RUNNING");
	}
	else
	{
		mStartButton->setText("START");
	}
}


void MainWidget::onResetButtonClicked()
{
	mStartButton->setChecked(false);
	mStartButton->setText("START");
}
