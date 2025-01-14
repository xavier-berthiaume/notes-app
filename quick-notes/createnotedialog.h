#ifndef CREATENOTEDIALOG_H
#define CREATENOTEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateNoteDialog;
}

class CreateNoteDialog : public QDialog
{
    Q_OBJECT

    bool validTitle, validText;

public:
    explicit CreateNoteDialog(QWidget *parent = nullptr);
    ~CreateNoteDialog();

private slots:
    void on_titleEdit_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

private:
    Ui::CreateNoteDialog *ui;
};

#endif // CREATENOTEDIALOG_H
