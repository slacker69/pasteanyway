#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QThread>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_pushButton_clicked();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void keyevent(QChar x);
    void norm(unsigned short x);
    void shift(unsigned short x);
};

#endif // MAINWINDOW_H

