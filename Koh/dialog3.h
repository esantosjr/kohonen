#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include <dialog.h>

namespace Ui {
    class Dialog3;
}

class Dialog3 : public QDialog {
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = 0, Dialog* mainWindow = 0);
    QPalette palette;
    void knn_classifier(int R, int G, int B);
    ~Dialog3();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_4_valueChanged(int arg1);

private:
    Dialog* mainWindow;
    Ui::Dialog3 *ui;
};

#endif // DIALOG3_H
