#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDialogButtonBox>

#include "createnotedialog.h"
#include "creditwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Quick Notes");

    notes = new NoteModel(this);
    QListView *listview = this->findChild<QListView *>("listView");
    listview->setModel(notes);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_creditsButton_clicked()
{
    CreditWidget creditDialog(this);

    creditDialog.exec();
}


void MainWindow::on_createButton_clicked()
{
    CreateNoteDialog createDialog(this);

    if(createDialog.exec() == QDialog::Accepted)
    {
        notes->addNote({static_cast<uint32_t>(notes->rowCount() + 1), createDialog.getTitle().toStdString(), createDialog.getBody().toStdString()});
    }
}
