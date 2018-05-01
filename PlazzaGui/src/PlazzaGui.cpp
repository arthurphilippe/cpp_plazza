/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Gui
*/

#include <QMessageBox>
#include <fstream>
#include "PlazzaGui.hpp"

plazza::master::PlazzaGui::PlazzaGui(int ac, char **av)
	:
	_window(new QWidget()),
	_layout(new QHBoxLayout),
	_bOk(new QPushButton("OK", _window)),
	_groupBox(new QGroupBox("Choose Type", _window)),
	_bIp_address(new QRadioButton("IP_ADDRESS", _groupBox)),
	_bPhone_number(new QRadioButton("PHONE_NUMBER", _groupBox)),
	_bEmail_address(new QRadioButton("EMAIL_ADDRESS", _groupBox)),
	_text(new QPlainTextEdit("", _window)),
	_bChoose(new QPushButton("Choose", _window)),
	_filelistbox(new QGroupBox("Parsing Queue:", _window)),
	_filelistwid(new QListWidget(_window)),
	_info(Information::IP_ADDRESS),
	_cmdQIdx(1)
{
	_window->setFixedSize(1680, 720);
	_bChoose->move(600, 200);
	_bOk->move(600, 600);
	_layout->addWidget(_bIp_address);
	_layout->addWidget(_bEmail_address);
	_layout->addWidget(_bPhone_number);
	_bIp_address->setChecked(true);
	_layout->setAlignment(Qt::AlignCenter);
	_groupBox->setFlat(true);
	_groupBox->move(100, 40);
	_groupBox->setLayout(_layout);
	_window->show();
	_text->move(100, 200);
	_text->setFixedSize(460, 30);
	_filelistbox->move(800, 150);
	_filelistwid->move(800, 175);
	_filelistwid->setFixedSize(650, 200);
	QObject::connect(_bChoose, SIGNAL(clicked()),
				this, SLOT(askFile()));
	QObject::connect(_bIp_address, SIGNAL(clicked()),
				this, SLOT(checkedIpAddress()));
	QObject::connect(_bEmail_address, SIGNAL(clicked()),
				this, SLOT(checkedEAddress()));
	QObject::connect(_bPhone_number, SIGNAL(clicked()),
				this, SLOT(checkedPhoneNbr()));
	QObject::connect(_bOk, SIGNAL(clicked()),
				this, SLOT(validateFile()));
}

plazza::master::PlazzaGui::~PlazzaGui()
{
}

void plazza::master::PlazzaGui::checkedIpAddress()
{
	_info = plazza::Information::IP_ADDRESS;
}

void plazza::master::PlazzaGui::checkedEAddress()
{
	_info = plazza::Information::EMAIL_ADDRESS;
}

void plazza::master::PlazzaGui::checkedPhoneNbr()
{
	_info = plazza::Information::PHONE_NUMBER;
}

void plazza::master::PlazzaGui::validateFile()
{
	std::string filename = _text->toPlainText().toStdString();
	std::ifstream istm(filename);
	if (istm.good()) {
		auto newcmd = Command {filename, _info, _cmdQIdx};
		_cmdQ.push(newcmd);
		_filelist.append(_createCommandQString(newcmd));
		_updateList();
		_cmdQIdx += 1;
	} else {
		QMessageBox error;
		QString errormsg(filename.c_str());
		errormsg.push_front("<p align='center'>");
		errormsg.push_back(": No such file or directory</p>");
		error.setText(errormsg);
		error.exec();
	}
}

QString plazza::master::
PlazzaGui::
_createCommandQString(plazza::Command &cmd)
{
	std::string filestring;
	filestring += "[";
	filestring += std::to_string(cmd.cmdId);
	filestring += "]: Path: `";
	filestring += cmd.cmdFileName;
	filestring += "` | Info: ";
	switch (cmd.cmdInfoType) {
		case Information::EMAIL_ADDRESS:
			filestring += "EMAIL_ADDRESS";
			break;
		case Information::IP_ADDRESS:
			filestring += "IP_ADDRESS";
			break;
		case Information::PHONE_NUMBER:
			filestring += "PHONE_NUMBER";
			break;
		case Information::NONE:
			filestring += "Nothing";
			break;
	}
	QString qstrcmd(filestring.c_str());
	return qstrcmd;
}

void plazza::master::PlazzaGui::_updateList()
{
	_filelistwid->clear();
	_filelistwid->addItems(_filelist);
}

void plazza::master::PlazzaGui::askFile()
{
	auto file = QFileDialog::getOpenFileName(
			0, tr("Plazza: Choose a file to parse", "."));
	if (file.length() > 0)
		_text->setPlainText(file);
}

bool plazza::master::PlazzaGui::poll(std::queue<plazza::Command> &cmdQ)
{
	while (!_cmdQ.empty()) {
		cmdQ.push(_cmdQ.front());
		_filelist.pop_front();
		_cmdQ.pop();
	}
	return true;
}
