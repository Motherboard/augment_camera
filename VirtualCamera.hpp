//
// Created by master on 9/24/20.
//

#ifndef AUGMENT_CAMERA_VIRTUALCAMERA_HPP
#define AUGMENT_CAMERA_VIRTUALCAMERA_HPP


#include <string>
#include <opencv2/opencv.hpp>

namespace virt_cam {

    //constexpr char VIDEO_OUT[] = "/dev/video0"; // V4L2 Loopack


    class VirtualCamera {
        int _fd = 0;
        size_t _frame_size;
    public:
        explicit VirtualCamera(const std::string & video_out, int width, int height);

        ~VirtualCamera();

        void writeFrame(const cv::Mat &frame);
    };
}


#endif //AUGMENT_CAMERA_VIRTUALCAMERA_HPP
