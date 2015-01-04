#include"lru.h"
#include<future>

int main(int argc, char* argv[]){
	string file_name(argv[1]);
	string frame_table_size(argv[2]);
	least_recently_used(file_name, frame_table_size);
return 0;
}
