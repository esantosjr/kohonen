#include "dialog2.h"
#include "ui_dialog2.h"
#include "QPushButton"
#include "dialog.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Dialog2::Dialog2(QWidget *parent, Dialog* mainWindow) : QDialog(parent), mainWindow(mainWindow), ui(new Ui::Dialog2) {
    ui->setupUi(this);

    ui->pushButton_2->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    palette = ui->frame->palette();
    palette.setColor(backgroundRole(), QColor(ui->horizontalSlider->value(), ui->horizontalSlider_2->value(), ui->horizontalSlider_3->value()));
    ui->frame->setPalette(palette);
    ui->frame->setAutoFillBackground(true);
}

Dialog2::~Dialog2() {
    delete ui;
}

void Dialog2::showDataSet() {
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    for(uint i = 0; i < mainWindow->dataSet.size(); i++) {
        ui->tableWidget->insertRow(i);
        for(int j = 0; j < 3; j++) {
            QTableWidgetItem *item = new QTableWidgetItem(QString::number(mainWindow->dataSet[i][j]));
            item->setBackgroundColor(QColor(mainWindow->dataSet[i][0], mainWindow->dataSet[i][1], mainWindow->dataSet[i][2]));
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

void Dialog2::on_horizontalSlider_valueChanged(int value) {
    ui->spinBox->setValue(value);
    palette.setColor(backgroundRole(), QColor(ui->horizontalSlider->value(), ui->horizontalSlider_2->value(), ui->horizontalSlider_3->value()));
    ui->frame->setPalette(palette);
}

void Dialog2::on_horizontalSlider_2_valueChanged(int value) {
    ui->spinBox_2->setValue(value);
    palette.setColor(backgroundRole(), QColor(ui->horizontalSlider->value(), ui->horizontalSlider_2->value(), ui->horizontalSlider_3->value()));
    ui->frame->setPalette(palette);
}

void Dialog2::on_horizontalSlider_3_valueChanged(int value) {
    ui->spinBox_3->setValue(value);
    palette.setColor(backgroundRole(), QColor(ui->horizontalSlider->value(), ui->horizontalSlider_2->value(), ui->horizontalSlider_3->value()));
    ui->frame->setPalette(palette);
}

void Dialog2::on_pushButton_clicked() {
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(false);
    vector<double> temp;
    temp.push_back(ui->horizontalSlider->value());
    temp.push_back(ui->horizontalSlider_2->value());
    temp.push_back(ui->horizontalSlider_3->value());
    mainWindow->dataSet.push_back(temp);
    ui->tableWidget->insertRow(mainWindow->dataSet.size()-1);
    for(int i = 0; i < 3; i++) {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(temp[i]));
        item->setBackgroundColor(QColor(temp[0], temp[1], temp[2]));
        ui->tableWidget->setItem(mainWindow->dataSet.size()-1, i, item);
    }
}

void Dialog2::on_pushButton_2_clicked() {
    for(int i = mainWindow->dataSet.size(); i >= 0; i--)
        ui->tableWidget->removeRow(i);

    mainWindow->dataSet.clear();
    ui->pushButton->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
}

void Dialog2::normalize() {
        mainWindow->koh->training_set = mainWindow->dataSet;
        for(uint i = 0; i < mainWindow->koh->training_set.size(); i++) {
            for(int j = 0; j < 3; j++)
                mainWindow->koh->training_set[i][j] /= 255;
        }
}

void Dialog2::on_pushButton_3_clicked() {
    this->close();
}

void Dialog2::on_pushButton_4_clicked() {
    if(mainWindow->dataSet.size() > 0) {
        ui->tableWidget->removeRow(mainWindow->dataSet.size()-1);
        mainWindow->dataSet.pop_back();
        if(mainWindow->dataSet.size() < 1) {
            ui->pushButton->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
        }
    }
}

void Dialog2::on_spinBox_valueChanged(int arg1) {
    ui->horizontalSlider->setValue(arg1);
}

void Dialog2::on_spinBox_2_valueChanged(int arg1) {
    ui->horizontalSlider_2->setValue(arg1);
}

void Dialog2::on_spinBox_3_valueChanged(int arg1) {
    ui->horizontalSlider_3->setValue(arg1);
}

void Dialog2::on_pushButton_5_clicked() { // cria o training_set padrão.
    ui->pushButton_5->setEnabled(false);
    vector<double> black, white, red, green, blue, yellow, orange, purple, dark_green, dark_blue, dark_red, dark_yellow;

    // valores de entrada: RGB / 255

    black.push_back(0);
    black.push_back(0);
    black.push_back(0);

    white.push_back(255);
    white.push_back(255);
    white.push_back(255);

    red.push_back(255);
    red.push_back(0);
    red.push_back(0);

    dark_red.push_back(178);
    dark_red.push_back(33);
    dark_red.push_back(33);

    green.push_back(0);
    green.push_back(255);
    green.push_back(0);

    dark_green.push_back(0);
    dark_green.push_back(127);
    dark_green.push_back(63);

    blue.push_back(0);
    blue.push_back(0);
    blue.push_back(255);

    dark_blue.push_back(0);
    dark_blue.push_back(0);
    dark_blue.push_back(127);

    yellow.push_back(255);
    yellow.push_back(255);
    yellow.push_back(51);

    dark_yellow.push_back(216);
    dark_yellow.push_back(163);
    dark_yellow.push_back(30);

    orange.push_back(255);
    orange.push_back(163);
    orange.push_back(0);

    purple.push_back(255);
    purple.push_back(0);
    purple.push_back(255);

    //mainWindow->dataSet.push_back(black);
    //mainWindow->dataSet.push_back(white);
    mainWindow->dataSet.push_back(red);
    mainWindow->dataSet.push_back(green);
    mainWindow->dataSet.push_back(blue);
    mainWindow->dataSet.push_back(yellow);
    mainWindow->dataSet.push_back(orange);
    //mainWindow->dataSet.push_back(purple);
    mainWindow->dataSet.push_back(dark_red);
    mainWindow->dataSet.push_back(dark_green);
    mainWindow->dataSet.push_back(dark_blue);
    //mainWindow->dataSet.push_back(dark_yellow);

    showDataSet();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}
