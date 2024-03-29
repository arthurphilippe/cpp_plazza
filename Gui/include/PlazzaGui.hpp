/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Gui
*/

#ifndef PLAZZAGUI_HPP_
	#define PLAZZAGUI_HPP_

	#include <QLabel>
	#include <QProgressBar>
	#include <QFileDialog>
	#include <QListWidget>
	#include <QPlainTextEdit>
	#include <QGroupBox>
	#include <QRadioButton>
	#include <QtGui>
	#include <QHBoxLayout>
	#include <QMainWindow>
	#include <QFileDialog>
	#include <QPushButton>
	#include <QWidget>
	#include <QApplication>
	#include "master/IUserController.hpp"
	#include "master/Manager.hpp"

namespace plazza {
	namespace master {
		class PlazzaGui;
	}
}

class
plazza::master::
PlazzaGui :
public QObject,
public plazza::master::IUserController {
	Q_OBJECT
	public:
		PlazzaGui(char **arg);
		~PlazzaGui() override;
	protected:
	private:
		QWidget *_window;
		QHBoxLayout *_layout;
		QPushButton *_bOk;
		QPushButton *_bCompute;
		QGroupBox *_groupBox;
		QRadioButton *_bIp_address;
		QRadioButton *_bPhone_number;
		QRadioButton *_bEmail_address;
		QPlainTextEdit *_text;
		QPushButton *_bChoose;
		QGroupBox *_filelistbox;
		QListWidget *_filelistwid;
		QStringList _filelist;
		QProgressBar *_PBpending;
		QProgressBar *_PBsent;
		QProgressBar *_PBcompleted;
		QLabel *_TxtPending;
		QLabel *_TxtSent;
		QLabel *_TxtCmplt;
		QPushButton *_bComputeFive;
		QLabel *_TxtTodo;

		plazza::Information _info;
		std::queue<Command> _cmdQ;
		std::queue<Command> _cmdQStack;
		uint		_cmdQIdx;
		uint		_threadNb;
		Manager		_manager;
		std::string	_binName;
		QTimer		*_loop;

		QString _createCommandQString(plazza::Command &cmd);
		void _updateList();
		void _updateBar();

	public slots:
		void _compute();
		void _computeFive();
		void checkedPhoneNbr();
		void checkedEAddress();
		void checkedIpAddress();
		void askFile();
		void validateFile();
		void manage();
};

#endif /* !PLAZZAGUI_HPP_ */
