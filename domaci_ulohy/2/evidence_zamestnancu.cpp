#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class Person {
    string name;
    string surname;
    string email;
    unsigned int salary;
public:
    Person(const string &name, const string &surname, const string &email, unsigned int salary);
    string get_name() const { return name; }
    string get_surname() const { return surname; }
    string get_email() const { return email;}
    unsigned int get_salary() const { return salary; }
    Person &set_name(const string &name);
    Person &set_surname(const string &surname);
    Person &set_email(const string &email);
    Person &set_salary(unsigned int newSalary);
};

Person::Person(const string &name, const string &surname, const string &email, unsigned int salary)
        : name(name), surname(surname), email(email), salary(salary) {}

Person &Person::set_name(const string &newName) {
    this->name = newName;
    return *this;
}

Person &Person::set_surname(const string &newSurname) {
    this->surname = newSurname;
    return *this;
}

Person &Person::set_email(const string &newEmail) {
    this->email = newEmail;
    return *this;
}

Person &Person::set_salary(unsigned int newSalary) {
    this->salary = newSalary;
    return *this;
}

class CPersonalAgenda {
public:
    CPersonalAgenda() {}
    ~CPersonalAgenda() {}
    bool add(const string &name, const string &surname, const string &email, unsigned int salary);
    bool del(const string &name, const string &surname);
    bool del(const string &email );
    bool changeName(const string &email, const string &newName, const string &newSurname);
    bool changeEmail(const string &name, const string &surname, const string &newEmail);
    bool setSalary(const string &name, const string &surname, unsigned int salary);
    bool setSalary(const string &email, unsigned int salary);
    unsigned int getSalary(const string &name, const string &surname) const;
    unsigned int getSalary(const string &email) const;
    bool getRank(const string &name, const string &surname, int &rankMin, int &rankMax) const;
    bool getRank(const string &email, int &rankMin, int &rankMax) const;
    bool getFirst(string &outName, string &outSurname) const;
    bool getNext(const string &name, const string &surname, string &outName, string &outSurname) const;
private:
    vector <Person> people;
    vector <Person> people_email;
};

bool cmp_names(const Person &p1, const Person &p2) {
    if (p1.get_surname() != p2.get_surname()) return p1.get_surname() < p2.get_surname();
    return p1.get_name() < p2.get_name();
}

bool cmp_emails(const Person &p1, const Person &p2) {
    return p1.get_email() < p2.get_email();
}

// 2n + 2 log n = n
bool CPersonalAgenda::add(const string &name, const string &surname, const string &email, unsigned int salary) {
    Person person(name, surname, email, salary);
    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    auto it_email = lower_bound(people_email.begin(), people_email.end(), person, cmp_emails); // log n
    if (it != people.end() and it_email != people_email.end() and ((it->get_name() == name and it->get_surname() == surname) or it_email->get_email() == email)) return false;
    people.insert(it, person); // n
    people_email.insert(it_email, person); // n
//    people.push_back(person);
//    people_email.push_back(person);
//    sort(people.begin(), people.end(), cmp_names); // n log n
//    sort(people_email.begin(), people_email.end(), cmp_emails); // n log n
    return true;
}

// 2n + 2 log n = n
bool CPersonalAgenda::del(const string &name, const string &surname) {
    Person person(name, surname, "", 0);
    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    if (it != people.end() and it->get_name() == name and it->get_surname() == surname) {
        Person person_email("", "", it->get_email(), 0);
        auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
        people.erase( it); // n
        people_email.erase( it_email); // n
        return true;
    }
    return false;
}

// 2n + 2 log n = n
bool CPersonalAgenda::del(const string &email) {
    Person person_email("", "", email, 0);
    auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
    if (it_email != people_email.end() and it_email->get_email() == email) {
        Person person(it_email->get_name(), it_email->get_surname(), "", 0);
        auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
        people.erase( it); // n
        people_email.erase( it_email); // n
        return true;
    }
    return false;
}

// 2n + 3 log n = n
bool CPersonalAgenda::changeName(const string &email, const string &newName, const string &newSurname) {
    Person person_email("", "", email, 0);
    Person person(newName, newSurname, "", 0);
    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    if (it != people.end() and it->get_email() != email and it->get_name() == newName and it->get_surname() == newSurname) return false;

    auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
    if (it_email != people_email.end() and it_email->get_email() == email) {
        if (it_email->get_name() == newName and it_email->get_surname() == newSurname) return false;
        Person new_person(it_email->get_name(), it_email->get_surname(), "", 0);
        auto it_change = lower_bound(people.begin(), people.end(), new_person, cmp_names); // log n
        it_email->set_name(newName);
        it_email->set_surname(newSurname);
        // !!!
        it_change->set_name(newName);
        it_change->set_surname(newSurname);
        Person tmp = *it_change;
        people.erase(it_change); // n
        people.insert(it, tmp); // n
//        sort(people.begin(), people.end(), cmp_names); // n log n
        return true;
    }
    return false;
}

