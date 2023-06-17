#pragma once
#include "traits.h"
#include <chrono>
#include <cstdlib>
#include <string>
#include <vector>

class University;
class Address;
class Course;

/**
 * @brief Stellt eine einfache menschliche Person dar. Sie wird über einen
 * Konstruktor initialisiert welcher die Daten auf Gültigkeit überprüft (1). Die
 * Personklasse ist die Basisklasse für die Klassen Student und Teacher. Diese
 * erben die Daten und Implementierungen der Klasse, womit diese ihnen zur
 * Verfügung stehen (4).
 *
 * Die Klasse erbt die von der abstrakten Klasse Display die Spezifikation der
 * to_string Methode welche implementiert werden muss. (3)
 */
class Person : public Displayable {
protected:
  std::string m_first_name;
  std::string m_last_name;
  std::chrono::system_clock::time_point m_birthday;
  Address *m_place_of_residence;

public:
  /**
   * @brief Erzeugt das Personen Objekt mit gültigen Daten, falls die Daten
   * ungültig sind wird im Konstruktor eine Exception vom Typ std::domain_error
   * geworfen.
   *
   * @throws std::domain_error Wenn die Validierung fehlschlägt.
   *
   * @param first_name Vorname der Person, muss mindesten 2 Zeichen lang sein
   * und darf nur Buchstaben enthalten.
   * @param last_name Nachname der Person, muss mindesten 2 Zeichen lang sein
   * und darf nur Buchstaben enthalten.
   * @param birthday Gebutstag der Person, darf nicht in der Zukunft liegen.
   * @param address Wohnort der Person.
   */
  // TODO Konstruktor welcher das Address Objekt initialisiert und dabei die
  // Daten validiert.
  Person(std::string first_name, std::string last_name, std::chrono::system_clock::time_point birthday, Address &place_of_residence);
  /**
   * @brief Lässt die Person an einen anderen Ort umziehen.
   *
   * @param place_of_residence der Ort zu dem die Person zieht.
   */
  void relocate(Address &place_of_residence);

  /**
   * @return Der Vorname der Person
   */
  const std::string &first_name(){return m_first_name;}

  /**
   * @return Der Nachname der Person
   */
  const std::string &last_name(){return m_last_name;}

  /**
   * @return Der Wohnort der Person
   */
  const Address &place_of_residence(){ return *m_place_of_residence; }

  /**
   * @return Der Geburtstag der Person
   */
  const std::chrono::system_clock::time_point birthday()
  {return m_birthday;}

  /**
   * @brief Gibt einen String zurück welcher menschenlesbar ist und für die
   * Ausgabe gedacht ist. Das Format soll in dieser Form erfolgen, die Trennung
   * erfolgt mit einem Zeilenumbruch am Ende der Zeile:
   *
   * Vorname Nachname
   * Geburtsdatum
   *
   * Address::to_string
   *
   * @return std::string Menschenlesbare Zusammenfassung des Objektes
   */
  // TODO to_string Methode überschreiben
  std::string to_string() const override;
};

/**
 * @brief Stellt einen Studiernden einer Universität dar und erbt alle Methoden
 * und Daten der Person Klasse (3) und erweitert diese um Spezifische Daten und
 * Verhalten z.B. die to_string Methode welche schon in der Person Klasse
 * implementiert wurde.
 *
 */
class Student : public Person {
private:
  const std::int32_t m_student_number;
  University *m_university;
  std::vector<Course *> m_courses;

