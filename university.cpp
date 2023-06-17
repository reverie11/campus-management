#include "university.h"
#include "persons.h"
#include "traits.h"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cctype>

bool digits_exist(const std::string &str)
{
	for (char c : str) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}

bool all_digits(const std::string &str)
{
	for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

void print_stdout(Displayable &displayable){
	std::cout << displayable.to_string() << std::endl;
}

University::University(const std::string &name, Address &address): m_address(address), Displayable()
{
	if(name.length() >= 10){
		m_name = name;
	} else throw std::domain_error("Invalid university name");
 
}

University::~University(){}

void University::enroll(Student &student)
{
	if(student.university() == NULL)
	{
		m_students.emplace_back(&student);
	}
	student.enroll(*this);
}

void University::exmatriculate(Student &student)
{
	int pos = 0;
	if(student.university() == this)
	{
		for(auto& ptr : m_students)
		{
			if(student.student_number() == ptr->student_number())
			{
				m_students.erase(m_students.begin()+pos);
				student.exmatriculate();
				break;
			}
			pos++;
		}
	}
}

void University::hire(Teacher &teacher, std::int32_t loan)
{
	bool found = false;
	for(auto& ptr : m_teachers)
	{
		if(teacher.first_name() == ptr->first_name())
		{
			if(teacher.last_name() == ptr->last_name())
			{
				found = true;
				break;
			}
		}
	}
	if (!found){
		m_teachers.emplace_back(&teacher);
		teacher.hire(*this, loan);
	}
}

void University::lay_off(Teacher &teacher)
{
	int pos = 0;
	if(teacher.university() == this)
	{
		for(auto& ptr : m_students)
		{
			if(teacher.first_name() == ptr->first_name())
			{
				if(teacher.last_name() == ptr->last_name())
				{
					m_teachers.erase(m_teachers.begin()+pos);
					teacher.lay_off();
					break;
				}
			}
			pos++;
		}
	}
}

std::string University::to_string() const
{
	std::stringstream strstream;
	strstream << "Universität: " << m_name << "\n\n";
	strstream << m_address.to_string() ;
	strstream << "Anzahl Studierender: " << m_students.size() << "\n";

	for(auto i=0; i < m_students.size(); i++ )
	{
		strstream << i + 1 << " " << m_students[i]->first_name() << " "
			<< m_students[i]->last_name() <<"\n";
	}

	strstream << "\nAnzahl Lehrkräfte: " << m_teachers.size() << "\n";
	for(auto i=0; i < m_teachers.size(); i++ )
	{
		strstream << i + 1 << " " << m_teachers[i]->first_name() << " "
			<< m_teachers[i]->last_name() <<"\n";
	}

	strstream << "\nAnzahl Seminare: " << m_courses.size() << "\n";
	for(auto i=0; i < m_courses.size(); i++ )
	{
		strstream << i + 1 << " " << m_courses[i].name() << "\n";
	}

	return strstream.str();
}

Course& University::offer_course(const std::string &name, Teacher &teacher)
{
	bool repeated = false;
	Course& course = *(new Course(name));
	
	for(const auto& ptr: m_courses)
	{
		if(name == ptr.name())
		{
			repeated = true;
			break;
		}
	}

	if(!repeated){
		m_courses.emplace_back(course);
		teacher.assign_course(course);
	}
	
	return course;
}

Address::Address(std::string street, std::int32_t street_no, 
		std::string zipcode,std::string city, std::string country): 
	Displayable()
{
	if (street.length() >= 10){
		m_street = street;
	} 
	else throw std::domain_error("Invalid street name");

	if (street_no > 0){
		m_street_no = street_no;
	}
	else throw std::domain_error("Invalid street number");

	if (all_digits(zipcode) && zipcode.length() == 5){
		m_zipcode = zipcode;
	}
	else throw std::domain_error("Invalid zipcode");

	if (city.length() >= 3){
		m_city = city;
	}
	else throw std::domain_error("Invalid city");

	if (country.length() >= 3){
		m_country = country;
	}
	else throw std::domain_error("Invalid country");
}

std::string Address::to_string() const {
	std::stringstream strstream;
	std::string str;

	strstream << m_street << " " << m_street_no << "\n";
	strstream << m_zipcode << " " << m_city << "\n";
	strstream << m_country << "\n";
		
	str = strstream.str();	
	return str;
}

Course::Course(const std::string &name) : Displayable()
{
	if(name.length() >= 10){
		m_name = name;
	} else throw std::domain_error("invalid course name");
	m_students.clear();
}

Course::~Course(){}

void Course::enlist(Student &student)
{
	bool repeated = false;
	
	for(const auto& ptr: m_students)
	{
		if(student.student_number() == ptr->student_number())
		{
			repeated = true;
			break;
		}
	}

	if(!repeated){
		m_students.emplace_back(&student);
		student.enlist(*this);
	}
	
}

void Course::leave(Student &student)
{
	int pos = 0;
	for(const auto& ptr : m_students)	
	{
		if(student.student_number() == ptr->student_number())
		{
			m_students.erase(m_students.begin()+pos);
			student.leave(*this);
			break;
		}
		pos++;
	}
}

void Course::assign_teacher(Teacher &teacher)
{
	m_teacher = &teacher;
	teacher.assign_course(*this);
}

void Course::resign_teacher()
{
	if(m_teacher != NULL)
	{
		m_teacher->resign_course(*this);	
		m_teacher = NULL;
	}
}

std::vector<Student *>& Course::list_students()
{
	return m_students;
}

Teacher* Course::teacher()
{
	return m_teacher;
}

std::string Course::to_string() const
{
	std::stringstream strstream;
	strstream << "Seminar: " << m_name << "\n\n";
	strstream << "Lehrkraft: " << m_teacher->first_name() << " " << m_teacher->last_name() << "\n\n";
	strstream << "Anzahl Studierende: " << m_students.size() << "\n";
	
	for(auto i = 0; i < m_students.size(); i++)
	{
		strstream << i +1 << " " << m_students[i]->first_name() << " " << m_students[i]->last_name() << "\n";
	}

	return strstream.str();
}


