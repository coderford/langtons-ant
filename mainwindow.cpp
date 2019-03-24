#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ruleScene = new RuleScene(this);
    connect(ruleScene, SIGNAL(dirArrowClicked(int)), this, SLOT(on_dirArrowClicked(int)));
    connect(ruleScene, SIGNAL(colorRectClicked(int)), this, SLOT(on_colorRectClicked(int)));
    ruleScene->construct(ui->render_area->moveTable, ui->render_area->getBackgroundColor());
    ui->movement_rules_view->setScene(ruleScene);

    stepsBeforeRedraw = ui->spin_speed->value();
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
    ui->render_area->clearScreen();
    ui->render_area->repaint();
}

void MainWindow::setControlsEnabled(bool val)
{
   ui->btn_start->setEnabled(val);
   ui->spin_steps->setEnabled(val);
   ui->spin_speed->setEnabled(val);
   ui->btn_clear->setEnabled(val);
}

void MainWindow::on_dirArrowClicked(int index)
{
    ui->render_area->flipDirAtIndex(index);
    ruleScene->construct(ui->render_area->moveTable, ui->render_area->getBackgroundColor());
}

void MainWindow::on_colorRectClicked(int index)
{
    if(index == 0) return;		// do not let background color to be changed... for now
    QColor newColor = QColorDialog::getColor(ui->render_area->colorIndex[index], this, "Choose New Color");
    ui->render_area->setNewColorAtIndex(index, newColor.rgba());
    ruleScene->construct(ui->render_area->moveTable, ui->render_area->getBackgroundColor());
}
