#include <iostream>
#include <vector>
using namespace std;

class BaseNode {
public:
    virtual void display() = 0;
    virtual void update() = 0;
    BaseNode* next = NULL; 
};

template<typename T>
class Node : public BaseNode {
public:
    T data;
    Node(T v){
		data = v;
	}
    void display() override {
        cout<<data<<" ";
    }
    void update() override {
    	T type;
    	cin>>type;
    	data = type;
	}
};

class Master{
	public:
	BaseNode *key;
	Master *next;
	Master(){
		key = NULL;
		next = NULL;
	}
};

class List{
	public:
	Master *head, *tail;
	int num;
	
	List (){
		head = NULL;
		tail = NULL;
		num = 0;
	}
	void addExpense(string name, float amount){
		Master *master = new Master();
		if (head == NULL){
			head = master;
			tail = master;
		}else{
			tail->next = master;
			tail = master;
		}
		
	
		Node<int> *newnode1 = new Node<int>(num+1);
		Node<string> *newnode2 = new Node<string>(name);
		Node<float> *newnode3 = new Node<float>(amount);
		
		tail->key = newnode1;
		newnode1->next = newnode2;
		newnode2->next = newnode3;
		
		num++;	
		cout<<"----Expense-Added----"<<endl;
	}
	void updateExpense(int step){
		if(step-1 >= num){
			cout<<"(NaN)"<<endl;
			return ;
		}
		Master *temp = head;
		
		for(int i=1;i<step;i++){
			temp = temp->next;
		}
		
		string type;
		float amount;
		
		cout<<"Expense type: ";
		temp->key->next->update();

		cout<<"Expense amount: ";
		temp->key->next->next->update();

		cout<<"----Expense-Updated----"<<endl;
	}
	void display(){
		if(num==0){
			cout<<"(List is empty)"<<endl;
			return ;
		}
		cout<<"----Displaying-List----"<<endl;
		Master *temp = head;
		while(temp!=NULL){
			BaseNode *t = temp->key;
			while(t!=NULL){
				t->display();
				t = t->next;
			}
		cout<<endl;
		temp = temp->next;
		}
	}
};


main(){
	List exp;
	int a;
	string name;
	float amount;
menu: 
	cout<<endl<<"<<<< Select Option >>>>"<<endl;	
	cout<<"1) Add new Expense\n2) Update List\n3) Display List\n0) Exit"<<endl;
	cin>>a;
	switch(a){
		case 1:
			cout<<"Expense name: ";
			cin>>name;
			cout<<"Expense amount: ";
			cin>>amount;
			exp.addExpense(name,amount);
			goto menu;
			//break;
		case 2:
			exp.display();
			cout<<"Select Expense to edit: ";
			cin>>a;
			exp.updateExpense(a);
			goto menu;
			break;
		case 3:
			exp.display();
			goto menu;
			//break;	
				
		case 0:
			break;
		default:
			cout<<"Invalid Input";
			goto menu;		
	}
	
}



//void traverse(BaseNode* head) {
//    BaseNode* current = head;
//    while (current != NULL) {
//        current->display();
//        current = current->next;
//    }
//}

