//Fahad Waheed (20I-0651)

#ifndef CITIZENSDB_H
#define CITIZENSDB_H
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct CCID_Data;

//Queue's Node
template <class T>
struct Data {
	T data; //to hold data of a citizen (string)
	Data<T>* next; //to hold address of next node of queue

	//NULL initialization
	Data() : data(T()), next(NULL) {};
};

//Queue
template <class T>
class DataPipeline {
	Data<T>* head;
public:
	DataPipeline() {
		head = NULL;
	}

	// to return the data of head node if exists
	T front() {
		if (!is_empty())
			return head->data;
		return T();
	}
	
	// to return the data of head node if exists
	T back() {
		if (!is_empty())
		{
			Data<T>* currnode = head;

			while (currnode->next)
			{
				currnode = currnode->next;
			}

			return currnode->data;
		}
		return T();
	}

	// to enter data at the end of the queue
	T enqueue(T input) {
		Data<T>* newnode = new Data<T>;

		newnode->data = input;
		newnode->next = NULL;

		if (is_empty())
			head = newnode;
		else
		{
			Data<T>* currnode = head;

			while (currnode->next) //traversing to get the last node of the queue
			{
				currnode = currnode->next;
			}

			currnode->next = newnode;
		}

		return input;
	}

	// to get data from the front (head) of the queue, to delete the front (head) and to set up front of the queue 
	T dequeue() {
		if (!is_empty())
		{
			Data<T>* currnode = head; // temporary node (because we need to delete it)
			T output = currnode->data; // temporary variable to hold temp. node's data as it will be deleted soon
			head = head->next; // setting up front of the queue
			delete currnode; // deleting temporary queue
			return output; //returning temporary variable
		}
		return T(); // if queue is empty then empty variable of type T will be returned
	}

	// to check if queue is empty or not
	bool is_empty() {
		if (head == NULL)
			return true;
		return false;
	}

	// destructor to delete all the nodes of the queue
	~DataPipeline()
	{
		while (head)
		{
			dequeue();
		}
	}
};

//CBIDList's Data
template <typename T>
struct CBID_Data
{
	T CNIC;
	T Name, FName, Gender, Address, Nationality;
	CCID_Data<T>* CriminalRecord;

	//NULL initialization
	CBID_Data() : CNIC(T()), Name(T()), FName(T()), Gender(T()), Address(T()), Nationality(T()), CriminalRecord(NULL) {};
};

//CBIDList's Node
template <typename T>
struct CBID_NODE {
	CBID_Data<T> data; //to store the required data of citizen
	CBID_NODE<T>* next, * previous; //pointers to hold the address of next & previous node

	//NULL initialization
	CBID_NODE() : next(NULL), previous(NULL) {};
};

//CBIDList (Doubly Linked List) to store basic information of citizens
template <class T>
class CBIDList {
	CBID_NODE<T>* head, * tail; //pointers to store address of first & last node

public:
	CBIDList() //NULL initialization of pointers in default constructor
	{
		head = tail = NULL;
	}

	bool is_empty()//return true if list is empty or vice versa
	{
		if (head == NULL && tail == NULL)
			return true;
		return false;
	}

	// to insert data of new citizen
	void insert(T cnic, T name, T fname, T gender, T address, T nationality)
	{
		if (!uniquecnic(cnic))
			return;

		CBID_NODE<T>* newnode = new CBID_NODE<T>; //creating new node

		//setting up data of citizen
		newnode->data.CNIC = cnic;
		newnode->data.Name = name;
		newnode->data.FName = fname;
		newnode->data.Gender = gender;
		newnode->data.Address = address;
		newnode->data.Nationality = nationality;
		newnode->next = NULL;
		newnode->previous = NULL;
		newnode->data.CriminalRecord = NULL;

		if (is_empty()) // if list is empty
		{
			head = tail = newnode;
		}
		else // if list has some elements
		{
			CBID_NODE<T>* currnode = head;

			//finding first node whose cnic is greater than newly created node
			while (currnode && (stoi(currnode->data.CNIC) < stoi(newnode->data.CNIC)))
			{
				currnode = currnode->next;
			}

			if (currnode == head) // if cnic of first node is greater than newly created node
			{
				newnode->next = currnode;
				currnode->previous = newnode;
				head = newnode;
			}

			else if (currnode == NULL) // if cnic of newly created node is greater than all other nodes
			{
				newnode->previous = tail;
				tail->next = newnode;
				tail = newnode;
			}

			else // if cnic of newly created node is in between of cnic of other nodes 
			{
				newnode->previous = currnode->previous;
				newnode->next = currnode;
				currnode->previous->next = newnode;
				currnode->previous = newnode;
			}
		}
	}

