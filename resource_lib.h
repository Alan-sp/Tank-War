#pragma once
#include <map>
#include "plane_model.h"
#include <qpixmap.h>
class resource_lib
{
private:
	std::map <int, QPixmap> imap;//QPixmap storage
	std::map <int, plane_model> mmap;//Model storage
public:

	resource_lib() {}
	~resource_lib(){}

	bool add_image_resource(int flag, std::string file);
	bool add_model_resource(int flag, plane_model model);
	QPixmap get_image(int flag);
	plane_model get_model(int flag);

};
