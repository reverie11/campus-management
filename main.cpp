#include "persons.h"
#include "traits.h"
#include "university.cpp"
#include "persons.cpp"
#include <chrono>
#include <cstdlib>
#include <math.h>

std::chrono::system_clock::time_point change_birthday(int years_ago)
{
	long double years_to_seconds = years_ago*3.154*pow(10, 7);
	std::chrono::system_clock::time_point 
		now = std::chrono::system_clock::now();
	std::time_t 
		now_t = std::chrono::system_clock::to_time_t(now) - years_to_seconds;
		now = std::chrono::system_clock::from_time_t(now_t);
	return now;
}

int main(){
	Address ad1("Sherlock Street", 12, "12785", "London", "United Kingdom");
	Address ad2("Kebon Jahe", 12, "81800", "Bali", "Indonesia");
	Address ad3("Bergstrasse", 83, "31311", "Musterstadt", "Deutschland");
	Address ad4("Jägerstraße", 83, "31311", "Berlin", "Deutschland");
	Address ad5("Wilhelminnenhof", 83, "31311", "Berlin", "Deutschland");
	Address ad6("TestStreet", 1, "12345", "Berlin", "Germany");
	Address *p_ad3 = &ad3;
		
	std::chrono::system_clock::time_point date1, date2, date3, date4;
		
	date1 = change_birthday(18);
	date2 = change_birthday(26);	
	date3 = change_birthday(20);	
	date4 = change_birthday(40);	

	Person fred("fred", "Ong", date1, ad1);
	Person man("Walter", "White", date4, ad1);
	Person john("John", "Cena", date2, *p_ad3);

	Student man2("Jesse", "Pinkmann", date3, ad1);
	Student man3("Michael", "Scott", date2, ad4);
	Student man4(fred);

	University univ("HTW Berlin", ad5);
	Teacher dozent(man);	
	Teacher dozent2(john);	
	univ.hire(dozent, 1500);
	univ.hire(dozent2, 1500);
	Course& chem = univ.offer_course("Chemistry Meth Cooking", dozent);
	Course& math = univ.offer_course("Mathematik", dozent2);
	man2.enlist(chem);
	man2.enroll(univ);
	man3.enroll(univ);
	man3.enlist(math);
	man4.enroll(univ);
	man4.enlist(math);
	man4.leave(math);

	dozent.resign_course(chem);

	print_stdout(dozent);
}
