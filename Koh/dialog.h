#ifndef DIALOG_H
#define DIALOG_H

#include "network.h"
#include "kohonen.h"
#include <QDialog>
#include <QtGui>

// Classe que controla a janela principal.
namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void generateMap();
    void showMap(Network net, int sizeInputVector, int type, bool classification, int classPos);
    void organizeMap();
    void reorganizeMap();

    // atributos
    Kohonen* koh;
    vector<vector<double> > dataSet;
    bool buttonClicked = false;
    bool button2Clicked = false;

private:
    Ui::Dialog *ui;

public slots:
    void on_pushButton_clicked();
private slots:
    void on_spinBox_valueChanged(int arg1);
};

#endif // DIALOG_H
