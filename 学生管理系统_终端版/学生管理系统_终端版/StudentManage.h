#pragma once

#include <string>
#include <map>

typedef struct _STUDENT_
{
	uint32_t	no;             // 编号(学号) -- 自增
	std::string name;			// 姓名
	uint8_t		age;			// 年龄
	bool		sex;            // 性别

}STUDENT, *LPSTUDENT;

// 单例模式,构造函数私有化(懒汉模式)
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

	std::map<uint32_t, LPSTUDENT> m_studetMap;        // 存储所有学生信息
	uint32_t	no;
};
static StudentManage* pStudentManager = nullptr;
