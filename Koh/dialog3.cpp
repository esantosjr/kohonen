#include "dialog3.h"
#include "ui_dialog3.h"

Dialog3::Dialog3(QWidget *parent, Dialog* mainWindow) : QDialog(parent), mainWindow(mainWindow), ui(new Ui::Dialog3) {
    ui->setupUi(this);

    palette = ui->frame->palette();
    ui->frame->setAutoFillBackground(true);
    ui->spinBox_4->setValue(ui->horizontalSlider->value());
}

Dialog3::~Dialog3() {
    delete ui;
}

void Dialog3::knn_classifier(int R, int G, int B) {
    uint k = 3;
    int threshold = ui->horizontalSlider->value();
    int size = mainWindow->koh->get_pSOM().getSize();
    vector<double> vec;
    vector<int> is;
    vector<float> distances;
    vector<vector<double> > rgb;
    float distance = 0;
    float sum = 0; float mediaDistances = 0;
    int Rvalue = 0; int Gvalue = 0; int Bvalue = 0;
    int classPos = 0;

    for(int i = 0; i < size; i++) {
        vec = mainWindow->koh->get_pSOM().get_SOM()[i].get_weights();
        distance = pow(((int)(vec[0]*255) - R), 2) + pow(((int)(vec[1]*255) - G), 2) + pow(((int)(vec[2]*255) - B), 2);
        distance = sqrt(distance);
        if((int)distance < threshold) {
           distances.push_back(distance);
           rgb.push_back(vec);
           is.push_back(i);
        }
    }
    int pos = 0;
    if(!is.empty())
        classPos = is[pos];

    for(uint j = 1; j < distances.size(); j++) {
        if(distances[j] < distances[pos]) { // em algum momento ele não entra nesse if e o neuronio vencedor fica como o da posição 0 como default.
            pos = j; // posição do neurônio vencedor.
            classPos = is[pos];
        }
    }

    sort(distances.begin(), distances.end());
    // seleciona os K's pontos mais próximos.
    if(distances.size() >= k) {
       for(uint m = 0; m < k; m++)
           sum += distances[m];
    }

    mediaDistances = sum / k;
    if(mediaDistances < threshold && distances.size() >= k) {
       ui->textBrowser->setText(QString("Valor pertence à classe indicada ao lado. \nNeurônio vencedor está destacado no mapa."));
       Rvalue = (int)(rgb[pos][0]*255);
       Gvalue = (int)(rgb[pos][1]*255);
       Bvalue = (int)(rgb[pos][2]*255);
       palette.setColor(backgroundRole(), QColor(Rvalue, Gvalue, Bvalue));
       ui->frame->setPalette(palette);
       mainWindow->showMap(mainWindow->koh->get_pSOM(), 3, 1, true, classPos);
    } else {
       ui->textBrowser->setText(QString("Valor não pertence à uma classe."));
       palette.setColor(backgroundRole(), Qt::transparent);
       ui->frame->setPalette(palette);
       mainWindow->showMap(mainWindow->koh->get_pSOM(), 3, 1, false, 0);
    }
}

void Dialog3::on_pushButton_clicked() {
      knn_classifier(ui->spinBox->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
}

void Dialog3::on_pushButton_2_clicked() {
    this->close();
}

void Dialog3::on_horizontalSlider_valueChanged(int value) {
    ui->spinBox_4->setValue(value);
}

void Dialog3::on_spinBox_4_valueChanged(int arg1) {
    ui->horizontalSlider->setValue(arg1);
}
