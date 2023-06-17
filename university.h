
#pragma once
#include "traits.h"
#include "persons.h"
#include <stdexcept>
#include <vector>

class Address;
class Course;
class Student;
class Teacher;

/**
 * @brief Universität welche alle ihr untergeordneten Objekte wie
 * Lehrkräfte, Studierende und Seminare über öffentlich Methoden
 * verwalten. Dies geschiet über die öffentlichen Methoden der Klasse, welche in
 * der Implementierung die öffentlichen Methoden der verwalteten Klassen nutzt.
 * (1)
 *
 * Die Klasse erbt die von der abstrakten Klasse Display die
 * Spezifikation der to_string Methode welche implementiert
 * werden muss. (3)
 */
class University : public Displayable {
private:
  std::string m_name;
  Address &m_address;
  std::vector<Student *> m_students;
  std::vector<Teacher *> m_teachers;
  std::vector<Course> m_courses;

public:
  /**
   * @brief Instanziert ein neues University Objekt.
   *
   * @param name Name der Universität, dieser muss mindesten 10 Zeichen lang
   * sein.
   * @param address Adresse der Universität.
   */
  University(const std::string &name, Address &address);

  /**
   * @brief Destruktor der Universität. Dieser entlässt alle Lehrkräfte und
   * exmatrikuliert alle Studierenden. Diese Veränderung wird allen Lehrkräften
   * und Studierenden mitgeteilt.
   */
  virtual ~University();

  /**
   * @brief Schreibt einen neuen Studierenden ein falls diese nicht schon an der
   * Universität ist, dieser bekommt auch seine neue Universität zugewiesen.
   *
   * @param student Studierender welcher immatrikuliert wird.
   */
  void enroll(Student &student);

  /**
   * @brief Exmatrikuliert den Studierenden falls dieser an der Universität
   * eingeschrieben ist. Der Studierende bekommt diese Veränderung mitgeteilt.
   *
   * @param student Studierender welcher exmatrikuliert wird.
   */
  void exmatriculate(Student &student);

  /**
   * @brief Stellt eine neue Lehrkraft an der Universität an falls diese nicht
   * schon an der Universität ist, diese bekommt seine neue Universität
   * zugewiesen.
   *
   * @param teacher Lehrkraft welche angestellt wird.
   * @param loan Gehalt welches der Lehrkraft gezahlt wird.
   */
  void hire(Teacher &teacher, std::int32_t loan);

  /**
   * @brief Entlässt eine Lehrkraft von der Universität falls diese angestellt
   * ist. Diese Veränderung wird auch der Lehrkraft mitgeteilt.
   *
   * @param teacher Lehrkraft welche entlassen wird.
   */
  void lay_off(Teacher &teacher);

  /**
   * @brief Erstellt ein neues Seminar aus den übergebenen Argumenten und
   * speichert dieses intern ab, falls dieser nicht schon existiert und weist
   * der Lehrkraft den neuen Kurs zu.
   *
   * @param name Der Name des Seminars
   * @param teacher Die Lehrkraft welche des Seminar hällt.
   * @return Course& Referenz auf das neue Seminar
   */
  Course &offer_course(const std::string &name, Teacher &teacher);

  /**
   *  @return Der Name der Universität.
   */
  std::string name() const{return m_name;};

  /**
   * @return std::vector<Teacher*>& Alle Lehrkräfte der Universität.

   */
	std::vector<Teacher *> &list_teachers(){
		return m_teachers;
	};

  /**
   * @return std::vector<Student*>& Alle Studierenden der Universität.
   */
	std::vector<Student *> &list_students(){
		return m_students;
	}

  /**
   * @return std::vector<Course>& Alle Seminare der Universität.
   */
	std::vector<Course> &list_courses(){
		return m_courses;
	}

