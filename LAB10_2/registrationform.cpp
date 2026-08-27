#include "registrationform.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDir>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>

ClearableLineEdit::ClearableLineEdit(QWidget *parent) : QLineEdit(parent) {}

void ClearableLineEdit::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->clear();
    }
    QLineEdit::mouseDoubleClickEvent(event);
}

RegistrationForm::RegistrationForm(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Регистрация");
    setStyleSheet(
        "QWidget { background-color: #ffffff; color: #000000; font-size: 14px; }"
        "QLineEdit { background-color: #ffffff; color: #000000; border: 1px solid #aaaaaa; border-radius: 3px; padding: 4px; }"
        "QLineEdit::placeholder { color: #888888; }"
        "QPushButton { background-color: #4a90e2; color: white; border-radius: 4px; padding: 6px 12px; font-weight: bold; }"
        "QPushButton:hover { background-color: #357abd; }"
        "QRadioButton { color: #000000; }"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    QVBoxLayout *photoLayout = new QVBoxLayout();
    photoLabel = new QLabel("Фото");
    photoLabel->setFixedSize(120, 120);
    photoLabel->setStyleSheet("border: 2px dashed #888888;");
    photoLabel->setAlignment(Qt::AlignCenter);
    btnUpload = new QPushButton("Загрузить");
    connect(btnUpload, &QPushButton::clicked, this, &RegistrationForm::uploadPhoto);
    photoLayout->addWidget(photoLabel);
    photoLayout->addWidget(btnUpload);
    photoLayout->addStretch();

    QGridLayout *formLayout = new QGridLayout();
    firstName = new ClearableLineEdit();
    lastName = new ClearableLineEdit();
    nickname = new ClearableLineEdit();
    idKey = new ClearableLineEdit();
    email = new ClearableLineEdit();
    password = new ClearableLineEdit();

    password->setEchoMode(QLineEdit::Password);

    firstName->setPlaceholderText("Иван");
    lastName->setPlaceholderText("Иванов");
    nickname->setPlaceholderText("Ivan_2026");
    idKey->setPlaceholderText("А123-45Б-В");
    email->setPlaceholderText("ivan@example.com");
    password->setPlaceholderText("min 6 symbols");

    firstName->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-zА-Яа-яЁё]+$"), this));
    lastName->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-zА-Яа-яЁё]+$"), this));
    nickname->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-z0-9_]+$"), this));
    idKey->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-Za-zА-Яа-яЁё]\\d{0,3}-?\\d{0,2}[A-Za-zА-Яа-яЁё]?-?[A-Za-zА-Яа-яЁё]?$"), this));
    email->setValidator(new QRegularExpressionValidator(QRegularExpression("^[\\w\\.-]*@?[\\w\\.-]*\\.?\\w*$"), this));

    formLayout->addWidget(new QLabel("Имя"), 0, 0);
    formLayout->addWidget(firstName, 0, 1);
    formLayout->addWidget(new QLabel("Фамилия"), 1, 0);
    formLayout->addWidget(lastName, 1, 1);
    formLayout->addWidget(new QLabel("Никнейм"), 2, 0);
    formLayout->addWidget(nickname, 2, 1);
    formLayout->addWidget(new QLabel("ID-Key"), 3, 0);
    formLayout->addWidget(idKey, 3, 1);
    formLayout->addWidget(new QLabel("Почта"), 4, 0);
    formLayout->addWidget(email, 4, 1);
    formLayout->addWidget(new QLabel("Пароль"), 5, 0);
    formLayout->addWidget(password, 5, 1);

    topLayout->addLayout(photoLayout);
    topLayout->addLayout(formLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QHBoxLayout *serverLayout = new QHBoxLayout();
    serverLayout->addWidget(new QLabel("Сервера:"));
    serverGroup = new QButtonGroup(this);
    rbEu = new QRadioButton("Европа");
    rbAs = new QRadioButton("Азия");
    rbNa = new QRadioButton("Америка");
    serverGroup->addButton(rbEu);
    serverGroup->addButton(rbAs);
    serverGroup->addButton(rbNa);
    serverLayout->addWidget(rbEu);
    serverLayout->addWidget(rbAs);
    serverLayout->addWidget(rbNa);

    btnRegister = new QPushButton("Регистрация");
    connect(btnRegister, &QPushButton::clicked, this, &RegistrationForm::registerUser);

    bottomLayout->addLayout(serverLayout);
    bottomLayout->addStretch();
    bottomLayout->addWidget(btnRegister);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
}

