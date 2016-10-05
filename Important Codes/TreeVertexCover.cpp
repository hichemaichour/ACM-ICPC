#include "h.cpp"

#define NIL -1

VI P;				// Parent
VI NC;				// number of children
VB Not;				// Not in the graph ??
VB Mark;			// In the vertex cover ??
deque<int> L;		// Leafs
int Root;			// Root

void Find_Leafs_and_Root(){
	L.clear();
	int i;
	FOR(i,NC.size()){
		if(NC[i] == 0)
			L.push_back(i);
		if(P[i] == NIL)
			Root = i;
	}
}

int Vertex_Cover(){
	Find_Leafs_and_Root();
	while(!L.empty()){
		int f = L.front(); L.pop_front();
		if(!Not[f]){
			if(!Mark[f] && P[f] == NIL)
				Mark[f] = true;
			else if(!Mark[f] && P[f] != NIL)
				Mark[P[f]] = true;
			Not[f] = true;
			NC[P[f]]--;
			if(P[f] != NIL && P[f] != Root)
				if( NC[P[f]] == 0 )
					L.push_back(P[f]);
		}
	}

	int i;
	int ret=0;
	FOR(i,Mark.size())
		if(Mark[i])
			ret++;
	return ret;
}

int main(){
	return 0;
}