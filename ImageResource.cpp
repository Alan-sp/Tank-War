#include "ImageResource.h"

bool image_resource::add_image_resource(int flag, std::string file) {//register pixmap for this flag
	std::map <int, QPixmap>::iterator i;
	i = imap.find(flag);
	if (i != imap.end())return false;//If this flag already exist
	QString qfilename(file.c_str());
	QPixmap img(qfilename);
	imap.insert(std::map<int, QPixmap>::value_type(flag, img));
	return true;
}

QPixmap image_resource::get_image(int flag)//get pixmap by flag
{
	std::map <int, QPixmap>::iterator i;
	i = imap.find(flag);
	if (i == imap.end())return QPixmap();
	return i->second;
}
