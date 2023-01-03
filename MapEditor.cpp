#include "MapEditor.h"
#include <fstream>
#include <sstream>

MapEditor::MapEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setFixedSize(1300, 800);

	qclipb = QApplication::clipboard();

	QObject::connect(ui.actionCopyToClipboard, SLOT(triggered()), this, SLOT(save_to_clipboard()));
	QObject::connect(ui.actionReadFromClipboard, SLOT(triggered()), this, SLOT(read_from_clipboard()));
	QObject::connect(ui.actionSaveToFile, SLOT(triggered()), this, SLOT(save_to_file()));
	QObject::connect(ui.actionReadFromFile, SLOT(triggered()), this, SLOT(read_from_file()));

}

MapEditor::~MapEditor()
{}

void MapEditor::save_to_clipboard() {
	qclipb->setText(QString::fromStdString(MapCoder::encode(tempmap)));
}

void MapEditor::read_from_clipboard()
{
	tempmap = MapCoder::decode(qclipb->text().toStdString());
}

void MapEditor::save_to_file()
{
	QString filename = QFileDialog::getSaveFileName(this, "保存到", ".", "*");
	std::ofstream ofs(filename.toStdString(),std::ios::out);
	if (!ofs) {
		QMessageBox::critical(this, "错误", "无法打开文件");
		return;
	}
	ofs << MapCoder::encode(tempmap);
	ofs.flush();
	ofs.close();
}

void MapEditor::read_from_file()
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
	tempmap = MapCoder::decode(strdata);
}
