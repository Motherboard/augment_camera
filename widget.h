#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <memory>
#include <functional>
//#include <opencv2/opencv.hpp>

constexpr char BACKGROUNDS_PATH[] = "backgrounds";
constexpr char FOREGROUNDS_PATH[] = "foregrounds";
constexpr char MASKS_PATH[] = "masks";

class QListWidget;
class QLabel;
namespace cv {
    class Mat;
}

namespace Ui {
class Widget;
}

namespace augment {
    class CameraAugment;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void populateListWithImagesFromDir(QListWidget *list, const QDir &dir);
    void addImages(QListWidget *list, const QDir &dir, bool should_scale = false);
    void addImagesScaled(QListWidget *list, const QDir &dir);
    void image_selection_changed(const QString &filename, QLabel * display, std::function<void(const cv::Mat &)> set_img);
    Ui::Widget *ui;
    QDir _background_dir, _foreground_dir, _mask_dir;
    std::unique_ptr<augment::CameraAugment> _camera_augment_ptr;
private slots:
    void on_take_background_picture_clicked();
    void on_add_background_clicked();
    void on_add_foreground_clicked();
    void on_add_mask_clicked();
    void on_mask_list_itemSelectionChanged();
    void on_background_list_itemSelectionChanged();
    void on_foreground_list_itemSelectionChanged();


};

#endif // WIDGET_H
