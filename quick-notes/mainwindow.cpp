#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDialogButtonBox>
#include <QMessageBox>

#include "notedelegate.h"
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

    NoteDelegate *delegate = new NoteDelegate(this);
    listview->setItemDelegate(delegate);

    connect(notes, &NoteModel::dataChanged, this, &MainWindow::on_data_modified);
    connect(listview->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &MainWindow::on_note_selected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_display(const QModelIndex &index)
{
    QLabel *titleLabel = findChild<QLabel *>("titleLabel");
    QTextBrowser *body = findChild<QTextBrowser *>("body");

    qDebug() << "Updating display";

    if (!index.isValid()) {
        qDebug() << "Bad index: " << index.row();
        titleLabel->setText("No note selected.");
        body->clear();
        return;
    }

    qDebug() << "Valid index: " << index.row();

    // Fetch note data
    QString title = index.data(NoteModel::TitleRole).toString();
    QString bodyText = index.data(NoteModel::BodyRole).toString();

    // Elide the title if it's too long
    QFontMetrics metrics(titleLabel->font());
    int availableWidth = titleLabel->width();
    QString elidedTitle = metrics.elidedText(title, Qt::ElideRight, availableWidth);

    // Update the widgets
    titleLabel->setText(elidedTitle);
    body->setText(bodyText);
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

    CreateNoteDialog createDialog(this, selectedIndex.data(NoteModel::TitleRole).toString(), selectedIndex.data(NoteModel::BodyRole).toString());

    if (createDialog.exec() == QDialog::Accepted)
    {
        QString newTitle = createDialog.getTitle();
        QString newBody = createDialog.getBody();

        notes->modifyNote(selectedIndex, newTitle, newBody);
    }

}

void MainWindow::on_deleteButton_clicked()
{
    QListView *noteListView = findChild<QListView *>("listView");
    QModelIndex currentIndex = noteListView->currentIndex();

    QPushButton *editButton = findChild<QPushButton *>("editButton");
    QPushButton *deleteButton = findChild<QPushButton *>("deleteButton");

    if (!currentIndex.isValid()) {
        return;
    }

    notes->removeNote(currentIndex.row());

    if (notes->rowCount() == 0) {
        update_display(QModelIndex());
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
    } else {
        QModelIndex newIndex;

        if (currentIndex.row() >= notes->rowCount()) {
            newIndex = notes->index(notes->rowCount() - 1); // If we deleted the last note, select the new last note to display
        } else {
            newIndex = notes->index(currentIndex.row());
        }

        noteListView->setCurrentIndex(newIndex);
        update_display(newIndex);
    }

}

void MainWindow::on_note_selected(const QModelIndex& index)
{
    qDebug() << "on_note_selected called";
    QPushButton *editButton = findChild<QPushButton *>("editButton");
    QPushButton *deleteButton = findChild<QPushButton *>("deleteButton");

    update_display(index);

    if (!index.isValid()) {
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
        return;
    }

    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void MainWindow::on_data_modified(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    qDebug() << "on_data_modified called";
    QListView *noteListView = findChild<QListView *>("listView");
    QModelIndex currentIndex = noteListView->currentIndex();

    if (currentIndex.row() >= topLeft.row() && currentIndex.row() <= bottomRight.row()) {
        update_display(currentIndex);
    }
}
