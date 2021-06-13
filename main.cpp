#include <iostream>
#include "opencv2/opencv.hpp"
#include <chrono>
#include <exception>
#include "SimpleFaceDetector.hpp"
#include "VirtualCamera.hpp"

using namespace cv;
using namespace std;


//void cascade_detection_vs_deep_example() {
//    auto video = VideoCapture("/home/master/Videos/4K Video Downloader/HOW TO VLOG LIKE CASEY NEISTAT by CASEY NEISTAT.mp4");
//    constexpr auto model = "/home/master/projects/augment_camera/opencv_face_detector_uint8.pb";
//    constexpr auto net_config = "/home/master/projects/augment_camera/opencv_face_detector.pbtxt";
//    auto point_detector = ORB::create(50, 1, 1);
//    auto cascade_face_detector = CascadeClassifier("/home/master/projects/augment_camera/haarcascade_frontalface_alt2.xml");
//    auto _face_detector = dnn::readNetFromTensorflow(model, net_config);
//    Rect _roi((WIDTH - HEIGHT) / 2, 0, HEIGHT, HEIGHT);
//    Mat frame, frame_gray;
//    namedWindow("face");
//    vector<Rect> faces;
//    while (video.read(frame)) {
//        cvtColor( frame(_roi), frame_gray, COLOR_BGR2GRAY );
//        equalizeHist( frame_gray, frame_gray );
//        //cout << frame.cols << ", " << frame.rows << endl;
//        _face_detector.setInput(dnn::blobFromImage(frame(_roi), 1, Size(150, 150), Scalar(104, 177, 123, 0), false, false), "data");
//        auto start = chrono::high_resolution_clock::now();
//        auto detection = _face_detector.forward("detection_out");
//        auto end = chrono::high_resolution_clock::now();
//        cout << "forward took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
//        rectangle(frame, getFaceFromDetection(detection, _roi), Scalar(0, 255, 0),2, 4);
//        start = chrono::high_resolution_clock::now();
//        cascade_face_detector.detectMultiScale(frame_gray, faces);
//        end = chrono::high_resolution_clock::now();
//        cout << "cascade took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
//        if (!faces.empty())
//            rectangle(frame, Rect(faces[0].x + _roi.x, faces[0].y + _roi.y, faces[0].width, faces[0].height), Scalar(255, 0, 0), 2, 4);
//        imshow("face", frame);
//        waitKey(0);
//    }
//}


