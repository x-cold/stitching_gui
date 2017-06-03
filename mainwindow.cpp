#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stitching.cpp"
#include <QButtonGroup>
#include <stdlib.h>
#include <QFileDialog>
#include <list>
using namespace std;

// 是否启用GPU加速
QButtonGroup *btnGroupGPU;
// 波形校正方向
QButtonGroup *btnGroupWaveCorrect;
// 是否保存过程图片
QButtonGroup *btnGroupSaveGraph;
// 融合平面
QButtonGroup *btnGroupWrapType;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

//    btnGroupWaveCorrect = new QButtonGroup(this);
//    btnGroupWaveCorrect->addButton(ui->radioButton_1, 0);
//    btnGroupWaveCorrect->addButton(ui->radioButton_2, 1);
//    ui->radioButton_1->setChecked(true);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    int len = this->path.size();

    char* argv[len];

    for(int i = 0; i < len; i++)
    {
        const char* file = this->path[i].toStdString().c_str();
        argv[i] = new char[strlen(file)+1];
        strcpy(argv[i], file);
    }

    start(len, argv);
}

void MainWindow::on_actionOpen_triggered()
{
    QStringList path = QFileDialog::getOpenFileNames(this, tr("Open Image"), ".", tr("Image File(*.jpg *.png)"));                                                                                                     //标题：Open Image  过滤器筛选jpg和png
    if(path.length() == 0)
    {
        cout << "You didn't select any files." << endl;
    } else {
        ui->megapix_2->setText(path.join(' '));
        this->path = path;
    }
}
