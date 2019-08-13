#include "crow_all.h"
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/video.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/face.hpp"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <thread>         // std::thread, std::this_thread::yield
#include <atomic>
#include <string>

using namespace std;
using namespace cv;
/*
int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
*/

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app,"/hell")
    ([](){
        VideoCapture capture(0);
	Mat frame;

        while(true){
		capture >> frame;
                vector<uchar> buf;
                imencode(".jpg", frame, buf);
                string s(buf.begin(), buf.end());
		std::ostringstream os;
		os << s;
		return crow::response{os.str()};
	}

	return crow::response("");
    });

    CROW_ROUTE(app,"/hello/<int>")
    ([](int count){
        if (count > 100)
            return crow::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
    });

    CROW_ROUTE(app, "/")
    ([]{
        char name[256];
        gethostname(name, 256);
        crow::mustache::context x;
        x["servername"] = name;
	
        auto page = crow::mustache::load("ws.html");
        return page.render(x);
     });

    app.port(5000)
        .multithreaded()
        .run();
}
