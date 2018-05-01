/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Gui
*/

#ifndef PLAZZAGUI_HPP_
	#define PLAZZAGUI_HPP_

#include <QtCore/QtGlobal>

	#include <QFileDialog>
	#include <QListWidget>
	#include <QPlainTextEdit>
	#include <QGroupBox>
	#include <QRadioButton>
	#include <QtGui>
	#include <QHBoxLayout>
	#include <QMainWindow>
	#include <QFileDialog>
	#include <QLibraryInfo>
	#include <QPushButton>
	#include <QWidget>
	#include <QApplication>

	#include "IUserController.hpp"

namespace plazza {
	namespace master {
	class  PlazzaGui;
}
}

class
plazza::master::
PlazzaGui :
public QObject,
public plazza::master::IUserController {
	Q_OBJECT
	public:
		PlazzaGui(int ac, char **av);
		~PlazzaGui();
        bool poll(std::queue<Command> &cmdQ);
	protected:
	private:
		QWidget *_window;
		QHBoxLayout *_layout;
		QPushButton *_bOk;
		QGroupBox *_groupBox;
		QRadioButton *_bIp_address;
		QRadioButton *_bPhone_number;
		QRadioButton *_bEmail_address;
		QPlainTextEdit *_text;
		QPushButton *_bChoose;
		QGroupBox *_filelistbox;
		QListWidget *_filelistwid;
		QStringList _filelist;
		plazza::Information _info;
		std::queue<Command> _cmdQ;
		uint _cmdQIdx;

		QString _createCommandQString(plazza::Command &cmd);
		void _updateList();

	public slots:
		void checkedPhoneNbr();
		void checkedEAddress();
		void checkedIpAddress();
		void askFile();
		void validateFile();
};

#endif /* !PLAZZAGUI_HPP_ */
