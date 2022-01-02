#include <queue>
#include <iostream>
using namespace std;

class node {
public:
	int arr[3][3];
	int heur;
public:
	
	node() {};
	node(int array[][3], int h) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->arr[i][j] = array[i][j];
			}
		}
		this->heur = h;
	}
	//copy constructor
	node(const node& n) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->arr[i][j] = n.arr[i][j];
			}
		}
		this->heur = n.heur;
	}
	
};
class index {
public:
	int ivalue;
	int jvalue;
};


bool operator<(const node& p1, const node& p2)
{

	return p1.heur > p2.heur;
}

int calculateheuristic(int array1[][3],int refarray[][3]) {
	int h = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (array1[i][j] != refarray[i][j]&&array1[i][j]!=0) {
				h += 1;
			}
		}
	}
	return h;
}
int calculatedistance(int array1[][3], int refarray[][3]) {
	int sum = 0;
	for (int x1 = 0; x1 < 3; x1++) {
		for (int y1 = 0; y1 < 3; y1++) {
			for (int x2 = 0; x2 < 3; x2++) {
				for (int y2 = 0; y2 < 3; y2++) {
					if (array1[x1][y1] == refarray[x2][y2]) {
						int dx = x1 - x2;
						int dy = y1 - y2;
						if (dx < 0) { dx *= -1; }
						if (dy < 0) { dy *= -1; }
						sum = sum + dx + dy;
					}
				}
			}
		}
	}
	return sum;
}

index returnindex(node n) {
	index in;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (n.arr[i][j] == 0) {
				in.ivalue = i;
				in.jvalue = j;
			}
		}
	}
	return in;
}

void createrightchild(node n, priority_queue<node>& pq, index ind, int goal[][3],int i) {
	node rc(n);
	rc.arr[ind.ivalue][ind.jvalue] = rc.arr[ind.ivalue][ind.jvalue + 1];
	rc.arr[ind.ivalue][ind.jvalue + 1] = 0;
	if (i == 1) {
		rc.heur = calculateheuristic(rc.arr, goal);
	}
	if (i == 2) {
		rc.heur = calculatedistance(rc.arr, goal);
	}
	pq.push(rc);
}
void createleftchild(node n, priority_queue<node>& pq, index ind, int goal[][3],int i) {
	node lc(n);
	lc.arr[ind.ivalue][ind.jvalue] = lc.arr[ind.ivalue][ind.jvalue - 1];
	lc.arr[ind.ivalue][ind.jvalue - 1] = 0;
	if (i == 1) {
		lc.heur = calculateheuristic(lc.arr, goal);
	}
	if (i == 2) {
		lc.heur = calculatedistance(lc.arr, goal);

	}
	pq.push(lc);
}
void createupchild(node n, priority_queue<node>& pq, index ind, int goal[][3],int i) {
	node uc(n);
	uc.arr[ind.ivalue][ind.jvalue] = uc.arr[ind.ivalue - 1][ind.jvalue];
	uc.arr[ind.ivalue - 1][ind.jvalue] = 0;
	if (i == 1) {
		uc.heur = calculateheuristic(uc.arr, goal);
	}
	if (i == 2) {
		uc.heur = calculatedistance(uc.arr, goal);

	}
	pq.push(uc);
}
void createdownchild(node n, priority_queue<node>& pq, index ind, int goal[][3],int i) {
	node dc(n);
	dc.arr[ind.ivalue][ind.jvalue] = dc.arr[ind.ivalue + 1][ind.jvalue];
	dc.arr[ind.ivalue + 1][ind.jvalue] = 0;
	if (i == 1) {
		dc.heur = calculateheuristic(dc.arr, goal);
	}
	if(i==2){
		dc.heur = calculatedistance(dc.arr, goal);

	}

	pq.push(dc);
}
void createchildnodes(node n, priority_queue<node>& pq, int goal[][3],int i) {
	index ind = returnindex(n);
	if (ind.jvalue < 2) {
		createrightchild(n, pq, ind, goal,i);
	}
	if (ind.jvalue > 0) {
		createleftchild(n, pq, ind, goal,i);
	}
	if (ind.ivalue > 0) {
		createupchild(n, pq, ind, goal,i);
	}
	if (ind.ivalue < 2) {
		createdownchild(n, pq, ind, goal,i);
	}
}
void display(node n) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << n.arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "Heuristic value is: " << n.heur << "\n";
	cout << "\n" << "\n";
}
void bestfirstsearch(priority_queue<node> &pq, int goal[][3],int i) {
	node n;
	n = pq.top();
	while (n.heur != 0) {
		pq.pop();
		display(n);
		createchildnodes(n,pq,goal,i);
		n = pq.top();
	}
	display(n);

}


int main() {
	int goal[3][3] = { {1,8,7},{2,0,6},{3,4,5} };
	int start[3][3] = { {1,8,7},{0,6,5},{2,3,4} };
	
	int choice;
	priority_queue<node> pq;
	cout << "Enter 1 to solve by using number of misplaced tiles heuristic " << "\n";
	cout<< "Enter 2 to solve by using number of misplaced tiles heuristic " << "\n";
	cin >> choice;
	switch (choice) {
	case 1: {
		int h = calculateheuristic(start, goal);
		node n(start, h);
		pq.push(n);
		cout << "Solving using no of misplaced tiles heuristic" << "\n";
		bestfirstsearch(pq, goal, 1);
		break; }
	case 2: {
		int newheuristic = calculatedistance(start, goal);
		node nn(start, newheuristic);
		pq.push(nn);
		cout << "Solving using manhattan distance heuristic" << "\n";
		bestfirstsearch(pq, goal, 2);
		break;
	}
	}
	
	
	
	
	
	


	return 0;
}