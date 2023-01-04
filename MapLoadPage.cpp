#include "MapLoadPage.h"
#include "statics.h"
#include "mapcreate.cpp"
#include "base64.cpp"
#include <sstream>
#include <fstream>
#include "qclipboard.h"
#include "main_game.h"
#include "TankWarGUI.h"
#include <qfiledialog.h>
#include <qmessagebox.h>

MapLoadPage::MapLoadPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.pushButtonClipboard, SIGNAL(clicked()), this, SLOT(fromClipboard()));
	QObject::connect(ui.pushButtonFile, SIGNAL(clicked()), this, SLOT(fromFile()));
	QObject::connect(ui.pushButtonRandom, SIGNAL(clicked()), this, SLOT(randomGenerate()));
	QObject::connect(ui.pushButtonReturn, SIGNAL(clicked()), this, SLOT(return_to_menu()));
	QObject::connect(ui.pushButtonStart, SIGNAL(clicked()), this, SLOT(startGame()));

}

MapLoadPage::~MapLoadPage()
{}

void MapLoadPage::fromClipboard()
{
	auto qclipb = QApplication::clipboard();
	ui.textEdit->setText(qclipb->text());
}

void MapLoadPage::fromFile()
{
	QString filename = QFileDialog::getOpenFileName(this, "打开", ".", "*");
	std::ifstream ifs(filename.toStdString(), std::ios::in);
	if (!ifs) {
		QMessageBox::critical(this, "错误", "无法打开文件");
		return;
	}
	std::istreambuf_iterator<char> beg(ifs), end;
	std::string strdata(beg, end);
	ifs.close();
	ui.textEdit->setText(QString::fromStdString(strdata));
}

void MapLoadPage::randomGenerate()
{
	std::ostringstream oss;
	mapcreate::generateMap(&oss);
	ui.textEdit->setText(QString::fromStdString(Base64::encrypt(oss.str())));
}

void MapLoadPage::return_to_menu()
{
	statics st;
	st.gamegui->showMainFrame();
}

void MapLoadPage::startGame()
{
	statics st;
	this->hide();
	st.maingame->load_map(ui.textEdit->toPlainText().toStdString());
	emit st.gamegui->restart_game();
}
