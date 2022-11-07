#include "ImageResource.h"

bool ImageResource::addImageResource(int flag, std::string file) {//调用这个方法为object注册图片
	std::map <int, QImage>::iterator i;
	i = imap.find(flag);
	if (i != imap.end())return false;//这个flag已经存在，注册失败
	QString qfilename(file.c_str());
	QImage img(qfilename);
	imap.insert(std::map<int, QImage>::value_type(flag, img));
	return true;//注册成功
}

QImage ImageResource::getImage(int flag)//通过指定的flag获取图片
{
	std::map <int, QImage>::iterator i;
	i = imap.find(flag);
	if (i == imap.end())return QImage();
	return i->second;
}