	bool uniquecnic(T cnic)//returns true if cnic is unique
	{
		if (is_empty())
			return true;

		CBID_NODE<T> * currnode = head;

		while (currnode)
		{
			if (currnode->data.CNIC == cnic) // if cnic already exists in List
			{
				return false;
			}
			currnode = currnode->next;
		}

		return true;
	}

	CBID_NODE<T>* search(T cnic)// to search for specific node associated with provided cnic
	{
		CBID_NODE<T>* currnode = head;

		if (is_empty())// if list is empty
			return NULL;

		while (currnode && currnode->data.CNIC != cnic)//traversing until required cnic is found
		{
			currnode = currnode->next;
		}

		if (currnode == NULL)// if cnic isn't found
			return NULL;
		else if (currnode->data.CNIC == cnic)// if cnic found
			return currnode;
		else
			return NULL;
	}

	bool setcriminalrecord(T cnic, CCID_Data<T>* C)// if citizen has a criminal record 
	{
		if (is_empty())
			return false;
		
		CBID_NODE<T>* currnode = search(cnic);

		if (currnode != NULL)// if citizen found
		{
			currnode->data.CriminalRecord = C;
			return true;
		}
		else// if citizen not found
			return false;
	}

	bool updatename(T cnic, T name)// to update name of a citizen
	{
		CBID_NODE<T>* currnode = search(cnic);

		if (currnode != NULL)//if citizen found
		{
			currnode->data.Name = name;
			return true;
		}
		else//if citizen not found
			return false;
	}

	bool updatefname(T cnic, T fname)// to update father name of a citizen
	{
		CBID_NODE<T>* currnode = search(cnic);

		if (currnode != NULL)//if citizen found
		{
			currnode->data.FName = fname;
			return true;
		}
		else//if citizen not found
			return false;
	}

	bool updategender(T cnic, T gender)// to update gender of a citizen
	{
		CBID_NODE<T>* currnode = search(cnic);

		if (currnode != NULL)//if citizen found
		{
			currnode->data.Gender = gender;
			return true;
		}
		else//if citizen not found
			return false;
	}

	bool updateaddress(T cnic, T address)// to update address of a citizen
	{
		CBID_NODE<T>* currnode = search(cnic);

		if (currnode != NULL)//if citizen found
		{
			currnode->data.Address = address;
			return true;
		}
		else//if citizen not found
			return false;
	}

	bool updatenationality(T cnic, T nationality)// to update nationality of a citizen
	{
		CBID_NODE<T>* currnode = search(cnic);

		if (currnode != NULL)//if citizen found
		{
			currnode->data.Nationality = nationality;
			return true;
		}
		else//if citizen not found
			return false;
	}

	void DisplayAll()//to display whole database
	{
		if (is_empty())
			return;

		CBID_NODE<T> * currnode = head;

		while (currnode)
		{
			cout << "CNIC: " << currnode->data.CNIC << endl
				<< "Name: " << currnode->data.Name << endl
				<< "Father Name: " << currnode->data.FName << endl
				<< "Gender: " << currnode->data.Gender << endl
				<< "Address: " << currnode->data.Address << endl
				<< "Nationality: " << currnode->data.Nationality << endl;

			if (currnode->data.CriminalRecord != NULL)
			{
				cout << "Crimes:\n";
				currnode->data.CriminalRecord->crimes.DisplayAll();
			}

			cout << endl << endl;

			currnode = currnode->next;
		}
	}

	//to destroy all nodes
	~CBIDList()
	{
		CBID_NODE<T>* currnode = head;
		while (currnode)
		{
			head = head->next;
			delete currnode;
			currnode = head;
		}
		head = tail = NULL;
	}
};

//CRIMEList's Data
template <typename T>
struct CRIME_Data
{
	T Description, Punishment, Fine;

	//NULL initialization
	CRIME_Data() : Description(T()), Punishment(T()), Fine(T()) {};
};

