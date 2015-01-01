#include"lru.h"
#include"async_io.h"

int main(int argc, char* argv[]){
	count_accesses(argv[1]);
	string frame_table_size(argv[2]);
	LeastRecentlyUsed(argv[1],frame_table_size);
return 0;
}
