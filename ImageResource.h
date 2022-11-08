#pragma once
#include <map>
#include <qpixmap.h>
class ImageResource
{
private:
	std::map <int, QPixmap> imap;//QPixmap storage

public:

	ImageResource() {}
	~ImageResource(){}

	bool addImageResource(int flag, std::string file);
	QPixmap getImage(int flag);

};
