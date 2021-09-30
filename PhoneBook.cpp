#include <iostream> 
#include <string> 
#include <iomanip> 
#include <fstream> 

using namespace std;

struct Phone {
	int city_code;
	int operator_code;
	int phone_num;
};

struct Contact {
	string first_name;
	string last_name;
	Phone mobile_num;
	Phone home_num;
	string description;
};

const string path = "d:\\Contact.txt";
ofstream file(path);
ifstream read("d:\\ContactRead.txt");

Contact* Add(Contact* contact_list, int& size);
Contact* Delete(Contact* contact_list, int& size);
void Edit(Contact* contact_list);
void Search(Contact* contact_list, int size);
void Show(Contact contact_list);
void Sort(Contact* contact_list, int size);
void SaveToFile(Contact* contact_list, int size);
Contact* ReadFromFile(Contact* contact_list, int& size);
Contact Fill();
Phone Num();

int main() {
	int size = 0;
	Contact* contact_list = nullptr;
	int operation;
	do {
		cout << "Choose operation: " << endl;
		cout << "1 - add" << endl;
		cout << "2 - delete" << endl;
		cout << "3 - search" << endl;
		cout << "4 - edit" << endl;
		cout << "5 - show" << endl;
		cout << "6 - read from file" << endl;
		cout << "0 - save and exit" << endl;
		cin >> operation;
		system("cls");
		if (operation == 1) {
			contact_list = Add(contact_list, size);
			cout << endl;
		}
		else if (operation == 2) {
			contact_list = Delete(contact_list, size);
		}
		else if (operation == 3) {
			Search(contact_list, size);
		}
		else if (operation == 4) {
			Edit(contact_list);
		}
		else if (operation == 5) {
			system("cls");
			cout << "How do you want to show?" << endl;
			cout << "1 - all without sort" << endl;
			cout << "2 - all with sort" << endl;
			cout << "3 - by search" << endl;
			int choice;
			cin >> choice;
			if (choice == 1) {
				system("cls");
				for (int i = 0; i < size; i++) {
					Show(contact_list[i]);
					cout << endl << endl;
				}
			}
			else if (choice == 2) {
				Sort(contact_list, size);
				for (int i = 0; i < size; i++) {
					Show(contact_list[i]);
					cout << endl << endl;
				}
			}
			else if (choice == 3) {
				Search(contact_list, size);
			}
			else {
				cout << "No such command" << endl;
				continue;
			}
		}
		else if (operation == 6) {
			cout << "How many contacts read from file?" << endl;
			int n;
			cin >> n;
			for (int i = 0; i < n; i++) {
				contact_list = ReadFromFile(contact_list, size);
				cout << endl;
			}

		}
	} while (operation != 0);
	SaveToFile(contact_list, size);
	return 0;
}
Contact* Add(Contact* contact_list, int& size) {
	++size;
	Contact* new_contact_list = new Contact[size];
	for (int i = 0; i < size - 1; i++) new_contact_list[i] = contact_list[i];
	new_contact_list[size - 1] = Fill();
	return new_contact_list;
}
Contact* Delete(Contact* contact_list, int& size) {
	int index = 0;
	cout << "Index - ";
	cin >> index;
	--size;
	--index;
	Contact* new_contact_list = new Contact[size];
	for (int i = 0; i < index; i++) {
		new_contact_list[i] = contact_list[i];
	}
	for (int i = index; i < size; i++) {
		new_contact_list[i] = contact_list[i + 1];
	}

	return new_contact_list;
}
void Edit(Contact* contact_list) {
	int index = 0;
	cout << "Index - ";
	cin >> index;
	--index;
	contact_list[index] = Fill();
}
void Search(Contact* contact_list, int size) {
	int srch;
	system("cls");
	cout << "How do you want to search contact?" << endl;
	cout << "1 - Name" << endl;
	cout << "2 - Home number" << endl;
	cout << "3 - Mobile number" << endl;
	cout << "4 - Description" << endl;
	cin >> srch;
	system("cls");
	if (srch == 1) {
		string name;
		cout << "Enter the name - ";
		cin >> name;
		for (int i = 0; i < size; i++) {
			if (contact_list[i].first_name == name || contact_list[i].last_name == name) {
				Show(contact_list[i]);
			}
		}
	}
	else if (srch == 2) {
		Phone home_n = Num();
		for (int i = 0; i < size; i++) {
			if (contact_list[i].home_num.city_code == home_n.city_code &&
				contact_list[i].home_num.operator_code == home_n.operator_code &&
				contact_list[i].home_num.phone_num == home_n.phone_num) {
				Show(contact_list[i]);
			}
		}
	}
	else if (srch == 3) {
		Phone mob_n = Num();
		for (int i = 0; i < size; i++) {
			if (contact_list[i].mobile_num.city_code == mob_n.city_code &&
				contact_list[i].mobile_num.operator_code == mob_n.operator_code &&
				contact_list[i].mobile_num.phone_num == mob_n.phone_num) {
				Show(contact_list[i]);
			}
		}
	}
	else if (srch == 4) {
		string dscrp;
		cout << "Enter description - ";
		cin >> dscrp;
		for (int i = 0; i < size; i++) {
			if (contact_list[i].description == dscrp) {
				Show(contact_list[i]);
			}
		}
	}
	else {
		cout << "No such command" << endl;
	}
}

