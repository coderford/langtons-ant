#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

   for(long i = 0; i < steps; i++) {
       ui->render_area->repaint();
   }

   ui->btn_start->setEnabled(true);
   ui->spin_steps->setEnabled(true);
   ui->spin_speed->setEnabled(true);

}

void MainWindow::on_spin_speed_valueChanged(int val)
{
    ui->render_area->setSpeed(val);
}