//CRIMEList's Node
template <typename T>
struct CRIME_NODE
{
	CRIME_Data<T> data;
	CRIME_NODE<T>* next;

	//NULL initialization
	CRIME_NODE() : next(NULL) {};
};

//CRIMEList (Singly Linked List) to store all crimes of a criminal
template <typename T>
class CRIMEList
{
	CRIME_NODE<T>* head;

public:
	CRIMEList()//NULL initialization of pointers in default constructor
	{
		head = NULL;
	}

	void addcrime(T description, T punishment, T fine)// to insert data of a new crime
	{
		CRIME_NODE<T>* newnode = new CRIME_NODE<T>;//creating new node

		//setting up data
		newnode->data.Description = description;
		newnode->data.Punishment = punishment;
		newnode->data.Fine = fine;
		newnode->next = NULL;

		if (is_empty())//if list is empty
		{
			head = newnode;
		}
		else//if list not empty
		{
			CRIME_NODE<T>* currnode = head;

			while (currnode->next)//traversing to the last node of the list
			{
				currnode = currnode->next;
			}
			currnode->next = newnode;//adding newly created node in the list
		}
	}

	CRIME_NODE<T>* search(T description, T punishment, T fine)//to search for a specific crime
	{
		CRIME_NODE<T>* currnode = head;

		while (currnode && currnode->data.Description != description &&
			currnode->data.Punishment != punishment && currnode->data.Fine != fine)
		{
			currnode = currnode->next;
		}

		if (currnode == NULL)
			return NULL;
		else if (currnode->data.Description == description && currnode->data.Punishment == punishment
			&& currnode->data.Fine == fine)
			return currnode;
		else
			return NULL;
	}

	bool deletecrime(T description, T punishment, T fine)// to delete a crime
	{
		CRIME_NODE<T>* currnode = head; //temp pointer
		//need two pointer in order to remember address of previous node for proper linking of list after deleting node
		CRIME_NODE<T>* prevnode = NULL; 
		
		while (currnode && currnode->data.Description != description &&
			currnode->data.Punishment != punishment && currnode->data.Fine != fine)
		{
			prevnode = currnode;
			currnode = currnode->next;
		}

		if (currnode == NULL)//if crime not found
		{
			return false;
		}
		else if (currnode->data.Description == description && currnode->data.Punishment == punishment
			&& currnode->data.Fine == fine)//if crime found
		{
			if (prevnode == NULL)//if crime is the first node of the list
				head = currnode->next;
			else if (currnode->next == NULL)//if crime is the last node of the list
				prevnode->next = NULL;
			else//if crime is in between in the list
				prevnode->next = currnode->next;

			delete currnode;//deleting node
			return true;
		}
		else
			return false;
	}

	T getallcrimes()//to return all crimes in type string (space + all crimes)
	{
		T output = "";//empty string
		CRIME_NODE<T>* currnode = head;

		while (currnode)//traversing to concatenate all crimes
		{
			output += " " + currnode->data.Description + " " + currnode->data.Punishment 
				+ " " + currnode->data.Fine;
			
			currnode = currnode->next;
		}

		return output;
	}

	bool updatecrime(T description, T punishment, T fine)//updating first crime of list if list is not empty
	{
		if (is_empty())
			return false;
		else
		{
			head->data.Description = description;
			head->data.Punishment = punishment;
			head->data.Fine = fine;

			return true;
		}
	}

	//Updating a specific crime
	bool updatecrime(T odescription, T opunishment, T ofine, T ndescription, T npunishment, T nfine)
	{
		CRIME_NODE<T>* currnode = head;

		while (currnode && currnode->data.Description != odescription &&
			currnode->data.Punishment != opunishment && currnode->data.Fine != ofine)
		{
			currnode = currnode->next;
		}

		if (currnode == NULL)
			return false;
		else if (currnode->data.Description == odescription && currnode->data.Punishment == opunishment
			&& currnode->data.Fine == ofine)
		{
			currnode->data.Description = ndescription;
			currnode->data.Punishment = npunishment;
			currnode->data.Fine = nfine;
			return true;
		}
		else
			return false;

	}

	bool is_empty()//checking if list is empty or not
	{
		if (head == NULL)
			return true;
		return false;
	}

