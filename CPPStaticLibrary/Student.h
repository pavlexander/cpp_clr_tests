#pragma once
#include <cstring>
#include <iostream>

class Student
{
	private:
		char *_fullname;
		double _gpa;
	public:
		Student(char *name, double gpa)
		{
			_fullname = new char[strlen(name) + 1];
			//strcpy(_fullname, name);
			strcpy_s(_fullname, strlen(name) + 1, name);
			_gpa = gpa;
			std::cout << "Name is " << _fullname << std::endl;
			std::cout << "Gpa is " << _gpa << std::endl;
		}

		~Student()
		{
			delete[] _fullname;
		}

		double getGpa()
		{
			return _gpa;
		}

		char *getName()
		{
			return _fullname;
		}
};