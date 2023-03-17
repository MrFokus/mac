#include <iostream>

using namespace std;

int max_elem=99;
struct Tree
{
	int Data; 
	Tree* LeftBranch;
	Tree* RightBranch;
};
void Add(int aData, Tree*& aBranch)
{
	if (!aBranch)
	{
		aBranch = new Tree;
		aBranch->Data = aData;
		aBranch->LeftBranch = 0;
		aBranch->RightBranch = 0;
		return;
}
else 
	if (aBranch->Data > aData)
	{
		Add(aData, aBranch->LeftBranch);
	}
else
	{
		Add(aData, aBranch->RightBranch);
	}
}
void pr_obh(Tree*& aBranch)
{
	if (NULL == aBranch) return; 
	cout << aBranch->Data << endl; 
	pr_obh(aBranch->LeftBranch); 
	pr_obh(aBranch->RightBranch);
}
int max(Tree*& aBranch)
{
	if (NULL == aBranch) return 0; 
	if (aBranch->Data % 3 == 0 && aBranch->Data==max_elem)
	{
		max_elem-=3;
	}
	max(aBranch->LeftBranch);
	max(aBranch->RightBranch);
	return max_elem;
}
int main()
{
srand(time(0));
setlocale(LC_ALL, "rus");
Tree* Root = 0;
int vel;
int element;
int k;
cout << "Введите кол-во элементов для будущего дерева: ";
cin >> vel;
cout << endl;
cout << endl;
for (int i = 0; i < vel; i++)
{
Add(rand() % 100, Root);
}
cout << "Прямой обход бинарного дерева: " << endl;
pr_obh(Root);
cout << endl;
cout << "максимальное двухзначное число кратное трем, не встречающегося в этом дереве: ";
cout << max(Root) << endl;
return 0;
}