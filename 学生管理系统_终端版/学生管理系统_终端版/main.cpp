#include <iostream>
#include "StudentManage.h"

int main(void)
{

	int key = 0;
	while (1)
	{
		printf("|---------------- 菜单选项 -----------------|\n");
		printf("|---------------- 0.退出         -----------|\n");
		printf("|---------------- 1.增加学生信息 -----------|\n");
		printf("|---------------- 2.修改学生信息 -----------|\n");
		printf("|---------------- 3.删除学生信息 -----------|\n");
		printf("|---------------- 4.查找学生信息 -----------|\n");
		printf("|---------------- 5.打印学生信息 -----------|\n");
		printf("|-------------------------------------------|\n");

		scanf_s("%d", &key);
		switch (key)
		{
		case 0:

			break;
		case 1:
			StudentManage::Instance()->AddStudent("干饭小白", 23, 1);
			break;
		case 2:
			StudentManage::Instance()->ModStudent(1);
			break;
		case 3:
			StudentManage::Instance()->DelStudent(1);
			break;
		case 4:
			StudentManage::Instance()->SearchStudent(1);
			break;
		case 5:
			StudentManage::Instance()->PrintStudetList();
			break;
		default:
			break;
		}

		if (key == 0)
		{
			break;
		}
	}

	getchar();

	return 0;
}

