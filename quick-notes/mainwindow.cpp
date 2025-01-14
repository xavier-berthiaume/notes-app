#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDialogButtonBox>
#include <QMessageBox>

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

    connect(listview->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &MainWindow::on_note_selected);
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

void MainWindow::on_editButton_clicked()
{
    QListView *noteListView = findChild<QListView *>("listView");
    QModelIndex selectedIndex = noteListView->currentIndex();
    if (!selectedIndex.isValid()) {
        QMessageBox::warning(this, "Edit Note", "No note selected.");
        return;
    }

    CreateNoteDialog createDialog(this);

    if (createDialog.exec() == QDialog::Accepted)
    {
        QString newTitle = createDialog.getTitle();
        QString newBody = createDialog.getBody();

        notes->modifyNote(selectedIndex, newTitle, newBody);
    }

}

void MainWindow::on_note_selected(const QModelIndex& index)
{
    QLabel *titleLabel = findChild<QLabel *>("titleLabel");
    QTextBrowser *bodyArea = findChild<QTextBrowser *>("body");

    QPushButton *editButton = findChild<QPushButton *>("editButton");
    QPushButton *deleteButton = findChild<QPushButton *>("deleteButton");

    if (!index.isValid()) {
        titleLabel->setText("No note selected");
        bodyArea->setText("");
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
        return;
    }

    QString title = index.data(NoteModel::TitleRole).toString();
    QString body = index.data(NoteModel::BodyRole).toString();

    titleLabel->setText(title);
    bodyArea->setText(body);
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

