#define _CRT_SECURE_NO_WARNINGS

#include"PIM.h"
void Show_Team()
{
	printf("--------------------------\n");
	printf(">     ��������Ϣչʾ     <\n");
	printf(">      �ӳ�������ӽ      <\n");
	printf(">      ��Ա�����㶫      <\n");
	printf(">                        <\n");
	printf(">  22���������ѧ�뼼��  <\n");
	printf(">  ����ʱ�䣺2024.4.27   <\n");
	printf("--------------------------\n");
}

void menu()
{
	printf("--------------------------\n");
	printf(">      ���¹���ϵͳ      <\n");
	printf(">     1.���Ա����Ϣ     <\n");
	printf(">     2.ɾ��Ա����Ϣ     <\n");
	printf(">     3.չʾԱ����Ϣ     <\n");
	printf(">     4.����Ա����Ϣ     <\n");
	printf(">     5.�޸�Ա����Ϣ     <\n");
	printf(">     6.����Ա����Ϣ     <\n");
	printf(">     7.���Ա����Ϣ     <\n");
	printf(">     8.����Ա����Ϣ     <\n");
	printf(">     9.չʾС����Ϣ     <\n");
	printf(">     0.  �˳�ϵͳ       <\n");
	printf("--------------------------\n");
}


int main()
{
	int choice;
	PIM m;
	Init_PIM(&m);
	do 
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &choice);
		//ͨ��ö��ѡ��
		switch (choice)
		{
		case ADD:
			Add_PIM(&m);
			printf("��ӳɹ�\n");
			break;
		case DEL:
			Del_PIM(&m);
			break;
		case SHOW:
			system("cls");
			Show_PIM(&m);
			break;
		case SEARCH:
			Search_PIM(&m);
			break;
		case MOD:
			Modify_PIM(&m);
			break;
		case SORT:
			Sort_PIM(&m);
			break;
		case CLEAR:
			system("cls");
			Clear_PIM(&m);
			break;
		case SAVE:
			Save_PIM(&m);
			printf("����ɹ�\n");
			break;
		case SHOW_TEAM:
			system("cls");
			Show_Team();
			break;
		case EXIT:
			Save_PIM(&m);
			Destroy_PIM(&m);
			printf("�˳�ϵͳ\n");
			break;
		default:
			printf("�޴�ѡ��\n");
			break;
		}
	} while (choice);
	return 0;
}

