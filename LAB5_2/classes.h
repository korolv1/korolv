#ifndef CLASSES_H
#define CLASSES_H

#include <QString>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>
#include <QIcon>

struct Date {
    int day, month, year;
};

class R {
protected:
    QString lastName;
    QString firstName;
    Date dob;
    QString photoPath;
public:
    R(QString f, QString i, Date d) : lastName(f), firstName(i), dob(d), photoPath("") {}
    virtual ~R() = default;

    virtual QDialog* Craft(QWidget* parent = nullptr) = 0;

    virtual QString getTableNames() const = 0;
    QString getTableDate() const {
        return QString("%1.%2.%3")
        .arg(dob.day, 2, 10, QChar('0'))
            .arg(dob.month, 2, 10, QChar('0'))
            .arg(dob.year);
    }
};

class RuP : public R {
    QString patronymic;
public:
    RuP(QString f, QString i, QString o, Date d) : R(f, i, d), patronymic(o) {}

    QDialog* Craft(QWidget* parent = nullptr) override {
        QDialog* dialog = new QDialog(parent);
        dialog->setWindowTitle("Пропуск (RuP)");

        QHBoxLayout* mainLayout = new QHBoxLayout(dialog);

        QPushButton* imgBtn = new QPushButton(dialog);
        imgBtn->setFixedSize(100, 120);
        imgBtn->setCursor(Qt::PointingHandCursor);

        if (photoPath.isEmpty()) {
            imgBtn->setText("ФОТО");
            imgBtn->setStyleSheet("QPushButton { background-color: lightgray; border: 2px solid black; }");
        } else {
            QPixmap pix(photoPath);
            imgBtn->setIcon(QIcon(pix.scaled(96, 116, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
            imgBtn->setIconSize(QSize(96, 116));
            imgBtn->setStyleSheet("QPushButton { border: 2px solid black; }");
        }

        QObject::connect(imgBtn, &QPushButton::clicked, [this, imgBtn, dialog]() {
            QString filePath = QFileDialog::getOpenFileName(dialog, "", "", "*.png *.jpg *.jpeg *.bmp");
            if (!filePath.isEmpty()) {
                this->photoPath = filePath;
                imgBtn->setText("");
                QPixmap pix(this->photoPath);
                imgBtn->setIcon(QIcon(pix.scaled(96, 116, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
                imgBtn->setIconSize(QSize(96, 116));
                imgBtn->setStyleSheet("QPushButton { border: 2px solid black; }");
            }
        });

        QVBoxLayout* textLayout = new QVBoxLayout();
        textLayout->addWidget(new QLabel("<b>Фамилия:</b> " + lastName));
        textLayout->addWidget(new QLabel("<b>Имя:</b> " + firstName));
        textLayout->addWidget(new QLabel("<b>Отчество:</b> " + (patronymic.isEmpty() ? "-" : patronymic)));
        textLayout->addWidget(new QLabel("<b>" + getTableDate() + "</b>"));

        QHBoxLayout* btnLayout = new QHBoxLayout();
        QPushButton* btnPrint = new QPushButton("Печать", dialog);
        QPushButton* btnCancel = new QPushButton("Отмена", dialog);

        btnPrint->setStyleSheet("background-color: #00a8ff; color: white; font-weight: bold;");
        btnCancel->setStyleSheet("background-color: #e84118; color: white; font-weight: bold;");

        btnLayout->addWidget(btnPrint);
        btnLayout->addWidget(btnCancel);
        textLayout->addLayout(btnLayout);

        mainLayout->addWidget(imgBtn);
        mainLayout->addLayout(textLayout);

        QObject::connect(btnPrint, &QPushButton::clicked, dialog, &QDialog::accept);
        QObject::connect(btnCancel, &QPushButton::clicked, dialog, &QDialog::reject);

        return dialog;
    }

    QString getTableNames() const override {
        return lastName + " " + firstName + " " + (patronymic.isEmpty() ? "" : patronymic);
    }
};

class AmP : public R {
    QString middleName;
public:
    AmP(QString i, QString m, QString f, Date d) : R(f, i, d), middleName(m) {}

    QDialog* Craft(QWidget* parent = nullptr) override {
        QDialog* dialog = new QDialog(parent);
        dialog->setWindowTitle("Пропуск (AmP)");

        QHBoxLayout* mainLayout = new QHBoxLayout(dialog);

        QPushButton* imgBtn = new QPushButton(dialog);
        imgBtn->setFixedSize(100, 120);
        imgBtn->setCursor(Qt::PointingHandCursor);

        if (photoPath.isEmpty()) {
            imgBtn->setText("PHOTO");
            imgBtn->setStyleSheet("QPushButton { background-color: lightblue; border: 2px solid black; }");
        } else {
            QPixmap pix(photoPath);
            imgBtn->setIcon(QIcon(pix.scaled(96, 116, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
            imgBtn->setIconSize(QSize(96, 116));
            imgBtn->setStyleSheet("QPushButton { border: 2px solid black; }");
        }

        QObject::connect(imgBtn, &QPushButton::clicked, [this, imgBtn, dialog]() {
            QString filePath = QFileDialog::getOpenFileName(dialog, "", "", "*.png *.jpg *.jpeg *.bmp");
            if (!filePath.isEmpty()) {
                this->photoPath = filePath;
                imgBtn->setText("");
                QPixmap pix(this->photoPath);
                imgBtn->setIcon(QIcon(pix.scaled(96, 116, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
                imgBtn->setIconSize(QSize(96, 116));
                imgBtn->setStyleSheet("QPushButton { border: 2px solid black; }");
            }
        });

        QVBoxLayout* textLayout = new QVBoxLayout();
        textLayout->addWidget(new QLabel("<b>Имя:</b> " + firstName));
        textLayout->addWidget(new QLabel("<b>Вт. Имя:</b> " + middleName));
        textLayout->addWidget(new QLabel("<b>Фамилия:</b> " + lastName));
        QString usDate = QString("%1-%2-%3")
                             .arg(dob.month, 2, 10, QChar('0'))
                             .arg(dob.day, 2, 10, QChar('0'))
                             .arg(dob.year);
        textLayout->addWidget(new QLabel("<b>" + usDate + "</b>"));

        QHBoxLayout* btnLayout = new QHBoxLayout();
        QPushButton* btnPrint = new QPushButton("Печать", dialog);
        QPushButton* btnCancel = new QPushButton("Отмена", dialog);

        btnPrint->setStyleSheet("background-color: #00a8ff; color: white; font-weight: bold;");
        btnCancel->setStyleSheet("background-color: #e84118; color: white; font-weight: bold;");

        btnLayout->addWidget(btnPrint);
        btnLayout->addWidget(btnCancel);
        textLayout->addLayout(btnLayout);

        mainLayout->addWidget(imgBtn);
        mainLayout->addLayout(textLayout);

        QObject::connect(btnPrint, &QPushButton::clicked, dialog, &QDialog::accept);
        QObject::connect(btnCancel, &QPushButton::clicked, dialog, &QDialog::reject);

        return dialog;
    }

    QString getTableNames() const override {
        return firstName + " " + middleName + " " + lastName;
    }
};

#endif
