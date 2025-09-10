#include "window.h"
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QScrollArea>
#include <QStatusBar>
#include <QDebug>

Window::Window(QWidget *parent)
    : QMainWindow(parent),
      imgLabel(new QLabel),
      slider(new QSlider(Qt::Horizontal)),
      brightnessLabel(new QLabel("0")),
      btnLoad(new QPushButton("Load Image")),
      btnReset(new QPushButton("Reset")),
      btnSave(new QPushButton("Save Image"))
{
    imgLabel->setAlignment(Qt::AlignCenter);

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(imgLabel);
    scroll->setWidgetResizable(true);

    slider->setRange(-100,100);
    slider->setValue(0);

    brightnessLabel = new QLabel("0");

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(btnLoad);
    hbox->addWidget(slider);
    hbox->addWidget(brightnessLabel);
    hbox->addWidget(btnReset);
    hbox->addWidget(btnSave);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(scroll);
    vbox->addLayout(hbox);

    QWidget *central = new QWidget;
    central->setLayout(vbox);
    setCentralWidget(central);

    connect(btnLoad,&QPushButton::clicked,this,&Window::loadImg);
    connect(btnReset,&QPushButton::clicked,this,&Window::resetSlider);
    connect(slider,&QSlider::valueChanged,this,&Window::sliderMoved);
    connect(btnSave,&QPushButton::clicked,this,[this](){
        if(showImg.isNull()){
            statusBar()->showMessage("No image to save");
            return;
        }
        QString path = QFileDialog::getSaveFileName(this,"Save Image","","PNG (*.png);;JPEG (*.jpg)");
        if(!path.isEmpty() && showImg.save(path)){
            statusBar()->showMessage("Saved: "+path);
        }

        
    });

    statusBar()->showMessage("Click Load to add new Image");
    
      // default image on startup
        QString defaultPath = QDir::toNativeSeparators("C:/Users/Chandra shekar/Desktop/ImageViewerApp/default.jpg");
        qDebug() << "Default image exists? " << QFile(defaultPath).exists();

        if(QFile(defaultPath).exists()) {
            if(!origImg.load(defaultPath))
                qDebug() << "Failed to load default image!";
            else {
                origImg = origImg.convertToFormat(QImage::Format_ARGB32);
                slider->setValue(0);
                updateImg();
            }
       }


}

void Window::loadImg()
{
    QString file = QFileDialog::getOpenFileName(this,"Open Image","","Images (*.png *.jpg *.jpeg *.bmp)");
    if(file.isEmpty()) return;

    QImage img;
    if(!img.load(file)){
        statusBar()->showMessage("Could not load image");
        return;
    }
    origImg = img.convertToFormat(QImage::Format_ARGB32);
    slider->setValue(0);
    updateImg();
    statusBar()->showMessage("Loaded: "+file);
}

void Window::resetSlider()
{
    slider->setValue(0);
}

void Window::sliderMoved(int val)
{
    brightnessLabel->setText(QString::number(val));
    updateImg();
}

void Window::updateImg()
{
    if(origImg.isNull()){
        imgLabel->setText("No image loaded");
        return;
    }
    int b = slider->value();
    showImg = changeBrightness(origImg,b);
    imgLabel->setPixmap(QPixmap::fromImage(showImg).scaled(
                            imgLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

QImage Window::changeBrightness(const QImage &img, int diff)
{
    if(img.isNull()) return img;
    QImage out = img.copy();

    for(int y=0; y<out.height(); ++y){
        QRgb *line = reinterpret_cast<QRgb*>(out.scanLine(y));
        for(int x=0; x<out.width(); ++x){
            QColor c = QColor::fromRgb(line[x]);
            int r = qBound(0, c.red()+diff, 255);
            int g = qBound(0, c.green()+diff, 255);
            int b = qBound(0, c.blue()+diff, 255);
            line[x] = qRgb(r,g,b);
        }
    }
    return out;
}
