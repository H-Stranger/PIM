#define _CRT_SECURE_NO_WARNINGS

#include"PIM.h"

//初始信息表
void Init_PIM(PIM* pm)
{
	pm->size = 0;
	pm->capacity = 4;
	pm->emp = (Employee*)malloc(4 * sizeof(Employee));
	if (pm->emp == NULL)
		return;
	Load_PIM(pm);
}


//增容
static void CheckCapacity(PIM* pm)
{
	if (pm->size == pm->capacity)
	{
		//realloc扩容
		PIM* tmp = realloc(pm->emp,sizeof(Employee) * (pm->capacity+2));//一次扩两个空间
		if (tmp == NULL)
		{
			printf("扩容失败\n");
			exit(0);
		}
		pm->emp = tmp;
		pm->capacity += 2;
	}
}


//加载文件信息到信息表
void Load_PIM(PIM* pm)
{
	FILE* pf = fopen("emp.txt", "r");
	if (pf == NULL)
	{
		printf("Load_PIM : %s\n", strerror(errno));
		//errno 获取错误码，将出错具体原因通过strerror函数呈现
		//读入文件时，如果不存在文件，提示作用
		return;
	}
	int num = 0;
	fscanf(pf, "%d\n", &num);
	int i;
	for (i = 0; i < num; i++)
	{
		CheckCapacity(pm);
		fscanf(pf, "%s %s %d %s %s %d %s ",
			pm->emp[i].name,
			pm->emp[i].ID,
			&pm->emp[i].age,
			pm->emp[i].sex,
			pm->emp[i].tel,
			&pm->emp[i].salary,
			pm->emp[i].officialName);
	}
	pm->size = num;
	printf("文件读入成功\n");

	fclose(pf);
	pf = NULL;
}

//添加信息
void Add_PIM(PIM* pm)
{
	printf("请输入要添加的人事信息个数:>\n");
	int num = 0;
	scanf("%d", &num);
	int count = 1;
	system("cls");		//清屏
	while (num)
	{
		//检查空间是否 足够
		CheckCapacity(pm);

		printf("请添加第%d员工相关信息\n", count);
		count++;
		printf("请输入员工姓名:>\n");
		scanf("%s", pm->emp[pm->size].name);
		printf("请输入员工工号:>\n");
		scanf("%s", pm->emp[pm->size].ID);
		printf("请输入员工年龄:>\n");
		scanf("%d", &pm->emp[pm->size].age);
		printf("请输入员工性别:>\n");
		scanf("%s", pm->emp[pm->size].sex);
		printf("请输入员工电话:>\n");
		scanf("%s", pm->emp[pm->size].tel);
		printf("请输入员工薪水:>\n");
		scanf("%d", &pm->emp[pm->size].salary);
		printf("请输入员工职务:>\n");
		scanf("%s", pm->emp[pm->size].officialName);

		pm->size++;
		num--;
		//实现清屏效果，避免冗余
		system("cls");
	}
}

//打印信息
void Show_PIM(const PIM* pm)
{
	if (pm->size == 0)
		printf("人事管理系统暂无信息，请进行添加 > \n");
	else
	{
		//标题
		int i = 0;
		printf("查询成功\n");
		printf("%-20s\t%-10s\t%-5s\t%-4s\t%-15s\t%-8s\t%-8s\n", "姓名", "工号", "年龄", "性别", "电话", "薪资", "职务");
		//数据
		//格式化输出
		for (i = 0; i < pm->size; i++)
		{
			printf("%-20s\t%-10s\t%-5d\t%-4s\t%-15s\t%-8d\t%-8s\n",
				pm->emp[i].name,
				pm->emp[i].ID,
				pm->emp[i].age,
				pm->emp[i].sex,
				pm->emp[i].tel,
				pm->emp[i].salary,
				pm->emp[i].officialName);
		}
	}
}
static int FinidByName(const PIM* pm, char* name)
{
	int i = 0;
	for (int i = 0; i < pm->size; i++) 
	{
		if (0 == strcmp(pm->emp[i].name, name))
			return i;
	}

	return -1;//找不到
}

static int compare_emp_ID(void* p1, void* p2)
{
	return atoi(((Employee*)p1)->ID) - atoi(((Employee*)p2)->ID);
	//先将p1强制类型转换为 Employee类型指针 ，指向ID后，再由字符串转换为整型（atoi函数），比较大小
}

