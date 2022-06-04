#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

struct Node {
	struct Node* prev;
	unsigned long long int data;
	struct Node* next;
};

void insert_bef(struct Node* old_node, unsigned long long int new_data, Node** head) {

	struct Node* new_node = new Node;
	new_node->data = new_data;
	new_node->prev = old_node->prev;
	new_node->next = old_node;
	if (old_node->prev != NULL) {
		old_node->prev->next = new_node;
	}
	if (new_node->next != NULL) {
		new_node->next->prev = new_node;
	}
	if (old_node == *head) {
		*head = new_node;
	}
}

void insert_aft(struct Node* old_node, unsigned long long int new_data) {

	struct Node* new_node = new Node;
	new_node->data = new_data;
	new_node->prev = old_node;
	new_node->next = old_node->next;
	if(old_node->next != NULL) 	old_node->next->prev = new_node;
	old_node->next = new_node;
}

Node* insert_head(struct Node* old_node, unsigned long long int new_data, bool *init) {

	struct Node* new_node = new Node;
	if (*init == false) {
		new_node->data = new_data;
		new_node->next = NULL;
		new_node->prev = NULL;
		*init = true;
	}
	else {
		new_node->data = new_data;
		new_node->prev = old_node->prev;
		new_node->next = old_node;
		old_node->prev = new_node;
		if (new_node->next != NULL) {
			new_node->next->prev = new_node;
		}
	}
	return new_node;
}

void make(struct Node* tail, int new_data) {

	struct Node* new_node = new Node;
	new_node->data = new_data;
	new_node->prev = tail;
	new_node->next = NULL;
	tail->next = new_node;

}

int get_end(Node* head) {
	int count = 1;
	while (head->next != NULL) {
		head = head->next;
		count++;
	}
	return count;
}

void del(struct Node* node, struct Node** head, bool* init, int* length) {
	if (node->prev != NULL) {
		node->prev->next = node->next;
	}
	if (node->next != NULL) {
		node->next->prev = node->prev;
	}
	if (node == *head && *length>1) {
		*head = node->next;
	}
	else if (node == *head && *length == 1) {
		*init = false;
	}
	*length -= 1;
	delete node;
}

void deleteList(Node** head,int length)
{

	Node* current = *head;
	Node* next = NULL;

	if (length > 0) {
		while (current != NULL)
		{
			next = current->next;
			delete current;
			current = next;
		}

		*head = NULL;
	}
	
}

bool exists(int index, Node* head) {
	int i = 0;
	while (i <= index) {
		if (head->next != NULL) {
			head = head->next;
			if (i == index) {
				return 1;
			}
		}
		else {
			return 0;
		}
		i++;
	}
	return 1;
}

Node* getNode(int index, Node* head) {
	int i = 0;
	struct Node* search = head;
	while (i <= index) {
		search = head;
		if(head->next != NULL)
			head = head->next;
		i++;
	}
	return search;
}

Node* getTail(Node* head) {
	struct Node* search = head;
	while (head->next != NULL) {
		head = head->next;
		search = head;
	}
	return search;
}

void move_up(Node** it, bool del) {
	if ((*it)->next != NULL) {
		*it = (*it)->next; // NAPRAW USUWANIE ITERATORA NA 1 I OSTATNIM MIEJSCU!!!!!!!!!!!!!!!
	}
	else if(del){
		*it = nullptr;
	}
}

void move_down(Node** it) {
	if (*it != NULL) {
		if ((*it)->prev != NULL) {
			*it = (*it)->prev;
		}
	}
}


void print_all(Node* head, bool init) {
	bool go = true;
	if (init) {
		while (go) {
			cout << head->data << " ";
			if (head->next != NULL) {
				head = head->next;
			}
			else
				go = false;
		}
	}
	cout << endl;
}

bool using_its(bool begit, bool endit) {
	if (!begit && !endit) return true;
	else return false;
}

void reset(bool* begit, bool* endit) {
	*begit = false;
	*endit = false;
}

void del_it_up(Node* its[10], Node* ex) {
	for (int i = 0; i < 10; i++) {
		if (its[i] == ex) move_up(&its[i],true);
	}
}

void del_it_down(Node* its[10], Node* ex) {
	for (int i = 0; i < 10; i++) {
		if (its[i] == ex) move_down(&its[i]);
	}
}

void null_it(Node* its[10], Node* ex) {
	for (int i = 0; i < 10; i++) {
		if (its[i] == ex) its[i] = NULL;
	}
}

void del_it(Node** node,Node** head, bool* init, int* length, Node* its[10]) {
	if (*node != NULL) {
		struct Node* new_node = *node;
		if (*length == 1) {
			null_it(its, new_node);
			del(new_node, head, init, length);
			return;
		}
		if (new_node == getTail(*head)) {
			del_it_down(its, new_node);
		}
		else 	del_it_up(its, new_node);

		del(new_node, head, init, length);
	}
}

int main() {
	struct Node* head = new Node;
	char str[3];
	int length = 0;
	bool init = false;
	int pos;
	Node* its[10];
	char indtab[4];
	char postab[4];
	int index = -1;
	unsigned long long int key = -1;
	bool all = false;
	bool begit = false;
	bool endit = false;
	while (true)
	{
		scanf("%2s %3s", str, indtab);
		if (indtab[0] != 'B' && indtab[0] != 'E' && indtab[0] != 'A')
			index = indtab[0] - '0';
		else if (indtab[0] == 'B') {
			begit = true;
			index = 0;
		}
		else if (indtab[0] == 'E'){
			if (init == false) {
				begit = true;
				index = 0;
			}
			else
				index = get_end(head);
			endit = true;
		}
		else if (str[0] == 'P' && indtab[0] == 'A') {
			all = true;
		}
		if (feof(stdin) != 0)
		{
			break;
		}
		if (strcmp(str, "A.")==0 || strcmp(str, ".A")==0) {
			scanf("%lld", &key);
			length += 1;
			if (begit) {
					head = insert_head(head, key, &init);
			}
			else {
				if (strcmp(str, "A.")==0) {
					if (exists(index, head)) {
						if (using_its(begit, endit)) insert_aft(its[index], key);
						else insert_aft(getNode(index, head), key);
					}
					else {
						make(getTail(head), key);
					}
				}
				else {
						if (using_its(begit, endit)) insert_bef(its[index], key, &head);
						else insert_bef(getNode(index, head), key, &head);
				}
			}
		}
		if (str[0] == 'i') {
			scanf("%3s", postab);
			if (postab[0] == 'B')
				pos = 0;
			else if (postab[0] == 'E') {
				if (init == false)
					pos = 0;
				else
					pos = get_end(head);
			}
			else {
				pos = postab[0] - '0';
			}
			its[index] = getNode(pos, head);
			
			
		}
		if (str[0] == '+') {
			move_up(&(its[index]), false);
		}
		if (str[0] == '-') {
			move_down(&(its[index]));
		}
		if (str[0] == 'R') {
			if (using_its(begit, endit)) del_it(&its[index], &head,&init,&length, its);
			else del(getNode(index, head), &head, &init, &length);
		}
		if (str[0] == 'P') {
			if (all) {
				print_all(head, init);
				all = false;
			}
			else
				cout << its[index]->data << endl;
		}
		if (str[0] == 'q') {
			break;
		}
		reset(&begit, &endit);
	}
	deleteList(&head, length);
	return 0;
}