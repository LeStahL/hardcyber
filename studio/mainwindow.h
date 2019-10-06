#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "renderviewwidget.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
public:
	MainWindow();

    void setTimeNow(double timeNow);
    void setTimeRange(double timeStart, double timeEnd);

protected slots:
    void onChangeTimeNowSlider(int timeNow);
    void onChangeTimeNowSpinBox(double timeNow);

private:
    void setControlsTimeNow(double timeNow);
    void setControlsTimeRange(double timeStart, double timeEnd);

private:
	Ui::MainWindow window;
};

#endif // MAINWINDOW_H
