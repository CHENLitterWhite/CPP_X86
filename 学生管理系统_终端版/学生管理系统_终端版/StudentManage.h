#pragma once

#include <string>
#include <map>

typedef struct _STUDENT_
{
	uint32_t	no;             // ���(ѧ��) -- ����
	std::string name;			// ����
	uint8_t		age;			// ����
	bool		sex;            // �Ա�

}STUDENT, *LPSTUDENT;

// ����ģʽ,���캯��˽�л�(����ģʽ)
class StudentManage
{
public:
	~StudentManage();
	
	static StudentManage* Instance();

	bool AddStudent(std::string name, uint8_t age, bool sex);
	bool ModStudent(uint32_t no);
	bool DelStudent(uint32_t no);
	bool SearchStudent(uint32_t no);
	bool PrintStudetList();

private:

	StudentManage();  

	std::map<uint32_t, LPSTUDENT> m_studetMap;        // �洢����ѧ����Ϣ
	uint32_t	no;
};
static StudentManage* pStudentManager = nullptr;
