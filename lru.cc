#include"lru.h"
#define num_of_cores 4

struct pagev {
	unsigned long long accesses;
	unsigned long long hits;
	unsigned long long misses;
	pagev() {
		accesses = 0;
		hits = 0;
		misses = 0;
	}
};

struct line_members {
	string core;
	string page_num;
};

unordered_map<int, pagev> page;
unordered_map<int, pagev>::iterator itpage;
unsigned long long ghits = 0;
unsigned long long gmisses = 0;
unsigned long long core_stat[num_of_cores] = {0};

void record_page_stat(int number, bool c){
	if(c)
		page[number].hits++;
  else
		page[number].misses++;	
	page[number].accesses++;
}

void generate_aim_report(){
	ofstream aim_report;
	aim_report.open("Aim_report.txt");
	aim_report<<"Accesses     Hits     Misses\n";
	aim_report<<ghits+gmisses<<" "<<ghits<<"  "<<gmisses << endl;
	aim_report.close();
	cout<<"Accesses:: "<<ghits+gmisses<< "Hits:: " << ghits << " Misses : " << gmisses<<endl;
}

void generate_page_report(){
	ofstream paging_report;
	paging_report.open("paging_report.txt");
	paging_report
			<< "Page Numer ---------- Accesses ----------------- Hits ----------------- Misses\n";
	for (itpage = page.begin(); itpage != page.end(); itpage++) {
		paging_report<<itpage->first<<"----------"<<itpage->second.accesses<<"-----------------"<<itpage->second.hits
			<<"-----------------"<<itpage->second.misses<<endl;
	}
	paging_report.close();
}

void generate_core_report(){
	ofstream core_report;
	core_report.open("core_miss_report.txt");
	for(int i=0; i<num_of_cores; i++){
		core_report<<i<<": "<<core_stat[i]<<endl;
	}
	core_report.close();
}

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

void least_recently_used(string file_name, string frame_size) {
  unsigned long long intc_counter = 0, inc_counter = 0;
	deque<int> lru;
	deque<int>:: iterator itlru;
	string line;
	int number;
	unsigned int lsize = atoi(frame_size.c_str());
	ifstream pf(file_name);
	if (pf.is_open()) {
		while (getline(pf, line)) {
			if(intc_counter == inc_counter){
				cout<<"Working on line "<<intc_counter<<endl;
				intc_counter = inc_counter+1000000;
			}
			inc_counter++;
			struct line_members lm;
			split_line(lm, line);
			number = atoi(lm.page_num.c_str());
			itlru = find(lru.begin(), lru.end(), number);
			if (itlru != lru.end()) {
				int lvalue = *itlru;
				lru.erase(itlru);
				lru.push_back(lvalue);
				ghits++;
				record_page_stat(number, true);
			} else if (lsize == lru.size()) {
				lru.pop_front();
				lru.push_back(number);
				gmisses++;
				core_stat[atoi(lm.core.c_str())]++;
				record_page_stat(number, false);
			} else {
				lru.push_back(number);
				gmisses++;
				core_stat[atoi(lm.core.c_str())]++;
				record_page_stat(number, false);
			}
		}
		pf.close();
	} else {
		cout << "Unable to open file\n";
	}

	/* Report Generation */
	generate_aim_report();
	generate_core_report();
	generate_page_report();
	cout<<"Done!"<<endl;
}

