#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ruleScene.construct(ui->render_area->moveTable, ui->render_area->getBackgroundColor());
    ui->movement_rules_view->setScene(&ruleScene);

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
