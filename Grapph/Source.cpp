#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

typedef struct Tree_s
{
	int data; // значение элемента
	int left_count; // счётсчик левых потомков (детей)
	int right_count; // счётчик правых потомков (детей)
	struct Tree_s* parent; // указатель на предка (родителя)
	struct Tree_s* left; // указатель на левого потомка
	struct Tree_s* right; // указатель на правого потомка
}Tree;
Tree* newNode(int data, Tree* par)     // функция создания нового элемента
{
	Tree* Node = (Tree*)malloc(sizeof(Tree));
	if (Node == NULL)
	{
		printf("malloc returned NULL");
		exit(1);
	}
	Node->data = data;
	Node->left = NULL;
	Node->right = NULL;
	Node->parent = par;
	Node->left_count = 0;
	Node->right_count = 0;
return Node;

}
void right_balance(Tree**);  // это предварительные объявления, строчки 31-33
void left_balance(Tree**);  
void proverka(Tree**);  

void push(Tree** tree, int value) // функция, которая вставляет число в дерево
{
	int left = 0;
	int right = 0;
	Tree* temp = *tree;
	//proverka(tree);
	if (temp == NULL)
	{
		*tree = newNode(value, NULL);
	}
	else if (value < temp->data)
	{
		(temp->left_count) += 1;
		if (temp->left == NULL)
		{
			temp->left = newNode(value, temp);
		}
		else
		{
			push(&(temp->left), value);
		}
	}
	else if (value > temp->data)
	{
		(temp->right_count) += 1;
		if (temp->right == NULL)
		{
			temp->right = newNode(value, temp);
		}
		else
		{
			push(&(temp->right), value);
		}
	}
	proverka(&(*tree));
	proverka(&((*tree)->right));
	proverka(&((*tree)->left));
	
	

}
void Show(Tree* treeNode)   // функция, которая выводит дерево
{
	if (treeNode == NULL)
	{
		return;
	}
	printf("%d\n", treeNode->data);
	if (treeNode->left != NULL)
	{
		Show(treeNode->left);
	}
	if (treeNode->right != NULL)
	{
		Show(treeNode->right);

	}
}
void Sorted(Tree* tree)  // функция, которая выводит дерево, сортируя значения
{
	if ((tree->left) != NULL)
	{
		Sorted(tree->left);
	}
	printf("%d ", tree->data);
	if ((tree->right != NULL))
	{
		Sorted(tree->right);
	}
}


void read(Tree** tr)  // функция чтения чисел из файла
{
	FILE* doc = NULL;
	doc = fopen("2.txt", "r");
	int simbol = 0;
	while (!feof(doc))
	{
		fscanf(doc, "%d", &simbol);
		push(tr, simbol);
	}

}
Tree** left_return(Tree** element) // функция, которая возвращает указатель на первый элемент дерева, у которого нет левых потомков; используется для right_balance
{
	if ((*element)->parent->right != (*element))
	{

		(*element)->parent->left_count -= 1;
	}
	else
	{
		(*element)->parent->right_count -= 1;
	}
	if ((*element)->left == NULL)
	{
		return(element);
	}
	else
	{
		return left_return(&((*element)->left));
	}

}
 void right_balance(Tree** element)  // функция, которая балансирует дерево, если элементов в правой стороне больше, чем в левой
{
	Tree* example = *element;
	(*element) = *(left_return(&((*element)->right)));
	if ((*element)->parent != example)
	{
		(*element)->parent->left = (*element)->right;
		if (((*element)->parent->left) != NULL)
		{
			(*element)->parent->left->parent = (*element)->parent;
		}

	}
	(*element)->parent = example->parent;
	if (example->right != (*element))
	{
		(*element)->right = example->right;
		example->right->parent = (*element);
	}
	(*element)->left = example->left;
	if ((*element)->left != NULL)
	{
		(*element)->left->parent = (*element);
	}
	(*element)->right_count = example->right_count;
	(*element)->left_count = example->left_count;
	push(element, example->data);
 }

 Tree** right_return(Tree** element)  // функция, которая возвращает указатель на первый элемент, у которого справа нет потомков
 {
	 if ((*element)->parent->left != (*element))
	 {

		 (*element)->parent->right_count -= 1;
	 }
	 else
	 {
		 (*element)->parent->left_count -= 1;
	 }
	 if ((*element)->right == NULL)
	 {
		 return(element);
	 }
	 else
	 {
		 return right_return(&((*element)->right));
	 }
 }

 void left_balance(Tree** element) // функция, которая балансирует дерево, если слева элементов больше, чем справа
 {
	 Tree* example = *element;
	 (*element) = *(right_return(&((*element)->left)));
	 if ((*element)->parent != example)
	 {
		 (*element)->parent->right = (*element)->left;
		 if (((*element)->parent->left) != NULL)
		 {
		 (*element)->parent->left->parent = (*element)->parent;    /////////////////////////////////просмотреть это и для другой ветки
		 }

	 }
	 (*element)->parent = example->parent;
	 if (example->left != (*element))
	 {
		 (*element)->left = example->left;
		 example->left->parent = (*element);
	 }
	 (*element)->right = example->right;
	 if ((*element)->right != NULL)
	 {
		 (*element)->right->parent = (*element);
	 }
	 (*element)->right_count = example->right_count;
	 (*element)->left_count = example->left_count;
	 push(element, example->data);
 }

 void proverka(Tree** element) // функция сравнения кол-ва элементов справа и слева, если находит, что где-то больше чем на 1 элемент, то вызывает функции балансировки
 {
	 if ((*element) != NULL)
	 {
		 if ((((*element)->left_count) - ((*element)->right_count)) > 1)
		 {
			 left_balance(element);
		 }
		 else  if ((((*element)->left_count) - ((*element)->right_count)) < -1)
		 {
			 right_balance(element);
		 }
	 }
 }


 
 int main()
 {
	 system("chcp 1251");
	 system("cls");
	 Tree* X = NULL;

	 read(&X);
	 //right_balance(&X);
	 //printf("%d", (*left_return(&(X->right)))->data);
	 
	 Show(X);
	 Sorted(X);
	 
	 //Sorted(X)
	// printf("%d\n", (*right_return(&(X->left)))->data);
	 //printf("%d\n", X->data);
	 //printf("%d", X->left->right->left_count);

 }





