#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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

private:
    Ui::MainWindow *ui;
    int stepsBeforeRedraw;				// number of steps ant takes before screen is redrawn

    QGraphicsScene movementRulesScene;
    void constructMovementRulesScene(const QMap<QRgb, QPair<char, QRgb> > &moveTable);
    void drawMovementRulesScene();

    void setControlsEnabled(bool val);

    QPolygon makeDirIndicator(int x, int y, int w, int h, char dir);
};

#endif // MAINWINDOW_H
