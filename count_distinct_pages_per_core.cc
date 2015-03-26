#include<iostream>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

struct line_members {
	string core;
	string page_num;
};

typedef struct core_info{
	unsigned int d_accesses;
	vector<string> d_list;
	core_info(){
		d_accesses = 0;
	}
}icore ;


void split_line(struct line_members &lm, string line) {
istringstream iss(line);
	int count=0;
	while(iss){
		count++;
		string word;
		iss >> word;
		if(count==1)
			lm.core = word;
		else if(count==2)
			lm.page_num = word;
	}
}

void distinct_page_count(string file_name){
	unsigned long long inc_counter=0, intc_counter=0;
	unordered_map<string, icore> core_map;
	unordered_map<string, icore> :: iterator coreit;
	vector<string> :: iterator vit;
	ifstream pf(file_name);
	string line;
	if (pf.is_open()) {
		while (getline(pf, line)) {
			if(intc_counter == inc_counter){
				cout<<"Working on line "<<intc_counter<<endl;
				intc_counter = inc_counter+1000000;
			}
			inc_counter++;
			struct line_members lm;
			split_line(lm, line);
			vit = find(core_map[lm.core].d_list.begin(), core_map[lm.core].d_list.end(), lm.page_num);
			if(vit == core_map[lm.core].d_list.end()){
				core_map[lm.core].d_list.push_back(lm.page_num);
				core_map[lm.core].d_accesses++;
			}
		}
	}
	
	for(coreit=core_map.begin(); coreit!=core_map.end(); coreit++){
		cout<<coreit->first<<" "<<coreit->second.d_list.size()<<" "<<coreit->second.d_accesses<<endl;
	}
}

int main(int argc, char* argv[]) {
	if(argc!=2)
		fprintf(stderr, "Not enough command line arguments");
	string file_name(argv[1]);
	distinct_page_count(file_name);
	return 0;
}
