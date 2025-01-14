#include "createnotedialog.h"
#include "ui_createnotedialog.h"

#include <QPalette>
#include <QPlainTextEdit>
#include <QPushButton>

#include "note.h"

/*
CreateNoteDialog::CreateNoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateNoteDialog)
{
    CreateNoteDialog(parent, "", "");
}
*/

CreateNoteDialog::CreateNoteDialog(QWidget *parent, QString title, QString body) :
    QDialog(parent),
    ui(new Ui::CreateNoteDialog)
{
    ui->setupUi(this);

    QDialogButtonBox *buttonBox = findChild<QDialogButtonBox *>("dialogButtons");
    buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);

    QLineEdit *titleEdit = findChild<QLineEdit *>("titleEdit");
    QPlainTextEdit *textEdit = findChild<QPlainTextEdit *>("textEdit");

    titleEdit->setText(title);
    textEdit->insertPlainText(body);

    connect(titleEdit, &QLineEdit::textChanged, this, &CreateNoteDialog::validateInput);
    connect(textEdit, &QPlainTextEdit::textChanged, this, &CreateNoteDialog::validateInput);
}

CreateNoteDialog::~CreateNoteDialog()
{
    delete ui;
}

QString CreateNoteDialog::getTitle() const
{
    QLineEdit *titleEdit = findChild<QLineEdit *>("titleEdit");

    return titleEdit->text();
}

QString CreateNoteDialog::getBody() const
{
    QPlainTextEdit *textEdit = findChild<QPlainTextEdit *>("textEdit");

    return textEdit->toPlainText();
}

void CreateNoteDialog::validateInput()
{
    QLineEdit *titleEdit = findChild<QLineEdit *>("titleEdit");
    QPlainTextEdit *textEdit = findChild<QPlainTextEdit *>("textEdit");

    bool titleIsValid = Note::validateTitle(titleEdit->text().toStdString());
    bool bodyIsValid = Note::validateBody(textEdit->toPlainText().toStdString());

    QPalette palette;

    if (titleIsValid) {
        titleEdit->setStyleSheet("QLineEdit {background-color: green; color: white;}");
    } else {
        titleEdit->setStyleSheet("QLineEdit {background-color: red; color: black;}");
    }

    titleEdit->setPalette(palette);

    if (bodyIsValid) {
        textEdit->setStyleSheet("QPlainTextEdit {background-color: green; color: white;}");
    } else {
        textEdit->setStyleSheet("QPlainTextEdit {background-color: red; color: black;}");
    }

    textEdit->setPalette(palette);

    QDialogButtonBox *buttonBox = findChild<QDialogButtonBox *>("dialogButtons");
    buttonBox->button(QDialogButtonBox::Save)->setEnabled(titleIsValid && bodyIsValid);
}