void RegistrationForm::uploadPhoto() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите фото", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        photoPath = fileName;
        QPixmap pixmap(fileName);
        photoLabel->setPixmap(pixmap.scaled(photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

QString RegistrationForm::encryptPassword(const QString &password) {
    QString encrypted;
    for (QChar c : password) {
        encrypted.append(QChar(c.unicode() + 5));
    }
    return encrypted;
}

void RegistrationForm::showError(const QString &message) {
    QMessageBox::warning(this, "Ошибка регистрации", message);
}

void RegistrationForm::registerUser() {
    QString fname = firstName->text().trimmed();
    QString lname = lastName->text().trimmed();
    QString nick = nickname->text().trimmed();
    QString idk = idKey->text().trimmed();
    QString mail = email->text().trimmed();
    QString pwd = password->text().trimmed();

    QRegularExpression nameRegex("^[A-Za-zА-Яа-яЁё]+$");
    QRegularExpression nickRegex("^[A-Za-z0-9_]+$");
    QRegularExpression idRegex("^[A-Za-zА-Яа-яЁё]\\d{3}-\\d{2}[A-Za-zА-Яа-яЁё]-[A-Za-zА-Яа-яЁё]$");
    QRegularExpression mailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");

    if (fname.isEmpty() || !nameRegex.match(fname).hasMatch()) {
        showError("Поле 'Имя' не заполнено до конца.");
        return;
    }
    if (lname.isEmpty() || !nameRegex.match(lname).hasMatch()) {
        showError("Поле 'Фамилия' не заполнено до конца.");
        return;
    }
    if (nick.isEmpty() || !nickRegex.match(nick).hasMatch()) {
        showError("Поле 'Никнейм' не заполнено до конца.");
        return;
    }
    if (!idRegex.match(idk).hasMatch()) {
        showError("ID-Key заполнен не до конца или неверно. Требуется формат: А111-11А-А");
        return;
    }
    if (!mailRegex.match(mail).hasMatch()) {
        showError("Почта введена не полностью или имеет неверный формат.");
        return;
    }
    if (pwd.length() < 6) {
        showError("Пароль должен содержать минимум 6 символов.");
        return;
    }

    QAbstractButton *selectedServer = serverGroup->checkedButton();
    if (!selectedServer) {
        showError("Необходимо выбрать один из доступных серверов.");
        return;
    }
    QString serverName = selectedServer->text();

    QString accountsPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/Accounts";
    QDir userDir(accountsPath + "/" + nick);

    if (userDir.exists()) {
        showError("Указанный логин (Никнейм) уже занят.");
        return;
    }

    userDir.mkpath(".");

    QString photoDest = userDir.filePath("photo.png");
    if (!photoPath.isEmpty()) {
        QFile::copy(photoPath, photoDest);
    } else {
        QPixmap defaultPix(120, 120);
        defaultPix.fill(Qt::white);
        defaultPix.save(photoDest);
    }

    QJsonObject json;
    json["Имя"] = fname;
    json["Фамилия"] = lname;
    json["Никнейм"] = nick;
    json["ID-Key"] = idk;
    json["Почта"] = mail;
    json["Сервер"] = serverName;

    QJsonDocument jsonDoc(json);
    QFile jsonFile(userDir.filePath("data.json"));
    if (jsonFile.open(QIODevice::WriteOnly)) {
        jsonFile.write(jsonDoc.toJson());
        jsonFile.close();
    }

    QFile txtFile(userDir.filePath("credentials.txt"));
    if (txtFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&txtFile);
        out << mail << "/" << encryptPassword(pwd);
        txtFile.close();
    }

    QMessageBox::information(this, "Успешно", "Регистрация успешно завершена!");

    firstName->clear();
    lastName->clear();
    nickname->clear();
    idKey->clear();
    email->clear();
    password->clear();

    serverGroup->setExclusive(false);
    selectedServer->setChecked(false);
    serverGroup->setExclusive(true);

    photoLabel->setPixmap(QPixmap());
    photoLabel->setText("Фото");
    photoPath.clear();
}