void Show(Contact contact_list) {
	cout << "Full name: " << contact_list.last_name << " " << contact_list.first_name << endl;
	cout << "Phone number: +" << contact_list.mobile_num.city_code << " " << contact_list.mobile_num.operator_code << " " << contact_list.mobile_num.phone_num << endl;
	cout << "Home number: +" << contact_list.home_num.city_code << " " << contact_list.home_num.operator_code << " " << contact_list.home_num.phone_num << endl;
	cout << "Description: " << contact_list.description << endl;
}

void Sort(Contact* contact_list, int size) {
	system("cls");
	cout << "How do you want to sort it?" << endl;
	cout << "1 - by name" << endl;
	cout << "2 - by number" << endl;
	int srt;
	cin >> srt;
	if (srt == 1) {
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (contact_list[j].last_name[0] < contact_list[i].last_name[0] && contact_list[j].first_name[0] < contact_list[i].first_name[0]) {
					Contact tmp1 = contact_list[i];
					contact_list[i] = contact_list[j];
					contact_list[j] = tmp1;
				}
			}
		}
	}
	else if (srt == 2) {
		system("cls");
		cout << "Which number will be sorted?" << endl;
		cout << "1 - mobile number" << endl;
		cout << "2 - home number" << endl;
		int n;
		cin >> n;
		if (n == 1) {
			for (int i = 0; i < size; i++) {
				for (int j = i + 1; j < size; j++) {
					if (contact_list[j].mobile_num.city_code < contact_list[i].mobile_num.city_code ||
						contact_list[j].mobile_num.operator_code < contact_list[i].mobile_num.operator_code ||
						contact_list[j].mobile_num.phone_num < contact_list[i].mobile_num.phone_num) {
						Contact temp1 = contact_list[i];
						contact_list[i] = contact_list[j];
						contact_list[j] = temp1;
					}
				}
			}
		}
		else if (n == 2) {
			for (int i = 0; i < size; i++) {
				for (int j = i + 1; j < size; j++) {
					if (contact_list[j].home_num.city_code < contact_list[i].home_num.city_code ||
						contact_list[j].home_num.operator_code < contact_list[i].home_num.operator_code ||
						contact_list[j].home_num.phone_num < contact_list[i].home_num.phone_num) {
						Contact temp1 = contact_list[i];
						contact_list[i] = contact_list[j];
						contact_list[j] = temp1;
					}
				}
			}
		}
	}
}
Contact* ReadFromFile(Contact* contact_list, int& size) {
	++size;
	Contact* new_contact_list = new Contact[size];
	for (int i = 0; i < size - 1; i++) new_contact_list[i] = contact_list[i];
	if (read) {
		//last name 
		read.ignore(11);
		read >> new_contact_list[size - 1].last_name;
		//first name 
		read.ignore(1);
		read >> new_contact_list[size - 1].first_name;
		//mobile number 
		read.ignore(16);
		read >> new_contact_list[size - 1].mobile_num.city_code;
		read.ignore(1);
		read >> new_contact_list[size - 1].mobile_num.operator_code;
		read.ignore(1);
		read >> new_contact_list[size - 1].mobile_num.phone_num;
		//home number 
		read.ignore(14);
		read >> new_contact_list[size - 1].home_num.city_code;
		read.ignore(1);
		read >> new_contact_list[size - 1].home_num.operator_code;
		read.ignore(1);
		read >> new_contact_list[size - 1].home_num.phone_num;
		//description 
		read.ignore(13);
		read >> new_contact_list[size - 1].description;
		read.ignore(1);
	}
	else cout << "There is no file" << endl;
	return new_contact_list;
}

void SaveToFile(Contact* contact_list, int size) {
	for (int i = 0; i < size; i++) {
		file << "Full name: " << contact_list[i].last_name << " " << contact_list[i].first_name << endl;
		file << "Mobile number: +" << contact_list[i].mobile_num.city_code << " " << contact_list[i].mobile_num.operator_code << " " << contact_list[i].mobile_num.phone_num << endl;
		file << "Home number: +" << contact_list[i].home_num.city_code << " " << contact_list[i].home_num.operator_code << " " << contact_list[i].home_num.phone_num << endl;
		file << "Description: " << contact_list[i].description << endl << endl;
	}
}

Contact Fill() {
	Contact tmp;
	cout << "First name - ";
	cin >> tmp.first_name;
	cout << "Last name - ";
	cin >> tmp.last_name;
	cout << "Mobile number: " << endl;
	tmp.mobile_num = Num();
	cout << "Home number: " << endl;
	tmp.home_num = Num();
	cout << "Description - ";
	cin >> tmp.description;
	return tmp;
}
Phone Num() {
	Phone tmp;
	cout << "Code of city - ";
	cin >> tmp.city_code;
	cout << "Code of operator - ";
	cin >> tmp.operator_code;
	cout << "Number - ";
	cin >> tmp.phone_num;
	return tmp;
}
