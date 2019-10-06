#include "mainwindow.h"

#include <QApplication>

class StudioApp : public QApplication
{
public:
    StudioApp(int argc, char* argv[])
        : QApplication(argc, argv)
    {
        // MainWindow opens automatically upon instantiation
    }

private:
    MainWindow mainWindow;
};

int main(int argc, char* argv[])
{
    StudioApp app(argc, argv);
    return app.exec();
}
