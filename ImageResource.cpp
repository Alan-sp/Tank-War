#include "ImageResource.h"

bool ImageResource::addImageResource(int flag, std::string file) {//�����������Ϊobjectע��ͼƬ
	std::map <int, QImage>::iterator i;
	i = imap.find(flag);
	if (i != imap.end())return false;//���flag�Ѿ����ڣ�ע��ʧ��
	QString qfilename(file.c_str());
	QImage img(qfilename);
	imap.insert(std::map<int, QImage>::value_type(flag, img));
	return true;//ע��ɹ�
}

QImage ImageResource::getImage(int flag)//ͨ��ָ����flag��ȡͼƬ
{
	std::map <int, QImage>::iterator i;
	i = imap.find(flag);
	if (i == imap.end())return QImage();
	return i->second;
}