static int FindByID(PIM* pm, char* ID)
{
	//首先要将信息表排序(按照工号排序)
	qsort(pm->emp, pm->size, sizeof(Employee), compare_emp_ID);

	int left = 0;
	int right = pm->size - 1;
	//等号 ： 假如只有一个信息的时候
	while (left <= right)
	{
		int mid = left + ((right - left) >> 1); // 类似left + (right - left)/2
		//目标值小于中间值，左区间搜
		if (atoi(pm->emp[mid].ID) > atoi(ID))
			right = mid  - 1;
		else if (atoi(pm->emp[mid].ID) < atoi(ID))
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}


//删除信息
void Del_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("人事管理系统暂无信息，请进行添加 > \n");
		return;
	}
	int choice = 0;
	printf("请输入要选择的删除方式:> 1.工号删除(自动排序)    2.姓名删除\n");
	scanf("%d", &choice);
	//获取索引 操作
	int res;
	if (choice == 1)
	{
		char ID[ID_MAXSIZE];
		printf("请输入要删除的员工工号\n");
		scanf("%s", ID);
		res = FindByID(pm, ID);		//返回索引
	}
	else if (choice == 2)
	{
		char name[NAME_MAXSIZE];
		printf("请输入要删除的员工姓名\n");
		scanf("%s", name);
		res = FinidByName(pm, name);  //返回索引
	}
	else
	{
		printf("输入错误!\n");
		return;
	}
	//删除操作
	if (res == -1)
	{
		printf("要删除的员工不存在\n");
		return;
	}
	else
	{
		//展示删除员工信息
		printf("姓名:%s\t工号:%s\t职务:%s\t\n", pm->emp[res].name, pm->emp[res].ID, pm->emp[res].officialName);
		int j;
		for (j = res; j < pm->size - 1; j++)
			pm->emp[j] = pm->emp[j + 1];
		pm->size--;
		printf("删除成功\n");
	}
}

//查找指定的人的信息
void Search_PIM(const PIM* pm)
{
	if (pm->size == 0)
	{
		printf("人事管理系统暂无信息，请进行添加 > \n");
		return;
	}
	int choice = 0;
	printf("请输入要选择的查询方式:> 1.工号查询(自动排序)    2.姓名查询\n");
	scanf("%d", &choice);
	//获取索引 操作
	int res;
	if (choice == 1)
	{
		char ID[ID_MAXSIZE];
		printf("请输入要查询的员工工号\n");
		scanf("%s", ID);
		res = FindByID(pm, ID);		//返回索引
		if (res == -1)
		{
			printf("工号不存在\n");
			return;
		}
		printf("\n");
		printf("查询结果如下: \n");
		printf("%-20s\t%-10s\t%-4s\t%-4s\t%-15s\t%-8s\t%-8s\n", "姓名", "工号", "年龄", "性别", "电话", "薪资", "职务");
		printf("%-20s\t%-10s\t%-5d\t%-4s\t%-15s\t%-8d\t%-8s\n",
			pm->emp[res].name,
			pm->emp[res].ID,
			pm->emp[res].age,
			pm->emp[res].sex,
			pm->emp[res].tel,
			pm->emp[res].salary,
			pm->emp[res].officialName);
	}
	else if (choice == 2)
	{
		char name[NAME_MAXSIZE];
		printf("请输入要查询的员工姓名\n");
		scanf("%s", name);
		int i = 0;
		int res = FinidByName(pm, name);   //先查询姓名是否存在
		if (res == -1)
		{
			printf("查无此人\n");
			return;
		}
		printf("\n");
		printf("查询结果如下: \n");
		//具体查询姓名重复的情况
		printf("%-20s\t%-10s\t%-5s\t%-4s\t%-15s\t%-8s\t%-8s\n", "姓名", "工号", "年龄", "性别", "电话", "薪资", "职务");
		for (i = res; i < pm->size; i++)
		{
			if (0 == strcmp(pm->emp[i].name, name))
			{
				printf("%-20s\t%-10s\t%-5d\t%-4s\t%-15s\t%-8d\t%-8s\n",
					pm->emp[i].name,
					pm->emp[i].ID,
					pm->emp[i].age,
					pm->emp[i].sex,
					pm->emp[i].tel,
					pm->emp[i].salary,
					pm->emp[i].officialName);
			}
		}
	}
	else
	{
		printf("输入错误!\n");
		return;
	}
}

