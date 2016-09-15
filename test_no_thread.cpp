/*----------------------------------------------------------------------------
Copyright (c) 2015 Cipherstone Technologies AB
This code is the property of Cipherstone Technologies AB and may not be
redistributed in any form without prior written permission from Cipherstone
Technologies AB.
----------------------------------------------------------------------------*/
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

//******************************************************************************
// Module constants
//******************************************************************************

//******************************************************************************
// Module variables
//******************************************************************************
static const int w = 1920;
static const int h = 1200;
static const Size size(w, h);
static const std::string dstFilename("/tmp/no_thread.avi");
static const int fps = 60;
static const bool isColor = false;
static const float duration_s = 3;
static const int nbFrames = duration_s * fps;

//******************************************************************************
// Function prototypes
//******************************************************************************
Mat generateFrame(Size s);

//******************************************************************************
// Function definitions
//******************************************************************************

//******************************************************************************
// Internal functions
//******************************************************************************
int main()
{
    VideoWriter vw;
    Mat frame;

    vw.open(dstFilename, CV_FOURCC(0, 0, 0, 0), fps, size, isColor);

    for (int i = 0; i < nbFrames; ++i) {
        frame = generateFrame(size);
        vw.write(frame);
    }
    // vw is closed and released in its destructor.
    return 0;
}

Mat generateFrame(Size s)
{
    Mat frame(s, CV_8UC1);
    randu(frame, 0, 255);
    return frame;
}
