#define _CRT_SECURE_NO_WARNINGS

#include"PIM.h"

//��ʼ��Ϣ��
void Init_PIM(PIM* pm)
{
	pm->size = 0;
	pm->capacity = 4;
	pm->emp = (Employee*)malloc(4 * sizeof(Employee));
	if (pm->emp == NULL)
		return;
	Load_PIM(pm);
}


//����
static void CheckCapacity(PIM* pm)
{
	if (pm->size == pm->capacity)
	{
		//realloc����
		PIM* tmp = realloc(pm->emp,sizeof(Employee) * (pm->capacity+2));//һ���������ռ�
		if (tmp == NULL)
		{
			printf("����ʧ��\n");
			exit(0);
		}
		pm->emp = tmp;
		pm->capacity += 2;
	}
}


//�����ļ���Ϣ����Ϣ��
void Load_PIM(PIM* pm)
{
	FILE* pf = fopen("emp.txt", "r");
	if (pf == NULL)
	{
		printf("Load_PIM : %s\n", strerror(errno));
		//errno ��ȡ�����룬���������ԭ��ͨ��strerror��������
		//�����ļ�ʱ������������ļ�����ʾ����
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
	printf("�ļ�����ɹ�\n");

	fclose(pf);
	pf = NULL;
}

//�����Ϣ
void Add_PIM(PIM* pm)
{
	printf("������Ҫ��ӵ�������Ϣ����:>\n");
	int num = 0;
	scanf("%d", &num);
	int count = 1;
	system("cls");		//����
	while (num)
	{
		//���ռ��Ƿ� �㹻
		CheckCapacity(pm);

		printf("����ӵ�%dԱ�������Ϣ\n", count);
		count++;
		printf("������Ա������:>\n");
		scanf("%s", pm->emp[pm->size].name);
		printf("������Ա������:>\n");
		scanf("%s", pm->emp[pm->size].ID);
		printf("������Ա������:>\n");
		scanf("%d", &pm->emp[pm->size].age);
		printf("������Ա���Ա�:>\n");
		scanf("%s", pm->emp[pm->size].sex);
		printf("������Ա���绰:>\n");
		scanf("%s", pm->emp[pm->size].tel);
		printf("������Ա��нˮ:>\n");
		scanf("%d", &pm->emp[pm->size].salary);
		printf("������Ա��ְ��:>\n");
		scanf("%s", pm->emp[pm->size].officialName);

		pm->size++;
		num--;
		//ʵ������Ч������������
		system("cls");
	}
}

//��ӡ��Ϣ
void Show_PIM(const PIM* pm)
{
	if (pm->size == 0)
		printf("���¹���ϵͳ������Ϣ���������� > \n");
	else
	{
		//����
		int i = 0;
		printf("��ѯ�ɹ�\n");
		printf("%-20s\t%-10s\t%-5s\t%-4s\t%-15s\t%-8s\t%-8s\n", "����", "����", "����", "�Ա�", "�绰", "н��", "ְ��");
		//����
		//��ʽ�����
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

	return -1;//�Ҳ���
}

static int compare_emp_ID(void* p1, void* p2)
{
	return atoi(((Employee*)p1)->ID) - atoi(((Employee*)p2)->ID);
	//�Ƚ�p1ǿ������ת��Ϊ Employee����ָ�� ��ָ��ID�������ַ���ת��Ϊ���ͣ�atoi���������Ƚϴ�С
}

static int FindByID(PIM* pm, char* ID)
{
	//����Ҫ����Ϣ������(���չ�������)
	qsort(pm->emp, pm->size, sizeof(Employee), compare_emp_ID);

	int left = 0;
	int right = pm->size - 1;
	//�Ⱥ� �� ����ֻ��һ����Ϣ��ʱ��
	while (left <= right)
	{
		int mid = left + ((right - left) >> 1); // ����left + (right - left)/2
		//Ŀ��ֵС���м�ֵ����������
		if (atoi(pm->emp[mid].ID) > atoi(ID))
			right = mid  - 1;
		else if (atoi(pm->emp[mid].ID) < atoi(ID))
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}


//ɾ����Ϣ
void Del_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("���¹���ϵͳ������Ϣ���������� > \n");
		return;
	}
	int choice = 0;
	printf("������Ҫѡ���ɾ����ʽ:> 1.����ɾ��(�Զ�����)    2.����ɾ��\n");
	scanf("%d", &choice);
	//��ȡ���� ����
	int res;
	if (choice == 1)
	{
		char ID[ID_MAXSIZE];
		printf("������Ҫɾ����Ա������\n");
		scanf("%s", ID);
		res = FindByID(pm, ID);		//��������
	}
	else if (choice == 2)
	{
		char name[NAME_MAXSIZE];
		printf("������Ҫɾ����Ա������\n");
		scanf("%s", name);
		res = FinidByName(pm, name);  //��������
	}
	else
	{
		printf("�������!\n");
		return;
	}
	//ɾ������
	if (res == -1)
	{
		printf("Ҫɾ����Ա��������\n");
		return;
	}
	else
	{
		//չʾɾ��Ա����Ϣ
		printf("����:%s\t����:%s\tְ��:%s\t\n", pm->emp[res].name, pm->emp[res].ID, pm->emp[res].officialName);
		int j;
		for (j = res; j < pm->size - 1; j++)
			pm->emp[j] = pm->emp[j + 1];
		pm->size--;
		printf("ɾ���ɹ�\n");
	}
}

//����ָ�����˵���Ϣ
void Search_PIM(const PIM* pm)
{
	if (pm->size == 0)
	{
		printf("���¹���ϵͳ������Ϣ���������� > \n");
		return;
	}
	int choice = 0;
	printf("������Ҫѡ��Ĳ�ѯ��ʽ:> 1.���Ų�ѯ(�Զ�����)    2.������ѯ\n");
	scanf("%d", &choice);
	//��ȡ���� ����
	int res;
	if (choice == 1)
	{
		char ID[ID_MAXSIZE];
		printf("������Ҫ��ѯ��Ա������\n");
		scanf("%s", ID);
		res = FindByID(pm, ID);		//��������
		if (res == -1)
		{
			printf("���Ų�����\n");
			return;
		}
		printf("\n");
		printf("��ѯ�������: \n");
		printf("%-20s\t%-10s\t%-4s\t%-4s\t%-15s\t%-8s\t%-8s\n", "����", "����", "����", "�Ա�", "�绰", "н��", "ְ��");
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
		printf("������Ҫ��ѯ��Ա������\n");
		scanf("%s", name);
		int i = 0;
		int res = FinidByName(pm, name);   //�Ȳ�ѯ�����Ƿ����
		if (res == -1)
		{
			printf("���޴���\n");
			return;
		}
		printf("\n");
		printf("��ѯ�������: \n");
		//�����ѯ�����ظ������
		printf("%-20s\t%-10s\t%-5s\t%-4s\t%-15s\t%-8s\t%-8s\n", "����", "����", "����", "�Ա�", "�绰", "н��", "ְ��");
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
		printf("�������!\n");
		return;
	}
}

//�޸�ָ������Ϣ
void Modify_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("���¹���ϵͳ������Ϣ���������� > \n");
		return;
	}
	int choice = 0;
	printf("������Ҫѡ����޸ķ�ʽ:> 1.�����޸�(�����Զ�����)    2.�����޸�\n");
	scanf("%d", &choice);
	//��ȡ���� ����
	int res;
	if (choice == 1)
	{
		char ID[ID_MAXSIZE];
		printf("������Ҫ�޸���Ϣ��Ա������\n");
		scanf("%s", ID);
		res = FindByID(pm, ID);		//��������
	}
	else if (choice == 2)
	{
		char name[NAME_MAXSIZE];
		printf("������Ҫ�޸���Ϣ��Ա������\n");
		scanf("%s", name);
		res = FinidByName(pm, name);  //��������
	}
	else
	{
		printf("�������!\n");
		return;
	}
	//չʾ���޸ĵ�Ա����Ϣ
	printf("����:%s\t����:%s\tְ��:%s\t\n", pm->emp[res].name, pm->emp[res].ID, pm->emp[res].officialName);
	//�޸Ĳ���
	if (res == -1)
	{
		printf("Ҫ�޸ĵ�Ա��������\n");
		return;
	}
	else
	{
		printf("������Ա������:>\n");
		scanf("%s", pm->emp[res].name);
		printf("������Ա������:>\n");
		scanf("%s", pm->emp[res].ID);
		printf("������Ա������:>\n");
		scanf("%d", &pm->emp[res].age);
		printf("������Ա���Ա�:>\n");
		scanf("%s", pm->emp[res].sex);
		printf("������Ա���绰:>\n");
		scanf("%s", pm->emp[res].tel);
		printf("������Ա��нˮ:>\n");
		scanf("%d", &pm->emp[res].salary);
		printf("������Ա��ְ��:>\n");
		scanf("%s", pm->emp[res].officialName);
		printf("�޸ĳɹ�\n");
	}
}


