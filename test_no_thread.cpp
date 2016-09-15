/*----------------------------------------------------------------------------
Demonstrator for memory leak in OpenCV video writer.
----------------------------------------------------------------------------*/
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

//******************************************************************************
// Module variables
//******************************************************************************
static const Size size(200, 100);
static const std::string dstFilename("/tmp/no_thread.avi");
static const int fps = 60;
static const bool isColor = false;
static const float duration_s = 3;
static const int nbFrames = duration_s * fps;

//******************************************************************************
// Function prototypes
//******************************************************************************
static Mat generateFrame(Size s);

//******************************************************************************
// Function definitions
//******************************************************************************
int main()
{
    std::cout << "No thread. OpenCV version: " << CV_VERSION << std::endl;

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

//******************************************************************************
// Internal functions
//******************************************************************************
static Mat generateFrame(Size s)
{
    Mat frame(s, CV_8UC1);
    randu(frame, 0, 255);
    return frame;
}
