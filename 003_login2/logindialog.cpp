#include "logindialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

// 我今天测试的时候，中文对话框显示总有问题
// 暂时先使用英文，主要时学习Qt类和接口的使用
LoginDialog::LoginDialog(QWidget * parent) :
    QDialog(parent)
{
    usrLabel = new QLabel(this);
    usrLabel->move(60,80);
    usrLabel->setText(tr("用户名a"));
    usrLineEdit = new QLineEdit(this);
    usrLineEdit->move(140,80);
    usrLineEdit->setPlaceholderText(tr("请输入用户名a"));

    pwdLabel = new QLabel(this);
    pwdLabel->move(60,130);
    pwdLabel->setText(tr("密码a"));
    pwdLineEdit = new QLineEdit(this);
    pwdLineEdit->move(140,130);
    pwdLineEdit->setPlaceholderText(tr("请输入密码a"));
    pwdLineEdit->setEchoMode(QLineEdit::Password);


    loginBtn = new QPushButton(this);
    loginBtn->move(50,200);
    loginBtn->setText(tr("登陆a"));
    exitBtn = new QPushButton(this);
    exitBtn->move(210,200);
    exitBtn->setText(tr("退出a"));

    connect(loginBtn,&QPushButton::clicked,this,&LoginDialog::login);
    connect(exitBtn,&QPushButton::clicked,this,&LoginDialog::close);
}

LoginDialog::~LoginDialog()
{

}

void LoginDialog::login()
{
    if(usrLineEdit->text().trimmed() == tr("original") &&
            pwdLineEdit->text() == tr("123456"))
    {
        accept();
    }
    else
    {
        QMessageBox::warning(this,tr("警告!"),tr("用户名或者密码错误a"),QMessageBox::Yes);
        // 清空错误密码，并定位到用户名处重新输入
        usrLineEdit->clear();
        pwdLineEdit->clear();
        usrLineEdit->setFocus();
    }
}
