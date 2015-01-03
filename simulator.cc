#include"lru.h"
#include"async_io.h"
#include<future>

int main(int argc, char* argv[]){
	future<bool> fut = async(async_file_read, string(argv[1]));
	bool  init = fut.get();
	if(init)
		cout<<"System Initialized"<<endl;
	else{
		cout<<argv[1] << " couldn't open correctly"<<endl;
		exit(2);
	}
return 0;
}
