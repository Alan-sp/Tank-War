#pragma once
#include <map>
#include <qpixmap.h>
class image_resource
{
private:
	std::map <int, QPixmap> imap;//QPixmap storage

public:

	image_resource() {}
	~image_resource(){}

	bool add_image_resource(int flag, std::string file);
	QPixmap get_image(int flag);

};