  /**
   * @brief Gibt einen String zurück welcher menschenlesbar ist und für die
   * Ausgabe gedacht ist. Das Format ist folgendes:
   *
   * Universität: University::name
   *
   * Address::to_string
   *
   * Anzahl Studierender: xxx
   * Student::first_name Student::last_name (Für alle Studierenden)
   *
   * Anzahl Lehrkräfte: xxx
   * Teacher::first_name Teacher::last_name (Für alle Lehrkräfte)
   *
   * Anzahl Seminare: xxx
   * Course::name (Für alle Seminare)
   *
   * @return std::string Menschenlesbare Zusammenfassung des Objektes
   */
  // TODO to_string Methode überschreiben
  std::string to_string() const override;
};

/**
 * @brief Seminar welches an einer Hochschule gehalten wird. Die Klasse wird
 * durch die Klasse University instanziert, da diese in der Verantwortung ist
 * die Seminare zu verwalten. Nach der Instanzierung können neue Studiernde dem
 * Seminar hinzugefügt werden. Die Lehrkraft kann ebenfalls ausgetauscht werden
 * (1).
 *
 * Die Klasse erbt die von der abstrakten Klasse Display die Spezifikation der
 * to_string Methode welche implementiert werden muss. (3)
 */
class Course : public Displayable {
private:
  std::string m_name;
  std::vector<Student *> m_students;
  Teacher *m_teacher;

public:
  /**
   * @brief Erzeugt das Course Objekt mit gültigen Daten, falls die Daten
   * ungültig sind wird im Konstruktor eine Exception vom Typ std::domain_error
   * geworfen.
   *
   * @throws std::domain_error Wenn die Validierung fehlschlägt.
   *
   * @param name Der Name des Seminars, dieser darf nicht leer sein und muss
   * mindesten 10 Zeichen lang sein.
   */
  Course(const std::string &name);

  /**
   * @brief Destruktor des Seminars. Dieser zieht die Lehrkräft aus dem Kurs ab
   * und trägt alle Studierenden aus. Diese Veränderung wird auch der Lehrkräft
   * und den Studierenden mitgeteilt.
   */
  virtual ~Course();

  /**
   * @brief Schreibt einen Studierenden in das Seminar ein, falls dieser nicht
   * schon eingeschrieben ist, der Studierende wird ebenfalls darüber
   * benachrichtigt das er eingeschrieben wird.
   *
   * @param student Der einzuschreibende Student.
   */
  void enlist(Student &student);

  /**
   * @brief Trägt einen Studierenden aus dem Seminar aus, falls dieser
   * eingeschrieben ist. Der Studierende wird ebenfalls darüber benachrichtigt
   * das er ausgetragen wurde.
   *
   * @param student Der Student welcher ausgetragen wird.
   */
  void leave(Student &student);

  /**
   * @brief Weist die Lehrkraft dem Seminar zu. Die Lehrkraft wird ebenfalls
   * darüber benachrichtigt das sie zugewiesen wurde. Falls eine Lehrkraft
   * bereits für den Kurs zuständig ist wird diese von diesem Kurs
   * zurückgezogen.
   *
   * @param teacher Die Lehrkraft welche für das Seminar zuständig ist.
   */
  void assign_teacher(Teacher &teacher);

  /**
   * @brief Zieht die aktuelle Lehrkraft vom Kurs zurück, falls eine zugewiesen
   * war. Die Lehrkraft wird ebenfalls über die Veränderung benachrichtigt.
   */
  void resign_teacher();

  /**
   * @return std::vector<Student&> Alle eingeschriebenen Studierenden des
   * Kurses.
   */
  std::vector<Student *> &list_students();

  /**
   * @return Teacher& Die Lehrkraft welche für den Kurs verantwortlich
   * ist.
   */
  Teacher *teacher();

  /**
   * @return Der Name des Kurses.
   */
	std::string name() const{
		return m_name;
	}

