#pragma once
#include <unordered_map>
#include "plane_model.h"
#include <qpixmap.h>
class resource_lib
{
private:
	std::unordered_map <int, QPixmap> imap;//QPixmap storage
	plane_model mlist[10000];
	//std::unordered_map <int, plane_model> mmap;//Model storage
public:

	resource_lib() {
		imap = std::unordered_map <int, QPixmap>();
		//mmap = std::unordered_map <int, plane_model>();
	}
	~resource_lib(){}

	bool add_image_resource(int flag, std::string file);
	bool add_model_resource(int flag, plane_model model);
	QPixmap get_image(int flag);
	plane_model get_model(int flag);

};
