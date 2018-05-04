/*
** EPITECH PROJECT, 2018
** Plazza
** File description:
** Gui
*/

#include <QMessageBox>
#include <fstream>
#include "slave/Launch.hpp"
#include "PlazzaGui.hpp"

plazza::master::PlazzaGui::PlazzaGui(char **arg)
	:
	_window(new QWidget()),
	_layout(new QHBoxLayout),
	_bOk(new QPushButton("OK", _window)),
	_bCompute(new QPushButton("Compute", _window)),
	_groupBox(new QGroupBox("Choose Type", _window)),
	_bIp_address(new QRadioButton("IP_ADDRESS", _groupBox)),
	_bPhone_number(new QRadioButton("PHONE_NUMBER", _groupBox)),
	_bEmail_address(new QRadioButton("EMAIL_ADDRESS", _groupBox)),
	_text(new QPlainTextEdit("/home/cheap/Code_Arena/cpp_plazza/tests/4phone_numbers.txt", _window)),
	_bChoose(new QPushButton("Choose", _window)),
	_filelistbox(new QGroupBox("Parsing Queue:", _window)),
	_filelistwid(new QListWidget(_window)),
	_PBpending(new QProgressBar(_window)),
	_PBsent(new QProgressBar(_window)),
	_PBcompleted(new QProgressBar(_window)),
	_TxtPending(new QLabel(_window)),
	_TxtSent(new QLabel(_window)),
	_TxtCmplt(new QLabel(_window)),
	_bComputeFive(new QPushButton("Compute 5", _window)),
	_TxtTodo(new QLabel(_window)),
	_info(Information::PHONE_NUMBER),
	_cmdQIdx(1),
	_threadNb(std::stoi(arg[1])),
	_manager(_threadNb, _cmdQ),
	_binName(arg[0]),
	_loop(new QTimer(_window))
{
	_window->setFixedSize(1680, 720);
	_bChoose->move(600, 200);
	_bOk->move(470, 330);
	_bCompute->move(600, 330);
	_bComputeFive->move(600, 270);
	_layout->addWidget(_bIp_address);
	_layout->addWidget(_bEmail_address);
	_layout->addWidget(_bPhone_number);
	_bPhone_number->setChecked(true);
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
	QObject::connect(_bCompute, SIGNAL(clicked()),
				this, SLOT(_compute()));
	QObject::connect(_bComputeFive, SIGNAL(clicked()),
				this, SLOT(_computeFive()));
	_TxtPending->move(850, 455);
	_TxtPending->setText(QString("Pending"));
	_TxtPending->adjustSize();
	_PBpending->setValue(0);
	_PBpending->setGeometry(900, 450, 350, 30);
	_TxtSent->move(869, 495);
	_TxtSent->setText(QString("Sent"));
	_TxtSent->adjustSize();
	_PBsent->setValue(0);
	_PBsent->setGeometry(900, 490, 350, 30);
	_TxtCmplt->move(837, 535);
	_TxtCmplt->setText(QString("Completed"));
	_TxtCmplt->adjustSize();
	_TxtTodo->move(1000, 400);
	_TxtTodo->setText("Total Commands: 0");
	_TxtTodo->adjustSize();
	_PBcompleted->setValue(0);
	_PBcompleted->setGeometry(900, 530, 350, 30);
	_loop->setInterval(100);
	QObject::connect(_loop, SIGNAL(timeout()), this, SLOT(manage()));
	_loop->start();
}

void plazza::master::PlazzaGui::manage()
{
	try {
		_manager.manage();
	} catch (plazza::slave::Launch &slaveLauncher) {
		slaveLauncher.exec(_binName.c_str());
	}
}

plazza::master::PlazzaGui::~PlazzaGui()
{
	try {
		_manager.wait();
	} catch (slave::Launch &slaveLauncher) {
		slaveLauncher.exec(_binName.c_str());
	}
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
	std::string info;
	std::string filename = _text->toPlainText().toStdString();
	std::ifstream istm(filename);
	if (istm.good()) {
		auto newcmd = Command {filename, _info, _cmdQIdx};
		_cmdQStack.push(newcmd);
		_filelist.append(_createCommandQString(newcmd));
		_updateList();
		info += "Total Commands: ";
		info += std::to_string(_cmdQIdx);
		_TxtTodo->setText(info.c_str());
		_TxtTodo->adjustSize();
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

void plazza::master::PlazzaGui::update()
{
}

void plazza::master::PlazzaGui::_computeFive()
{
	int i = 5;
	while (!_cmdQStack.empty()) {
		_cmdQ.push(_cmdQStack.front());
		if (_filelist.size() > 0)
			_filelist.pop_front();
		_filelistwid->takeItem(0);
		i -= 1;
		_cmdQStack.pop();
		if (i < 1)
			break;
	}
}

void plazza::master::PlazzaGui::_compute()
{
	while (!_cmdQStack.empty()) {
		_cmdQ.push(_cmdQStack.front());
		if (_filelist.size() > 0)
			_filelist.pop_front();
		_filelistwid->takeItem(0);
		_cmdQStack.pop();
	}
}
