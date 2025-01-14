#ifndef CREATENOTEDIALOG_H
#define CREATENOTEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateNoteDialog;
}

class CreateNoteDialog : public QDialog
{
    Q_OBJECT

public:
    // explicit CreateNoteDialog(QWidget *parent = nullptr);
    CreateNoteDialog(QWidget *parent = nullptr, QString title = "", QString body = "");
    ~CreateNoteDialog();

    QString getTitle() const;
    QString getBody() const;

private slots:
    void validateInput();

private:
    Ui::CreateNoteDialog *ui;
};

#endif // CREATENOTEDIALOG_H
