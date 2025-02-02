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

    void update_display(const QModelIndex &index);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    NoteModel *notes;

private slots:
    void on_creditsButton_clicked();

    void on_createButton_clicked();

    void on_note_selected(const QModelIndex &index);

    void on_editButton_clicked();

    void on_data_modified(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

    void on_deleteButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
