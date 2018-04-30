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
	Counter(QWidget *p, QApplication *&a, QPlainTextEdit *&Text) :_text(Text) { m_value = 0; _p = p;

	_text->move(100, 200);
	_text->setReadOnly(true);
	_text->setGeometry(100, 200, 600, 30);
	_text->setPlainText("AERFG");
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
		_text->setPlainText(file);
	}
private:
	QWidget *_p;
	QPlainTextEdit *_text;
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
