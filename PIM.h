#pragma once
#define ID_MAXSIZE 10
#define NAME_MAXSIZE 20
#define TEL_MAXSIZE 15
#define OFFICIALNAME_MAXSIZE 10
#define SEX_MAXSIZE 5

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

enum option
{
	EXIT,  //0
	ADD,   //1
	DEL,   //2
	SHOW,
	SEARCH,
	MOD,
	SORT,
	CLEAR,
	SAVE,
	SHOW_TEAM,
};

//ְԱ��Ϣ
typedef struct Employee {
	char name[NAME_MAXSIZE];  //����
	char ID[ID_MAXSIZE];      //����
	int age;		          //����
	char sex[SEX_MAXSIZE];	  //�Ա�
	char tel[TEL_MAXSIZE];	  //�绰
	int salary;				  //н��
	char officialName[OFFICIALNAME_MAXSIZE];  //ְ��
}Employee;


//��̬��Ϣ��
typedef struct PIM {
	Employee* emp;  //���ְԱ����
	int size;       //����
	int capacity;   //����
}PIM;



//��������
//��ʼ��Ϣ��
void Init_PIM(PIM * pm);

//�����Ϣ
void Add_PIM(PIM * pm);

//��ӡ��Ϣ
void Show_PIM(const PIM * pm);

//ɾ����Ϣ
void Del_PIM(PIM * pm);

//����ָ������Ϣ
void Search_PIM(const PIM* pm);

//�޸�ָ������Ϣ
void Modify_PIM(PIM * pm);

//������Ϣ������
void Sort_PIM(PIM * pm);

//�����Ϣ��
void Clear_PIM(PIM * pm);

//�ͷ��ڴ�
void Destroy_PIM(PIM* pm);

//�����ļ�
void Save_PIM(PIM * pm);

//�����ļ���Ϣ����Ϣ��
void Load_PIM(PIM * pm);


//��װ����
//����
static void CheckCapacity(PIM* pm);
//��������
static int FinidByName(const PIM* pm,char* str);
//ID����
static int FindByID(const PIM* pm,char* ID);
//��ID����
static int compare_emp_ID(void* p1, void* p2);
//����������
static int compare_emp_name(void* p1, void* p2);
//��нˮ����
static int compare_emp_salary(void* p1, void* p2);
