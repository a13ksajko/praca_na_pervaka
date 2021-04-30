#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
using namespace std;
class Lake;
class Farm;
class Attribute;
class Duck;
class Valley;
class Hunter;
enum State{
	main_menu,
	valley_info,
	lake_info,
	farm_info,
	input_lake,
	input_duck,
	input_farm
};
enum Ability{
	bites, knowshome, swims, flies, fishes
};

void display_ability(Ability *ability){
	switch(*ability){
		case bites:
			cout<<"��������";
			break;
		case knowshome:
			cout<<"����� ������ �����";
			break;
		case swims:
			cout<<"�������";
			break;
		case flies:
			cout<<"������";
			break;
		case fishes:
			cout<<"��������";
			break;
	}
}
bool IsSubset(std::vector<Ability> A, std::vector<Ability> B)
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

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
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
		lake->assign_farm(this);
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
		cout<<"����� "<<name<<", ����� "<<hunters.size()<<" ���������\n";
		cout<<"����� �������, ���� ����� �����: ";
		for(int i=0;i<toescape.size();i++){
			if(i!=0)cout<<", ";
			display_ability(&toescape[i]);
		}
		cout<<".\n";
	}
};
void Lake::display_info(){
		cout<<"����� "<<name<<", �� �� "<< ducks.size()<<" ����";
		if(!wild)
			cout<<", ����������� ����� "<<farm->get_name()<<"\n";
		else
			cout<<", �����\n";
	}
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
	string home, lake;
	bool canescape;
	bool escaped;
	bool action;
	Duck(string name){
		this->name=name;
		canescape=true;
		escaped=false;
		action=false;
	}
	void assign_lake(Lake *home){
		this->lake=home->name;
		this->home=home->name;
	}
	void add_ability(Ability *a){
		abilities.push_back(*a);
	}
	void add_attribute(Attribute *a){
		attrs.push_back(*a);
	}
	void display_info(){
		cout<<"���� ���� "<<name<<", ��� "<<home<<((canescape)?", ������ �� ���������":" ������ ���������")<<"\n";
		cout<<"�����: ";
		for(int i=0;i<abilities.size();i++){
			if(i!=0)cout<<", ";
			display_ability(&abilities[i]);
		}
		cout<<".\n";
		cout<<"��������: ";
		for(int i=0;i<attrs.size();i++){
			if(i!=0)cout<<", ";
			attrs[i].display_info();
		}
		cout<<".\n";
	}
};
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
		cout<<"������� ����� ������� �� "<<min<<" ���� �� "<<max<<" ����\n";
	}
};
void Farm::add_hunter(Hunter *hunter){
		hunters.push_back(*hunter);
		hunter->assign_farm(this);
	}
