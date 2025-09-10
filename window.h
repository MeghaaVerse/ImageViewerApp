#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QImage>

class QLabel;
class QSlider;
class QPushButton;

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QWidget *parent=nullptr);

private slots:
    void loadImg();
    void resetSlider();
    void sliderMoved(int val);

private:
    void updateImg();
    QImage changeBrightness(const QImage &img, int diff);

    QLabel *imgLabel;
    QSlider *slider;
    QLabel *brightnessLabel;
    QPushButton *btnLoad;
    QPushButton *btnReset;
    QPushButton *btnSave;

    QImage origImg;
    QImage showImg;
};

#endif
