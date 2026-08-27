#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QRegularExpressionValidator>

class ClearableLineEdit : public QLineEdit {
    Q_OBJECT
public:
    explicit ClearableLineEdit(QWidget *parent = nullptr);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

class RegistrationForm : public QWidget {
    Q_OBJECT
public:
    explicit RegistrationForm(QWidget *parent = nullptr);
private slots:
    void uploadPhoto();
    void registerUser();
private:
    void showError(const QString &message);
    QString encryptPassword(const QString &password);

    ClearableLineEdit *firstName;
    ClearableLineEdit *lastName;
    ClearableLineEdit *nickname;
    ClearableLineEdit *idKey;
    ClearableLineEdit *email;
    ClearableLineEdit *password;

    QLabel *photoLabel;
    QPushButton *btnUpload;
    QPushButton *btnRegister;
    QButtonGroup *serverGroup;
    QRadioButton *rbEu, *rbAs, *rbNa;
    QString photoPath;
};
#endif
