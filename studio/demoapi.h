#ifndef DEMOAPI_H
#define DEMOAPI_H

extern "C" {
#include "config_types.h"
}


struct OpenGLSettings;

class DemoApi
{
public:
	static DemoApi api;

public:
    const OpenGLSettings& getOpenGlSettings() const;
	void initializeGL();
	void resizeView(int w, int h);

    void setTimeNow(double now);
    double getTimeNow() const;

    void setTimeStart(double start);
    double getTimeStart() const;

    void setTimeEnd(double end);
    double getTimeEnd() const;

    void renderFrame();

private:
	DemoApi() = default;
};

#endif // DEMOAPI_H
