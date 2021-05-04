#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
using namespace std;
class Valley; 		
class Lake;  		
class Duck;  		
class Farm;			
class Hunter;		
class Attribute;	
enum State{			
	main_menu,		
	valley_info,	
	lake_info,		
	farm_info,		
	input_lake,		
	input_duck,		
	input_farm,
	input_id	
};
enum Ability{
	bites, knowshome, swims, flies, fishes //don't forget to add one of each to "allabilities" vector!
};
vector<Ability> allabilities;
void display_ability(Ability *ability){
	switch(*ability){
		case bites:
			cout<<"êóñàòüñÿ";
			break;
		case knowshome:
			cout<<"çíàòü äîðîãó äîìîé";
			break;
		case swims:
			cout<<"ïëàâàòü";
			break;
		case flies:
			cout<<"ëåòàòü";
			break;
		case fishes:
			cout<<"ðûáà÷èòü";
			break;
	}
}
bool IsSubset(vector<Ability> A, vector<Ability> B)
{
	for(int i=0;i<A.size();i++){
    	bool found;
    	found=false;
    	for(int j=0;j<B.size();j++){
    		if(B[j]==A[i])found=true;
		}
		if(!found){
			return false;
		}
	}
	return true;
}
class Lake{
	public:
	string name;
	vector <Duck> ducks;
	bool wild;
	Farm *farm;
	Lake(string name, bool wild){
		this->name=name;
		this->wild=wild;
	}
	void assign_farm(Farm *farm){
		this->farm=farm;
	}
	int getnducks(){
		return ducks.size();
	}
	void add_duck(Duck *duck);
	void display_info();
	void display_info_about_duck(int nduck);
};
class Farm{
	public:
	string name;
	vector <Hunter> hunters;
	vector <Ability> toescape;
	Lake *lake;
	bool  random;
	Farm(string name, Lake *lake, bool random){
		this->random=random;
		this->name=name;
		this->lake=lake;
		lake->assign_farm(this);  //×òî ýòî íàõóé?
	}
	void add_ability(Ability *a){
		toescape.push_back(*a);
	}
	void add_hunter(Hunter *hunter);
	string get_name(){
		return name;
	}
	void display_info_about_lake(){
		lake->display_info();
	}
	void display_info_about_hunters();
	void display_info(){
		cout<<"Ôåðìà "<<name<<", èìååò "<<hunters.size()<<" îõîòíèêîâ\n";
		cout<<"×òîáû ñáåæàòü, óòêå íóæíî óìåòü: ";
		for(int i=0;i<toescape.size();i++){
			if(i!=0)cout<<", ";
			display_ability(&toescape[i]);
		}
		cout<<".\n";
	}
};
class Attribute{
	public:
	string name;
	string str;
	int value;
	Attribute(string name, string str, int value){
		this->name=name;
		this->str=str;
		this->value=value;
	}
	void display_info(){
		if(value==-1){
			cout<<name<<" - "<<str;
		}else{
			cout<<name<<"="<<value;
		}
	}
};
class Duck{
	public:
	string name;
	vector <Ability> abilities;
	vector <Attribute> attrs;
	vector <string> path;
	string home, lake;
	int id;
	bool canescape;
	bool escaped;
	bool action;
	Duck(string name, int id){
		this->name=name;
		canescape=true;
		escaped=false;
		action=false;
		this->id=id;
	}
	void assign_lake(Lake *home){
		this->lake=home->name;
		this->home=home->name;
		path.push_back(home->name);
	}
	void add_ability(Ability *a){
		abilities.push_back(*a);
	}
	void add_attribute(Attribute *a){
		attrs.push_back(*a);
	}
	void display_info(){
		cout<<"Óòêà âèäà "<<name<<", id="<<id<<", äîì "<<home<<((canescape)?", êðûëüÿ íå ïîäðåçàíû":" êðûëüÿ ïîäðåçàíû")<<"\n";
		cout<<"Ìîæåò: ";
		for(int i=0;i<abilities.size();i++){
			if(i!=0)cout<<", ";
			display_ability(&abilities[i]);
		}
		cout<<".\n";
		cout<<"Ñâîéñòâà: ";
		for(int i=0;i<attrs.size();i++){
			if(i!=0)cout<<", ";
			attrs[i].display_info();
		}
		cout<<"\n";
		cout<<"Å¸ ïóòü: ";
		for(int i=0;i<path.size();i++){
			cout<<path[i]<<", ";
		}
		cout<<"\n";
	}
};
void Lake::display_info(){   
		cout<<"Îçåðî "<<name<<", íà í¸ì "<< ducks.size()<<" óòîê";
		if(!wild)
			cout<<", ïðèíàäëåæèò ôåðìå "<<farm->get_name()<<"\n";
		else
			cout<<", äèêîå\n";
		vector<int> count;
		int c=0;
		for(int i=0;i<allabilities.size();i++){
			c=0;
			for(int j=0;j<ducks.size();j++){
			
				if (std::find(ducks[j].abilities.begin(), ducks[j].abilities.end(), allabilities[i]) != ducks[j].abilities.end()){
					c+=1;
				}
			}
			count.push_back(c);
		}
		cout<<"Ñðåäè óòîê: ";
		for(int i=0;i<allabilities.size();i++){
			if(count[i]==0)continue;
			display_ability(&allabilities[i]);
			cout<<" - "<<count[i]<<", ";
		}
		cout<<"\n";
		count.clear();
	}

