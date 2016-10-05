#include <iostream>
#include <vector>
#include <algorithm>

#define T int
#define NIL NULL

using namespace std;

struct Node{
	T ID;
	Node* L;
	Node* R;
	Node* P;
	/* Todo : Info */
	Node(){ L=NIL; R=NIL; P=NIL;}
	Node operator=(Node node){
		ID = node.ID;
		L = node.L; R = node.R; P = node.P;
		/* Todo : Info = node.Info */
	}
};

int N;
vector<T> nodes;
Node* root;

void Init_Nodes(Node* node,int Start,int End){
	if( (End-Start < 2) || (node == NIL) )
		return;

	int Mid = (End-Start)/2 + Start;

	node->L = new Node;
	node->L->ID = nodes[ (Mid-Start)/2 + Start ];
	node->L->P = node;
	if(End-Start != 2){
		node->R = new Node;
		node->R->ID = nodes[ (End-(Mid+1))/2 + Mid+1 ];
		node->R->P = node;
	}

	Init_Nodes(node->L,Start,Mid);
	Init_Nodes(node->R,Mid+1,End);

	/* Todo : Update Info */
}

void Build_Tree(){
	sort(nodes.begin(),nodes.end());
	N = nodes.size();
	root = new Node();
	root->ID = nodes[N/2];
	Init_Nodes(root,0,N);
}

Node* Find(Node* node,T ID){
	if(node == NIL || node->ID == ID)
		return node;
	if(node->ID > ID)
		return Find(node->L,ID);
	else
		return Find(node->R,ID);
}

Node* Tree_Min(Node* node){
	if(node->L == NIL)
		return node;
	else
		return Tree_Min(node->L);
}

Node* Tree_Max(Node* node){
	if(node->R == NIL)
		return node;
	else
		return Tree_Max(node->R);
}

void Exchange(Node* Old,Node* New){
	if(Old->P == NIL){
		if(New == NIL)
			delete Old;
		else if(New->P == Old){
			New->P = NIL;
			*Old = *New;
			delete New;
		}
		else{

		}
	}
	else if(Old->ID > Old->P->ID)
		Old->P->R = New;
	else
		Old->P->L = New;
}

bool Delete_Node(Node* node,T ID){
	if(node == NIL)
		return false;
	if(node == ID){
		if(node->R==NIL && node->L==NIL)
			Exchange(node,NIL);
		else if(node->R==NIL)
			Exchange(node,node->L);
		else if(node->L==NIL)
			Exchange(node,node->R);
		else
			Exchange(node,Tree_Min(node->R));
		return true;
	}

	bool ret;

	if(node->ID > ID){
		ret = Delete_Node(node->L,ID);
		if(ret){
			/* Todo : Modify Info */
		}
	}
	else{
		ret = Delete_Node(node->R,ID);
		if(ret){
			/* Todo : Modify Info */
		}
	}
	return ret;
}

void Delete_Tree(Node* node){
	if(node == NIL)
		return;
	Delete(node->L);
	Delete(node->R);
	delete node;
}

int main(){
	nodes.clear();
	nodes.resize(5);
	for(int i=0 ; i<5 ; i++)
		nodes[i] = i*10;
	Build_Tree();

	Node* test = Find(root,30);
	if(test->ID > test->P->ID)
		test->P->R = NIL;
	else
		test->P->L = NIL;
	delete test;

	cout<<endl;

	Delete_Tree(root);
}