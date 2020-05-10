#include "stdafx.h"
#include <iostream>
#include<conio.h>
#include<string>
#define LEN sizeof(struct Addritem)//����ṹ��ĳ���//
using namespace std;

//����ͨѶ¼��Ϣ�ṹ��
struct Addritem
{
	//����
	char name[15];
	//����
	char age[10];
	//�Ա�
	char sex[10];
	//��ַ
	char address[30];
	//��ϵ�绰
	char tel[15];
};

Addritem *add=new Addritem[100];

/***************
��������Insert
���ܣ���ͨѶ¼�������ϵ������
�����������
���ز�������
***************/
void Insert();

/***************
��������Delete
���ܣ���ͨѶ¼��ɾ����ϵ������
�����������
���ز�������
***************/
void Delete();

/***************
��������Search
���ܣ�����ָ����ϵ�˵ļ�¼
�����������
���ز�������
***************/
void Search();

/***************
��������Modify
���ܣ��޸�ָ����ϵ�˵ļ�¼
�����������
���ز�������
***************/
void Modify();

/***************
��������Show
���ܣ���ʾͨѶ¼���м�¼
�����������
���ز�������
***************/
void Show();

/***************
��������Empty
���ܣ����ͨѶ¼��¼
�����������
���ز�������
***************/
void Empty();

/***************
��������Sort
���ܣ�����ϵ������������ĸ˳������
�����������
���ز�������
***************/
void Sort();

/***************
��������meun
���ܣ�����˵�����
�����������
���ز�������
***************/
void menu();

