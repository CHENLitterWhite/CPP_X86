#include "StudentManage.h"
#include <regex>

StudentManage::StudentManage()
{
	no = 0;
}

StudentManage::~StudentManage()
{
	for (auto it = pStudentManager->m_studetMap.begin(); it != pStudentManager->m_studetMap.end(); ++it)
	{
		delete it->second;
	}

	delete pStudentManager;
}

StudentManage* StudentManage::Instance()
{
	if (pStudentManager == nullptr)
	{
		pStudentManager = new StudentManage();
	}

	return pStudentManager;
}

bool StudentManage::AddStudent(std::string name, uint8_t age, bool sex)
{
	LPSTUDENT p = new STUDENT;

	p->name = name;
	p->age = age;
	p->no = ++pStudentManager->no;
	p->sex = sex;

	pStudentManager->m_studetMap.insert(std::make_pair(p->no, p));

	return true;
}

bool StudentManage::ModStudent(uint32_t no)
{
	

	return true;
}

bool StudentManage::DelStudent(uint32_t no)
{
	pStudentManager->Instance()->m_studetMap.erase(no);

	return true;
}

bool StudentManage::PrintStudetList()
{

	for (auto it = pStudentManager->Instance()->m_studetMap.begin(); it != pStudentManager->m_studetMap.end(); ++it)
	{
		printf("---------------------------------------\n");
		printf("|Ñ§ºÅ:|%d\n", it->second->no);
		printf("|ĞÕÃû:|%s\n", it->second->name.c_str());
		printf("|ÄêÁä:|%d\n", it->second->age);
		printf("|sex: |%d\n", it->second->sex);
		printf("---------------------------------------\n");
	}

	return true;
}

bool StudentManage::SearchStudent(uint32_t no)
{

	return true;
}

