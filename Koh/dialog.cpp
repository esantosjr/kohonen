#include "dialog.h"
#include "ui_dialog.h"
#include "QPushButton"
#include "dialog2.h"
#include "dialog3.h"
#include "network.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    ui->spinBox->setValue(ui->horizontalSlider->value());
    ui->pushButton_2->setEnabled(false);
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::generateMap() {
    if(ui->dim4->isChecked() == true)
        koh = new Kohonen(2, 2, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else if(ui->dim16->isChecked() == true)
        koh = new Kohonen(4, 4, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else if(ui->dim64->isChecked() == true)
        koh = new Kohonen(8, 8, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else if(ui->dim100->isChecked() == true)
        koh = new Kohonen(10, 10, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else if(ui->dim256->isChecked() == true)
        koh = new Kohonen(16, 16, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else if(ui->dim400->isChecked() == true)
        koh = new Kohonen(20, 20, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else if(ui->dim1600->isChecked() == true)
        koh = new Kohonen(40, 40, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
    else
        koh = new Kohonen(60, 60, 3, ui->horizontalSlider->value(), ui->doubleSpinBox->value());
}

void Dialog::showMap(Network net, int sizeInputVector, int type, bool classification, int classPos) { // type = 0 -> mapa vem do botão gerar. type = 1 -> mapa vem do botão auto-organizar.
    vector<vector<int> > colors;
    vector<double> vec;
    vector<int> temp;
    int size = net.getSize();
    for(int i = 0; i < size; i++) {
        vec = net.get_SOM()[i].get_weights();
        for(int k = 0; k < sizeInputVector; k++) {
            temp.push_back(vec[k] * 255);
        }
        colors.push_back(temp);
        temp.clear();
    }

    Mat img(480, 480, CV_64F);
    int cont = 0;
    int k = 0;
    int l = 0;
    int var = 0;
    int nodeSize = sqrt(480 * 480 / size);
    for(int i = 0; i < img.rows; i+=480/sqrt(size)) {
        for(int j = 0; j < img.cols; j+=480/sqrt(size)) {
            k = j; l = i;
            while(var < (nodeSize + j)) {
                img.at<Vec3b>(l, k)[0] = colors[cont][0];
                img.at<Vec3b>(l, k)[1] = colors[cont][1];
                img.at<Vec3b>(l, k)[2] = colors[cont][2];
                k++;
                if(k >= (nodeSize + j)) {
                    l++;
                    var++;
                    k = j;
                }
            }
            cont++;
        }
        var = 0;
    }

    if(type == 0) {
        QImage qimg((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        ui->image_label->setPixmap(QPixmap::fromImage(qimg));
    } else {
        QImage qimg((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);

        if(classification) {
            int x = koh->get_pSOM().get_SOM()[classPos].get_position_x();
            int y = koh->get_pSOM().get_SOM()[classPos].get_position_y();
            vector<double> cols = koh->get_pSOM().get_SOM()[classPos].get_weights();

            QPainter p;
            p.begin(&qimg);
            p.setPen(QPen(QColor(255 - (int)(cols[0]*255), 255 - (int)(cols[1]*255), 255 - (int)(cols[2]*255), 255)));
            p.setBrush(QBrush(QColor(255 - (int)(cols[0]*255), 255 - (int)(cols[1]*255), 255 - (int)(cols[2]*255), 255), Qt::NoBrush));
            p.drawRect(QRect(y * nodeSize, x * nodeSize, nodeSize, nodeSize));
            p.end();
        }

        ui->image_label_2->setPixmap(QPixmap::fromImage(qimg));
        ui->image_label_2->repaint();
        QApplication::processEvents();
    }
}

void Dialog::organizeMap() {
    ui->horizontalSlider->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);

    int percent;
    while(!koh->finished()) {
          if(!koh->train())
             cout << "Problema no treinamento." << endl;

          percent = (koh->get_itCount()*100) / ui->horizontalSlider->value();
          ui->progressBar->setValue(percent);
          if(ui->iterative->isChecked() == true)
             showMap(koh->get_pSOM(), 3, 1, false, 0);
    }
    showMap(koh->get_pSOM(), 3, 1, false, 0);

    ui->horizontalSlider->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}

void Dialog::reorganizeMap() {
    koh->set_startLearningRate(ui->doubleSpinBox->value());
    koh->set_NumIterations(ui->horizontalSlider->value());
    koh->set_pSOM(koh->get_pSOMoriginal());
    organizeMap();
}

void Dialog::on_pushButton_clicked() {
    QObject* button = QObject::sender();
    Dialog2 *secondWindow = new Dialog2(this, this);
    Dialog3 *thirdWindow = new Dialog3(this, this);
    if(button == ui->pushButton && ui->horizontalSlider->value() > 0) {
        generateMap();
        showMap(koh->get_pSOMoriginal(), 3, 0, false, 0);
        buttonClicked = true;
        if(button2Clicked)
            ui->pushButton_2->setEnabled(true);
    } else if(button == ui->pushButton_2 && ui->horizontalSlider->value() > 0) {
        if(!dataSet.empty()) {
            secondWindow->normalize();
            reorganizeMap();
        }
    } else if(button == ui->horizontalSlider) {
        ui->spinBox->setValue(ui->horizontalSlider->value());
    } else if(button == ui->pushButton_3) {
        secondWindow->show();
        button2Clicked = true;
        if(buttonClicked)
            ui->pushButton_2->setEnabled(true);
        if(!dataSet.empty())
           secondWindow->showDataSet();
    } else if(button == ui->pushButton_4) {
        thirdWindow->show();
    }
}

void Dialog::on_spinBox_valueChanged(int arg1) {
    ui->horizontalSlider->setValue(arg1);
}
