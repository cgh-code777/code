#include"stdafx.h"
#include <iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#define LEN sizeof(struct Addritem)//定义结构体的长度//
#define M 100
using namespace std;

//单条通讯录信息结构体
struct Addritem
{
	//ID
	char ID[15];
	//姓名
	char name[15];
	//年龄
	char age[10];
	//性别
	char sex[10];
	//地址
	char address[30];
	//联系电话
	char tel[15];
};

/***************
函数名：Insert
功能：向通讯录中添加联系人数据
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Insert(Addritem add[], int &count);

/***************
函数名：Delete
功能：向通讯录中删除联系人数据
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Delete(Addritem add[], int &count);

/***************
函数名：Search
功能：查找指定联系人的记录
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Search(Addritem add[], int &count);

/***************
函数名：Modify
功能：修改指定联系人的记录
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Modify(Addritem add[], int &count);

/***************
函数名：Show
功能：显示通讯录所有记录
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Show(Addritem add[], int &count);

/***************
函数名：Empty
功能：清空通讯录记录
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Empty(Addritem add[], int &count);

/***************
函数名：Sort
功能：将联系人姓名按照字母顺序排序
输入参数：Addritem数组add，整型变量count
返回参数：无
***************/
void Sort(Addritem add[], int &count);

/***************
函数名：meun
功能：输出菜单界面
输入参数：无
返回参数：无
***************/
void menu();

/***************
函数名：operate
功能：执行通讯录
输入参数：无
返回参数：无
***************/
void operate();

/***************
函数名：display
功能：显示单条记录
输入参数：Addritem 变量
返回参数：无
****************/
void display(Addritem a);

/***************
函数名：Is_number
功能：判断是否全为数字
输入参数：字符数组s
返回参数：true或false
****************/
bool Is_number(char s[]);

/***************
函数名：check_repeat
功能：判断是否有重复ID
输入参数：Addritem数组add,整型变量n
返回参数：true或false
****************/
bool  check_repeat(Addritem add[], int n);

int main()
{
	operate();
	return 0;
}

//菜单
void menu()
{
	system("cls");
	cout << endl << endl << endl << endl;
	cout << "\t\t----------------------------------------通讯录-----------------------------------------------" << endl;
	cout << "\t\t0. 退出                                                                                                                                 " << endl;;
	cout << "\t\t1. 添加联系人                                                                                                                   " << endl;
	cout << "\t\t2. 删除联系人                                                                                                                  " << endl;
	cout << "\t\t3. 修改联系人                                                                                                                  " << endl;
	cout << "\t\t4. 查找联系人                                                                                                                  " << endl;
	cout << "\t\t5. 排序                                                                                                                                 " << endl;
	cout << "\t\t6. 显示通讯录                                                                                                                  " << endl;
	cout << "\t\t7. 清空通讯录                                                                                                                  " << endl;
	cout << "\t\t---------------------------------------------------------------------------------------------" << endl;
	cout << "输入(0-7):";
}

//运行主界面
void operate()
{
	int n, i, count = 0;
	Addritem  add[M];
	FILE *fp;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		cout << "无法打开！" << endl;
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	fclose(fp);
	menu();
	cin >> n;
	while (n)
	{
		switch (n)
		{
		case 1:Insert(add, count); break;
		case 2:Delete(add, count); break;
		case 3:Modify(add, count); break;
		case 4:Search(add, count); break;
		case 5:Sort(add, count); break;
		case 6:Show(add, count); break;
		case 7:Empty(add, count); break;
		}
		getch();
		menu();
		cin >> n;
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		cout << "无法打开！" << endl;
		return;
	}
	for (i = 0; i< count; i++)
	if (fwrite(&add[i], LEN, 1, fp) != 1)
	{
		printf("保存失败!");
		getch();
	}
	fclose(fp);
	cout << "欢迎下次使用！" << endl;
}

//添加联系人
void Insert(Addritem add[], int& count)
{
	if (count == 0)
	{
		system("cls");
		cout << "通讯录为空！" << endl;
	}
	else
	{
		system("cls");
		Show(add, count);
	}
	cout << "请输入ID号：" << endl;
	cin >> add[count].ID;
	while (check_repeat(add, count + 1))
	{
		cout << "该ID已存在，请重新输入：";
		cin >> add[count].ID;
	}
	cout << "请输入姓名：" << endl;
	cin >> add[count].name;
	cout << "请输入年龄：" << endl;
	cin >> add[count].age;
	while (!(Is_number(add[count].age)))
	{
		cout << "您输入的数据含有非数字的字符，请重新输入只含数字的数据：";
		cin >> add[count].age;
	}
	cout << "请输入性别：" << endl;
	cin >> add[count].sex;
	cout << "请输入地址：" << endl;
	cin >> add[count].address;
	cout << "请输入电话：" << endl;
	cin >> add[count].tel;
	while (!(Is_number(add[count].tel)))
	{
		cout << "您输入的数据含有非数字的字符，请重新输入只含数字的数据：";
		cin >> add[count].tel;
	}
	count++;
	cout << "添加成功！" << endl;
}

