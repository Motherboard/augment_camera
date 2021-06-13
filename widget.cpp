#include "widget.h"
#include "tmp/ui_widget.h"
#include "CameraAugment.hpp"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <string>


QImage scale(const QImage &img, int width, int height) {
    float img_to_cam_height_ratio = static_cast<float>(img.height()) / height;
    float img_to_cam_width_ratio = static_cast<float>(img.width()) / width;
    if (img_to_cam_height_ratio < 1 || img_to_cam_width_ratio < 1) {
        if (img_to_cam_height_ratio > img_to_cam_width_ratio)
            return img.scaledToHeight(height);
        else
            return  img.scaledToWidth(width);
    }
    else if (img_to_cam_height_ratio > 1 && img_to_cam_width_ratio > 1) {
        if (img_to_cam_height_ratio > img_to_cam_width_ratio)
            return img.scaledToWidth(width);
        else
            return img.scaledToHeight(height);
    }
    return img;
}


QImage crop(const QImage &img, int width, int height) {
    int width_delta = std::max(0, img.width() - width);
    int height_delta = std::max(0, img.height() - height);
    return img.copy(width_delta / 2, height_delta / 2, width, height);
}


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    _background_dir = QDir(BACKGROUNDS_PATH);
    _foreground_dir = QDir(FOREGROUNDS_PATH);
    _mask_dir = QDir(MASKS_PATH);
    populateListWithImagesFromDir(ui->background_list, _background_dir);
    populateListWithImagesFromDir(ui->foreground_list, _foreground_dir);
    populateListWithImagesFromDir(ui->mask_list, _mask_dir);
    _camera_augment_ptr = std::make_unique<augment::CameraAugment>(
            "/home/master/projects/augment_camera/opencv_face_detector.pbtxt",
            "/home/master/projects/augment_camera/opencv_face_detector_uint8.pb",
            "/home/master/Videos/4K Video Downloader/HOW TO VLOG LIKE CASEY NEISTAT by CASEY NEISTAT.mp4",
            "/dev/video0"
            );

}

void Widget::populateListWithImagesFromDir(QListWidget *list, const QDir &dir) {
    if (dir.exists()) {
        for (const auto & file: dir.entryList({ "*.png", "*.jpg", "*.gif", "*.bmp", "*.tif", "*.jpeg", "*.tiff"}))
            list->addItem(file);
    }
    else {
        if (!dir.mkdir(dir.absolutePath())) {
            QMessageBox::information(this, QString("failed"), "Failed creating " + dir.absolutePath());
        }
    }
}

void Widget::on_add_background_clicked() {
    addImagesScaled(ui->background_list, _background_dir);
}

void Widget::on_add_foreground_clicked() {
    addImagesScaled(ui->foreground_list, _foreground_dir);
}

void Widget::on_add_mask_clicked() {
    addImages(ui->mask_list, _mask_dir);
}

void Widget::on_mask_list_itemSelectionChanged() {
    image_selection_changed(
            _mask_dir.absoluteFilePath(ui->mask_list->item(ui->mask_list->currentRow())->text()),
            ui->mask_preview,
            [&](const cv::Mat &img)->void { _camera_augment_ptr->set_face_mask(img); }
    );
}

void Widget::on_background_list_itemSelectionChanged() {
    image_selection_changed(
            _background_dir.absoluteFilePath(ui->background_list->item(ui->background_list->currentRow())->text()),
            ui->background_preview,
            [&](const cv::Mat &img)->void { _camera_augment_ptr->set_background(img); }
            );
}

void Widget::on_foreground_list_itemSelectionChanged() {
    image_selection_changed(
            _foreground_dir.absoluteFilePath(ui->foreground_list->item(ui->foreground_list->currentRow())->text()),
            ui->foreground_preview,
            [&](const cv::Mat &img)->void { _camera_augment_ptr->set_foreground(img); }
    );
}

void Widget::image_selection_changed(const QString &filename, QLabel * display, std::function<void( const cv::Mat &)> set_img)
{
    QImage img(filename);
    if (img.depth() != 32) {
        img = img.convertToFormat(QImage::Format_RGB32);
    }
    display->setPixmap(QPixmap::fromImage(img));
    std::cout << "stride: " << img.bytesPerLine() << ", bits per pixel: " << img.depth() << std::endl;
    cv::Mat mat(cv::Size(img.width(), img.height()), CV_8UC4, img.bits(), img.bytesPerLine());
    set_img(mat);
}

void Widget::addImages(QListWidget *list, const QDir &dir, bool should_scale) {
    auto files = QFileDialog::getOpenFileNames(this, "Select images", "", "Images (*.png *.jpg *.gif *.bmp *.tif *.jpeg *.tiff)");
    for (const auto &file: files) {
        QImage selected_img(file);
        if (selected_img.height() == 0) {
            QMessageBox::warning(this, "Failed reading image", "Failed reading from " + QFileInfo(file).fileName());
            continue;
        }
        if (should_scale)
            selected_img = crop(
                    scale(selected_img, _camera_augment_ptr->width(), _camera_augment_ptr->height()),
                    _camera_augment_ptr->width(), _camera_augment_ptr->height()
                    );
        if (!selected_img.save(dir.absoluteFilePath(QFileInfo(file).fileName()))) {
            QMessageBox::warning(this, "Failed saving image",
                                 "Failed saving to " + QFileInfo(file).fileName() + " to " +
                                 dir.absoluteFilePath(QFileInfo(file).fileName()) + " in " + dir.absoluteFilePath(""));
            continue;
        }
        list->addItem(QFileInfo(file).fileName());
    }
}

void Widget::addImagesScaled(QListWidget *list, const QDir &dir) {
    addImages(list, dir, true);
}

void Widget::on_take_background_picture_clicked() {
    cv::Mat frame = _camera_augment_ptr->untouched_current_frame();
    _camera_augment_ptr->set_real_background(frame);
}

Widget::~Widget()
{
    _camera_augment_ptr->stop();
    delete ui;
}
