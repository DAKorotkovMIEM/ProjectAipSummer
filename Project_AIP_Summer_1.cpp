#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
class deadline{
private:
	char *subject, *date, *info;
public:
	deadline() {
		subject = new char[20];
		date = new char[20];
		info = new char[40];
	}
	void feeddata();
	void editdata();
	void showdata();
	string getdata_subj();
	string getdata_date();
	string getdata_info();
	int search(char[], char[]);
	int search_date(char[]);
	int search_subj(char[]);
};
void deadline::feeddata() {
	cin.ignore();
	cout << "\nEnter subject: ";      
	cin.getline(subject, 20);
	cout << "Enter date (dd.mm): ";       
	cin.getline(date, 20);
	cout << "Enter add.info: ";   
	cin.getline(info, 40);
}
void deadline::editdata() {
	cout << "\nEnter subject: ";
	cin.getline(subject, 20);
	cout << "Enter date (dd.mm): ";
	cin.getline(date, 20);
	cout << "Enter add. info: ";
	cin.getline(info, 40);
}
void deadline::showdata() {
	cout << "\nSubject: " << subject;
	cout << "\nDate: " << date;
	cout << "\nAdd. info: " << info;
}
string deadline::getdata_subj() {
	return subject;
}
string deadline::getdata_date() {
	return date;
}
string deadline::getdata_info() {
	return info;
}
int deadline::search(char sdelete[20], char ddelete[20]) {
	if (strcmp(sdelete, subject) == 0 && strcmp(ddelete, date) == 0)
		return 1;
	else return 0;
}
int deadline::search_subj(char sdelete[20]) {
	if (strcmp(sdelete, subject) == 0)
		return 1;
	else return 0;
}
int deadline::search_date(char ddelete[20]) {
	if (strcmp(ddelete, date) == 0)
		return 1;
	else return 0;
}
int main() {
	deadline *B[20];
	deadline *C[20];
	int d = 0;
	int i = 0,r, t, choice, counter;
	char subj_search[20], date_search[20], answer[3], temp_subj[20], temp_date[20], temp_info[40];
	ofstream deadline_list;
	while (1) {
		cout << "\n\n\t\tMENU"
			<< "\n1. Add deadline"
			<< "\n2. Search deadline"
			<< "\n3. Search deadline on subject"
			<< "\n4. Search deadline on date"
			<< "\n5. Edit deadline"
			<< "\n6. Save deadlines"
			<< "\n7. Delete deadlines on subject"
			<< "\n0. Exit"
			<< "\n\nYour choice: ";
		cin >> choice;
		switch (choice) {
		case 1:	
			B[i] = new deadline;
			B[i]->feeddata();
			i++;
			break;
		case 2: 
			cin.ignore();
			cout << "\nEnter subject: ";
			cin.getline(subj_search, 20);
			cout << "Enter date: "; 
			cin.getline(date_search, 20);
			counter++;
			for (t = 0;t < i;t++) {
				if (B[t]->search(subj_search, date_search)) {
					cout << "\nOne (possibly, of many) is found:";
					B[t]->showdata();
					counter++;
				}
			}
			if (counter == 0)
				cout << "\nThere is no such deadline";
			else
				cout << "\nThere are no more such deadlines";
			break;
		case 3: 
			cin.ignore();
			cout << "\nEnter subject: "; 
			cin.getline(subj_search, 20);
			counter = 0;
			for (t = 0;t < i;t++) {
				if (B[t]->search_subj(subj_search)) {
					cout << "\nOne (possibly, of many) is found:";
					B[t]->showdata();
					counter++;
				}
			}
			if (counter == 0)
				cout << "\nThere is no such deadline";
			else
				cout << "\nThere are no more such deadlines";
			break;
		case 4: 
			cin.ignore();
			cout << "\nEnter date: "; 
			cin.getline(date_search, 20);
			counter = 0;
			for (t = 0;t < i;t++) {
				if (B[t]->search_date(date_search)) {
					cout << "\nOne (possibly, of many) is found:";
					B[t]->showdata();
					counter++;
				}
			}
			if (counter == 0)
				cout << "\nThere is no such deadline";
			else
				cout << "\nThere are no more such deadlines";
			break;
		case 5:
			cin.ignore();
			cout << "\nEnter subject: "; 
			cin.getline(subj_search, 20);
			cout << "Enter date: ";  
			cin.getline(date_search, 20);
			counter++;
			for (t = 0;t < i;t++) {
				if (B[t]->search(subj_search, date_search)) {
					cout << "\nOne deadline found:";
					B[t]->showdata();
					counter++;
					while (answer != "Yes" and answer != "No") {
						cout << "\nRight one? (Only Yes or No)";
						cin.getline(answer, 3);
					}
					if (answer == "Yes") {
						B[t]->editdata();
						break;
					}
				}
			}
			if (t == i)
				cout << "\nThere is no such deadline";
			break;
		case 6:
			deadline_list.open("deadlines.txt");
			for (t = 0;t < i;t++) {
				deadline_list << "\nSubject: " <<B[t]->getdata_subj();
				deadline_list << "\nDate: " <<B[t]->getdata_date();
				deadline_list << "\nAdd. info: " <<B[t]->getdata_info();
			}
			deadline_list.close();
		case 7:
			cin.ignore();
			cout << "\nWhat subject will be deleted?: ";
			cin.getline(subj_search, 20);
			for (t = 0;t < i;t++) {
				if (typeid(B[t]) == typeid(deadline)) {
					if (B[t]->getdata_subj() != subj_search) {
						C[d] = B[t];
						d++;
					}
				}
			}
			for (t = 0; t < d; t++) {
				B[t] = C[d];
			}
		case 0: 
			exit(0);
		default: cout << "\nChose one of the opt.";
		}
	}
	return 0;
}