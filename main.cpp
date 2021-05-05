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
			cout<<"кусаться";
			break;
		case knowshome:
			cout<<"знать дорогу домой";
			break;
		case swims:
			cout<<"плавать";
			break;
		case flies:
			cout<<"летать";
			break;
		case fishes:
			cout<<"рыбачить";
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
		lake->assign_farm(this);  //работает и заебись
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
		cout<<"Ферма "<<name<<", имеет "<<hunters.size()<<" охотников\n";
		cout<<"Чтобы сбежать, утке нужно уметь: ";
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
		cout<<"Утка вида "<<name<<", id="<<id<<", дом "<<home<<((canescape)?", крылья не подрезаны":" крылья подрезаны")<<"\n";
		cout<<"Может: ";
		for(int i=0;i<abilities.size();i++){
			if(i!=0)cout<<", ";
			display_ability(&abilities[i]);
		}
		cout<<".\n";
		cout<<"Свойства: ";
		for(int i=0;i<attrs.size();i++){
			if(i!=0)cout<<", ";
			attrs[i].display_info();
		}
		cout<<"\n";
		cout<<"Её путь: ";
		for(int i=0;i<path.size();i++){
			cout<<path[i]<<", ";
		}
		cout<<"\n";
	}
};
void Lake::display_info(){   
		cout<<"Озеро "<<name<<", на нём "<< ducks.size()<<" уток";
		if(!wild)
			cout<<", принадлежит ферме "<<farm->get_name()<<"\n";
		else
			cout<<", дикое\n";
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
		cout<<"Среди уток: ";
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
		cout<<"Охотник может поймать от "<<min<<" уток до "<<max<<" уток\n";
	}
};
void Farm::add_hunter(Hunter *hunter){
		hunters.push_back(*hunter);
		hunter->assign_farm(this);
	}
void Farm::display_info_about_hunters(){
	for(int i=0;i<hunters.size();i++){
		cout<<"Охотник №"<<i+1<<"\n";
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
			cout<<"В долине "<<lakes.size()<<" диких озер и "<<farms.size()<<" ферм, до конца сезона охоты осталось "<<hunting_days_left<<" дней\n";
			else
			cout<<"В долине "<<lakes.size()<<" диких озер и "<<farms.size()<<" ферм, сезон охоты закончился\n";
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
		cout<<"Утка с таким id не найдена\n";
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
				cout<<"Охотники с фермы "<<farms[i].name<<" отправились на озеро "<<lakes[targetlake].name<<" и поймали "<<caught<<" уток\n";
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
						cout<<"Утке "<<duck.name<<"(id="<<duck.id<<") удалось укусить охотника и убежать\n";
						continue;
					}
					lakes[targetlake].ducks.erase(lakes[targetlake].ducks.begin()+caughtvec[j]);
					cout<<"Утка "<<duck.name<<"(id="<<duck.id<<") поймана";
					if(duck.escaped){
						duck.canescape=false;
						cout<<" и ей подрезали крыло\n";
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
					cout<<"Утка "<<duck.name<<"(id="<<duck.id<<") убежала с фермы "<<farms[i].name;
					if (!farms[i].random){
						cout<<" на озеро "<<duck.home<<"\n";
						farms[i].lake->ducks.erase(farms[i].lake->ducks.begin()+j);
						j-=1;
						duck.escaped=true;
						duck.action=true;
						duck.path.push_back(duck.home);
						findlake(duck.home)->ducks.push_back(duck);
					}else{
						uniform_int_distribution<int> dist4(0,lakes.size()-1);
						duck.home=lakes[dist4(r)].name;
						cout<<" на случайное озеро "<<duck.home<<"\n";
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
	Lake *lake = new Lake("Челан",true);
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
	int id=1;
	for(int i=0;i<30;i++){
		duck=new Duck("Гоголь",id++);
		ability = new Ability(flies);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("Имя","Дональд",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Вес","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Размах крыльев","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Цвет глаз","Карий",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("Нырка",id++);
		ability = new Ability(bites);
		duck->add_ability(ability);
		attribute= new Attribute("Имя","Дональд",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Вес","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Высота","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Сила","",8);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("Матано",true);
	for(int i=0;i<30;i++){
		duck=new Duck("Чирок-свистунок",id++);
		ability = new Ability(flies);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("Имя","Чи",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Вес","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Размер лап","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Выносливость","",3);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("Хохлатая",id++);
		ability = new Ability(fishes);
		duck->add_ability(ability);
		attribute= new Attribute("Имя","Дональд",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Вес","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Высота","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("Размер хвоста","",8);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("Хауроко",true);
	for(int i=0;i<30;i++){
		duck=new Duck("Нырки",id++);
		ability = new Ability(swims);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("Имя","Фамилия",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Вес","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Хобби","Диалектика",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Цвет глаз","Морской волны",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<34;i++){
		duck=new Duck("Хохлатая",id++);
		ability = new Ability(bites);
		duck->add_ability(ability);
		attribute= new Attribute("Имя","Володiмiр",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Вес","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("Окрас клюва","желтый",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("Цвет","сизый",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	int maxid=id-1;
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
				cout<<"Опции:\n";
				cout<<"1. Узнать информацию о долине\n";
				cout<<"2. Сделать ход\n";
				cout<<"3. Выход\n";
				_flushall();
				break;
			case valley_info:
				cout<<"Опции:\n";
				cout<<"1. Узнать информацию об озере\n";
				cout<<"2. Узнать информацию о ферме\n";
				cout<<"3. Узнать информацию об утке по ID\n";
				cout<<"4. В главное меню\n";
				_flushall();
				break;
			case farm_info:
				cout<<"Опции:\n";
				cout<<"1. Узнать информацию об озере\n";
				cout<<"2. Узнать информацию об охотниках\n";
				cout<<"3. В главное меню\n";
				_flushall();
				break;
			case lake_info:
				cout<<"Опции:\n";
				cout<<"1. Узнать информацию об утке\n";
				cout<<"2. В главное меню\n";
				_flushall();
				break;
			case input_lake:
				cout<<"В долине "<<valley->getnlakes()<<" озера\n";
				cout<<"Введите номер озера:\n";
				_flushall();
				break;
			case input_farm:
				cout<<"В долине "<<valley->getnfarms()<<" фермы\n";
				cout<<"Введите номер фермы:\n";
				_flushall();
				break;
			case input_duck:
				cout<<"На озере "<<valley->lake_getnducks(lake)<<" уток\n";
				cout<<"Введите номер утки:\n";
				_flushall();
				break;
			case input_id:
				cout<<"Введите ID утки:\n";
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
							cout<<"Уток на озере нет\n";
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
			num=-1;
			ss>>num;
			switch(state){
				case input_farm:
					while(!((num>0)&&(num-1<(valley->farms.size())))){
						cout<<"Введите корректный номер фермы\n";
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
						cout<<"Введите корректный номер озера\n";
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
						cout<<"Введите корректный номер утки\n";
						cin>>option;
						istringstream ss2(option);
						ss2>>num;
					}
					lake->display_info_about_duck(num-1);
					state=main_menu;
					break;
				case input_id:
					while(!((num>=0)&&(num<=maxid))){
						cout<<"Введите корректный id\n";
						cin>>option;
						istringstream ss2(option);
						ss2>>num;
					}
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
