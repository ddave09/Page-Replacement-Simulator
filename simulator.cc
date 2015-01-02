#include"lru.h"
#include"async_io.h"
#include<future>

int main(int argc, char* argv[]){
	async(async_file_read, string(argv[1]));
return 0;
}
