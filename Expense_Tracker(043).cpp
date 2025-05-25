#include <iostream>
#include <iomanip>
using namespace std;


class BaseNode {
public:
    virtual void display() = 0;
    virtual void update() = 0;
 
    BaseNode* next ;
	BaseNode(){
		next= NULL;
	} 
};

template<typename T>
class Node : public BaseNode {
public:
    T data;
    Node(T v){
		data = v;
	}
    void display() override {
        cout <<left<<data;
    }
    void update() override {
    	T type;
    	cin>>type;
    	data = type;
	}
};

class MasterNode{
	public:
	BaseNode *key;
	MasterNode *next;
	Master(){
		key = NULL;
		next = NULL;
	}
};

class List{
	public:
	MasterNode *head, *tail;
	int num;
	
	List (){
		head = NULL;
		tail = NULL;
		num = 0;
	}
	void addExpense(string name, float amount,int date,int month,int year){
		MasterNode *master = new MasterNode();
		if (head == NULL){
			head = master;
			tail = master;
		}else{
			tail->next = master;
			tail = master;
		}
		
		Node<string> *newnode1 = new Node<string>(name);
		Node<float> *newnode2 = new Node<float>(amount);
		Node<string> *newnode3 = new Node<string>("Unpaid");
		Node<int> *newnode4 = new Node<int>(date);
		Node<int> *newnode5 = new Node<int>(month);
		Node<int> *newnode6 = new Node<int>(2000+year);
			
		tail->key = newnode1;
		newnode1->next = newnode2;
		newnode2->next = newnode3;
		newnode3->next = newnode4;
		newnode4->next = newnode5;
		newnode5->next = newnode6;
		
		num++;	
		cout<<"     ----Expense-Added----"<<endl;
	}
	
	bool check(int step){
		if(step-1 >= num){
			cout<<"(Not Found)"<<endl;
			return false;
		}
		return true;
	}
	
	void updateExpense(int step){
		MasterNode *temp = head;
		
		for(int i=1;i<step;i++){
			temp = temp->next;
		}	
		string type;
		float amount;
		cout<<"Expense name: ";
		temp->key->update();

		cout<<"Expense amount: ";
		temp->key->next->update();
		cout<<"     ----Expense-Updated----"<<endl;
	}
	
	void markpaid(int step){
		MasterNode *temp = head;
		
		for(int i=1;i<step;i++){
			temp = temp->next;
		}
	BaseNode *t = temp->key->next->next; 
	Node<string> *stringNode = static_cast<Node<string>*>(t);
	stringNode->data = "Paid";
		cout<<"     ----Expense Marked Paid----"<<endl;
	}
	
	deleteExp(int step){
			MasterNode *temp = head, *prev = head;
		for(int i=1;i<step;i++){
			temp = temp->next;
		}
		delete temp->key->next->next->next->next->next;//year
		delete temp->key->next->next->next->next;//month
		delete temp->key->next->next->next;//day
		delete temp->key->next->next;//status
		delete temp->key->next;//amount
		delete temp->key;//name
		
		for(int i=1;i<step-1;i++){
			prev = prev->next;
		}
		prev->next = temp->next;
		delete temp;//masternode
		cout<<"    ----Expense-Removed----"<<endl;
	}

bool display() {
    if (num == 0) {
        cout << "(List is empty)" << endl;
        return false;
    }

    cout << "       ---- Displaying Expense List ----" << endl;

    cout << left << setw(5) << "ID"
         << setw(15) << "Name"
         << setw(10) << "Amount"
         << setw(10) << "Status"
         << setw(8) << "Date"
         << endl;
    cout << string(50, '-') << endl;

    MasterNode *temp = head;
    int count = 1;
    while (temp != NULL) {
        BaseNode *t = temp->key;
        
        cout<< setw(5)<<left<<count;
        cout<< setw(15); t->display(); t = t->next;
        cout<< setw(10); t->display(); t = t->next;
        cout<< setw(10); t->display(); t = t->next;
        t->display();                  t = t->next;
        cout<<"-";  t->display();      t = t->next;
        cout<<"-";  t->display();
        cout<<endl;

        temp = temp->next;
        count++;
    }
     cout << string(50, '-') << endl;
     return true;
}
	void report(){
		MasterNode *temp = head;
		float ptotal = 0,utotal=0;
		int paid = 0, unpaid =0;
		while(temp!=NULL){
			
			BaseNode *t = temp->key->next->next; 
			Node<string> *status = static_cast<Node<string>*>(t);
			t = temp->key->next;
			Node<float> *value= static_cast<Node<float>*>(t);
				
			if(status->data != "Paid"){
				utotal += value->data;
				unpaid++;
			}
			else{
				ptotal += value->data;
				paid++;
			} 
			
			temp = temp->next;
		}
		cout<<setw(10)<<"Paid"<<setw(10)<<"Unpaid"<<setw(20)<<"Amount Paid"<<setw(20)<<"Amount Unpaid"<<endl;
		cout<<setw(10)<<left<<paid<<setw(10)<<left<<unpaid<<setw(20)<<left<<ptotal<<setw(20)<<left<<utotal<<endl;
	}

};


main(){
	List exp;
	int a,date,month,year;
	string name;
	float amount;
menu: 
	cout<<endl<<"<<<< Select Option >>>>"<<endl;	
	cout<<"1) Add new Expense\n2) Update List\n3) Mark Paid\n4) Delete Expense\n5) Display List \n0) Exit"<<endl;
	cin>>a;
	switch(a){
		case 1:
			cout<<"Expense name: ";
			cin>>name;
			cout<<"Expense amount: ";
			cin>>amount;
		   date:
			cout<<"Enter day (1-31): ";
			cin>>date;
			cout<<"Enter month (1-12): ";
			cin>>month;
			cout<<"Enter year (0-25): ";
			cin>>year;
			if(date>31 || month>12 ||year>25){
				cout<<"Invalid Date!"<<endl;
				goto date;
			}
			exp.addExpense(name,amount,date,month,year);
			goto menu;
			//break;
		case 2:
			if(exp.display()){
			cout<<"0) Exit"<<endl;
			cout<<"Select Expense ID to edit: ";
			cin>>a;
			if(a==0){
				goto menu;
			}
			else if(exp.check(a)){
				exp.updateExpense(a);
				}
			}
			goto menu;
			break;
		case 3:
			if(exp.display()){
			cout<<"0) Exit"<<endl;
			cout<<"Select Expense ID: ";
			cin>>a;
			if(a==0){
				goto menu;
			}
			else if(exp.check(a)){
				exp.markpaid(a);
				}
			}
			goto menu;
			break;
		case 4:
			if(exp.display()){
			cout<<"0) Exit"<<endl;
			cout<<"Select Expense ID to delete: ";
			cin>>a;
			if(a == 0){
				goto menu;
			}
			else if(exp.check(a)){
				exp.deleteExp(a);
				}
			}
			goto menu;
				
		case 5: 
			if(exp.display()){
				exp.report();
			}
			goto menu;
			//break;
				
		case 0:
			break;
		default:
			cout<<"Invalid Input";
			goto menu;		
	}
	
}
