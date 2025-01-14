#include "creditwidget.h"
#include "./ui_creditwidget.h"

CreditWidget::CreditWidget(QWidget *parent)
    : QDialog{parent}
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setWindowTitle("Credits");
}

CreditWidget::~CreditWidget()
{
    delete ui;
}
