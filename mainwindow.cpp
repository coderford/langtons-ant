#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stepsBeforeRedraw = 1;
    constructMovementRulesScene(ui->render_area->moveTable);
    drawMovementRulesScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_start_clicked()
{
   ui->btn_start->setEnabled(false);
   ui->spin_steps->setEnabled(false);
   ui->spin_speed->setEnabled(false);

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

   ui->btn_start->setEnabled(true);
   ui->spin_steps->setEnabled(true);
   ui->spin_speed->setEnabled(true);

}

void MainWindow::on_spin_speed_valueChanged(int val)
{
    stepsBeforeRedraw = val;
}

void MainWindow::constructMovementRulesScene(const QMap<QRgb, QPair<char, QRgb> > &moveTable)
{
    int x = 0, y = 0;
    int w = 30, h = 20;
    int gap = 40;

    QMap<QRgb, QPair<char, QRgb> >::const_iterator it = moveTable.begin();
    while(it != moveTable.end()) {
        QColor fromColor = QColor::fromRgba(it.key());
        QColor toColor = QColor::fromRgba(it.value().second);

        movementRulesScene.addRect(x, y, w, h, QPen(Qt::black), QBrush(fromColor));
        /* arrow v */
        movementRulesScene.addLine(x + w, y + h/2, x + w + gap, y + h/2, QPen(Qt::black));
        movementRulesScene.addLine(x + w + gap-10, y, x + w + gap, y + h/2, QPen(Qt::black));
        movementRulesScene.addLine(x + w + gap-10, y + h, x + w + gap, y + h/2, QPen(Qt::black));
        /* arrow ^ */
        movementRulesScene.addRect(x + w + gap, y, w, h, QPen(Qt::black), QBrush(toColor));
        y += 25;
        it++;
    }
}

void MainWindow::drawMovementRulesScene()
{
    ui->movement_rules_view->setScene(&movementRulesScene);
}
