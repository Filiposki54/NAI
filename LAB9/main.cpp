#include <opencv2/aruco.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main()
{
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_4X4_50);
    Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();

    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        return -1;
    }

    while (true)
    {
        Mat frame;
        capture >> frame;
        if (frame.empty())
        {
            break;
        }
        vector<vector<Point2f>> corners;
        vector<int> ids;
        aruco::detectMarkers(frame, dictionary, corners, ids, parameters);

        if (corners.size() >= 2)
        {
            Point2f point1 = corners[0][0];
            Point2f point2 = corners[1][0];
            float distance = sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));

            cout << "Odleglosc:" << distance << endl;
        }
        aruco::drawDetectedMarkers(frame,corners,ids);
        imshow("image",frame);
        char key =(char) waitKey(1);
        if(key == 'q'){
            break;
        }
    }

    return 0;
}