	void DisplayAll()//to display whole list
	{
		if (head == NULL)
			return;

		CRIME_NODE<T> * currnode = head;

		while (currnode)
		{
			cout << "Description: " << currnode->data.Description << endl
				<< "Punishment: " << currnode->data.Punishment << endl
				<< "Fine: " << currnode->data.Fine << endl;
			cout << endl << endl;
			currnode = currnode->next;
		}
	}
	
	void clear()//to delete all the crimes in the list
	{
		CRIME_NODE<T>* currnode = head;
		while (currnode)
		{
			head = head->next;
			delete currnode;
			currnode = head;
		}
	}
};

template <typename T>
struct CCID_Data
{
	T CNIC;
	CRIMEList<T> crimes;
	CBID_Data<T>* BasicInfo;

	//NULL initialization
	CCID_Data() :CNIC(T()), BasicInfo(NULL) {};
};

template <typename T>
struct CCID_NODE {
	CCID_Data<T> data;
	CCID_NODE<T>* next, * previous;

	//NULL initialization
	CCID_NODE() : next(NULL), previous(NULL) {};
};

template <class T>
class CCIDList {
	CCID_NODE<T>* head, * tail;

public:
	CCIDList()//NULL initialization of pointers in default constructor
	{
		head = tail = NULL;
	}

	bool is_empty()//return true if list is empty or vice versa
	{
		if (head == NULL && tail == NULL)
			return true;
		return false;
	}

	void insert(T cnic, T description, T punishment, T fine)//to add record of a new criminal
	{
		CCID_NODE<T>* newnode = new CCID_NODE<T>;//creating new node

		//setting up data
		newnode->data.CNIC = cnic;
		newnode->data.crimes.addcrime(description, punishment, fine);
		newnode->data.BasicInfo = NULL;
		newnode->next = NULL;
		newnode->previous = NULL;

		if (is_empty())//if list is empty
		{
			head = newnode;
			head->next = head;
			head->previous = head;
			tail = head;
		}
		//if cnic of head is greater than or equal to cnic of newly created node
		else if (stoi(head->data.CNIC) >= stoi(newnode->data.CNIC))
		{
			newnode->next = head;
			newnode->previous = head->previous;
			head->previous->next = newnode;
			head->previous = newnode;
			head = newnode;
		}
		else //if cnic of newly created node is in between or greater than the cnic of all nodes
		{
			CCID_NODE<T>* currnode = head->next;

			while (currnode != head && stoi(currnode->data.CNIC) < stoi(newnode->data.CNIC))
			{
				currnode = currnode->next;
			}

			newnode->next = currnode;
			newnode->previous = currnode->previous;
			currnode->previous->next = newnode;
			currnode->previous = newnode;

			if (currnode == head)//if cnic of newly created node is greater than the cnic of all nodes
			{
				tail = newnode;
			}
		}
	}

	CCID_NODE<T>* search(T cnic)// to search for specific node associated with provided cnic
	{
		if (is_empty())//checking if list is empty
			return NULL;

		CCID_NODE<T> * currnode = head; //temp node

		//traversing to search the whole list against provided cnic
		do
		{
			if (currnode->data.CNIC == cnic)//if cnic found in list
				break;
			currnode = currnode->next;
		} while (currnode != head);
		
		if (currnode->data.CNIC == cnic)//if found then return
			return currnode;
		else
			return NULL;
	}

	bool addcrime(T cnic, T description, T punishment, T fine)//to add another crime of a criminal
	{
		CCID_NODE<T>* currnode = search(cnic);//searching for the required criminal node

		if (currnode == NULL)//if not found return false
			return false;
		else if (currnode->data.CNIC == cnic)//if found add another crime in crimelist of that criminal
		{
			currnode->data.crimes.addcrime(description, punishment, fine);
			return true;
		}
		else
			return false;
	}

	void deleterecord(CCID_NODE<T>* node)//to delete a node
	{
		if (node == head && node == tail)//if last node of list
		{
			head = tail = NULL;
		}
		else if (node->previous == tail)//head
		{
			node->next->previous = tail;
			tail->next = node->next;
			head = node->next;
		}
		else if (node->next == head)//tail
		{
			node->previous->next = head;
			head->previous = node->previous;
			tail = node->previous;
		}
		else//if node is in between list
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
		}

