#include <iostream>
#include <time.h>
using namespace std;

struct node{
	int data;
	struct node *link;
};

class circular_linklist{
	private:
		node *first;
	
	public:
		int execute ( int k , int n );
		circular_linklist();
		void Delete( int num );
};

circular_linklist::circular_linklist(){
	first = NULL;
}

int circular_linklist::execute( int k , int n ){
	
	int i = 1;
	node *temp;
	int kill=0;
	node *deletenode;
	int current;
	node *before;
	int result;
	
	while( i <= 2*k ){                         /*Creat circular linked list*/
		if( i == 1 ){                           /*Mark bad guy with 0 and good guy with 1*/
			first=new node;
			temp=first;
			temp->data=0;
		}
		else if ( ( i > 1 ) && ( i <= k ) ){
			temp->link=new node;
			temp=temp->link;
			temp->data=0;
		}
		else if ( ( i > k ) && ( i <= 2*k ) ){
			temp->link=new node;
			temp=temp->link;
			temp->data=1;
	    }
		i++;
	}
	
	temp->link=first;                            /*Let the last node link to the first node*/
	temp=first;
	
	while( kill < k ){                           
		for ( int a = 1 ;a <= n; a++ ){                   
			if( a == n-1 )                           /*Record beforenode*/
			   before=temp;
			current=temp->data;
			temp=temp->link;
	    }
	    if ( current == 1 ){
		    deletenode=before->link;
		    before->link = before->link->link;
		    delete deletenode;
		    kill++;
        }
        else{
        	kill=2*k;
        	result=1;
		}
		if( kill == k ){
		    result=0;
		}
    }
    return result;
}

int main(){
	
	int k , n ;
	double time=0;
	circular_linklist a;
	double start,end;
	cout << "Input number K between 1~13" << endl;
	cin >> k;
	cout << "Input number n you want to kill " << endl;
	cout << "You need to find the minimum n in 15 seconds!!" << endl;
	cin >> n;
	while( time<= 15 ){                                                  /*Execute the program and find min n in 15 s*/
		if( a.execute(k,n) == 1){
			start=clock();
			cout << "fail" << endl;
			n=0;
		    cout << "Input number n you want to kill" << endl;
	        cin >> n;
	        end=clock();
			time=time+(end-start)/CLOCKS_PER_SEC;
			cout << "current time : " << time << "seconds" << endl;
	    }
	    else{
	    	time=16;
	    	cout << "success" << endl;
		}
	}
	cout << "Time is up!!";
	
	
	system("pause");
	return 0;	
}