static int compare_emp_name(void* p1, void* p2)
{
	return strcmp(((Employee*)p1)->name, ((Employee*)p2)->name);
	//��ǿ������ת������strcmp�����ȽϽṹ�� �ַ���
}

static int compare_emp_salary_asc(void* p1, void* p2)
{
	return ((Employee*)p1)->salary - ((Employee*)p2)->salary;
	//��ǿ��������ת������ͨ������Ƚϴ�С��������
}
static int compare_emp_salary_desc(void* p1, void* p2)
{
	return ((Employee*)p2)->salary - ((Employee*)p1)->salary;
	//��ǿ��������ת������ͨ������Ƚϴ�С��������
}

//������Ϣ������
void Sort_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("���¹���ϵͳ������Ϣ���������� > \n");
		return;
	}
	int choice = 0;
	printf("������Ҫѡ�������ʽ:> 1.��������    2.������������ĸ˳��    3.н������(����    4.н�����򣨵���\n");
	scanf("%d", &choice);

	if (choice == 1)
	{
		//���Ա����Ϣ�ṹ������   ���鳤��  �ṹ����ռ�ռ�   compare����
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
		printf("�������!\n");
		return;
	}
	printf("����ɹ�\n");
}

//�����Ϣ��
void Clear_PIM(PIM* pm)
{
	if (pm->size == 0)
	{
		printf("���¹���ϵͳ������Ϣ���������� > \n");
		return;
	}
	char choice;
	//�ٴ�ȷ���Ƿ�ѡ�������������
	getchar(); //��\n����
	printf("���ٴ�ȷ���Ƿ�ѡ�������������:>(Y or N)\n");
	scanf("%c", &choice);
	if (choice == 'Y')
	{
		free(pm->emp);
		pm->capacity = 4;
		pm->size = 0;
		printf("����ɹ�\n");
	}
	else if (choice == 'N')
		printf("�˳����\n");
	else 
	{
		printf("�������!\n");
	}
}

//�ͷ��ڴ�
void Destroy_PIM(PIM* pm)
{
	free(pm->emp);
	pm->capacity = 0;
	pm->size = 0;
	pm->emp = NULL;
}

//�����ļ�
void Save_PIM(PIM* pm)
{
	FILE* pf = fopen("emp.txt", "w");
	if (pf == NULL)
	{
		printf("There was an error: %s", strerror(errno));
		//errno ��ȡ�����룬���������ԭ��ͨ��strerror��������
		return;
	}
	fprintf(pf, "%d\n", pm->size); //���洢��Ϣ��������
	int i = 0;
	for (i = 0; i < pm->size; i++)
	{
		//����Ϣ��ʽ������
		fprintf(pf,"%-20s\t%-10s\t%-5d\t%-5s\t%-15s\t%-8d\t%-8s\n",
				pm->emp[i].name,
				pm->emp[i].ID,
				pm->emp[i].age,
				pm->emp[i].sex,
				pm->emp[i].tel,
				pm->emp[i].salary,
				pm->emp[i].officialName);
	}
	//�ر��ļ�
	fclose(pf);
	pf = NULL;
}

