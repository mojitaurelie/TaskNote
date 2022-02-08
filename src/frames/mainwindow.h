#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "../services/savemanager.h"
#include "aboutdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createNote();
    void selectionChanged(int);
    void removeSelected();
    void save();
    void contentChanged();
    void titleChanged();
    void showAboutBox();
    void encryptNote();

private:
    Ui::MainWindow *ui;
    SaveManager *savemng;
    QTimer *timer;

    int currentIndex = -1;

    void updateListView();
    void clearAndDisableFields();
};
#endif // MAINWINDOW_H