		delete node;//deleting node
	}

	bool deletecrime(T cnic, T description, T punishment, T fine)//to delete a crime
	{
		CCID_NODE<T>* currnode = search(cnic);

		if (currnode == NULL)//if criminal not found
			return false;
		else if (currnode->data.CNIC == cnic)//if record found then delete the provided record
		{
			//deleting crime from crime list
			currnode->data.crimes.deletecrime(description, punishment, fine);
			//checking if crimelist is empty then delete the record of the criminal
			if (currnode->data.crimes.is_empty())
				deleterecord(currnode);
			return true;
		}
		else
			return false;
	}

	bool updatecrime(T cnic, T description, T punishment, T fine)//to update a crime
	{
		CCID_NODE<T>* currnode = search(cnic);

		if (currnode == NULL)//if record not found
			return false;
		//if record found then updating the first crime of the criminal
		currnode->data.crimes.updatecrime(description, punishment, fine);
		return true;
	}

	bool setBasicInfo(T cnic, CBID_Data<T> * C)//Basic information of criminal
	{
		CCID_NODE<T>* currnode = search(cnic);//locating node of criminal

		if (currnode != NULL)//if found then setting up his/her record
		{
			currnode->data.BasicInfo = C;
			return true;
		}
		else
			return false;
	}

	void DisplayAll()//to display whole database
	{
		if (head == NULL)
			return;

		CCID_NODE<T> * currnode = head;

		do
		{
			cout << "CNIC: " << currnode->data.CNIC << endl
				<< "Crimes: \n";
			currnode->data.crimes.DisplayAll();
			cout << endl;
			currnode = currnode->next;
		} while (currnode != head);
	}

	~CCIDList()//to delete all nodes
	{
		CCID_NODE<T>* curr;
		while (head != tail)//if list has more than one node
		{
			curr = head;
			head->previous->next = head->next;
			head = head->next;
			if (!curr->data.crimes.is_empty())//to delete all crimes of current criminal
				curr->data.crimes.clear();
			delete curr;
		}
		if (!is_empty())//to delete last node
		{
			delete head;
			head = tail = NULL;
		}
	}
};

template <class T>
class Database {

	CBIDList<T> CBID; //CBID Database
	CCIDList<T> CCID; //CCID Database
	DataPipeline<T> dataPipeline;

public:

	Database(const T& filename, const T& filename1)//default constructor (reading data from file)
	{
		ifstream myfile;

		myfile.open(filename);//Opening CBID.txt file
		T temp;
		
		if (myfile.is_open())//checking if file is opened
		{
			//storing the data of whole file in queue (line by line as string)
			getline(myfile, temp);
			while (!myfile.eof())
			{
				dataPipeline.enqueue(temp);
				getline(myfile, temp);
			}
		}

		myfile.close();

		T cnic, name, fname, gender, address, nationality;
		int pos;

		//splitting data and inserting it in CBIDList
		while (!dataPipeline.is_empty())
		{
			temp = dataPipeline.dequeue();

			pos = temp.find(' ');
			cnic = temp.substr(0, pos);

			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			name = temp.substr(0, pos);

			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			fname = temp.substr(0, pos);

			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			gender = temp.substr(0, pos);

			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			pos = temp.find(' ', pos + 1);
			pos = temp.find(' ', pos + 1);

			address = temp.substr(0, pos);

			nationality = temp.substr(pos + 1);

			CBID.insert(cnic, name, fname, gender, address, nationality);
		}

		myfile.open(filename1);//Opening CCID.txt file

		if (myfile.is_open())//checking if file is opened or not
		{
			//storing the data of whole file in queue (line by line as string)
			getline(myfile, temp);
			while (!myfile.eof())
			{
				dataPipeline.enqueue(temp);
				getline(myfile, temp);
			}
		}

		myfile.close();

		T charges, punishment, fine;

		T key = "in prison";
		//splitting data and inserting it in CCIDList
		while (!dataPipeline.is_empty())
		{
			temp = dataPipeline.dequeue();

			pos = temp.find(' ');
			cnic = temp.substr(0, pos);

			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			charges = temp.substr(0, pos);

			temp = temp.substr(pos + 1);

			pos = temp.find(key);
			punishment = temp.substr(0, pos);
			punishment += key;

			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			temp = temp.substr(pos + 1);

			pos = temp.find(' ');
			fine = temp.substr(pos + 1);

			if (CBID.search(cnic) != NULL)//checking if a user exists in CBID database
			{
				CCID.insert(cnic, charges, punishment, fine);//inserting record in CCID
				//linking the record of criminals
				CBID.setcriminalrecord(cnic, &CCID.search(cnic)->data);
				CCID.setBasicInfo(cnic, &CBID.search(cnic)->data);
			}
		}
	}