void Farm::display_info_about_hunters(){
	for(int i=0;i<hunters.size();i++){
		cout<<"������� �"<<i<<"\n";
		hunters[i].display_info();
	}
}
class Valley{
	public:
	int hunting_days_left;
	vector <Lake> lakes;
	vector <Farm> farms;
	void display_info(){
		cout<<"� ������ "<<lakes.size()<<" ����� ���� � "<<farms.size()<<" ����, �� ����� ������ ����� �������� "<<hunting_days_left<<" ����\n";
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
	void simulate(){
		//std::random_device rd;  //Will be used to obtain a seed for the random number engine
    	//std::mt19937 r(rd()); //Standard mersenne_twister_engine seeded with rd()
    	std::mt19937 r(static_cast<unsigned int>(time(0)));
		if(hunting_days_left>0){
			for(int i=0;i<farms.size();i++){
				std::uniform_int_distribution<int> dist(0,lakes.size()-1);
				int targetlake=dist(r);
				int caught;
				caught=0;
				for(int j=0;j<farms[i].hunters.size();j++){
					std::uniform_int_distribution<int> dist2(farms[i].hunters[j].min,farms[i].hunters[j].max-1);
					caught+=dist2(r);
				}
				if(caught>lakes[targetlake].ducks.size())caught=lakes[targetlake].ducks.size();
				cout<<"�������� � ����� "<<farms[i].name<<" ����������� �� ����� "<<lakes[targetlake].name<<" � ������� "<<caught<<" ����\n";
				for(int j=0;j<caught;j++){
					std::uniform_int_distribution<int> dist3(0,lakes[targetlake].ducks.size()-1);
					int nduck=dist3(r);
					Duck duck=lakes[targetlake].ducks[nduck];
					lakes[targetlake].ducks.erase(lakes[targetlake].ducks.begin()+nduck);
					if(duck.escaped){
						duck.canescape=false;
						cout<<"���� "<<duck.name<<" ��������� �����"<<endl;
					}
					duck.action=true;
					farms[i].lake->ducks.push_back(duck);
					
				}
			}
		}
		for(int i=0;i<farms.size();i++){
			for(int j=0;j<farms[i].lake->ducks.size();j++){
				if(farms[i].lake->ducks[j].action)continue;
				if(!farms[i].lake->ducks[j].canescape)continue;
				std::uniform_int_distribution<int> dist3(0,9);
				int chance=dist3(r);	
				if(IsSubset(farms[i].lake->ducks[j].abilities,farms[i].toescape))
				if(chance<5)
				{
					Duck duck = farms[i].lake->ducks[j];
					cout<<"���� "<<duck.name<<" ������� � ����� "<<farms[i].name<<" �� ����� "<<duck.home<<"\n";
					farms[i].lake->ducks.erase(farms[i].lake->ducks.begin()+j);
					j-=1;
					duck.escaped=true;
					duck.action=true;
					findlake(duck.home)->ducks.push_back(duck);
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
	Lake *lake = new Lake("�����",true);
	Duck *duck;
	Ability *ability;
	Attribute *attribute;
	for(int i=0;i<30;i++){
		duck=new Duck("������");
		ability = new Ability(flies);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("���","�������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("������ �������","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("���� ����","�����",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("�����");
		ability = new Ability(bites);
		duck->add_ability(ability);
		attribute= new Attribute("���","�������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("������","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("����","",8);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("������",true);
	for(int i=0;i<30;i++){
		duck=new Duck("�����-���������");
		ability = new Ability(flies);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("���","��",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("������ ���","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("������������","",3);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("��������");
		ability = new Ability(fishes);
		duck->add_ability(ability);
		attribute= new Attribute("���","�������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("������","",6);
		duck->add_attribute(attribute);
		attribute= new Attribute("������ ������","",8);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	valley->add_lake(lake);
	lake = new Lake("�������",true);
	for(int i=0;i<30;i++){
		duck=new Duck("�����");
		ability = new Ability(swims);
		duck->add_ability(ability);
		ability = new Ability(knowshome);
		duck->add_ability(ability);
		attribute= new Attribute("���","�������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("�����","�������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���� ����","������� �����",-1);
		duck->add_attribute(attribute);
		lake->add_duck(duck);
	}
	for(int i=0;i<30;i++){
		duck=new Duck("��������");
		ability = new Ability(bites);
		duck->add_ability(ability);
		attribute= new Attribute("���","�������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("���","",5);
		duck->add_attribute(attribute);
		attribute= new Attribute("����� �����","������",-1);
		duck->add_attribute(attribute);
		attribute= new Attribute("����","�����",-1);
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
	State state=main_menu;
	bool nextoption=true;	
	while(1){
		switch (state){
			case main_menu:
				cout<<"�����:\n";
				cout<<"1. ������ ���������� � ������\n";
				cout<<"2. ������� ���\n";
				cout<<"3. �����\n";
				break;
			case valley_info:
				cout<<"�����:\n";
				cout<<"1. ������ ���������� �� �����\n";
				cout<<"2. ������ ���������� � �����\n";
				cout<<"3. � ������� ����\n";
				break;
			case farm_info:
				cout<<"�����:\n";
				cout<<"1. ������ ���������� �� �����\n";
				cout<<"2. ������ ���������� �� ���������\n";
				cout<<"3. � ������� ����\n";
				break;
			case lake_info:
				cout<<"�����:\n";
				cout<<"1. ������ ���������� �� ����\n";
				cout<<"2. � ������� ����\n";
				break;
			case input_lake:
				cout<<"� ������ "<<valley->getnlakes()<<" ����\n";
				cout<<"������� ����� �����:\n";
				break;
			case input_farm:
				cout<<"� ������ "<<valley->getnfarms()<<" ����\n";
				cout<<"������� ����� �����:\n";
				break;
			case input_duck:
				cout<<"�� ����� "<<valley->lake_getnducks(lake)<<" ����\n";
				cout<<"������� ����� ����:\n";
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
						state=input_duck;
						nextoption=false;
						break;
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
					case valley_info:
					case farm_info:
						state=main_menu;
						break;
				}
				break;
			
		}else{
			int number;
			istringstream ss(option);
			switch(state){
				case input_farm:
					ss>>number;
					valley->display_info_about_farm(number);
					state=farm_info;
					farm=valley->get_farm(number);
					break;
				case input_lake:
					ss>>number;
					valley->display_info_about_lake(number);
					state=lake_info;
					lake=valley->get_lake(number);
					break;
				case input_duck:
					ss>>number;
					lake->display_info_about_duck(number);
					state=main_menu;
					break;
			}
			nextoption=true;
		}
	}	
	return 0;
}
