#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->appNameLabel->setText(QString("%1 (%2)").arg(APP_NAME, APP_ARCH));
    ui->versionLabel->setText(QString("Version %1").arg(APP_VERSION));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
