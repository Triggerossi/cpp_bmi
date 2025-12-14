#include "mainwindow.h"
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("Калькулятор ИМТ");
    resize(500, 500);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Заголовок
    QLabel *titleLabel = new QLabel("Калькулятор индекса массы тела (ИМТ)");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");

    // рост
    QHBoxLayout *heightLayout = new QHBoxLayout();
    QLabel *heightLabel = new QLabel("Рост (см):");
    heightEdit = new QLineEdit();
    heightEdit->setPlaceholderText("Введите рост в сантиметрах");
    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightEdit);

    // вес имею
    QHBoxLayout *weightLayout = new QHBoxLayout();
    QLabel *weightLabel = new QLabel("Вес (кг):");
    weightEdit = new QLineEdit();
    weightEdit->setPlaceholderText("Введите вес в килограммах");
    weightLayout->addWidget(weightLabel);
    weightLayout->addWidget(weightEdit);

    // кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *calculateButton = new QPushButton("Рассчитать ИМТ");
    QPushButton *resetButton = new QPushButton("Сбросить");
    buttonLayout->addWidget(calculateButton);
    buttonLayout->addWidget(resetButton);

    // резы
    resultLabel = new QLabel("Результат: ");
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setStyleSheet("font-size: 14px; margin: 10px; padding: 10px; border: 1px solid gray;");

    // картинка
    imageLabel = new QLabel();
    imageLabel->setFixedSize(250,250);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: 1px dashed gray;");
    imageLabel->setScaledContents(true);
    imageLabel->setVisible(false);

    // шаблон
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(heightLayout);
    mainLayout->addLayout(weightLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(resultLabel);
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addStretch();            
    imageLayout->addWidget(imageLabel);   
    imageLayout->addStretch();            
    mainLayout->addLayout(imageLayout);   
    mainLayout->addStretch();


    // сигналы
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::calculateBMI);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetFields);
}

void MainWindow::calculateBMI()
{
    QString heightText = heightEdit->text();
    QString weightText = weightEdit->text();

    if (heightText.isEmpty() || weightText.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля!");
        return;
    }

    bool heightOk, weightOk;
    double height = heightText.toDouble(&heightOk);
    double weight = weightText.toDouble(&weightOk);

    if (!heightOk || !weightOk || height <= 0 || height >= 250 || weight <= 0 || weight >= 500) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите корректные числовые значения!");
        return;
    }

    // считаем
    double heightMeters = height / 100.0;
    double bmi = weight / (heightMeters * heightMeters);

    QString category = getBMICategory(bmi);
    QString result = QString("ИМТ: %1\nКатегория: %2")
                        .arg(bmi, 0, 'f', 1)
                        .arg(category);

    resultLabel->setText(result);

    showImage(bmi);

    //колор
    if (category.contains("Недостаточный")) {
        resultLabel->setStyleSheet("font-size: 14px; margin: 10px; padding: 10px; border: 2px solid blue; background-color: #e6f3ff;");
    } else if (category.contains("Нормальный")) {
        resultLabel->setStyleSheet("font-size: 14px; margin: 10px; padding: 10px; border: 2px solid green; background-color: #e6ffe6;");
    } else if (category.contains("Избыточный")) {
        resultLabel->setStyleSheet("font-size: 14px; margin: 10px; padding: 10px; border: 2px solid orange; background-color: #fff9e6;");
    } else {
        resultLabel->setStyleSheet("font-size: 14px; margin: 10px; padding: 10px; border: 2px solid red; background-color: #ffe6e6;");
    }
}

QString MainWindow::getBMICategory(double bmi)
{
    if (bmi < 18.5) {
        return "Недостаточный вес";
    } else if (bmi < 25.0) {
        return "Нормальный вес";
    } else if (bmi < 30.0) {
        return "Избыточный вес";
    } else if (bmi < 35.0) {
        return "Ожирение";
    } else {
        return "Экстремальное Ожирение";
    }
}

void MainWindow::resetFields()
{
    heightEdit->clear();
    weightEdit->clear();
    resultLabel->setText("Результат: ");
    resultLabel->setStyleSheet("font-size: 14px; margin: 10px; padding: 10px; border: 1px solid gray;");
    imageLabel->clear();
    imageLabel->setVisible(false);  // прячем картинку при сбросе


}

void MainWindow::showImage(double bmi)
{
    QString path;

    if (bmi < 18.5)
        path = "../images/underweight.png";
    else if (bmi < 25.0)
        path = "../images/normal.png";
    else if (bmi < 30.0)
        path = "../images/bese.png";
    else if (bmi < 35.0)
        path = "../images/overweight.png";
    else
        path = "../images/obese.png";

    QPixmap pixmap(path);

    if (pixmap.isNull()) {
        qDebug() << "Picture don't load! Path:" << path;
        imageLabel->clear();
        imageLabel->setVisible(false); // скрываем, если не загрузилось
    } else {
        imageLabel->setPixmap(pixmap);
        imageLabel->setVisible(true);  // показываем после успешной загрузки
    }
}