// 2n + 3 log n = n
bool CPersonalAgenda::changeEmail(const string &name, const string &surname, const string &newEmail) {
    Person person(name, surname, "", 0);
    Person person_email("", "", newEmail, 0);
    auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
    if (it_email != people_email.end() and newEmail == it_email->get_email() and (name != it_email->get_name() or surname != it_email->get_surname())) return false;

    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    if (it != people.end() and it->get_name() == name and it->get_surname() == surname) {
        if (it->get_email() == newEmail) return false;
        Person new_person_email("", "", it->get_email(), 0);
        auto it_email_change = lower_bound(people_email.begin(), people_email.end(), new_person_email, cmp_emails); // log n
        it->set_email(newEmail);
        // !!!
        it_email_change->set_email(newEmail);
        Person tmp = *it_email_change;
        people_email.erase(it_email_change); // n
        people_email.insert(it_email, tmp); // n
//        sort(people_email.begin(), people_email.end(), cmp_emails); // n log n
        return true;
    }
    return false;
}

// 2 log n = log n
bool CPersonalAgenda::setSalary(const string &name, const string &surname, unsigned int salary) {
    Person person(name, surname, "", 0);
    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    if (it != people.end() and it->get_name() == name and it->get_surname() == surname) {
        Person person_email("", "", it->get_email(), 0);
        auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
        it->set_salary(salary);
        it_email->set_salary(salary);
        return true;
    }
    return false;
}

// 2 log n = log n
bool CPersonalAgenda::setSalary(const string &email, unsigned int salary) {
    Person person_email("", "", email, 0);
    auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
    if (it_email != people_email.end() and it_email->get_email() == email) {
        Person person(it_email->get_name(), it_email->get_surname(), "", 0);
        auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
        it->set_salary(salary);
        it_email->set_salary(salary);
        return true;
    }
    return false;
}

// log n
unsigned int CPersonalAgenda::getSalary(const string &name, const string &surname) const {
    Person person(name, surname, "", 0);
    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    if (it != people.end() and it->get_name() == name and it->get_surname() == surname) {
        return it->get_salary();
    }
    return 0;
}

// log n
unsigned int CPersonalAgenda::getSalary(const string &email) const {
    Person person_email("", "", email, 0);
    auto it_email = lower_bound(people_email.begin(), people_email.end(), person_email, cmp_emails); // log n
    if (it_email != people_email.end() and it_email->get_email() == email) {
        return it_email->get_salary();
    }
    return 0;
}

bool CPersonalAgenda::getRank(const string &name, const string &surname, int &rankMin, int &rankMax) const {
    size_t pos = people.size()+1, minimum = 0, maximum = 0;
    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].get_name() == name and people[i].get_surname() == surname) {
            pos = i;
            break;
        }
    }
    if (pos == people.size()+1) return false;
    unsigned int sal = people[pos].get_salary();
    for (size_t i = 0; i < people.size(); ++i) {
        if (i == pos) continue;
        if (people[i].get_salary() < sal) {
            minimum++;
            maximum++;
        }
        if (people[i].get_salary() == sal) maximum++;
    }
    rankMin = minimum;
    rankMax = maximum;
    return true;
}

bool CPersonalAgenda::getRank(const string &email, int &rankMin, int &rankMax) const {
    size_t pos = people.size()+1, minimum = 0, maximum = 0;
    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].get_email() == email) {
            pos = i;
            break;
        }
    }
    if (pos == people.size()+1) return false;
    unsigned int sal = people[pos].get_salary();
    for (size_t i = 0; i < people.size(); ++i) {
        if (i == pos) continue;
        if (people[i].get_salary() < sal) {
            minimum++;
            maximum++;
        }
        if (people[i].get_salary() == sal) maximum++;
    }
    rankMin = minimum;
    rankMax = maximum;
    return true;
}

// 2 = 1
bool CPersonalAgenda::getFirst(string &outName, string &outSurname) const {
    if (people.size() == 0) return false;
//    sort(people.begin(), people.end(), cmp_names);
    outName = people[0].get_name(); // 1
    outSurname = people[0].get_surname(); // 1
    return true;
}

// log n
bool CPersonalAgenda::getNext(const string &name, const string &surname, string &outName, string &outSurname) const {
//    sort(people.begin(), people.end(), cmp_names);
    Person person(name, surname, "", 0);
    auto it = lower_bound(people.begin(), people.end(), person, cmp_names); // log n
    if (name == it->get_name() and surname == it->get_surname() and (it+1) != people.end()) {
        outName = (it+1)->get_name();
        outSurname = (it+1)->get_surname();
        return true;
    }
    return false;
}


