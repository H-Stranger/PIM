#define _CRT_SECURE_NO_WARNINGS

#include"PIM.h"
void Show_Team()
{
	printf("--------------------------\n");
	printf(">     创作者信息展示     <\n");
	printf(">      队长：董文咏      <\n");
	printf(">      队员：何秀东      <\n");
	printf(">                        <\n");
	printf(">  22级计算机科学与技术  <\n");
	printf(">  创作时间：2024.4.27   <\n");
	printf("--------------------------\n");
}

void menu()
{
	printf("--------------------------\n");
	printf(">      人事管理系统      <\n");
	printf(">     1.添加员工信息     <\n");
	printf(">     2.删除员工信息     <\n");
	printf(">     3.展示员工信息     <\n");
	printf(">     4.查找员工信息     <\n");
	printf(">     5.修改员工信息     <\n");
	printf(">     6.排序员工信息     <\n");
	printf(">     7.清空员工信息     <\n");
	printf(">     8.保存员工信息     <\n");
	printf(">     9.展示小组信息     <\n");
	printf(">     0.  退出系统       <\n");
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
		printf("请选择:>");
		scanf("%d", &choice);
		//通过枚举选择
		switch (choice)
		{
		case ADD:
			Add_PIM(&m);
			printf("添加成功\n");
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
			printf("保存成功\n");
			break;
		case SHOW_TEAM:
			system("cls");
			Show_Team();
			break;
		case EXIT:
			Save_PIM(&m);
			Destroy_PIM(&m);
			printf("退出系统\n");
			break;
		default:
			printf("无此选项\n");
			break;
		}
	} while (choice);
	return 0;
}

