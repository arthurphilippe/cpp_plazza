#ifndef PLAZZAGUI_H
#define PLAZZAGUI_H
#include <QPlainTextEdit>
#include <QFileDialog>
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QApplication>
#include <QLCDNumber>
#include <QSlider>
#include <QInputDialog>

#if defined SHAREGUI
 #define SHAREGUI_COMMON_DLLSPEC Q_DECL_EXPORT
#else
 #define SHAREGUI_COMMON_DLLSPEC Q_DECL_IMPORT
#endif


class Counter : public QWidget
{
	Q_OBJECT
public:
	Counter(QWidget *p, QApplication &a) { m_value = 0; _p = p;

	Text = new QPlainTextEdit("file choosen", p);

	Text->move(100, 200);
	Text->setReadOnly(true);
	Text->setGeometry(100, 200, 300, 30);
	Text->setPlainText("AERFG");
	}
	~Counter() {}
	int value() const { return m_value; }
	std::string &get() {return _status;};
	int m_value;
public slots:
	void setValue() {
		bool ok;
		QString tmp;
		tmp =  QInputDialog::getText(_p, "Pseudo", "Kek", QLineEdit::Normal, QString(), &ok);
		if (ok) {
			_status = tmp.toStdString();
		}
		std::cout << _status << std::endl;
	}
	void files() {
		auto file = QFileDialog::getOpenFileName(this, tr("Plazza: Choose File", "."));
		std::cout << file.toStdString() << std::endl;
	}
private:
	QPlainTextEdit *Text;



	QWidget *_p;
	std::string _status;
};

namespace Ui {
class SHAREGUI_COMMON_DLLSPEC PlazzaGui;
}

class SHAREGUI_COMMON_DLLSPEC PlazzaGui : public QMainWindow
{
	Q_OBJECT

public:
	explicit PlazzaGui(QWidget *parent = 0);
	~PlazzaGui();
private:
	Ui::PlazzaGui *ui;
	QPushButton *m_button;
	QLCDNumber *m_lcd;
	QSlider *m_slider;
};

#endif // PLAZZAGUI_H
