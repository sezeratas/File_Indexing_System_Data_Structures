#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Node {
public:
	string word;
	vector <string> filenames;
	Node* next;
	Node() {
		word = "";
		next = NULL;
	}
	Node(string word, string filename) {
		this->word = word;
		filenames.push_back(filename);
		next = NULL;
	}
	Node(string word, vector <string> filenamescopy) {
		this->word = word;
		filenames = filenamescopy;
		next = NULL;
	}
};

class LinkedList {
public:
	Node* head;
	int size;

	LinkedList() {
		head = NULL;
		size = 0;
	}
	void addNode(string word, string filename) {
		Node* newNode = new Node(word, filename);
		if (head == NULL) {
			head = newNode;
		}
		else {
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
		size++;
	}
	void addNode(string word, vector<string> filenames) {
		Node* newNode = new Node(word, filenames[0]);
		for (int i = 1; i < filenames.size(); i++) {
			newNode->filenames.push_back(filenames[i]);
		}
		if (head == NULL) {
			head = newNode;
		}
		else {
			Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
	void printList() {
		Node* temp = head;
		while (temp != NULL) {
			cout << temp->word << " / ";
			for (int i = 0; i < temp->filenames.size(); i++) {
				cout << temp->filenames[i] << " - ";
			}
			cout << endl;
			temp = temp->next;
		}
	}
};

void MainMenu() {
	cout << "+========================================================================+" << endl;
	cout << "|			Simple Document Retrieval System                 |" << endl;
	cout << "|				(30 Minutes)                             |" << endl;
	cout << "+========================================================================+" << endl;
	cout << "|	1. Enter a single keyword to list the document(s)(file names)    |" << endl;
	cout << "|	2. Print the top 10 words that appeared most frequently          |" << endl;
	cout << "|	3. Print the top 10 words that appeared least frequently         |" << endl;
	cout << "|	4. Exit                                                          |" << endl;
	cout << "+========================================================================+" << endl;
	cout << "Option:";
}

void PrintFileWithName() {
	fstream AllDocs;
	string filename;
	cout << "Enter the name of the document:";
	cin >> filename;
	filename = "AllDocs/AllDocs/" + filename + ".txt";
	//filename = "AllDocs/AllDocs/1.txt";
	AllDocs.open(filename, ios::in);
	if (AllDocs.is_open()){
		cout << "File opened successfully." << endl;
		string line;
		while (getline(AllDocs, line)) {
			cout << line << endl;
		}
		AllDocs.close();
	}
	else
	{
		cout << "File could not be opened." << endl;
	}
}

void PrintAllFiles() {
	fstream AllDocs;
	string filename;
	for (int i = 1; i <= 10; i++) {
		filename = "AllDocs/AllDocs/" + to_string(i) + ".txt";
		//filename = "AllDocs/AllDocs/1.txt";
		AllDocs.open(filename, ios::in);
		if (AllDocs.is_open()) {
			cout << "+=====================File \"" << filename << "\" opened successfully.=====================+ " << endl;
			string line;
			while (getline(AllDocs, line)) {
				cout << line << endl;
			}
			AllDocs.close();
		}
		else
		{
			cout << "File could not be opened." << endl;
		}
	}

}

void DocumentIndexing(LinkedList* list) {
	clock_t time_req;
	time_req = clock();
	int i;
	//LinkedList* list = new LinkedList();
	for (i = 1;i < 20 ;i++) {     // You can change the number of documents to be indexed here.
		string filename = "AllDocs/AllDocs/" + to_string(i) + ".txt";
		ifstream infile(filename);
		if (!infile) {
			cout << "File not found!" << endl;
		}
		else {
			string word;
			int controlInt = 1;
			while (infile >> word) {
				controlInt = 1;
				if (word.find('.') != string::npos || word.find(',') != string::npos || word.find('/') != string::npos || word.find(';') != string::npos || word.find('\'') != string::npos
					|| word.find('[') != string::npos || word.find(']') != string::npos || word.find('?') != string::npos || word.find('<') != string::npos || word.find('>') != string::npos) {
					continue;
				}
				else if (word.find('-') != string::npos || word.find('/') != string::npos || word.find('*') != string::npos || word.find('+') != string::npos || word.find('1') != string::npos
					|| word.find('2') != string::npos || word.find('3') != string::npos || word.find('4') != string::npos || word.find('5') != string::npos || word.find('6') != string::npos
					|| word.find('7') != string::npos || word.find('8') != string::npos || word.find('9') != string::npos || word.find('0','9') != string::npos) {
					continue;
				}
				Node* temp = list->head;
				while (temp != NULL) {
					if (temp->word == word) {
						for (int n = 0;n < temp->filenames.size();n++) {
							if (filename == temp->filenames[n]) {
								controlInt = 0;
								break;
							}
						}
						if (controlInt == 1) {
							temp->filenames.push_back(filename);
							controlInt = 0;
							break;
						}
					}
					temp = temp->next;
				}
				if (controlInt == 1) {
					list->addNode(word, filename);
				}
			}
		}
	}
	time_req = clock() - time_req;
	cout << "Time taken for indexing: " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;
}

void PrintList(LinkedList* list) {
	Node* temp = list->head;
	while (temp != NULL) {
		cout << temp->word << " / ";
		for (int i = 0;i < temp->filenames.size();i++) {
			cout << temp->filenames[i] << " - ";
		}
		cout << endl << endl;
		temp = temp->next;
	}
}

LinkedList* SortTheLinkedList(LinkedList* list) {  // buyukten kucuge siralama
	if (list->head == NULL) {
		cout << "List is empty." << endl;
		return NULL;
	}
	LinkedList* sortedList = new LinkedList();
	Node* temp = list->head;
	while (temp != NULL) {
		Node* temp2 = sortedList->head;
		if (sortedList->head == NULL) {
			sortedList->addNode(temp->word, temp->filenames);
		}
		else {
			if(sortedList->head->filenames.size() <= temp->filenames.size()){
				Node* temp3 = sortedList->head;
				sortedList->head = new Node(temp->word, temp->filenames);
				sortedList->head->next = temp3;
				sortedList->size++;
			}
			else {
				while (temp2->next->filenames.size() > temp->filenames.size()) {
					temp2 = temp2->next;
				}
				Node* temp3 = temp2->next;
				temp2->next = new Node(temp->word, temp->filenames);
				temp2->next->next = temp3;
				sortedList->size++;
			}
		}
		temp = temp->next;
	}
	return sortedList;
}

void Choice1(LinkedList* list) {
	string word;
	cout << "Enter a single keyword:";
	cin >> word;
	Node* temp = list->head;
	while (temp != NULL) {
		if (temp->word == word) {
			cout << "The word \"" << word << "\" is found in the following files:" << endl;
			for (int i = 0;i < temp->filenames.size();i++) {
				cout << temp->filenames[i] << endl;
			}
			return;
		}
		temp = temp->next;
	}
	cout << "The word \"" << word << "\" is not found in any file." << endl;
}
void Choice2(LinkedList* list) {
	LinkedList* sortedList = SortTheLinkedList(list);
	Node* temp = sortedList->head;
	cout << "Top 10 words that appeared most frequently:" << endl;
	for (int i = 0;i < 10;i++) {
		cout << temp->word << " - " << temp->filenames.size() << " times" << endl;
		temp = temp->next;
	}
}
void Choice3(LinkedList* list) {
	LinkedList* sortedList = SortTheLinkedList(list);
	cout << "Top 10 words that appeared least frequently:" << endl;
	Node* temp = list->head;
	while (temp->next->next->next->next->next->next->next->next->next->next != NULL) {
		temp = temp->next;
	}
	for (int i = 0;i < 10;i++) {
		cout << temp->word << " - " << temp->filenames.size() << " times" << endl;
		temp = temp->next;
	}
}

int main() {
	LinkedList* list = new LinkedList();
	DocumentIndexing(list);
	int choice = 0;
	while (choice != 4) {
		MainMenu();
		cin >> choice;
		switch (choice) {
			case -4:
				PrintList(SortTheLinkedList(list));
				break;
			case -3:
				PrintList(list);
				break;
			case -2:
				PrintFileWithName();
				break;
			case -1:
				PrintAllFiles();
				break;
			case 1:
				Choice1(list);
				break;
			case 2:
				Choice2(list);
				break;
			case 3:
				Choice3(list);
				break;
			case 4:
				cout << "Exiting..." << endl;
				return 0;
			default:
				cout << "Invalid choice" << endl;
				break;
		}
	}

	return 0;
}