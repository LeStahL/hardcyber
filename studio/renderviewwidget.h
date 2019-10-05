#ifndef RENDERVIEWWIDGET_H
#define RENDERVIEWWIDGET_H

#include <QOpenGLWidget>


class RenderViewWidget : public QOpenGLWidget
{
public:
	RenderViewWidget(QWidget* parent = nullptr);

protected:
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

private:
	void setup();
};

#endif // RENDERVIEWWIDGET_H
