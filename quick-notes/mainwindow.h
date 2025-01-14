#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "notemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    NoteModel *notes;

private slots:
    void on_creditsButton_clicked();

    void on_createButton_clicked();

    void on_note_selected(const QModelIndex& index);

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
