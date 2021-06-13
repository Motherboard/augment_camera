//
// Created by master on 9/24/20.
//

#ifndef AUGMENT_CAMERA_CAMERAAUGMENT_HPP
#define AUGMENT_CAMERA_CAMERAAUGMENT_HPP

#include <string>
#include <thread>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <memory>
#include <atomic>
#include "VirtualCamera.hpp"
#include "SimpleFaceDetector.hpp"

namespace augment {

    class CameraAugment {
        std::unique_ptr<SimpleFaceDetector> _face_detector_ptr;
        std::unique_ptr<virt_cam::VirtualCamera> _virtual_camera_ptr;
        cv::VideoCapture _video_capture;
        cv::Mat _real_background, _background, _foreground, _face_mask, _original_frame;
        std::thread _run_thread;
        std::mutex _mutex;
        std::atomic_bool is_running = false;
        int _width, _height;
        cv::Ptr<cv::BackgroundSubtractor> _background_subtractor;
        cv::Ptr<cv::face::Facemark> _face_landmarks_ptr;
        void run();
        void augment(cv::Mat & frame);
    public:
        CameraAugment(const std::string & face_detector_net_config, const std::string & face_detector_weights, const std::string & real_video_path, const std::string & virtual_cam_name);
        ~CameraAugment();
        void set_background(const cv::Mat & background);
        void set_foreground(const cv::Mat & foreground);
        void set_face_mask(const cv::Mat & face_mask);
        void set_real_background(const cv::Mat & background);
        int width();
        int height();
        void stop();
        cv::Mat untouched_current_frame();
    };
}


#endif //AUGMENT_CAMERA_CAMERAAUGMENT_HPP
