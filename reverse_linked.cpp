#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class node{
	public:
		int data; // data field
		node *next;
};

node* reverse(node* head){
	node *next=NULL,*cur=head,*prev=NULL; //initialize the pointers
	while(cur!=NULL){//loop till the end of linked list
		next=cur->next;//next = cur->next to store the rest of the list;
		cur->next=prev;//change the direction of linked list
		prev=cur; //update prev
		cur=next; //update cur
	}

	head=prev; //update head
	return head; //return head
}

void traverse(node* head){
	node* current=head; // current node set to head
	int count=0; // to count total no of nodes
	printf("\ntraversing the list\n");
	while(current!=NULL){ //traverse until current node isn't NULL
		count++; //increase node count
		printf("%d ",current->data);
		current=current->next; // go to next node
	}
	printf("\ntotal no of nodes : %d\n",count);
}

node* creatnode(int d){
	node* temp=(node*)malloc(sizeof(node));
	temp->data=d;
	temp->next=NULL;
	return temp;
}

int main(){
	printf("creating the linked list by inserting new nodes at the begining\n");
	printf("enter 0 to stop building the list, else enter any integer\n");
	int k,count=1,x;

	node* curr;

	scanf("%d",&k);
	node* head=creatnode(k); //buliding list, first node
	scanf("%d",&k);

	//inserting at begining////
	while(k){
		curr=creatnode(k);
		curr->next=head;   //inserting each new node at the begining
		head=curr;
		scanf("%d",&k);
	}
	traverse(head); // displaying the list

	cout<<"reversing the list............"<<endl;
	head=reverse(head);// reverse the linked list
	traverse(head);//display reversed linked list

	return 0;	
}