	bool CBIDuniquecnic(int cnic)
	{
		return CBID.uniquecnic(cnic);
	}

	void InsertCBID(T cnic, T name, T fname, T gender, T address, T nationality)
	{
		CBID.insert(cnic, name, fname, gender, address, nationality);
	}

	/*Return a string in following format "Name FName Gender Address Nationality Crimes(if any) Charges punishment fine number network activation_date deactivation_date status"
	 Refer to test cases for further clerification*/
	T CBID_Search_by_CNIC(T cnic) //searching in CBID database
	{
		T output = "";//empty string

		//searching record associated with provided cnic in CBID database
		CBID_NODE<T>* searchednode = CBID.search(cnic);
		
		if (searchednode == NULL)//if not found
			return output;

		//concatenating string
		CBID_Data<T> Obj = searchednode->data;
		output = Obj.Name + " " + Obj.FName + " " + Obj.Gender + " " + Obj.Address + 
			" " + Obj.Nationality;

		if (Obj.CriminalRecord != NULL)//if citizen has a criminal record
		{
			output += Obj.CriminalRecord->crimes.getallcrimes();
		}

		return output;
	}
	
	T CCID_Search_by_CNIC(T cnic) 
	{
		T output = "";//empty string

		//searching cnic in CCID databse
		CCID_NODE<T>* searchednode = CCID.search(cnic);

		if (searchednode == NULL)//if not found
			return output;

		//concatenating string
		CCID_Data<T> Obj = CCID.search(cnic)->data;

		output = Obj.BasicInfo->Name + " " + Obj.BasicInfo->FName + " " +
			Obj.BasicInfo->Gender + " " + Obj.BasicInfo->Address +
			" " + Obj.BasicInfo->Nationality + Obj.crimes.getallcrimes();

		return output;
	}

	//updates name of a citizen and return true when cnic found else return false
	bool updateCBIDName(T Name, T cnic) 
	{
		return CBID.updatename(cnic, Name);
	}

	//updates father name of a citizen and return true when cnic found else return false
	bool updateCBIDFName(T Father_Name, T cnic) 
	{
		
		return CBID.updatefname(cnic, Father_Name);
	}

	//updates address of a citizen and return true when cnic found else return false
	bool updateCBIDAddress(T Address, T cnic) 
	{
		return CBID.updateaddress(cnic, Address);
	}

	//updates nationality of a citizen and return true when cnic found else return false
	bool updateCBIDNationality(T Nationality, T cnic) 
	{
		return CBID.updatenationality(cnic, Nationality);
	}
	
	//updates CCIDList, adds a new crime and return true when crime found else return false
	bool addCrime(T cnic, T charges, T punishment, T fine) 
	{
		CBID_NODE<T>* cbnode = CBID.search(cnic);//searching citizen

		if (cbnode == NULL)//checking if citizen exists
			return false;

		if (CCID.search(cnic) == NULL)//if citizen doesn't have any criminal charges
			CCID.insert(cnic, charges, punishment, fine);//creates a new node
		else
			CCID.addcrime(cnic, charges, punishment, fine);//adds a new crime in existing node

		//linking both databases
		CBID.setcriminalrecord(cnic, &CCID.search(cnic)->data);
		CCID.setBasicInfo(cnic, &cbnode->data);

		return true;
	}

	//updates first crime of a criminals and return true when crime found else return false
	bool updateCrime(T cnic, T charges, T punishment, T fine) 
	{
		return CCID.updatecrime(cnic, charges, punishment, fine);
	}

	//Deletes crime of a criminal and returns true when crime found else return false
	bool deleteCrime(T cnic, T charges, T punishment, T fine) 
	{
		bool check = CCID.deletecrime(cnic, charges, punishment, fine);

		if (CCID.search(cnic) == NULL)
		{
			CBID.search(cnic)->data.CriminalRecord = NULL;
		}

		return check;
	}

	~Database() {
		/* All the databases will be cleaned by the end of this destructor as all the classes above has their own destructors */
	}
};

#endif
