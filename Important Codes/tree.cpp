#include <iostream>
#include <fstream>

using namespace std;

#define NIL NULL

struct Node{
	int ID;
	Node* Left;
	Node* Right;
	int nRight;
	int nLeft;
	bool killed;

	Node(){
		Left=NIL;
		Right=NIL;
		nRight=0;
		nLeft=0;
		killed=false;
	}
};

Node* root;

void init_tree(Node* node,int Start,int End){
	if( (End-Start < 2) || (node == NIL) )
		return;

	node->Left = new Node;
	node->Left->ID = (node->ID-Start)/2 + Start;
	if(End-Start != 2){
		node->Right = new Node;
		node->Right->ID = (End-(node->ID+1))/2 + node->ID+1;
	}

	init_tree(node->Left,Start,node->ID);
	init_tree(node->Right,node->ID+1,End);

	node->nLeft = node->Left->nLeft + node->Left->nRight + 1 ;
	if(node->Right != NIL)
		node->nRight = node->Right->nLeft + node->Right->nRight + 1;
}

void Kill(int i,Node* node){
	if(node->nLeft == i){
		if(node->killed){
			Kill( i - node->nLeft , node->Right);
			node->nRight--;
		}
		else
			node->killed=true;
	}

	else if(node->nLeft < i){
		if(node->killed){
			Kill( i - node->nLeft , node->Right);
			node->nRight--;
		}
		else{
			Kill( i - node->nLeft - 1 , node->Right);
			node->nRight--;
		}
	}

	else{
		Kill(i,node->Left);
		node->nLeft--;
	}
}

int Josephos(Node* node){
	if(node->killed){
		if(node->nLeft)
			return Josephos(node->Left);
		else
			return Josephos(node->Right);
	}
	return node->ID+1;
}

void Delete(Node* node){
	if(node->Left != NIL)
		Delete(node->Left);
	if(node->Right != NIL)
		Delete(node->Right);
	delete node;
}

int main(){
	//ifstream cin("input.h");
	int N,K;
	while(true){
		cin>>N>>K;
		if(N==0)
			return 0;

		root = new Node;
		root->ID=N/2;
		init_tree(root,0,N);

		int i=-1;
		for(int cnt=N;cnt!=1;cnt--){
			i=(i+K)%cnt;
			Kill(i,root);
			i--;
		}

		cout<<N<<" "<<K<<" "<<Josephos(root)<<endl;

		Delete(root);
	}
}