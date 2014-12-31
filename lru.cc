#include"lru.h"

struct pagev{
		unsigned accesses;
		unsigned hits;
		unsigned misses;
		pagev(){
			accesses=0;
			hits=0;
			misses=0;
		}
};

unsigned long long gaccesses = 0;
unsigned long long ghits = 0;
unsigned long long gmisses = 0;

/* Least recently used memory page replacement algorithm using STACK method */
void LeastRecentlyUsed(char *file_name,string frame_table_size){
	list<int>lru;
	list<int>::iterator itlru;
	map<int,pagev> page;
	map<int,pagev>::iterator itpage;
	string line;
	int number;
	unsigned long hits=0,misses=0,accesses=0;
	unsigned int lsize =atoi(frame_table_size.c_str());
  	ifstream pf (file_name);
  	if (pf.is_open()){
    		while (getline (pf,line)){
			number = atoi(line.c_str());
			itlru = find(lru.begin(),lru.end(),number);
			if(itlru!=lru.end()){
				int lvalue = *itlru;
				lru.push_back(lvalue);
				lru.erase(itlru);
				itpage = page.find(number);
				if(itpage!=page.end()){
					itpage->second.hits++;
					itpage->second.accesses++;
					gaccesses++;
				}
				else{
					page[number].hits=1;
					page[number].accesses=1;
				}
			}
			else if(lsize == lru.size()){
				lru.remove(lru.front());
				lru.push_back(number);
				itpage = page.find(number);
				if(itpage!=page.end()){
					itpage->second.misses++;
					itpage->second.accesses++;
				}
				else{
					page[number].misses=1;
					page[number].accesses=1;
					
				}
			}
			else{
				lru.push_back(number);
				itpage = page.find(number);
				if(itpage!=page.end()){
					itpage->second.misses++;
					itpage->second.accesses++;
				}
				else{
					page[number].misses=1;
					page[number].accesses=1;
				}
			}				
		}
    		pf.close();
  	}
	else{
	cout << "Unable to open file\n"; 
	}

	ofstream pahm;
	pahm.open ("p_a_h_m.txt");
	pahm<<"Page Numer ---------- Accesses ----------------- Hits ----------------- Misses\n";
	for(itpage=page.begin();itpage!=page.end();itpage++){
		ghits =  ghits + itpage->second.hits;
		gmisses = gmisses + itpage->second.misses;
				stringstream ssfirst,ssa,ssh,ssm;
				ssfirst<<itpage->first;
				string s1=ssfirst.str();
				ssa<<itpage->second.accesses;
				s1=s1+" -------------------- "+ssa.str();
				ssh<<itpage->second.hits;
				s1=s1+" -------------------- "+ssh.str();
				ssm<<itpage->second.misses;
				s1=s1+" -------------------- "+ssm.str();
		pahm<<s1+"\n";
	}
	cout<<"Hits:: " <<ghits << " misses : " <<gmisses<<endl;	
	pahm.close();

}

