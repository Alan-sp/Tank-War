#include "resource_lib.h"

bool resource_lib::add_image_resource(int flag, std::string file) {//register pixmap for this flag
	std::map <int, QPixmap>::iterator i;
	i = imap.find(flag);
	if (i != imap.end())return false;//If this flag already exist
	QString qfilename(file.c_str());
	QPixmap img(qfilename);
	imap.insert(std::map<int, QPixmap>::value_type(flag, img));
	return true;
}
bool resource_lib::add_model_resource(int flag, plane_model model) {
	std::map <int, plane_model>::iterator j;
	j = mmap.find(flag);
	if (j != mmap.end())return false;//If this flag already exist
	mmap.insert(std::map<int, plane_model>::value_type(flag, model));
	return true;
}
QPixmap resource_lib::get_image(int flag)//get pixmap by flag
{
	std::map <int, QPixmap>::iterator i;
	i = imap.find(flag);
	if (i == imap.end())return QPixmap();
	return i->second;
}
plane_model resource_lib::get_model(int flag) {
	std::map <int, plane_model>::iterator i;
	i = mmap.find(flag);
	if (i == mmap.end())return plane_model();
	return i->second;
}