//修改指定人信息
void Modify_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("人事管理系统暂无信息，请进行添加 > \n");
		return;
	}
	int choice = 0;
	printf("请输入要选择的修改方式:> 1.工号修改(工号自动排序)    2.姓名修改\n");
	scanf("%d", &choice);
	//获取索引 操作
	int res;
	if (choice == 1)
	{
		char ID[ID_MAXSIZE];
		printf("请输入要修改信息的员工工号\n");
		scanf("%s", ID);
		res = FindByID(pm, ID);		//返回索引
	}
	else if (choice == 2)
	{
		char name[NAME_MAXSIZE];
		printf("请输入要修改信息的员工姓名\n");
		scanf("%s", name);
		res = FinidByName(pm, name);  //返回索引
	}
	else
	{
		printf("输入错误!\n");
		return;
	}
	//展示需修改的员工信息
	printf("姓名:%s\t工号:%s\t职务:%s\t\n", pm->emp[res].name, pm->emp[res].ID, pm->emp[res].officialName);
	//修改操作
	if (res == -1)
	{
		printf("要修改的员工不存在\n");
		return;
	}
	else
	{
		printf("请输入员工姓名:>\n");
		scanf("%s", pm->emp[res].name);
		printf("请输入员工工号:>\n");
		scanf("%s", pm->emp[res].ID);
		printf("请输入员工年龄:>\n");
		scanf("%d", &pm->emp[res].age);
		printf("请输入员工性别:>\n");
		scanf("%s", pm->emp[res].sex);
		printf("请输入员工电话:>\n");
		scanf("%s", pm->emp[res].tel);
		printf("请输入员工薪水:>\n");
		scanf("%d", &pm->emp[res].salary);
		printf("请输入员工职务:>\n");
		scanf("%s", pm->emp[res].officialName);
		printf("修改成功\n");
	}
}


static int compare_emp_name(void* p1, void* p2)
{
	return strcmp(((Employee*)p1)->name, ((Employee*)p2)->name);
	//先强制类型转，再由strcmp函数比较结构体 字符串
}

static int compare_emp_salary_asc(void* p1, void* p2)
{
	return ((Employee*)p1)->salary - ((Employee*)p2)->salary;
	//先强制类类型转换，再通过相减比较大小返回正负
}
static int compare_emp_salary_desc(void* p1, void* p2)
{
	return ((Employee*)p2)->salary - ((Employee*)p1)->salary;
	//先强制类类型转换，再通过相减比较大小返回正负
}

//排序信息表内容
void Sort_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("人事管理系统暂无信息，请进行添加 > \n");
		return;
	}
	int choice = 0;
	printf("请输入要选择的排序方式:> 1.工号排序    2.姓名排序（首字母顺序）    3.薪资排序(正序）    4.薪资排序（倒序）\n");
	scanf("%d", &choice);

	if (choice == 1)
	{
		//存放员工信息结构体数组   数组长度  结构体所占空间   compare函数
		qsort(pm->emp, pm->size, sizeof(Employee), compare_emp_ID);
	}
	else if (choice == 2)
	{
		qsort(pm->emp, pm->size, sizeof(Employee), compare_emp_name);
	}
	else if (choice == 3)
	{
		qsort(pm->emp, pm->size, sizeof(Employee), compare_emp_salary_asc);
	}
	else if (choice == 4)
	{
		qsort(pm->emp, pm->size, sizeof(Employee), compare_emp_salary_desc);
	}
	else
	{
		printf("输入错误!\n");
		return;
	}
	printf("排序成功\n");
}

//清除信息表
void Clear_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("人事管理系统暂无信息，请进行添加 > \n");
		return;
	}
	char choice;
	//再次确认是否选择清除所有数据
	getchar(); //将\n吸收
	printf("请再次确认是否选择清除所有数据:>(Y or N)\n");
	scanf("%c", &choice);
	if (choice == 'Y')
	{
		free(pm->emp);
		pm->capacity = 4;
		pm->size = 0;
		printf("清除成功\n");
	}
	else if (choice == 'N')
		printf("退出清除\n");
	else 
	{
		printf("输入错误!\n");
	}
}

//释放内存
void Destroy_PIM(PIM* pm)
{
	free(pm->emp);
	pm->capacity = 0;
	pm->size = 0;
	pm->emp = NULL;
}

//保存文件
void Save_PIM(PIM* pm)
{
	FILE* pf = fopen("emp.txt", "w");
	if (pf == NULL)
	{
		printf("There was an error: %s", strerror(errno));
		//errno 获取错误码，将出错具体原因通过strerror函数呈现
		return;
	}
	fprintf(pf, "%d\n", pm->size); //将存储信息个数保存
	int i = 0;
	for (i = 0; i < pm->size; i++)
	{
		//将信息格式化保存
		fprintf(pf,"%-20s\t%-10s\t%-5d\t%-5s\t%-15s\t%-8d\t%-8s\n",
				pm->emp[i].name,
				pm->emp[i].ID,
				pm->emp[i].age,
				pm->emp[i].sex,
				pm->emp[i].tel,
				pm->emp[i].salary,
				pm->emp[i].officialName);
	}
	//关闭文件
	fclose(pf);
	pf = NULL;
}

