#include "persons.h"
#include "traits.h"
#include "university.h"
#include <chrono>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>

Person::Person(std::string first_name, std::string last_name, std::chrono::system_clock::time_point birthday, Address &place_of_residence) : Displayable()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	
	if(first_name.length()>=2 && !(digits_exist(first_name))){
		m_first_name = first_name;
	}	
	else throw std::domain_error("invalid first name");

	if(last_name.length()>=2 && !(digits_exist(last_name))){
		m_last_name = last_name;
	}
	else throw std::domain_error("invalid last name");
	
	if(birthday < now){
		m_birthday = birthday;
	} else throw std::domain_error("impossible birthday");

	m_place_of_residence = &place_of_residence;
	
}

void Person::relocate(Address &place_of_residence)
{
	m_place_of_residence = &place_of_residence;
}

std::string Person::to_string() const 
{
	std::stringstream strstream;
	std::string str,
		address_str = m_place_of_residence->to_string();
	std::time_t birthday_t = std::chrono::system_clock::to_time_t(m_birthday);

	strstream << "\n" << m_first_name << " " << m_last_name << "\n";
	strstream << std::ctime(&birthday_t) << "\n";
	strstream << address_str;

	str = strstream.str();
	return str;
}

int32_t Student::s_student_counter = 0;

Student::Student(std::string first_name, std::string last_name, std::chrono::system_clock::time_point birthday, Address &place_of_residence): 
	Person(first_name, last_name, birthday, place_of_residence),
	m_student_number(++s_student_counter){
	m_university = NULL;
}

Student::~Student(){}

Student::Student(Person &person): Person(person), m_student_number(++s_student_counter){
	m_university = NULL;
}

void Student::enlist(Course &course)
{
	bool repeated = false;
		
	for(const auto& ptr: m_courses)
	{
		if(course.name() == ptr->name())
			repeated = true;
	}		

	if(!repeated){
		m_courses.emplace_back(&course);
		course.enlist(*this);
	}
}

void Student::leave(Course &course)
{
	int pos = 0;
	for( const auto& ptr : m_courses )	
	{
		if(course.name() == ptr->name())
		{
			m_courses.erase(m_courses.begin()+pos);
			course.leave(*this);
			break;
		}
		pos++;
	}
}

void Student::enroll(University &university)
{
	if(m_university == NULL)
	{
		m_university = &university;
		university.enroll(*this);
	} else if (m_university != &university){
		m_university->exmatriculate(*this);
		m_university = &university;
		university.enroll(*this);
	}
}

void Student::exmatriculate()
{
	if(m_university != NULL){
		m_university->exmatriculate(*this);
		m_university = NULL;
	}
}

std::string Student::to_string() const
{
	std::stringstream strstream;
	strstream << Person::to_string() << "\n";
	strstream << "Universität: " << m_university->name() << "\n\n";
	strstream << "Matrikelnummer: " << m_student_number << "\n\n";
	strstream << "Anzahl Seminare: " << m_courses.size() << "\n";
	for(auto i = 0; i<m_courses.size(); i++)
	{
		strstream << i + 1 << " " << m_courses[i]->name() << "\n";
	}


	return strstream.str();
}

Teacher::Teacher(std::string first_name, std::string last_name, std::chrono::system_clock::time_point birthday, Address &place_of_residence):
	Person(first_name, last_name, birthday, place_of_residence){
	m_loan = 0;
	m_university = NULL;
}

Teacher::Teacher(Person &person): Person(person){ m_loan = 0; m_university = NULL;}

Teacher::~Teacher(){}

void Teacher::assign_course(Course &course)
{
	bool repeated = false;
		
	for(const auto& ptr: m_courses)
	{
		if(course.name() == ptr->name())
		{
			repeated = true;
			break;
		}
	}		

	if(!repeated){
		m_courses.emplace_back(&course);
		course.assign_teacher(*this);
	}
}

void Teacher::resign_course(Course &course)
{
	int pos = 0;
	bool found = false;
	for(const auto& ptr: m_courses)
	{
		if(course.name() == ptr->name())
		{
			found = true;
			break;	
		}
		pos++;
	}

	if(found){
		m_courses.erase(m_courses.begin()+pos);
		course.resign_teacher();
	}
	
}

void Teacher::lay_off()
{
	if(m_university != NULL)
	{
		m_loan = 0;
		m_university->lay_off(*this);
		m_university = NULL;
	}
}

void Teacher::hire(University &university, std::int32_t loan)
{
	if(loan >= 1000)
	{
		m_university = &university;
		m_loan = loan;
		university.hire(*this, loan);
	} else throw std::domain_error("Salary too low");
}

std::string Teacher::to_string() const
{
	std::stringstream strstream;

	strstream << Person::to_string() << "\n"
		<< "Universität: " << m_university->name() << "\n"
		<< "Gehalt: " << m_loan << "€\n\n"
		<< "Anzahl Seminare: " << m_courses.size() << "\n";
	for(int i = 0; i < m_courses.size(); i++)
		{
			strstream << i +1 << " " << m_courses[i]->name() << "\n";
		}
	return strstream.str();
}