//bool is_rect_close_enough(const Rect &r1, const Rect &r2) {
//    return  (static_cast<float>(abs(r1.x - r2.x))/max(r1.width, r2.width) < MAX_MOVEMENT_THERSHOLD) && (static_cast<float>(abs(r1.y - r2.y))/max(r1.height, r2.height) < MAX_MOVEMENT_THERSHOLD);
//}
//
//
//
//class VideoFaceDetector {
//    static constexpr char model[] = "/home/master/projects/augment_camera/opencv_face_detector_uint8.pb";
//    static constexpr char net_config[] = "/home/master/projects/augment_camera/opencv_face_detector.pbtxt";
//    Ptr<ORB> point_detector = ORB::create(50, 1, 1);
//    BFMatcher matcher;
//    dnn::Net _face_detector = dnn::readNetFromTensorflow(model, net_config);
//    Rect _roi = Rect((WIDTH - HEIGHT) / 2, 0, HEIGHT, HEIGHT), prev_face_detection, detected_face_rect;
//    Mat frame_gray;
//    unsigned int num_consecutive_face_detections = 0;
//    vector<KeyPoint> face_keypoints, prev_face_keypoints;
//    Mat face_descriptors, prev_face_descriptors;
//public:
//    VideoFaceDetector() = default;
//    ~VideoFaceDetector() = default;
//    Rect get_face(Mat frame) {
//        prev_face_detection = detected_face_rect;
//        if ((num_consecutive_face_detections < CONSECUTIVE_DETECTIONS_THRESHOLD)) {
//            _face_detector.setInput(
//                    dnn::blobFromImage(frame(_roi), 1, Size(150, 150), Scalar(104, 177, 123, 0), false, false), "data");
//            auto start = chrono::high_resolution_clock::now();
//            auto detection = _face_detector.forward("detection_out");
//            auto end = chrono::high_resolution_clock::now();
//            cout << "forward took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
//            detected_face_rect = getFaceFromDetection(detection, _roi);
//            if ((detected_face_rect.width > 0) && (prev_face_detection.width > 0) &&
//                is_rect_close_enough(prev_face_detection, detected_face_rect))
//                num_consecutive_face_detections += 1;
//            else
//                num_consecutive_face_detections = 0;
//        }
//        else {
//            cvtColor( frame(detected_face_rect), frame_gray, COLOR_BGR2GRAY );
//            equalizeHist( frame_gray, frame_gray );
//            if (prev_face_keypoints.empty()) {
//                point_detector->detectAndCompute(frame_gray, noArray(), face_keypoints, face_descriptors);
//                return Rect(-1, -1, -1, -1);
//            }
//            else {
//                point_detector->detectAndCompute(frame_gray, noArray(), face_keypoints, face_descriptors);
//                vector<DMatch> matches;
//                matcher.match(face_descriptors, prev_face_descriptors, matches);
//                drawKeypoints(frame, face_keypoints, frame, Scalar(0, 0, 255));
//                drawKeypoints(frame, prev_face_keypoints, frame, Scalar(255, 0, 255));
//                const float ratio_thresh = 0.75f;
//                std::vector<Point2f> current_points;
//                std::vector<Point2f> prev_points;
//                for ( const auto & match : matches)
//                {
//                    //-- Get the keypoints from the good matches
//                    current_points.push_back( face_keypoints[ match.queryIdx ].pt );
//                    prev_points.push_back( prev_face_keypoints[ match.trainIdx ].pt );
//                }
//                auto transform = findHomography(prev_points, current_points, RANSAC);
//                if (determinant(transform) < 0.1) {
//                    num_consecutive_face_detections = 0;
//                    face_keypoints.clear();
//                    return Rect(-1, -1, -1, -1);
//                }
//                vector<Point> roi_points = {
//                        {detected_face_rect.x,             detected_face_rect.y},
//                        {detected_face_rect.x + detected_face_rect.width, detected_face_rect.y},
//                        {detected_face_rect.x + detected_face_rect.width, detected_face_rect.y + detected_face_rect.height},
//                        {detected_face_rect.x,             detected_face_rect.y + detected_face_rect.height}
//                };
//                cv::transform(roi_points, roi_points, transform);
//                detected_face_rect = boundingRect(roi_points);
//            }
//            if ((prev_face_keypoints.size() < MIN_FACE_KEYPOINTS) || (face_keypoints.size() < MIN_FACE_KEYPOINTS)) {
//                num_consecutive_face_detections = 0;
//                auto detection = _face_detector.forward("detection_out");
//                detected_face_rect = getFaceFromDetection(detection, _roi);
//                face_keypoints.clear();
//                return Rect(-1, -1, -1, -1);
//            }
//        }
//        return detected_face_rect;
//    }
//};





//int main() {
//
////    std::cout <<
////              "Using OpenCV version " << CV_VERSION << "\n" << std::endl;
////
////    std::cout << getBuildInformation();
//
//
//    auto video = VideoCapture("/home/master/Videos/4K Video Downloader/HOW TO VLOG LIKE CASEY NEISTAT by CASEY NEISTAT.mp4");
//    namedWindow("face");
//    Mat frame;
//    augment::SimpleFaceDetector faceDetector;
//    virt_cam::VirtualCamera outCamera;
//    while (video.read(frame)) {
//        //cout << frame.cols << ", " << frame.rows << endl;
//        auto face_rect = faceDetector.get_face(frame);
//        rectangle(frame, face_rect, Scalar(0, 255, 0), 2, 4);
//        outCamera.writeFrame(frame);
//        //imshow("face", frame);
//        //waitKey(0);
//    }
//    return 0;
//}

#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return QApplication::exec();
}
