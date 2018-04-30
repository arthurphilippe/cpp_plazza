#include <QPlainTextEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QtGui>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QLocale>
#include <QFileDialog>
#include <QLibraryInfo>
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include "include/plazzagui.h"


int main(int argc, char *argv[])
{
	QApplication *a = new QApplication(argc, argv);
	QWidget *wind = new QWidget();
	QHBoxLayout *layout = new QHBoxLayout;
	QPushButton *yay = new QPushButton("OK", wind);
	QPushButton *b1 = new QPushButton("Bouton 1");
	QGroupBox *t = new QGroupBox("Choose Type", wind);
	QRadioButton *ip_address = new QRadioButton("IP_ADDRESS", t);
	QRadioButton *phone_number = new QRadioButton("PHONE_NUMBER", t);
	QRadioButton *email_address = new QRadioButton("EMAIL_ADDRESS", t);
	QPlainTextEdit *Text = new QPlainTextEdit("file choosen", wind);
	Counter *b = new Counter(t, a, Text);
	QPushButton *ChooseFolder = new QPushButton("Choose", wind);

	QObject::connect(ChooseFolder, SIGNAL(clicked()), b, SLOT(files()));
	wind->setFixedSize(1280, 720);
	ChooseFolder->move(600, 200);
	yay->move(600, 600);
	b1->setGeometry(10, 10, 80, 30);
	layout->addWidget(ip_address);
	layout->addWidget(phone_number);
	layout->addWidget(email_address);
	layout->setAlignment(Qt::AlignCenter);
	t->setFlat(true);
	t->setLayout(layout);
	t->move(100, 40);
	QObject::connect(yay, SIGNAL(clicked()), b, SLOT(setValue()));
	wind->show();
	return a->exec();
}
