#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include<string>
#define LEN sizeof(struct Addritem)//定义结构体的长度//
using namespace std;

//单条通讯录信息结构体
struct Addritem
{
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

Addritem *add=new Addritem[100];

/***************
函数名：Insert
功能：向通讯录中添加联系人数据
输入参数：无
返回参数：无
***************/
void Insert();

/***************
函数名：Delete
功能：向通讯录中删除联系人数据
输入参数：无
返回参数：无
***************/
void Delete();

/***************
函数名：Search
功能：查找指定联系人的记录
输入参数：无
返回参数：无
***************/
void Search();

/***************
函数名：Modify
功能：修改指定联系人的记录
输入参数：无
返回参数：无
***************/
void Modify();

/***************
函数名：Show
功能：显示通讯录所有记录
输入参数：无
返回参数：无
***************/
void Show();

/***************
函数名：Empty
功能：清空通讯录记录
输入参数：无
返回参数：无
***************/
void Empty();

/***************
函数名：Sort
功能：将联系人姓名按照字母顺序排序
输入参数：无
返回参数：无
***************/
void Sort();

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

int main()
{
	operate();
	return 0;
}

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

void operate()
{
	int n;
	menu();
	cin >> n;
	while (n)
	{
		switch (n)
		{
		case 1:Insert(); break;
		case 2:Delete(); break;
		case 3:Modify(); break;
		case 4:Search(); break;
		case 5:Sort(); break;
		case 6:Show(); break;
		case 7:Empty(); break;
		}
		getch();
		menu();
		cin >> n;
	}
	cout << "欢迎下次使用！" << endl;
}

void Insert()
{
	int i, count = 0;
	FILE *fp;
	if ((fp = fopen("data.txt", "a+")) == NULL)
	{
		cout << "无法打开！" << endl;
		return;
	}
	while (!feof(fp))
	{
		if (fread(&add[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);
	if (count == 0)
	{
		system("cls");
		cout << "通讯录为空！" << endl;
	}
	else
	{
		system("cls");
		Show();
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		cout << "无法打开通讯录！" << endl;
		return;
	}
	for (i = 0; i<count; i++)
		fwrite(&add[i], LEN, 1, fp);
	cout << "请输入姓名：" << endl;
	cin >> add[count].name;
	cout << "请输入年龄：" << endl;
	cin >> add[count].age;
	cout << "请输入性别：" << endl;
	cin >> add[count].sex;
	cout << "请输入地址：" << endl;
	cin >> add[count].address;
	cout << "请输入电话：" << endl;
	cin >> add[count].tel;
	if (fwrite(&add[count], LEN, 1, fp) != 1)
	{
		cout << "添加失败！" << endl;
		getch();
	}
	else
	{
		count++;
		cout << "添加成功！" << endl;
	}
	fclose(fp);
}

void Delete()
{
	FILE *fp;
	int i, j, count = 0;
	string ch;
	char name[15];
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		cout << "无法打开！" << endl;
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	fclose(fp);
	if (count == 0)
	{
		cout << "记录为空！" << endl;
		return;
	}
	Show();
	cout << "请输入要删除联系人的姓名：";
	cin >> name;
	for (i = 0; i<count; i++)
	{
		if (strcmp(name, add[i].name) == 0)
		{
			cout << "该联系人存在，是否删除？(y/n)";
			cin >> ch;
			if (ch == "Y" || ch == "y")
			{
				for (j = i; j<count; j++)
					add[j] = add[j + 1];
				count--;
				if ((fp = fopen("data.txt", "wb")) == NULL)
				{
					cout << "无法打开！" << endl;
					return;
				}
				for (j = 0; j<count; j++)
				if (fwrite(&add[j], LEN, 1, fp) != 1)
				{
					cout << "无法保存！" << endl;
					getch();
				}
				fclose(fp);
				cout << "删除成功！" << endl;
			}
			return;
		}
	}
	cout << "查无此人！" << endl;
}

void Modify()
{
	FILE *fp;
	int i, j, count = 0;
	char name[15];
	string ch;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		cout << "无法打开！";
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	if (count == 0)
	{
		cout << "记录为空！" << endl;
		fclose(fp);
		return;
	}
	Show();
	cout << "请输入你说要修改联系人的姓名：";
	cin >> name;
	for (i = 0; i<count; i++)
	{
		if (strcmp(name, add[i].name) == 0)
		{
			cout << "该联系人存在，是否修改？(y/n)";
			cin >> ch;
			if (ch == "Y" || ch == "y")
			{
				cout << "请输入新的姓名：" << endl;
				cin >> add[i].name;
				cout << "请输入新的年龄：" << endl;
				cin >> add[i].age;
				cout << "请输入新的性别：" << endl;
				cin >> add[i].sex;
				cout << "请输入新的地址：" << endl;
				cin >> add[i].address;
				cout << "请输入新的电话：" << endl;
				cin >> add[i].tel;
				cout << "修改成功！" << endl;
				if ((fp = fopen("data.txt", "wb")) == NULL)
				{
					cout << "无法打开！" << endl;
					return;
				}
				for (j = 0; j < count; j++)
				if (fwrite(&add[j], LEN, 1, fp) != 1)
				{
					printf("保存失败!");
					getch();
				}
				fclose(fp);
			}
			return;
		}
	}
	cout << "查无此人！" << endl;
}

void Empty()
{
	FILE *fp;
	fp = fopen("data.txt", "w");
	if (fp== NULL)
	{
		cout << "无法打开！";
		return;
	}
	else
	{
		fclose(fp);
		cout << "清空完成！" << endl;
	}
}
void Sort()
{
	FILE *fp;
	struct Addritem t;
	int i, j, count = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		cout << "无法打开！";
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	if (count == 0)
	{
		cout << "记录为空！" << endl;
		fclose(fp);
		return;
	}
	for (i = 0; i<count - 1; i++)
	for (j = i + 1; j<count; j++)
	if (strcmp(add[i].name, add[j].name)>0)
	{
		t = add[i];
		add[i] = add[j];
		add[j] = t;
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		cout << "无法打开！" << endl;
		return;
	}
	for (j = 0; j < count; j++)
	if (fwrite(&add[j], LEN, 1, fp) != 1)
	{
		printf("保存失败!");
		getch();
	}
	fclose(fp);
	cout << "保存成功！" << endl;
}

void Show()
{
	FILE* fp;
	int i, count = 0;
	fp = fopen("data.txt", "rb");
	while (!feof(fp))
	{
		if (fread(&add[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);//关闭文件//
	if (count == 0)
	{
		cout << "无记录!" << endl;
		return;
	}
	cout << "姓名   " << "年龄" << "   性别" << "   地址" << "   电话" << endl;
	for (i = 0; i < count; i++)
		cout << add[i].name << "       " << add[i].age << "       " << add[i].sex << "       " << add[i].address << "       " << add[i].tel << endl;
}

void Search()
{
	FILE *fp;
	int i, count = 0;
	char name[15];
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		cout << "无法打开通讯录！" << endl;
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	if (count == 0)
	{
		cout << "无记录！" << endl;
		return;
	}
	cout << "请输入要查找的联系人姓名：";
	cin >> name;
	for (i = 0; i<count; i++)
	{
		if (strcmp(name, add[i].name) == 0)
		{
			cout << "姓名   " << "年龄" << "   性别" << "   地址" << "   电话" << endl;
			cout << add[i].name << "       " << add[i].age << "       " << add[i].sex << "       " << add[i].address << "       " << add[i].tel << endl;
			break;
		}
		if (i == count)
			cout << "找不到该联系人！" << endl;
	}
}
