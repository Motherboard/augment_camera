//
// Created by master on 9/24/20.
//

#include "CameraAugment.hpp"
#include <iostream>
#include <opencv2/face.hpp>

using namespace std;
using namespace cv;

namespace augment {
    CameraAugment::CameraAugment(const string & face_detector_net_config, const string & face_detector_weights, const string & real_video_path, const std::string & virt_cam_name)
    {
        _video_capture = VideoCapture(real_video_path);
        Mat frame;
        _video_capture.read(frame);
        _width = frame.cols;
        _height = frame.rows;
        _face_detector_ptr = std::make_unique<SimpleFaceDetector>(face_detector_net_config, face_detector_weights, _width, _height);
        _face_landmarks_ptr = cv::face::createFacemarkLBF();
        _face_landmarks_ptr->loadModel("/home/master/projects/augment_camera/lbfmodel.yaml");
        _virtual_camera_ptr = make_unique<virt_cam::VirtualCamera>(virt_cam_name, _width, _height);
        _background_subtractor = cv::createBackgroundSubtractorMOG2(10, 16);
        is_running = true;
        _run_thread = thread([this]{ run(); });
    }

    CameraAugment::~CameraAugment() {
        _run_thread.join();
    }

    void CameraAugment::run() {
        Mat frame;
        while (_video_capture.read(_original_frame) && is_running) {
            _original_frame.copyTo(frame);
            augment(frame);
            _virtual_camera_ptr->writeFrame(frame);
        }
    }

    void CameraAugment::augment(Mat & frame) {
        scoped_lock lock(_mutex);
        Rect face_rect;
        if (!_face_mask.empty())
            face_rect = _face_detector_ptr->get_face(frame);
        //rectangle(frame, face_rect, Scalar(0, 255, 0), 2, 4);
        if (!_background.empty() && !_real_background.empty()) {
            Mat diff;
            //_background_subtractor->apply(frame, diff);

            Mat hsv_frame, hsv_frame_channels[3], hue_diff, sat_diff;
            cvtColor(frame, hsv_frame, COLOR_RGB2HSV);
            split(hsv_frame, hsv_frame_channels);
            absdiff(_real_background, hsv_frame, diff);
            cv::inRange(diff, Scalar(30, 20, 0), Scalar(255, 255, 255), diff);

            //morphologyEx(diff, diff, MORPH_OPEN, getStructuringElement(MORPH_RECT, {3, 3}));
            //morphologyEx(diff, diff, MORPH_CLOSE, getStructuringElement(MORPH_RECT, {5, 5}), {-1, -1}, 4);
            diff.convertTo(diff, frame.type());
            Mat channels[] = {diff*255, diff*255, diff*255};
            cv::merge(channels, 3, hue_diff);
            bitwise_and(frame, hue_diff, frame);
            add(frame, _background, frame, 1 - diff);
            //cout << frame.depth() << endl;
            //diff.convertTo(frame, CV_8UC3, 255);
            //frame = diff;
            //frame = diff*255; //frame * (Scalar::all(1) - diff) + diff * _background;
        }
        if (!_face_mask.empty() && face_rect.area() > 0) {
            Mat tmp, landmarks;

            _face_landmarks_ptr->fit(frame, faces, landmarks);
            resize(_face_mask, tmp, face_rect.size());
            vector<Mat> channels;
            split(tmp, channels);
            Mat rgb_tmp;
            merge(channels.data(), 3, rgb_tmp);
            rgb_tmp.copyTo(frame(face_rect), channels[3]);
        }
        if (!_foreground.empty()) {
            vector<Mat> channels;
            split(_foreground, channels);
            Mat rgb_foreground;
            merge(channels.data(), 3, rgb_foreground);
            rgb_foreground.copyTo(frame, channels[3]);
        }
    }

    void CameraAugment::set_background(const cv::Mat & background) {
        scoped_lock lock(_mutex);
        if (background.empty()) {
            _background.release();
            return;
        }
        resize(background, _background, Size(_width, _height));
        if (_background.channels() == 4)
            cvtColor(_background, _background, COLOR_RGBA2RGB);

    }
    void CameraAugment::set_foreground(const cv::Mat & foreground) {
        scoped_lock lock(_mutex);
        if (foreground.empty()) {
            _foreground.release();
            return;
        }
        resize(foreground, _foreground, Size(_width, _height));
    }
    void CameraAugment::set_face_mask(const cv::Mat & face_mask) {
        scoped_lock lock(_mutex);
        if (face_mask.empty()) {
            _face_mask.release();
            return;
        }
        face_mask.copyTo(_face_mask);
    }
    void CameraAugment::set_real_background(const cv::Mat & background) {
        scoped_lock lock(_mutex);
        resize(background, _real_background, Size(_width, _height));
        cvtColor(_real_background, _real_background, COLOR_RGB2HSV);
        //Mat hsv_channels[3];
        //split(_real_background, hsv_channels);
        //_real_background = hsv_channels[1];
    }
    void CameraAugment::stop() {
        is_running = false;
    }
    int CameraAugment::width() {
        return _width;
    }
    int CameraAugment::height() {
        return _height;
    }
    Mat CameraAugment::untouched_current_frame() {
        Mat frame_copy;
        copyTo(_original_frame, frame_copy, noArray());
        return frame_copy;
    }
}