#include"lru.h"
#include<future>

int main(int argc, char* argv[]) {
	if(argc!=3)
		fprintf(stderr, "Not enough command line arguments");
	string file_name(argv[1]);
	string frame_size(argv[2]);
	least_recently_used(file_name, frame_size);
	return 0;
}
