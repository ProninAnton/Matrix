#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_spinBox_MtrxARow_valueChanged(int arg1);

    void on_spinBox_MtrxACol_valueChanged(int arg1);

    void on_spinBox_MtrxBRow_valueChanged(int arg1);

    void on_spinBox_MtrxBCol_valueChanged(int arg1);

    void on_pushButton_Count_clicked();

    void fillResultsInTable(std::shared_ptr<int*[]> massiv);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
