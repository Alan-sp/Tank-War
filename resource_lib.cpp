#include "resource_lib.h"

bool resource_lib::add_image_resource(int flag, std::string file) {//register pixmap for this flag
	auto i = imap.find(flag);
	if (i != imap.end())return false;//If this flag already exist
	QString qfilename(file.c_str());
	QPixmap img(qfilename);
	imap[flag] = img;
	return true;
}
bool resource_lib::add_model_resource(int flag, plane_model model) {
	//auto j = mmap.find(flag);
	//if (j != mmap.end())return false;//If this flag already exist
	//mmap[flag] = model;
	//return true;
	if (mlist[flag] != NULL)return false;
	mlist[flag] = &model;
	return true;
}
QPixmap resource_lib::get_image(int flag)//get pixmap by flag
{
	auto i = imap.find(flag);
	if (i == imap.end())return QPixmap();
	return i->second;
}
plane_model resource_lib::get_model(int flag) {
	/*auto i = mmap.find(flag);
	if (i == mmap.end())return plane_model();
	return i->second;*/
	if (flag < 0 || mlist[flag] == NULL)return plane_model();
	return *mlist[flag];
}