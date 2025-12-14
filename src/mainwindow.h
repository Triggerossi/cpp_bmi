#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateBMI();
    void resetFields();
    void showImage(double bmi);


private:
    void setupUI();
    QString getBMICategory(double bmi);
    
    QLineEdit *heightEdit;
    QLineEdit *weightEdit;
    QLabel *resultLabel;
    QLabel *imageLabel;

};

#endif // MAINWINDOW_H  