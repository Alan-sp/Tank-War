#include "ImageResource.h"

bool ImageResource::addImageResource(int flag, std::string file) {
	std::map <int, QImage>::iterator i;
	i = imap.find(flag);
	if (i != imap.end())return false;//���flag�Ѿ�����
	QString qfilename(file.c_str());
	QImage img(qfilename);
	imap.insert(std::map<int, QImage>::value_type(flag, img));
	return true;
}

QImage ImageResource::getImage(int flag)
{
	std::map <int, QImage>::iterator i;
	i = imap.find(flag);
	if (i == imap.end())return QImage();
	return i->second;
}