/***************
��������operate
���ܣ�ִ��ͨѶ¼
�����������
���ز�������
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
	cout << "\t\t----------------------------------------ͨѶ¼-----------------------------------------------" << endl;
	cout << "\t\t0. �˳�                                                                                                                                 " << endl;;
	cout << "\t\t1. �����ϵ��                                                                                                                   " << endl;
	cout << "\t\t2. ɾ����ϵ��                                                                                                                  " << endl;
	cout << "\t\t3. �޸���ϵ��                                                                                                                  " << endl;
	cout << "\t\t4. ������ϵ��                                                                                                                  " << endl;
	cout << "\t\t5. ����                                                                                                                                 " << endl;
	cout << "\t\t6. ��ʾͨѶ¼                                                                                                                  " << endl;
	cout << "\t\t7. ���ͨѶ¼                                                                                                                  " << endl;
	cout << "\t\t---------------------------------------------------------------------------------------------" << endl;
	cout << "����(0-7):";
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
	cout << "��ӭ�´�ʹ�ã�" << endl;
}

void Insert()
{
	int i, count = 0;
	FILE *fp;
	if ((fp = fopen("data.txt", "a+")) == NULL)
	{
		cout << "�޷��򿪣�" << endl;
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
		cout << "ͨѶ¼Ϊ�գ�" << endl;
	}
	else
	{
		system("cls");
		Show();
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		cout << "�޷���ͨѶ¼��" << endl;
		return;
	}
	for (i = 0; i<count; i++)
		fwrite(&add[i], LEN, 1, fp);
	cout << "������������" << endl;
	cin >> add[count].name;
	cout << "���������䣺" << endl;
	cin >> add[count].age;
	cout << "�������Ա�" << endl;
	cin >> add[count].sex;
	cout << "�������ַ��" << endl;
	cin >> add[count].address;
	cout << "������绰��" << endl;
	cin >> add[count].tel;
	if (fwrite(&add[count], LEN, 1, fp) != 1)
	{
		cout << "���ʧ�ܣ�" << endl;
		getch();
	}
	else
	{
		count++;
		cout << "��ӳɹ���" << endl;
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
		cout << "�޷��򿪣�" << endl;
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	fclose(fp);
	if (count == 0)
	{
		cout << "��¼Ϊ�գ�" << endl;
		return;
	}
	Show();
	cout << "������Ҫɾ����ϵ�˵�������";
	cin >> name;
	for (i = 0; i<count; i++)
	{
		if (strcmp(name, add[i].name) == 0)
		{
			cout << "����ϵ�˴��ڣ��Ƿ�ɾ����(y/n)";
			cin >> ch;
			if (ch == "Y" || ch == "y")
			{
				for (j = i; j<count; j++)
					add[j] = add[j + 1];
				count--;
				if ((fp = fopen("data.txt", "wb")) == NULL)
				{
					cout << "�޷��򿪣�" << endl;
					return;
				}
				for (j = 0; j<count; j++)
				if (fwrite(&add[j], LEN, 1, fp) != 1)
				{
					cout << "�޷����棡" << endl;
					getch();
				}
				fclose(fp);
				cout << "ɾ���ɹ���" << endl;
			}
			return;
		}
	}
	cout << "���޴��ˣ�" << endl;
}

void Modify()
{
	FILE *fp;
	int i, j, count = 0;
	char name[15];
	string ch;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		cout << "�޷��򿪣�";
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	if (count == 0)
	{
		cout << "��¼Ϊ�գ�" << endl;
		fclose(fp);
		return;
	}
	Show();
	cout << "��������˵Ҫ�޸���ϵ�˵�������";
	cin >> name;
	for (i = 0; i<count; i++)
	{
		if (strcmp(name, add[i].name) == 0)
		{
			cout << "����ϵ�˴��ڣ��Ƿ��޸ģ�(y/n)";
			cin >> ch;
			if (ch == "Y" || ch == "y")
			{
				cout << "�������µ�������" << endl;
				cin >> add[i].name;
				cout << "�������µ����䣺" << endl;
				cin >> add[i].age;
				cout << "�������µ��Ա�" << endl;
				cin >> add[i].sex;
				cout << "�������µĵ�ַ��" << endl;
				cin >> add[i].address;
				cout << "�������µĵ绰��" << endl;
				cin >> add[i].tel;
				cout << "�޸ĳɹ���" << endl;
				if ((fp = fopen("data.txt", "wb")) == NULL)
				{
					cout << "�޷��򿪣�" << endl;
					return;
				}
				for (j = 0; j < count; j++)
				if (fwrite(&add[j], LEN, 1, fp) != 1)
				{
					printf("����ʧ��!");
					getch();
				}
				fclose(fp);
			}
			return;
		}
	}
	cout << "���޴��ˣ�" << endl;
}

void Empty()
{
	FILE *fp;
	fp = fopen("data.txt", "w");
	if (fp== NULL)
	{
		cout << "�޷��򿪣�";
		return;
	}
	else
	{
		fclose(fp);
		cout << "�����ɣ�" << endl;
	}
}
void Sort()
{
	FILE *fp;
	struct Addritem t;
	int i, j, count = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		cout << "�޷��򿪣�";
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	if (count == 0)
	{
		cout << "��¼Ϊ�գ�" << endl;
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
		cout << "�޷��򿪣�" << endl;
		return;
	}
	for (j = 0; j < count; j++)
	if (fwrite(&add[j], LEN, 1, fp) != 1)
	{
		printf("����ʧ��!");
		getch();
	}
	fclose(fp);
	cout << "����ɹ���" << endl;
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
	fclose(fp);//�ر��ļ�//
	if (count == 0)
	{
		cout << "�޼�¼!" << endl;
		return;
	}
	cout << "����   " << "����" << "   �Ա�" << "   ��ַ" << "   �绰" << endl;
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
		cout << "�޷���ͨѶ¼��" << endl;
		return;
	}
	while (!feof(fp))
	if (fread(&add[count], LEN, 1, fp) == 1)
		count++;
	if (count == 0)
	{
		cout << "�޼�¼��" << endl;
		return;
	}
	cout << "������Ҫ���ҵ���ϵ��������";
	cin >> name;
	for (i = 0; i<count; i++)
	{
		if (strcmp(name, add[i].name) == 0)
		{
			cout << "����   " << "����" << "   �Ա�" << "   ��ַ" << "   �绰" << endl;
			cout << add[i].name << "       " << add[i].age << "       " << add[i].sex << "       " << add[i].address << "       " << add[i].tel << endl;
			break;
		}
		if (i == count)
			cout << "�Ҳ�������ϵ�ˣ�" << endl;
	}
}
