#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_MtrxA->setRowCount(ui->spinBox_MtrxARow->value());
    ui->tableWidget_MtrxA->setColumnCount(ui->spinBox_MtrxACol->value());
    ui->tableWidget_MtrxB->setRowCount(ui->spinBox_MtrxBRow->value());
    ui->tableWidget_MtrxB->setColumnCount(ui->spinBox_MtrxBCol->value());
    ui->tableWidget_MtrxA->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch);
    ui->tableWidget_MtrxB->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch);

    ui->comboBox_Operation->insertItem(0,QString::fromUtf8("+"));
    ui->comboBox_Operation->insertItem(1,QString::fromUtf8("*"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_MtrxARow_valueChanged(int arg1)
{
    ui->tableWidget_MtrxA->setRowCount(arg1);
}

void MainWindow::on_spinBox_MtrxACol_valueChanged(int arg1)
{
    ui->tableWidget_MtrxA->setColumnCount(arg1);
}


void MainWindow::on_spinBox_MtrxBRow_valueChanged(int arg1)
{
    ui->tableWidget_MtrxB->setRowCount(arg1);
}

void MainWindow::on_spinBox_MtrxBCol_valueChanged(int arg1)
{
    ui->tableWidget_MtrxB->setColumnCount(arg1);
}
// Выполнение операций с матрицами
void MainWindow::on_pushButton_Count_clicked()
{
    int rowCountA = ui->tableWidget_MtrxA->rowCount();
    int colCountA = ui->tableWidget_MtrxA->columnCount();
    int rowCountB = ui->tableWidget_MtrxB->rowCount();
    int colCountB = ui->tableWidget_MtrxB->columnCount();
    if ((ui->comboBox_Operation->currentText() == "+" && (rowCountA != rowCountB || colCountA != colCountB)) ||
            (ui->comboBox_Operation->currentText() == "*" && (rowCountB != colCountA))) {
        QMessageBox::warning(this, "Невозможная операция!",
                             "Не подходящие размеры матрицы для данной операции.",QMessageBox::Ok);
        return;
    }
    // Считывание матрицы A
    std::shared_ptr<int*[]> mtrxA {new int*[rowCountA]};
    for (int i = 0; i < rowCountA; ++i) {
        mtrxA[i] = new int[colCountA];
    }
    for (int i = 0; i < rowCountA; ++i) {
        for (int j = 0; j < colCountA; ++j) {
            if (ui->tableWidget_MtrxA->item(i, j)->text().isNull())
                mtrxA[i][j] = 0;
            else
                mtrxA[i][j] = ui->tableWidget_MtrxA->item(i, j)->text().toInt();
        }
    }
    // Считывание матрицы B
    std::shared_ptr<int*[]> mtrxB {new int*[rowCountB]};
    for (int i = 0; i < rowCountB; ++i) {
        mtrxB[i] = new int[colCountB];
    }
    for (int i = 0; i < rowCountB; ++i) {
        for (int j = 0; j < colCountB; ++j) {
            if (ui->tableWidget_MtrxB->item(i, j)->text().isNull())
                mtrxB[i][j] = 0;
            else
            mtrxB[i][j] = ui->tableWidget_MtrxB->item(i, j)->text().toInt();
        }
    }

    std::shared_ptr<int*[]> mtrxC {new int*[rowCountA]};
    // Операция сложения
    if (ui->comboBox_Operation->currentText() == "+") {
        for (int i = 0; i < rowCountA; ++i) {
            mtrxC[i] = new int[colCountA];
        }
        for (int i = 0; i < rowCountA; ++i) {
            for (int j = 0; j < colCountA; ++j) {
                mtrxC[i][j] = mtrxA[i][j] + mtrxB[i][j];
            }
        }
    }
    // Операция умножения
    else {
        for (int i = 0; i < colCountB; ++i) {
            mtrxC[i] = new int[colCountB];
        }
        for (int i = 0; i < rowCountA; ++i) {
            for (int j = 0; j < colCountB; ++j) {
                mtrxC[i][j] = 0;
                for (int k = 0; k < rowCountB; ++k) {
                   mtrxC[i][j] += mtrxA[i][k] * mtrxB[k][j];
                }
            }
        }
    }
    fillResultsInTable(mtrxC);
}

// Запись результата
void MainWindow::fillResultsInTable(std::shared_ptr<int *[]> massiv)
{
    ui->tableWidget_Result->setRowCount(ui->spinBox_MtrxARow->value());
    ui->tableWidget_Result->setColumnCount(ui->spinBox_MtrxBCol->value());
    ui->tableWidget_Result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int i = 0; i < ui->tableWidget_Result->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget_Result->columnCount(); ++j) {
             QTableWidgetItem *item = new QTableWidgetItem();
             item->setData(0,massiv[i][j]);
             ui->tableWidget_Result->setItem(i,j,item);
        }
    }
}