  /**
   * @brief Zähler mit stastischer Lebensdauer der alle erstellten
   * Studentenobjekte zählt, die Matrikelnummer ergibt sich aus der aktuellen
   * Zahl + 1.
   */
  static std::int32_t s_student_counter;

public:
  /**
   * Konstruktor welcher ein neues Studentenobjekt erzeugt, in dem der
   * Konstruktor der Basisklasse aufgerufen wird (4), die Validierungslogik muss
   * damit nur einmal geschrieben werden. Der statische Zähler für die
   * Matrikelnummer muss inkrementiert werden.
   *
   * @throws std::domain_error Wenn die Validierung fehlschlägt. (Vererbtes
   * Verhalten)
   *
   * @param first_name Vorname der Person, muss mindesten 2 Zeichen lang sein
   * und darf nur Buchstaben enthalten.
   * @param last_name Nachname der Person, muss mindesten 2 Zeichen lang sein
   * und darf nur Buchstaben enthalten.
   * @param birthday Gebutstag der Person, darf nicht in der Zukunft liegen.
   * @param address Wohnort der Person.
   */
  // TODO Constructor welcher das Studentobjekt initialisiert und bei der
  // Erstellung den Zähler inkrementiert.
  Student(std::string first_name, std::string last_name, std::chrono::system_clock::time_point birthday, Address &place_of_residence);
  /**
   * @brief Kopierkonstruktor welcher die Daten eines Personen Objekts übernimmt
   * und das Studentenobjekt übernimmt. Die Zähler muss ganz regulär
   * inkrementiert werden.
   *
   * @param person Person dessen Daten übernommen werden.
   */
  explicit Student(Person &person);

  /**
   * @brief Destruktor des Studierenden Objekts. Dieser trägt den Studierenden
   * aus allen Seminaren aus und exmatrikuliert diesen wenn er an einer
   * Universität immatrikuliert ist. Diese Veränderung wird auch allen Seminaren
   * und der Universität mitgeteilt.
   */
  virtual ~Student();

  /**
   * @brief Schreibt den Studierenden in das Seminar ein, falls dieser nicht
   * schon eingeschrieben ist. Das Seminar wird über die Einschreibung ebenfalls
   * benachrichtigt.
   *
   * @param course Das Seminar in welches der Studierende eingeschrieben wird
   */
  void enlist(Course &course);

  /**
   * @brief Trägt den Studierenden aus dem Seminar aus falls dieser eingetragen
   * ist. Das Seminar wird ebenfalls über diese Änderung benachrichtigt.
   *
   * @param course Kurs aus dem der Studierende ausgetragen werden soll
   */
  void leave(Course &course);

  /**
   * @brief Immatrikuliert den Studierenden an der Universität, falls der
   * Studierende bereits an einer Universität immatrikuliert ist wird er an
   * dieser exmatrikuliert. Die Universitäten bekommen diese Veränderungen
   * ebenfalls mitgeteilt.
   *
   * @param university Universität an welcher der Studierende immatrikuliert
   * wird
   */
  void enroll(University &university);

  /**
   * @brief Exmatrikuliert den Studierenden an der Universität, falls er in
   * einer eingeschrieben ist. Die Universität bekommt diese Veränderung
   * ebenfalls mitgeteilt.
   */
  void exmatriculate();

  /**
   * @return std::vector<Course&> Alle Seminare in die der Studierenden
   * eingeschrieben ist.
   */
	std::vector<Course *> &list_courses(){
		return m_courses;
	};

  /*
   * @return University Die Universität in die der Studierende eingeschrieben
   * ist.
   */
  University *university(){ return m_university; };

  const std::int32_t student_number(){return m_student_number;}

  /**
   * @brief Gibt einen String zurück welcher menschenlesbar ist und für die
   * Ausgabe gedacht ist. Das Format ist folgendes:
   *
   * Person::to_string
   *
   * Universität: University::name
   *
   * Matrikelnummer: xxx
   *
   * Anzahl Seminare: xxx
   * Course::name (Für jedes Seminar)
   *
   * @return std::string Menschenlesbare Zusammenfassung des Objektes
   */
  // TODO to_string Methode überschreiben
  std::string to_string() const override;
};

/**
 * @brief Stellt eine Lehrkraft an einer Universität dar und erbt alle Methoden
 * und Daten der Person Klasse (3) und erweitert diese um Spezifische Daten und
 * Verhalten z.B. die to_string Methode welche schon in der Person Klasse
 * implementiert wurde.
 */
