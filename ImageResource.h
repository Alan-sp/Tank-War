#pragma once
#include <map>
#include <qimage.h>
class ImageResource
{
private:
	std::map <int, QImage> imap;//����ͼƬ

public:

	ImageResource() {}
	~ImageResource(){}

	bool addImageResource(int flag, std::string file);
	QImage getImage(int flag);

};

