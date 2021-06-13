//
// Created by master on 9/24/20.
//

#ifndef AUGMENT_CAMERA_SIMPLEFACEDETECTOR_HPP
#define AUGMENT_CAMERA_SIMPLEFACEDETECTOR_HPP

#include <opencv2/opencv.hpp>

namespace augment {

    constexpr float CONFIDENCE_THERSHOLD = 0.5;


    class SimpleFaceDetector {
        int _width, _height;
        cv::Rect _roi;
        cv::dnn::Net _face_detector;
        cv::Mat _detection;
        cv::Rect getFaceFromDetection(cv::Mat detection) {
            cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
            for (int i = 0; i < detectionMat.rows; i++) {
                float confidence = detectionMat.at<float>(i, 2);
                float x1 = detectionMat.at<float>(i, 3) * _roi.width;
                float y1 = detectionMat.at<float>(i, 4) * _roi.height;
                float x2 = detectionMat.at<float>(i, 5) * _roi.width;
                float y2 = detectionMat.at<float>(i, 6) * _roi.height;
                float ratio = (x2 - x1) / (y2 - y1);
                if ((2 > ratio) && (ratio > 0.5) && (confidence > CONFIDENCE_THERSHOLD)) {
                    int x = x1 + _roi.x;
                    int y = y1 + _roi.y;
                    int width = x2 - x1;
                    int height = y2 - y1;
                    if (x < 0) {
                        width += x;
                        x = 0;
                    }
                    if (y < 0) {
                        height += y;
                        y = 0;
                    }
                    if (x + width >= _width)
                        width -= x + width - _width;
                    if (y + height >= _height)
                        height -= y + height - _height;
                    return cv::Rect(x, y, width, height);
                }
            }
            return cv::Rect(0, 0, 0, 0);
        }
    public:
        explicit SimpleFaceDetector(const std::string & net_config, const std::string & model, int width, int height)
            : _roi((width - height) / 2, 0, height, height), _height(height), _width(width)
        {
            _face_detector = cv::dnn::readNetFromTensorflow(model, net_config);
        }

        ~SimpleFaceDetector() = default;

        cv::Rect get_face(const cv::Mat &frame) {
            _face_detector.setInput(
                    cv::dnn::blobFromImage(frame(_roi), 1, cv::Size(150, 150), cv::Scalar(104, 177, 123, 0), false, false), "data");
            //auto start = chrono::high_resolution_clock::now();
            _detection = _face_detector.forward("detection_out");
            //auto end = chrono::high_resolution_clock::now();
            //cout << "forward took " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
            return getFaceFromDetection(_detection);
        }
    };
}

#endif //AUGMENT_CAMERA_SIMPLEFACEDETECTOR_HPP
