#include <iostream>
#include "StudentManage.h"

int main(void)
{

	int key = 0;
	while (1)
	{
		printf("|---------------- �˵�ѡ�� -----------------|\n");
		printf("|---------------- 0.�˳�         -----------|\n");
		printf("|---------------- 1.����ѧ����Ϣ -----------|\n");
		printf("|---------------- 2.�޸�ѧ����Ϣ -----------|\n");
		printf("|---------------- 3.ɾ��ѧ����Ϣ -----------|\n");
		printf("|---------------- 4.����ѧ����Ϣ -----------|\n");
		printf("|---------------- 5.��ӡѧ����Ϣ -----------|\n");
		printf("|-------------------------------------------|\n");

		scanf_s("%d", &key);
		switch (key)
		{
		case 0:

			break;
		case 1:
			StudentManage::Instance()->AddStudent("�ɷ�С��", 23, 1);
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

