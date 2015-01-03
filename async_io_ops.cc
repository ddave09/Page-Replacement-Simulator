#include"async_io.h"
#include<fstream>

bool async_file_read(string file_name){
	ifstream trace(file_name, ifstream::in);
	return trace.is_open();
}
