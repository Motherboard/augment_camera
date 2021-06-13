//
// Created by master on 9/24/20.
//
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/videodev2.h>
#include <exception>
#include "VirtualCamera.hpp"


namespace virt_cam {

    using namespace std;
    using namespace cv;

    VirtualCamera::VirtualCamera(const string & video_out, int width, int height) {
        v4l2_format vid_format;
        memset(&vid_format, 0, sizeof(v4l2_format));
        _frame_size = width * height * 3;

        if ((_fd = open(video_out.c_str(), O_RDWR)) == -1)
            throw runtime_error("Unable to open video output!");

        vid_format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        if (ioctl(_fd, VIDIOC_G_FMT, &vid_format) == -1)
            throw runtime_error(string("Unable to get video format data. Errno: ") + to_string(errno));

        vid_format.fmt.pix.width = width;
        vid_format.fmt.pix.height = height;
        vid_format.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
        vid_format.fmt.pix.sizeimage = _frame_size;
        vid_format.fmt.pix.field = V4L2_FIELD_NONE;

        if (ioctl(_fd, VIDIOC_S_FMT, &vid_format) == -1)
            throw runtime_error(string("Unable to set video format! Errno: ") + to_string(errno));
    }

    VirtualCamera::~VirtualCamera() {
        if (_fd)
            close(_fd);
    }

    void VirtualCamera::writeFrame(const Mat &frame) {
        if (write(_fd, frame.data, _frame_size) == -1)
            throw runtime_error(string("Unable to write to frame to camera. Errno: " + to_string(errno)));
    }

}