void Lake::display_info_about_duck(int nduck){
	ducks[nduck].display_info();
}

void Lake::add_duck(Duck *duck){
		duck->assign_lake(this);
		ducks.push_back(*duck);
	}
class Hunter{
	public:
	int min, max;
	int number;
	Farm *farm;
	Hunter(int min, int max){
		this->min=min;
		this->max=max;
	}
	void assign_farm(Farm *farm){
		this->farm=farm;
	}	
	void display_info(){
		cout<<"Îõîòíèê ìîæåò ïîéìàòü îò "<<min<<" óòîê äî "<<max<<" óòîê\n";
	}
};
void Farm::add_hunter(Hunter *hunter){
		hunters.push_back(*hunter);
		hunter->assign_farm(this);
	}
void Farm::display_info_about_hunters(){
	for(int i=0;i<hunters.size();i++){
		cout<<"Îõîòíèê ¹"<<i+1<<"\n";
		hunters[i].display_info();
	}
}
class Valley{
	public:
	int hunting_days_left;
	vector <Lake> lakes;
	vector <Farm> farms;
	void display_info(){
		if(hunting_days_left>=0)
			cout<<"Â äîëèíå "<<lakes.size()<<" äèêèõ îçåð è "<<farms.size()<<" ôåðì, äî êîíöà ñåçîíà îõîòû îñòàëîñü "<<hunting_days_left<<" äíåé\n";
			else
			cout<<"Â äîëèíå "<<lakes.size()<<" äèêèõ îçåð è "<<farms.size()<<" ôåðì, ñåçîí îõîòû çàêîí÷èëñÿ\n";
	}
	void display_info_about_lake(int nlake){
		lakes[nlake].display_info();
	}
	void display_info_about_farm(int nfarm){
		farms[nfarm].display_info();
	}
	void display_info_about_farm_lake(Farm *farm){
		farm->display_info_about_lake();
	}
	void display_info_about_farm_hunters(Farm *farm){
		farm->display_info_about_hunters();
	}
	Valley(int hunting_days_left){
		this->hunting_days_left=hunting_days_left;
	}
	void add_lake(Lake *lake){
		lakes.push_back(*lake);
	}
	void add_farm(Farm *farm){
		farms.push_back(*farm);
	}
	int getdays(){
		return hunting_days_left;
	}
	void day_passes(){
		hunting_days_left-=1;
	}
	Lake *get_lake(int nlake){
		return &lakes[nlake];
	}
	Farm *get_farm(int nfarm){
		return &farms[nfarm];
	}
	int getnlakes(){
		return lakes.size();
	}
	int getnfarms(){
		return farms.size();
	}
	int lake_getnducks(Lake *lake){
		return lake->getnducks();
	}
	Lake *findlake(string name){
		for(int i=0;i<lakes.size();i++){
			if(lakes[i].name==name)
			return &lakes[i];
		}
		return NULL;
	}
	void display_info_about_duck_by_id(int id){
		for(int i=0;i<lakes.size();i++){
			for(int j=0;j<lakes[i].ducks.size();j++){
				if(lakes[i].ducks[j].id==id){
					lakes[i].ducks[j].display_info();
					return;
				}
			}
		}
		for(int i=0;i<farms.size();i++){
			for(int j=0;j<farms[i].lake->ducks.size();j++){
				if(farms[i].lake->ducks[j].id==id){
					farms[i].lake->ducks[j].display_info();
					return;
				}
			}
		}
		cout<<"Óòêà ñ òàêèì id íå íàéäåíà\n";
	}
	void simulate(){
    	mt19937 r(static_cast<unsigned int>(time(0)));
		if(hunting_days_left>0)
			for(int i=0;i<farms.size();i++){
				uniform_int_distribution<int> dist(0,lakes.size()-1);
				int targetlake=dist(r);
				int caught;
				caught=0;
				for(int j=0;j<farms[i].hunters.size();j++){
					uniform_int_distribution<int> dist2(farms[i].hunters[j].min,farms[i].hunters[j].max-1);
					caught+=dist2(r);
				}
				if(caught>lakes[targetlake].ducks.size())caught=lakes[targetlake].ducks.size();		
				cout<<"Îõîòíèêè ñ ôåðìû "<<farms[i].name<<" îòïðàâèëèñü íà îçåðî "<<lakes[targetlake].name<<" è ïîéìàëè "<<caught<<" óòîê\n";
				vector <int> caughtvec;
				for(int j=0;j<caught;j++){
					uniform_int_distribution<int> dist3(0,lakes[targetlake].ducks.size()-1);		
					int nduck=dist3(r);
					if (std::find(caughtvec.begin(), caughtvec.end(), nduck) != caughtvec.end()){
						j-=1;
						continue;
					}
					caughtvec.push_back(nduck);
				}
				cout<<caughtvec.size()<<"\n";
				bool bites_bool;
				bites_bool=false;
				for(int j=0;j<caughtvec.size();j++){
					Duck duck=lakes[targetlake].ducks[caughtvec[j]];
					Ability ability(bites);
					if (std::find(lakes[targetlake].ducks[caughtvec[j]].abilities.begin(), lakes[targetlake].ducks[caughtvec[j]].abilities.end(), ability) != lakes[targetlake].ducks[caughtvec[j]].abilities.end())
						bites_bool=true;
					uniform_int_distribution<int> dist3(0,(bites_bool)?100:49);		
					int chance=dist3(r);
					if(chance>=50){
						cout<<"Óòêå "<<duck.name<<"(id="<<duck.id<<") óäàëîñü óêóñèòü îõîòíèêà è óáåæàòü\n";
						continue;
					}
					lakes[targetlake].ducks.erase(lakes[targetlake].ducks.begin()+caughtvec[j]);
					cout<<"Óòêà "<<duck.name<<"(id="<<duck.id<<") ïîéìàíà";
					if(duck.escaped){
						duck.canescape=false;
						cout<<" è åé ïîäðåçàëè êðûëî\n";
					}else{
						cout<<"\n";
					}
					duck.action=true;
					duck.path.push_back(farms[i].lake->name);
					farms[i].lake->ducks.push_back(duck);
					
				}
				caughtvec.clear();
			}
		for(int i=0;i<farms.size();i++){
			for(int j=0;j<farms[i].lake->ducks.size();j++){
				if(farms[i].lake->ducks[j].action)continue;
				if(!farms[i].lake->ducks[j].canescape)continue;
				uniform_int_distribution<int> dist3(0,9);
				int chance=dist3(r);	
				if(IsSubset(farms[i].lake->ducks[j].abilities,farms[i].toescape))
				if(chance<5)
				{
					Duck duck = farms[i].lake->ducks[j];
					cout<<"Óòêà "<<duck.name<<"(id="<<duck.id<<") óáåæàëà ñ ôåðìû "<<farms[i].name;
					if (!farms[i].random){
						cout<<" íà îçåðî "<<duck.home<<"\n";
						farms[i].lake->ducks.erase(farms[i].lake->ducks.begin()+j);
						j-=1;
						duck.escaped=true;
						duck.action=true;
						duck.path.push_back(duck.home);
						findlake(duck.home)->ducks.push_back(duck);
					}else{
						uniform_int_distribution<int> dist4(0,lakes.size()-1);
						duck.home=lakes[dist4(r)].name;
						cout<<" íà ñëó÷àéíîå îçåðî "<<duck.home<<"\n";
						farms[i].lake->ducks.erase(farms[i].lake->ducks.begin()+j);
						j-=1;
						duck.escaped=true;
						duck.action=true;
						duck.path.push_back(duck.home);
						findlake(duck.home)->ducks.push_back(duck);
					}
				}
			}
		}
		for(int i=0;i<farms.size();i++){
			for(int j=0;j<farms[i].lake->ducks.size();j++){
				farms[i].lake->ducks[j].action=false;
			}
		}
		for(int i=0;i<lakes.size();i++){
			for(int j=0;j<lakes[i].ducks.size();j++){
				lakes[i].ducks[j].action=false;
			}
		}
		hunting_days_left-=1;
	}
};

