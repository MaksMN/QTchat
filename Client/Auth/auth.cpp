#include "auth.h"
#include "misc.h"
#include "strings.h"
#include "ui_auth.h"
#include "user.h"

Auth::Auth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Auth)
{
    ui->setupUi(this);
}

Auth::~Auth()
{
    delete ui;
}

void Auth::on_regButton_clicked()
{
    bool check = ui->regLogin->text().isEmpty() && ui->regEmail->text().isEmpty()
                 && ui->regFirstName->text().isEmpty() && ui->regLastName->text().isEmpty()
                 && ui->regPass->text().isEmpty();

    if (check) {
        ui->labelMsg->setText(Strings::t(Strings::ALL_FIELDS_MUST_BE_FILLED_IN));
        ui->labelMsg->setStyleSheet("color: red;");
        return;
    }

    auto session_key = Misc::randomKey();
    user = std::make_shared<chat::User>(ui->regLogin->text(),
                                        ui->regEmail->text(),
                                        ui->regFirstName->text(),
                                        ui->regLastName->displayText(),
                                        0,
                                        chat::user::common,
                                        session_key,
                                        QString(),
                                        QString());
    QString pass = ui->regPass->text();
    user->setPass(pass);
    auto jsonUser = user->serialiseJson();
    jsonUser["command"] = "register";

    ui->labelMsg->setText(Strings::t(Strings::CONNECTION_TO_SERVER));
    auto response = client.send(jsonUser);

    if (response["response"].toString() == "timeout") {
        ui->labelMsg->setText(Strings::t(Strings::NO_SERVER_RESPONSE));
        ui->labelMsg->setStyleSheet("color: red;");
        return;
    }

    if (response["response"].toString() == "fail") {
        ui->labelMsg->setText(Strings::t(Strings::UNKNOWN_ERROR));
        ui->labelMsg->setStyleSheet("color: red;");
        return;
    }

    if (response["response"].toString() == "busy") {
        ui->labelMsg->setText(response["message"].toString());
        ui->labelMsg->setStyleSheet("color: red;");
        return;
    }
    if (response["response"].toString() == "registered") {
        user->deserialiseJson(response);
        _authorized = true;
    }
    if (response["response"].toString() == "not_registered") {
        ui->labelMsg->setText(Strings::t(Strings::UNKNOWN_REASON));
        ui->labelMsg->setStyleSheet("color: red;");
    }

    return;
}

bool Auth::authorized() const
{
    return _authorized;
}

void Auth::on_loginButton_clicked() {}
