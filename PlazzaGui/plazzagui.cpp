/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** GUI
*/

#include "include/plazzagui.h"
#include "ui_plazzagui.h"

PlazzaGui::PlazzaGui(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::PlazzaGui)
{
	ui->setupUi(this);
	
	// m_button = new QPushButton("Quit", this);
	// m_button->setGeometry(10, 10, 80, 30);
	// m_button->move(500, 500);
	// m_button->setEnabled(true);
	// m_button->setUpdatesEnabled(true);
	// QObject::connect(m_button, SIGNAL(clicked()), qApp, SLOT(quit()));	

	// m_lcd = new QLCDNumber(this);
	// m_lcd->move(60, 60);
	// m_lcd->setSegmentStyle(QLCDNumber::Flat);
	// m_lcd->setGeometry(10, 10, 100, 30);

	// m_slider = new QSlider(Qt::Horizontal, this);;
	// m_slider->setGeometry(10, 60, 150, 20);
	// connect(m_slider, SIGNAL(valueChanged(int)), m_lcd, SLOT(display(int)));	
}

PlazzaGui::~PlazzaGui()
{
	delete ui;
}
