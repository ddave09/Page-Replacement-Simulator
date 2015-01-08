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

unsigned long long ghits = 0;
unsigned long long gmisses = 0;
unsigned long long core_stat[num_of_cores] = {0};

void generate_page_report(map<int, pagev> page, map<int, pagev>::iterator itpage){
	ofstream paging_report, aim_report;
	paging_report.open("paging_report.txt");
	paging_report
			<< "Page Numer ---------- Accesses ----------------- Hits ----------------- Misses\n";
	for (itpage = page.begin(); itpage != page.end(); itpage++) {
		ghits = ghits + itpage->second.hits;
		gmisses = gmisses + itpage->second.misses;
		paging_report<<itpage->first<<"----------"<<itpage->second.accesses<<"-----------------"<<itpage->second.hits
			<<"-----------------"<<itpage->second.misses<<endl;
	}
	aim_report.open("Aim_report.txt");
	aim_report<<"Accesses     Hits     Misses\n";
	aim_report<<"Accesses:: "<<ghits+gmisses<< "Hits:: " << ghits << " Misses : " << gmisses; 
	aim_report.close();
	cout << "Accesses:: "<<ghits+gmisses<< "Hits:: " << ghits << " Misses : " << gmisses << endl;
	paging_report.close();
}

void generate_core_report(unsigned long long core_stat[]){
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
	list<int> lru;
	list<int>::iterator itlru;
	map<int, pagev> page;
	map<int, pagev>::iterator itpage;
	string line;
	int number;
	unsigned int lsize = atoi(frame_size.c_str());
	ifstream pf(file_name);
	if (pf.is_open()) {
		while (getline(pf, line)) {
			if(intc_counter == inc_counter){
				cout<<"Working on: "<<intc_counter<<"line"<<endl;
				intc_counter = inc_counter+1000000;
			}
			inc_counter++;
			struct line_members lm;
			split_line(lm, line);
			number = atoi(lm.page_num.c_str());
			itlru = find(lru.begin(), lru.end(), number);
			if (itlru != lru.end()) {
				int lvalue = *itlru;
				lru.push_back(lvalue);
				lru.erase(itlru);
				itpage = page.find(number);
				if (itpage != page.end()) {
					itpage->second.hits++;
					itpage->second.accesses++;
				} else {
					page[number].hits = 1;
					page[number].accesses = 1;
				}
			} else if (lsize == lru.size()) {
				lru.remove(lru.front());
				lru.push_back(number);
				itpage = page.find(number);
				if (itpage != page.end()) {
					itpage->second.misses++;
					itpage->second.accesses++;
					core_stat[atoi(lm.core.c_str())]++;
				} else {
					page[number].misses = 1;
					page[number].accesses = 1;
					core_stat[atoi(lm.core.c_str())]++;
				}
			} else {
				lru.push_back(number);
				itpage = page.find(number);
				if (itpage != page.end()) {
					itpage->second.misses++;
					itpage->second.accesses++;
					core_stat[atoi(lm.core.c_str())]++;
				} else {
					page[number].misses = 1;
					page[number].accesses = 1;
					core_stat[atoi(lm.core.c_str())]++;
				}
			}
		}
		pf.close();
	} else {
		cout << "Unable to open file\n";
	}

	/* Report Generation */
	generate_page_report(page, itpage);
	generate_core_report(core_stat);
}

