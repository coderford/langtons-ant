#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rulescene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void stopClicked();

private slots:
    void on_btn_start_clicked();
    void on_spin_speed_valueChanged(int arg1);
    void on_btn_clear_clicked();

public slots:
    void on_dirArrowClicked(int index);
    void on_colorRectClicked(int index);

private:
    Ui::MainWindow *ui;

    int stepsBeforeRedraw;					// number of steps ant takes before screen is redrawn

    RuleScene *ruleScene;

    void setControlsEnabled(bool val);
};

#endif // MAINWINDOW_H