  /**
   * @brief Gibt einen String zurück welcher menschenlesbar ist und für die
   * Ausgabe gedacht ist. Er soll folgendes Format haben.
   *
   * Seminar: Name
   *
   * Lehrkraft: Teacher::first_name Teacher::last_name
   *
   * Anzahl Studierende: xxx
   * Student::first_name Student::last_name (Für alle Studierenden)
   *
   * @return std::string Menschenlesbare Zusammenfassung des Objektes
   */
  // TODO to_string Methode überschreiben
  std::string to_string() const override;
};

/**
 * @brief Einfache Aggregationsklasse für eine Adresse, diese ist nach dem
 * Erstellen mit Hilfe des Konstruktors von Außen nur noch lesbar (immutable).
 * Dies wird dadurch erreicht das alle Methoden als const Methoden definiert
 * sind weshalb Sie die eigenen Membervariablen nicht verändert werden dürfen,
 * zusätzlich sind alle Refernzen auf die inneren Daten ebenfalls const weshalb
 * diese auch außerhalb der Klasse nicht verändert werden dürfen (1).
 *
 * Die Klasse erbt die von der abstrakten Klasse Display die Spezifikation der
 * to_string Methode welche implementiert werden muss. (3)
 */
class Address : public Displayable {
private:
  std::string m_street;
  std::int32_t m_street_no;
  std::string m_zipcode;
  std::string m_city;
  std::string m_country;


public:
  /**
   * @brief Erzeugt das Address Objekt mit gültigen Daten, falls die Daten
   * ungültig sind wird im Konstruktor eine Exception vom Typ std::domain_error
   * geworfen.
   *
   * @throws std::domain_error Wenn die Validierung fehlschlägt.
   *
   * @param street Der Straßenname, dieser darf nicht leer sein und muss
   * mindestens 10 Zeichen lang sein.
   *
   * @param streetNo Die Hausnummer, diese muss größer als 0 sein.
   *
   * @param zipcode Die Postleitzahl, diese muss 5 Zeichen lang sein und darf
   * nur Zahlen enthalten.
   *
   * @param city Der Stadtname, dieres darf nicht leer sein und muss mindestens
   * 3 Zeichen lang sein.
   *
   * @param country Der Name des Landes, dieser darf nicht leer sein und muss
   * mindestens 3 Zeichen lang sein.
   */
  // TODO Konstruktor welcher das Address Objekt initialisiert und dabei die
  // Daten validiert.

  Address(std::string street, std::int32_t street_no, std::string zipcode,
  std::string city, std::string country);

  /**
   * @brief Gibt eine Referenz auf den Straßennamen zurück. Diese ist nicht
   * veränderlich.
   *
   * @return const std::string Der Straßenname
   */
  const std::string &street() { return m_street; }

  /**
   * @brief Gibt eine Referenz auf die Hausnummer zurück. Diese ist nicht
   * veränderlich.
   *
   * @return const std::int32_t Die Hausnummer.
   */
  const std::int32_t &street_no() const { return m_street_no; }

  /**
   * @brief Gibt eine Referenz auf die Postleitzahl zurück. Diese ist nicht
   * veränderlich.
   *
   * @return const std::string& Die Postleitzahl
   */
  const std::string &zip_code() const { return m_zipcode; }

  /**
   * @brief Gibt eine Referenz auf den Stadtnamen zurück.
   *
   * @return const std::string Der Stadtname.
   */
  const std::string &city() const { return m_city; }

  /**
   * @brief Gibt eine Referenz auf den Namen des Landes zurück.
   *
   * @return const std::string Der Name des Landes.
   */
  const std::string &country() const { return m_country; }

  /**
   * @brief Gibt einen String zurück welcher menschenlesbar ist und für die
   * Ausgabe gedacht ist. Das Format soll in dieser Form erfolgen, die Trennung
   * erfolgt mit einem Leerzeichen und Zeilenumbruch am Ende der Zeile:
   *
   * Straßenname Hausnummer
   * Postleitzahl S&adt
   * Name des Landes
   *
   * @return std::string Menschenlesbare Zusammenfassung des Objektes
   */
  // TODO to_string Methode überschreiben
  std::string to_string() const override;
};