class Teacher : public Person {
private:
  std::int32_t m_loan;
  std::vector<Course *> m_courses;
  University *m_university;

public:
  /**
   * Konstruktor welcher ein neues Lehrkraft Objekt erzeugt, in dem der
   * Konstruktor der Basisklasse aufgerufen wird (4), die Validierungslogik muss
   * damit nur einmal geschrieben werden. Der Lohn wird am Anfang auf 0 gesetzt.
   *
   * @throws std::domain_error Wenn die Validierung fehlschlägt. (Vererbtes
   * Verhalten)
   *
   * @param first_name Vorname der Person, muss mindesten 2 Zeichen lang sein
   * und darf nur Buchstaben enthalten.
   * @param last_name Nachname der Person, muss mindesten 2 Zeichen lang sein
   * und darf nur Buchstaben enthalten.
   * @param birthday Gebutstag der Person, darf nicht in der Zukunft liegen.
   * @param address Wohnort der Person.
   */
  // TODO Konstruktor welcher das Lehrkraftobjekt initialisiert
  Teacher(std::string first_name, std::string last_name, std::chrono::system_clock::time_point birthday, Address &place_of_residence);

  /**
   * @brief Kopierkonstruktor welcher die Daten eines Personen Objekts
   * übernimmt. Der Lohn wird initial auf 0 gesetzt.
   *
   * @param person Person dessen Daten übernommen werden.
   */
  explicit Teacher(Person &person);

  /**
   * @brief Destruktor des Lehrkraft Objekts. Dieser zieht die Lehrkraft von
   * allen Seminaren ab falls welche zugeordnet wurden und kündigt die
   * Anstellung bei der Universität falls eine existiert. Die Seminare und die
   * Universität wird davon ebenfalls benachrichtigt.
   */
  virtual ~Teacher();

  /**
   * @brief Weist der Lehrkraft das Seminar zu, falls dies nicht schon geschehen
   * ist. Das Seminar wird ebenfalls darüber informiert.
   *
   * @param course Das Seminar welches der Lehrkraft zu gewiesen wird
   */
  void assign_course(Course &course);

  /**
   * @brief Zieht die Lehrkraft von dem Seminar ab falls diese zugewiesen ist,
   * das Seminar wird ebenfalls über diese Änderrung informiert.
   *
   * @param course Das Seminar von dem der Rückzug erfolgt.
   */
  void resign_course(Course &course);

  /**
   * @brief Stellt eine neue Lehrkraft an der Universität an. Falls diese schon
   * an einer anderen Universität angestellt ist kündigt die Lehrkraft an dieser
   * Universität. Die Universitäten bekommen diese Veränderung ebenfalls
   * mitgeteilt.
   *
   * @throws std::domain_error Wenn das Gehalt weniger als 1000€ beträgt.
   *
   * @param teacher Lehrkraft welche angestellt wird.
   * @param loan Gehalt welches der Lehrkraft gezahlt wird, mindestens 1000€.
   */
  void hire(University &university, std::int32_t loan);

  /**
   * @brief Entlässt die Lehrkraft von der Universität falls diese angestellt
   * ist. Diese Veränderung wird auch der Universität mitgeteilt.
   */
  void lay_off();

  /**
   * @return std::vector<Course&> Alle Seminare welche die Lehrkraft hält.
   */
	std::vector<Course *> &list_courses(){
		return m_courses;
	};

  /*
   * @return University Die Universität an der die Lehrkraft arbeitet.
   */
	University *university(){
		return m_university;
	}

  /**
   * @brief Gibt einen String zurück welcher menschenlesbar ist und für die
   * Ausgabe gedacht ist. Das Format ist folgendes:
   *
   * Person::to_string
   *
   * Universität: University::name
   * Gehalt: xxx
   *
   * Anzahl Seminare: xxx
   * Course::name (Für jedes Seminar)
   *
   * @return std::string Menschenlesbare Zusammenfassung des Objektes
   */
  // TODO to_string Methode überschreiben
  std::string to_string() const override;
};
