#include <cstdio>
#include <queue>
using namespace std;
struct node
{
	node(int v):val(v){}
	node *left = nullptr;
	node *right = nullptr;
	node *parent = nullptr;
	//false:black
	//true:red
	bool color = true;
	int val = -1; 
};
class rbTree
{
	public:	
	node *root(){return head;};
	void insert(int);
	void balance(node *);
	void display();
	node *left_rotate(node *p);
	node *right_rotate(node *p);
	
	private:
	node *head = nullptr;
};

void rbTree::insert(int val)
{
	if (head == nullptr)
	{
		head = new node(val);
		head->color = false;
	}
	else
	{
		node *tmp = head;
		node *parent;
		while (tmp != nullptr)
		{
			//printf("dsad");
			parent = tmp;
			if (val > tmp->val)
				tmp = tmp->right;
			else if (val < tmp->val)
				tmp = tmp->left;
			else
				;
				//
				//...
				//
		}
		node *ptr;
		if (val > parent->val)
		{
			ptr = new node(val);
			//default red;
			parent->right = ptr;
			ptr->parent = parent;
		}
		else if (val < parent->val)
		{
			ptr = new node(val);
			//default red;
			parent->left = ptr;
			ptr->parent = parent;
		}
		else
			;
		//
		//...
		//
		if (ptr->parent->color == true)
		{
			balance(ptr);
		}
		//return ptr;
	}
};


node *rbTree::left_rotate(node *p)
{
	if (head == p)
	{
		//坑: 如果p为head, 那么p->parent为null,如果不特殊处理会core dump, 而sgi stl的处理方法是使用header,p->parent = header
		node *x = p->right;
		p->right = x->left;
		//坑: 注意此处x->left(x的整颗左子树)可能为null
		if (x->left)
			x->left->parent = p;
		p->parent = x;
		x->left = p;
		head = x;
	}
	else
	{
		node *g = p->parent;
		node *x = p->right;
		p->right = x->left;
		if (x->left)
			x->left->parent = p;
		p->parent = x;
		x->left = p;
		if (p == g->left)
			g->left = x;
		else
			g->right = x;
		x->parent = g;
	}
	return p;
}


node *rbTree::right_rotate(node *p)
{
	if (head == p)
	{
		node *x = p->left;
		p->left = x->right;
		if (x->right)
			x->right->parent = p;
		p->parent = x;
		x->right = p;
		head = x;
	}
	else
	{
		node *g = p->parent;
		node *x = p->left;
		p->left = x->right;
		if (x->right)
			x->right->parent = p;
		p->parent = x;
		x->right = p;
		if (p == g->left)
			g->left = x;
		else
			g->right = x;
		x->parent = g;
	}
	return p;
}


//坑: 需传二级指针才能改变原指针指向
node *left_rotate(node **head, node *p)
{
	if (*head == p)
	{
		//坑: 如果p为head, 那么p->parent为null,如果不特殊处理会core dump, 而sgi stl的处理方法是使用header,p->parent = header
		node *x = p->right;
		p->right = x->left;
		//坑: 注意此处x->left(x的整颗左子树)可能为null
		if (x->left)
			x->left->parent = p;
		p->parent = x;
		x->left = p;
		*head = x;
	}
	else
	{
	node *g = p->parent;
	node *x = p->right;
	p->right = x->left;
	if (x->left)
		x->left->parent = p;
	p->parent = x;
	x->left = p;
	if (p == g->left)
		g->left = x;
	else
		g->right = x;
	x->parent = g;
	}
	return p;
}

//坑: 需传二级指针才能改变原指针指向
node *right_rotate(node **head, node *p)
{
	if (*head == p)
	{
		node *x = p->left;
		p->left = x->right;
		if (x->right)
			x->right->parent = p;
		p->parent = x;
		x->right = p;
		*head = x;
	}
	else
	{
	node *g = p->parent;
	node *x = p->left;
	p->left = x->right;
	if (x->right)
		x->right->parent = p;
	p->parent = x;
	x->right = p;
	if (p == g->left)
		g->left = x;
	else
		g->right = x;
	x->parent = g;
	}
	return p;
}

void rbTree::balance(node *x)
{
	node *p;
	node *g;
	node *s;
	while (x != head && x->color == true && x->parent->color == true)
	{
		p = x->parent;
		g = p->parent;
		if (p == g->left)
			s = g->right;
		else
			s = g->left;
		if (s && s->color == true)
		{
			s->color = false;
			p->color = false;
			g->color = true;
			x = g;
		}
		else//s->color == black || s == nullptr
		{
			if (s == g->right)
			{
				if (x == p->right)
					x = left_rotate(x->parent);
				//左旋右旋都需要修正x位置
				x->parent->color = false;
				x->parent->parent->color = true;
				x = right_rotate(x->parent->parent);
			}
			else
			{
				if (x == p->left)
					x = right_rotate(x->parent);
				x->parent->color = false;
				x->parent->parent->color = true;
				
				x = left_rotate(x->parent->parent);
			}
			x = x->parent;
		}
	}
	head->color = false;
}

void rbTree::display()
{
	queue<node *> q;
	q.push(head);
	while (!q.empty())
	{
		node * tmp = q.front();
		printf("value: %d\n", tmp->val);
		printf("color: %s\n", tmp->color?"red":"black");
		printf("parent val: %d\n", tmp->parent->val);
		printf("==============+\n");
		q.pop();
		if (tmp->left)
			q.push(tmp->left);
		if (tmp->right)
			q.push(tmp->right);
	}
}
int main(void)
{
	rbTree t;
	t.insert(10);
	t.insert(5);
	t.insert(6);
	t.insert(8);
	t.insert(9);
	t.insert(1);
	t.insert(2);
	t.insert(3);
	t.insert(20);
	t.insert(16);
	t.insert(13);
	t.insert(12);
	t.insert(11);
	t.insert(4);
	t.insert(7);
	t.display();
}
