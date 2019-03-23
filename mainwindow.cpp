#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    constructMovementRulesScene(ui->render_area->moveTable);
    ui->movement_rules_view->setScene(&movementRulesScene);

    stepsBeforeRedraw = 1000;
    ui->spin_speed->setValue(stepsBeforeRedraw);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{
   setControlsEnabled(false);
   long steps = ui->spin_steps->value();
   bool outOfBounds = false;

   for(long i = 0; i < steps; i++) {
       for(int j = 0; j < stepsBeforeRedraw; j++) {
           if(ui->render_area->oneStep() == false) {
               outOfBounds = true;
               break;
           }
       }
       if(outOfBounds) break;
       ui->render_area->repaint();
   }
   setControlsEnabled(true);
}

void MainWindow::on_spin_speed_valueChanged(int val)
{
    stepsBeforeRedraw = val;
}

void MainWindow::constructMovementRulesScene(const QMap<QRgb, QPair<char, QRgb> > &moveTable)
{
    QRgb startColor = ui->render_area->getBackgroundColor();
    QRgb currColor = startColor;
    int startx = 0, starty = 0;
    int x = startx, y = starty;
    int w = 40, h = 30;
    int gap = 10;

    int iters = 0;
    int maxiters = 100;

    while(true) {
        if(iters > maxiters) {
            qDebug() << "ERROR: too many iterations!";
            break;
        }
        movementRulesScene.addRect(x, y, w, h, QPen(Qt::black), QBrush(QColor::fromRgba(currColor)));
        currColor = moveTable[currColor].second;

        /* arrow v */
        movementRulesScene.addLine(x + w/2, y + h, x + w/2, y + h + gap, QPen(Qt::black));
        if(currColor == startColor) break;
        movementRulesScene.addLine(x + w/2 - 5, y + h + gap - 5, x + w/2, y + h + gap, QPen(Qt::black));
        movementRulesScene.addLine(x + w/2 + 5, y + h + gap - 5, x + w/2, y + h + gap, QPen(Qt::black));
        /* arrow ^ */
        y += gap + h;
        iters++;
    }

    // adding lines like this is really tedious! these are for the loop
    movementRulesScene.addLine(x + w/2, y + h + gap, x + 3*w/2, y + h + gap, QPen(Qt::black));
    movementRulesScene.addLine(x + 3*w/2, y + h + gap, startx + 3*w/2, starty - gap, QPen(Qt::black));
    movementRulesScene.addLine(startx + 3*w/2, starty - gap, startx + w/2, starty - gap, QPen(Qt::black));
    movementRulesScene.addLine(startx + w/2, starty - gap, startx + w/2, starty, QPen(Qt::black));

    // final arrowheads
    movementRulesScene.addLine(startx + w/2 - 5, starty - 5, startx + w/2, starty, QPen(Qt::black));
    movementRulesScene.addLine(startx + w/2 + 5, starty - 5, startx + w/2, starty, QPen(Qt::black));
}

void MainWindow::on_btn_clear_clicked()
{
    ui->render_area->reset();
    ui->render_area->repaint();
}

void MainWindow::setControlsEnabled(bool val)
{
   ui->btn_start->setEnabled(val);
   ui->spin_steps->setEnabled(val);
   ui->spin_speed->setEnabled(val);
   ui->btn_clear->setEnabled(val);
}
