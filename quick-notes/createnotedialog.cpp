#include "createnotedialog.h"
#include "ui_createnotedialog.h"

#include <QPalette>
#include <QPlainTextEdit>

#include "note.h"

CreateNoteDialog::CreateNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNoteDialog)
{
    ui->setupUi(this);

    validTitle = false;
    validText = false;
}

CreateNoteDialog::~CreateNoteDialog()
{
    delete ui;
}

void CreateNoteDialog::on_titleEdit_textChanged(const QString &arg1)
{
    QPalette palette;
    QLineEdit *edit = findChild<QLineEdit *>("titleEdit");

    qDebug() << "Title text: " << arg1;

    if (Note::validateTitle(arg1.toStdString())) {
        palette.setColor(QPalette::Base, Qt::green);
        palette.setColor(QPalette::Text, Qt::white);
        validTitle = true;
    } else {
        palette.setColor(QPalette::Base, Qt::red);
        palette.setColor(QPalette::Text, Qt::black);
        validTitle = false;
    }

    edit->setPalette(palette);
}

void CreateNoteDialog::on_textEdit_textChanged()
{
    QPalette palette;
    QPlainTextEdit *edit = findChild<QPlainTextEdit *>("textEdit");

    qDebug() << "Body text: " << edit->toPlainText();

    if (Note::validateBody(edit->toPlainText().toStdString())) {
        // edit->setStyleSheet("QPlainTextEdit {background-color: green; color: white;}");
        palette.setColor(QPalette::Base, Qt::green);
        palette.setColor(QPalette::Text, Qt::white);
        validText = true;
    } else {
        // edit->setStyleSheet("QPlainTextEdit {background-color: red; color: black;}");
        palette.setColor(QPalette::Base, Qt::red);
        palette.setColor(QPalette::Text, Qt::black);
        validText = false;
    }

    edit->setPalette(palette);
}