#ifndef __PROGTEST__
int main () {
    string outName, outSurname;
    int lo, hi;

    CPersonalAgenda b1;
    assert ( b1 . add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . add ( "John", "Miller", "johnm", 35000 ) );
    assert ( b1 . add ( "Peter", "Smith", "peter", 23000 ) );
    assert ( b1 . getFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( b1 . getNext ( "John", "Smith", outName, outSurname )
             && outName == "Peter"
             && outSurname == "Smith" );
    assert ( ! b1 . getNext ( "Peter", "Smith", outName, outSurname ) );
    assert ( b1 . setSalary ( "john", 32000 ) );
    assert ( b1 . getSalary ( "john" ) ==  32000 );
    assert ( b1 . getSalary ( "John", "Smith" ) ==  32000 );
    assert ( b1 . getRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . getRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . getRank ( "johnm", lo, hi )
             && lo == 2
             && hi == 2 );
    assert ( b1 . setSalary ( "John", "Smith", 35000 ) );
    assert ( b1 . getSalary ( "John", "Smith" ) ==  35000 );
    assert ( b1 . getSalary ( "john" ) ==  35000 );
    assert ( b1 . getRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . getRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . getRank ( "johnm", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . changeName ( "peter", "James", "Bond" ) );
    assert ( b1 . getSalary ( "peter" ) ==  23000 );
    //
    assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . getSalary ( "Peter", "Smith" ) ==  0 );
    assert ( b1 . getFirst ( outName, outSurname )
             && outName == "James"
             && outSurname == "Bond" );
    assert ( b1 . getNext ( "James", "Bond", outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . getNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . changeEmail ( "James", "Bond", "james" ) );
    assert ( b1 . getSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . getSalary ( "james" ) ==  23000 );
    assert ( b1 . getSalary ( "peter" ) ==  0 );
    assert ( b1 . del ( "james" ) );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 0
             && hi == 1 );
    assert ( b1 . del ( "John", "Miller" ) );
    assert ( b1 . getRank ( "john", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . getFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . getNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . del ( "john" ) );
    assert ( ! b1 . getFirst ( outName, outSurname ) );
    assert ( b1 . add ( "John", "Smith", "john", 31000 ) );
    assert ( b1 . add ( "john", "Smith", "joHn", 31000 ) );
    assert ( b1 . add ( "John", "smith", "jOhn", 31000 ) );

    CPersonalAgenda b2;
    assert ( ! b2 . getFirst ( outName, outSurname ) );
    assert ( b2 . add ( "James", "Bond", "james", 70000 ) );
    assert ( b2 . add ( "James", "Smith", "james2", 30000 ) );
    assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( ! b2 . add ( "James", "Bond", "james3", 60000 ) );
    assert ( ! b2 . add ( "Peter", "Bond", "peter", 50000 ) );
    assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . setSalary ( "Joe", "Black", 90000 ) );
    assert ( ! b2 . setSalary ( "joe", 90000 ) );
    assert ( b2 . getSalary ( "Joe", "Black" ) ==  0 );
    assert ( b2 . getSalary ( "joe" ) ==  0 );
    assert ( ! b2 . getRank ( "Joe", "Black", lo, hi ) );
    assert ( ! b2 . getRank ( "joe", lo, hi ) );
    assert ( ! b2 . changeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . changeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . del ( "Joe", "Black" ) );
    assert ( ! b2 . del ( "joe" ) );
    assert ( ! b2 . changeName ( "james2", "James", "Bond" ) );
    assert ( ! b2 . changeEmail ( "Peter", "Smith", "james" ) );
    assert ( ! b2 . changeName ( "peter", "Peter", "Smith" ) );
    assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter" ) );
    assert ( b2 . del ( "Peter", "Smith" ) );
    assert ( ! b2 . changeEmail ( "Peter", "Smith", "peter2" ) );
    assert ( ! b2 . setSalary ( "Peter", "Smith", 35000 ) );
    assert ( b2 . getSalary ( "Peter", "Smith" ) ==  0 );
    assert ( ! b2 . getRank ( "Peter", "Smith", lo, hi ) );
    assert ( ! b2 . changeName ( "peter", "Peter", "Falcon" ) );
    assert ( ! b2 . setSalary ( "peter", 37000 ) );
    assert ( b2 . getSalary ( "peter" ) ==  0 );
    assert ( ! b2 . getRank ( "peter", lo, hi ) );
    assert ( ! b2 . del ( "Peter", "Smith" ) );
    assert ( ! b2 . del ( "peter" ) );
    assert ( b2 . add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( b2 . getSalary ( "peter" ) ==  40000 );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