int main(int argc, char** argv) {
	setlocale(0,"rus");
	Valley *valley = new Valley(8);
	Lake *lake = new Lake("×åëàí",true);
	Duck *duck;
	Ability *ability;
	ability = new Ability(bites);
	allabilities.push_back(*ability);
	ability = new Ability(knowshome);
	allabilities.push_back(*ability);
	ability = new Ability(swims);
	allabilities.push_back(*ability);
	ability = new Ability(flies);
	allabilities.push_back(*ability); 
	ability = new Ability(fishes);
	allabilities.push_back(*ability);
	Attribute *attribute;
	int id=0;
	for(int i=0;i<30;i++){
		duck=new Duck("Ãîãîëü",id++);
		ability = new Ability(flies);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("Èìÿ","Äîíàëüä",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âåñ","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Ðàçìàõ êðûëüåâ","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Öâåò ãëàç","Êàðèé",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("Íûðêà",id++);
		ability = new Ability(bites);
		duck->add_ability(ability);
		attribute= new Attribute("Èìÿ","Äîíàëüä",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âåñ","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âûñîòà","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Ñèëà","",8);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("Ìàòàíî",true);
	for(int i=0;i<30;i++){
		duck=new Duck("×èðîê-ñâèñòóíîê",id++);
		ability = new Ability(flies);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("Èìÿ","×è",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âåñ","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Ðàçìåð ëàï","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âûíîñëèâîñòü","",3);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("Õîõëàòàÿ",id++);
		ability = new Ability(fishes);
		duck->add_ability(ability);
		attribute= new Attribute("Èìÿ","Äîíàëüä",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âåñ","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âûñîòà","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Ðàçìåð õâîñòà","",8);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("Õàóðîêî",true);
	for(int i=0;i<30;i++){
		duck=new Duck("Íûðêè",id++);
		ability = new Ability(swims);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("Èìÿ","Ôàìèëèÿ",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âåñ","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Õîááè","Äèàëåêòèêà",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Öâåò ãëàç","Ìîðñêîé âîëíû",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<34;i++){
		duck=new Duck("Õîõëàòàÿ",id++);
		ability = new Ability(bites);
		duck->add_ability(ability);
		attribute= new Attribute("Èìÿ","Âîëîäiìið",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Âåñ","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Îêðàñ êëþâà","æåëòûé",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Öâåò","ñèçûé",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("RUCEFOLO",false);
	Farm *farm = new Farm("RUCEFOLO",lake,true);
	ability = new Ability(swims);
	farm->add_ability(ability);
	ability = new Ability(knowshome);
	farm->add_ability(ability);
	Hunter *hunter = new Hunter(1,9);
	farm->add_hunter(hunter);
	hunter = new Hunter(3,7);
	farm->add_hunter(hunter);
	valley->add_farm(farm);
	lake = new Lake("TIQACED",false);
	farm= new Farm("TIQACED",lake,false);
	ability = new Ability(flies);
	farm->add_ability(ability);
	ability = new Ability(knowshome);
	farm->add_ability(ability);
	hunter = new Hunter(3,10);
	farm->add_hunter(hunter);
	hunter = new Hunter(3,8);
	farm->add_hunter(hunter);
	valley->add_farm(farm);
	string option;
	int opt=0;
	State state=main_menu;
	bool nextoption=true;
	int num=0;
	int pre_num=-1;	
	while(1){
		switch (state){
			case main_menu:
				cout<<"Îïöèè:\n";
				cout<<"1. Óçíàòü èíôîðìàöèþ î äîëèíå\n";
				cout<<"2. Ñäåëàòü õîä\n";
				cout<<"3. Âûõîä\n";
				_flushall();
				break;
			case valley_info:
				cout<<"Îïöèè:\n";
				cout<<"1. Óçíàòü èíôîðìàöèþ îá îçåðå\n";
				cout<<"2. Óçíàòü èíôîðìàöèþ î ôåðìå\n";
				cout<<"3. Óçíàòü èíôîðìàöèþ îá óòêå ïî ID\n";
				cout<<"4. Â ãëàâíîå ìåíþ\n";
				_flushall();
				break;
			case farm_info:
				cout<<"Îïöèè:\n";
				cout<<"1. Óçíàòü èíôîðìàöèþ îá îçåðå\n";
				cout<<"2. Óçíàòü èíôîðìàöèþ îá îõîòíèêàõ\n";
				cout<<"3. Â ãëàâíîå ìåíþ\n";
				_flushall();
				break;
			case lake_info:
				cout<<"Îïöèè:\n";
				cout<<"1. Óçíàòü èíôîðìàöèþ îá óòêå\n";
				cout<<"2. Â ãëàâíîå ìåíþ\n";
				_flushall();
				break;
			case input_lake:
				cout<<"Â äîëèíå "<<valley->getnlakes()<<" îçåðà\n";
				cout<<"Ââåäèòå íîìåð îçåðà:\n";
				_flushall();
				break;
			case input_farm:
				cout<<"Â äîëèíå "<<valley->getnfarms()<<" ôåðìû\n";
				cout<<"Ââåäèòå íîìåð ôåðìû:\n";
				_flushall();
				break;
			case input_duck:
				cout<<"Íà îçåðå "<<valley->lake_getnducks(lake)<<" óòîê\n";
				cout<<"Ââåäèòå íîìåð óòêè:\n";
				_flushall();
				break;
			case input_id:
				cout<<"Ââåäèòå ID óòêè:\n";
				_flushall();
				break;
		}
		cin>>option;
		cout<<"\n";
		if(nextoption)
		switch(option[0]){
			case '1':
				switch(state){
					case main_menu:
						valley->display_info();
						state=valley_info;	
						break;
					case valley_info:
						state=input_lake;
						nextoption=false;
						break;
					case lake_info:
						if(lake->ducks.size()==0){
							cout<<"Óòîê íà îçåðå íåò\n";
							break;
						}else{	
							state=input_duck;
							nextoption=false;
							break;
						}
					case farm_info:
						state=lake_info;
						lake=farm->lake;
						valley->display_info_about_farm_lake(farm);
						break;
				}
				break;
			case '2':
				switch(state){
					case main_menu:
						valley->simulate();
						break;
					case lake_info:
						state=main_menu;
						break;
					case valley_info:
						state=input_farm;
						nextoption=false;
						break;
					case farm_info:
						state=main_menu;
						valley->display_info_about_farm_hunters(farm);
						break;
				}
				break;
			case '3':
				switch (state){
					case main_menu:
						return 0;
						break;	
					case farm_info:
						state=main_menu;
						break;
					case valley_info:
						state=input_id;
						nextoption=false;
						break;
				}
				break;		
			case '4':
				switch(state){
					case valley_info:
						state=main_menu;
						break;
				}
				break;	
		}else{
			istringstream ss(option);
			_flushall();
			ss>>num;
			switch(state){
				case input_farm:
					while(!((num>0)&&(num-1<(valley->farms.size())))){
						cout<<"Ââåäèòå êîððåêòíûé íîìåð ôåðìû\n";
						cin>>option;
						istringstream ss2(option);
						ss2>>num;
					}					
					valley->display_info_about_farm(num-1);
					state=farm_info;
					farm=valley->get_farm(num-1);
					break;
				case input_lake:
					while(!((num>0)&&(num-1<(valley->lakes.size())))){
						cout<<"Ââåäèòå êîððåêòíûé íîìåð îçåðà\n";
						cin>>option;
						istringstream ss2(option);
						ss2>>num;
					}
					valley->display_info_about_lake(num-1);
					state=lake_info;
					lake=valley->get_lake(num-1);
					break;
				case input_duck:
					while(!((num>0)&&(num-1<(valley->lake_getnducks(lake))))){
						cout<<"Ââåäèòå êîððåêòíûé íîìåð óòêè\n";
						cin>>option;
						istringstream ss2(option);
						ss2>>num;
					}
					lake->display_info_about_duck(num-1);
					state=main_menu;
					break;
				case input_id:
					valley->display_info_about_duck_by_id(num);
					state=main_menu;
					break;
			}
			nextoption=true;
			pre_num=num;
		}
	}
	return 0;
}
