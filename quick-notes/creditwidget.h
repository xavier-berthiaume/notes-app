#ifndef CREDITWIDGET_H
#define CREDITWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class CreditWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CreditWidget(QWidget *parent = nullptr);
    ~CreditWidget();

signals:

private:
    Ui::Dialog *ui;

};

#endif // CREDITWIDGET_H
