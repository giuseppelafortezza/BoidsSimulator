#include <QApplication>
#include "QSFMLCanvas.h"
#include <QFrame>

#include "MainWidget.h"

int main(int argc, char *argv[])
{
	QApplication App(argc, argv);
	// Create the main frame
// 	QFrame* MainFrame = new QFrame;
// 	MainFrame->setWindowTitle("Qt SFML");
// 	MainFrame->show();
// 	// Create a SFML view inside the main frame
// 	QSFMLCanvas* SFMLView = new QSFMLCanvas(MainFrame);
// 	SFMLView->setFixedSize(400,400);
// 	SFMLView->show();
	
	MainWidget* widg = new MainWidget();
	widg->show();
	return App.exec();
}

