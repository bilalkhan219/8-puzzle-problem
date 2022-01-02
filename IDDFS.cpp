#include <iostream>
using namespace std;

class index {
public:
	int ivalue;
	int jvalue;
	index() {
		ivalue = 0;
		jvalue = 0;
	}
};

class node {
public:
	int arr[3][3];
	int* pt;

public:
	node(int array[][3]) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						arr[i][j] = array[i][j];
					}
				}
				pt = (int*)1;
	}
	node(const node& n) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
						this->arr[i][j] = n.arr[i][j];
			}
		}
		this->pt=n.pt;
	}
};
index returnindex(int array[][3]) {
		index in;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (array[i][j] == 0) {
					in.ivalue = i;
					in.jvalue = j;
				}
			}
		}
		return in;
}
bool isgoal(int start[][3] , int goal[][3]) {
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (start[i][j] != goal[i][j]) {
				return false;
			}
		}
	}
	return true;
}
void display(node n) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << n.arr[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";

}
node createrightchild(node n) {
	index ind;
	ind = returnindex(n.arr);
	if (ind.jvalue >= 2) {
		n.pt = nullptr;
		return n;
	}

	n.arr[ind.ivalue][ind.jvalue] = n.arr[ind.ivalue][ind.jvalue + 1];
	n.arr[ind.ivalue][ind.jvalue + 1] = 0;
	return n;
}
node createleftchild(node n) {
	index ind;
	ind = returnindex(n.arr);
	if (ind.jvalue <= 0) {
		n.pt = nullptr;
		return n;
	}
	
	n.arr[ind.ivalue][ind.jvalue] = n.arr[ind.ivalue][ind.jvalue - 1];
	n.arr[ind.ivalue][ind.jvalue - 1] = 0;
	return n;
}

node createupchild(node n) {
	index ind;
	ind = returnindex(n.arr);
	if (ind.ivalue <= 0) {
		n.pt = nullptr;
		return n;
	}
	
	n.arr[ind.ivalue][ind.jvalue] = n.arr[ind.ivalue-1][ind.jvalue];
	n.arr[ind.ivalue-1][ind.jvalue] = 0;
	return n;
}
node createdownchild(node n) {
	index ind;
	ind = returnindex(n.arr);
	if (ind.ivalue >= 2) {
		n.pt = nullptr;
		return n;
	}
	
	n.arr[ind.ivalue][ind.jvalue] = n.arr[ind.ivalue + 1][ind.jvalue];
	n.arr[ind.ivalue + 1][ind.jvalue] = 0;
	return n;
}



bool DLS (node n, int limit,int goal[][3]) {
	if (n.pt == nullptr) {
		return false;
	}

	if (isgoal(n.arr, goal)) {
		display(n);
		return true;
	}
	
	if (limit <= 0) {
		return false;
	}

	node n1(n);
	if (DLS(createrightchild(n1), limit-1, goal)==true) {
		display(n1);
		return true;
	}
	node n2(n);
	if (DLS(createleftchild(n2), limit-1, goal)==true) {
		display(n2);
		return true;
	}
	node n3(n);
	if (DLS(createupchild(n3), limit-1, goal)==true) {
		display(n3);
		return true;
	}
	node n4(n);
	if (DLS(createdownchild(n4), limit-1, goal)==true) {
		display(n4);
		return true;
	}
	return false;

}
bool IDDFS(node n, int depth,int goal[][3]) {
	for (int i = 0; i <= depth; i++) {
		if (DLS(n, i,goal)) {
			cout << "depth:" << i << "\n";
			return true;
		}
	}
	return false;
}

int main() {
	int g[3][3] = { {1,8,7},{2,0,6},{3,4,5} };
	int s[3][3] = { {1,8,7},{0,6,5},{2,3,4} };
	node no(s);
	bool iddfs = IDDFS(no, 6, g);
	if (!iddfs) {
		cout << "Cannot be solved" << "\n";
	}
}