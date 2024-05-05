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

//职员信息
typedef struct Employee {
	char name[NAME_MAXSIZE];  //姓名
	char ID[ID_MAXSIZE];      //工号
	int age;		          //年龄
	char sex[SEX_MAXSIZE];	  //性别
	char tel[TEL_MAXSIZE];	  //电话
	int salary;				  //薪资
	char officialName[OFFICIALNAME_MAXSIZE];  //职务
}Employee;


//动态信息表
typedef struct PIM {
	Employee* emp;  //存放职员数组
	int size;       //长度
	int capacity;   //容量
}PIM;



//声明函数
//初始信息表
void Init_PIM(PIM * pm);

//添加信息
void Add_PIM(PIM * pm);

//打印信息
void Show_PIM(const PIM * pm);

//删除信息
void Del_PIM(PIM * pm);

//查找指定人信息
void Search_PIM(const PIM* pm);

//修改指定人信息
void Modify_PIM(PIM * pm);

//排序信息表内容
void Sort_PIM(PIM * pm);

//清空信息表
void Clear_PIM(PIM * pm);

//释放内存
void Destroy_PIM(PIM* pm);

//保存文件
void Save_PIM(PIM * pm);

//加载文件信息到信息表
void Load_PIM(PIM * pm);


//封装函数
//增容
static void CheckCapacity(PIM* pm);
//姓名查找
static int FinidByName(const PIM* pm,char* str);
//ID查找
static int FindByID(const PIM* pm,char* ID);
//按ID排序
static int compare_emp_ID(void* p1, void* p2);
//按姓名排序
static int compare_emp_name(void* p1, void* p2);
//按薪水排序
static int compare_emp_salary(void* p1, void* p2);