//删除联系人
void Delete(Addritem add[], int &count)
{
	int i, j;
	string ch;
	char id[15];
	if (count == 0)
	{
		cout << "记录为空！" << endl;
		return;
	}
	system("cls");
	Show(add, count);
	cout << "请输入要删除联系人的ID：";
	cin >> id;
	for (i = 0; i<count; i++)
	{
		if (strcmp(id, add[i].ID) == 0)
		{
			cout << "该联系人存在，信息如下：" << endl;
			display(add[i]);
			cout << endl;
			cout << "是否删除该联系人？删除请输入y或Y：";
			cin >> ch;
			if (ch == "Y" || ch == "y")
			{
				for (j = i; j<count; j++)
					add[j] = add[j + 1];
				count--;
				cout << "删除成功！" << endl;
			}
			return;
		}
	}
	cout << "查无此人！" << endl;
}

//修改联系人
void Modify(Addritem add[], int &count)
{
	int i;
	char id[15];
	string ch;
	if (count == 0)
	{
		cout << "记录为空！" << endl;
		return;
	}
	system("cls");
	Show(add, count);
	cout << "请输入你说要修改联系人的ID：";
	cin >> id;
	for (i = 0; i<count; i++)
	{
		if (strcmp(id, add[i].ID) == 0)
		{
			cout << "该联系人存在，信息如下：" << endl;
			display(add[i]);
			cout << endl;
			cout << "是否修改该联系人？修改请输入y或Y：";
			cin >> ch;
			if (ch == "Y" || ch == "y")
			{
				cout << "请输入新的ID：" << endl;
				cin >> add[i].ID;
				while (check_repeat(add, count))
				{
					cout << "该ID已存在，请重新输入：";
					cin >> add[i].ID;
				}
				cout << "请输入新的姓名：" << endl;
				cin >> add[i].name;
				cout << "请输入新的年龄：" << endl;
				cin >> add[i].age;
				while (!(Is_number(add[i].age)))
				{
					cout << "您输入的数据含有非数字的字符，请重新输入只含数字的数据：";
					cin >> add[i].age;
				}
				cout << "请输入新的性别：" << endl;
				cin >> add[i].sex;
				cout << "请输入新的地址：" << endl;
				cin >> add[i].address;
				cout << "请输入新的电话：" << endl;
				cin >> add[i].tel;
				while (!(Is_number(add[i].tel)))
				{
					cout << "您输入的数据含有非数字的字符，请重新输入只含数字的数据：";
					cin >> add[i].tel;
				}
				cout << "修改成功！" << endl;
			}
			return;
		}
	}
	cout << "查无此人！" << endl;
}

//清空联系人
void Empty(Addritem add[], int &count)
{
	if (count == 0)
	{
		cout << "通讯录无记录，无需清空！";
		return;
	}
	memset(add, 0, M);
	count = 0;
	cout << "清空完成" << endl;
}

//排序
void Sort(Addritem add[], int &count)
{
	struct Addritem t;
	int i, j;
	if (count == 0)
	{
		cout << "记录为空！" << endl;
		return;
	}
	cout << "原始顺序为：" << endl;
	Show(add, count);
	for (i = 0; i<count - 1; i++)
	for (j = i + 1; j<count; j++)
	if (strcmp(add[i].name, add[j].name)>0)
	{
		t = add[i];
		add[i] = add[j];
		add[j] = t;
	}
	cout << "新的顺序为：" << endl;
	Show(add, count);
}

//显示
void Show(Addritem add[], int &count)
{
	int i;
	if (count == 0)
	{
		cout << "无记录!" << endl;
		return;
	}
	cout << "ID       " << "姓名       " << "年龄       " << "性别       " << "地址       " << "电话" << endl;
	for (i = 0; i < count; i++)
		cout << add[i].ID << "       " << add[i].name << "       " << add[i].age << "       " << add[i].sex << "       " << add[i].address << "       " << add[i].tel << endl;
}

//查找
void Search(Addritem add[], int &count)
{
	int i;
	char id[15];
	if (count == 0)
	{
		cout << "无记录！" << endl;
		return;
	}
	system("cls");
	cout << "请输入要查找的联系人ID：";
	cin >> id;
	for (i = 0; i<count; i++)
	{
		if (strcmp(id, add[i].ID) == 0)
		{
			cout << "ID   " << "姓名   " << "年龄" << "   性别" << "   地址" << "   电话" << endl;
			cout << add[i].ID << "       " << add[i].name << "       " << add[i].age << "       " << add[i].sex << "       " << add[i].address << "       " << add[i].tel << endl;
			return;
		}
	}
	cout << "查无此人！" << endl;
}

//显示单条通讯录数据
void display(Addritem a)
{
	cout << "ID       " << "姓名       " << "年龄       " << "性别       " << "地址       " << "电话" << endl;
	cout << a.ID << "       " << a.name << "       " << a.age << "       " << a.sex << "       " << a.address << "       " << a.tel << endl;
}

//判断是否全为数字
bool Is_number(char s[])
{
	for (int i = 0; i<strlen(s); i++)
	{
		if (s[i] > '9' || s[i] < '0')
		{
			return false;
		}
	}
	return true;
}

//检查是否有重复ID
bool  check_repeat(Addritem add[], int n)
{
	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (strcmp(add[i].ID, add[j].ID) == 0)
				return true;
		}
	}
	return false;
}
