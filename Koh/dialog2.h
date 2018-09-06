#ifndef DIALOG2_H
#define DIALOG2_H

#include <QDialog>
#include "network.h"
#include "kohonen.h"
#include"dialog.h"

// Classe responsável pelas ações da segunda janela e por criar o vetor de entrada (training_set).
namespace Ui {
    class Dialog2;
}

class Dialog2 : public QDialog {
    Q_OBJECT

public:
    explicit Dialog2(QWidget *parent = 0, Dialog* mainWindow = 0);
    QPalette palette;
    void showDataSet();
    void normalize();
    ~Dialog2();

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_2_valueChanged(int arg1);
    void on_spinBox_3_valueChanged(int arg1);

private:
    Dialog* mainWindow;
    Ui::Dialog2 *ui;
};

#endif // DIALOG2_H
