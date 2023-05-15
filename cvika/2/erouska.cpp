#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

class CTimeStamp {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
public:
    CTimeStamp(int year, int month, int day, int hour, int minute, int second);
    int get_year() const { return year; }
    int get_month() const { return month; }
    int get_day() const { return day; }
    int get_hour() const { return hour; }
    int get_minute() const { return minute; }
    int get_second() const { return second; }
};

CTimeStamp::CTimeStamp(int year, int month, int day, int hour, int minute, int second)
        : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}


class CContact {
    CTimeStamp timestamp;
    int phone1;
    int phone2;
public:
    CContact(const CTimeStamp &timestamp, int phone1, int phone2) : timestamp(timestamp), phone1(phone1), phone2(phone2) {}
    const CTimeStamp &get_timestamp() const { return timestamp; }
    int get_phone1() const { return phone1; }
    int get_phone2() const { return phone2; }
};

class CEFaceMask {
    vector <CContact> contacts;
public:
    CEFaceMask &addContact(CContact contact);
    vector <int> listContacts(int phone) const;
    vector <int> listContacts(int phone, const CTimeStamp &start, const CTimeStamp &end) const;
};

CEFaceMask &CEFaceMask::addContact(CContact contact) {
    int check1 = contact.get_phone1();
    int check2 = contact.get_phone2();
    for (auto c : contacts) {
        if (((check1 == c.get_phone1()) && (check2 == c.get_phone2())) || ((check1 == c.get_phone2()) && (check2 == c.get_phone1())))
            return *this;
    }
    contacts.push_back(contact);
    return *this;
}

vector<int> CEFaceMask::listContacts(int phone) const {
    vector <int> to_return;
    for (const auto &contact : contacts) {
        if (contact.get_phone1() == phone) {
            int check = contact.get_phone2();
            if (find(to_return.begin(), to_return.end(), check) == to_return.end() && check != phone)
                to_return.push_back(check);
        } else if (contact.get_phone2() == phone) {
            int check = contact.get_phone1();
            if (find(to_return.begin(), to_return.end(), check) == to_return.end() && check != phone)
                to_return.push_back(check);
        }
    }
    return to_return;
}

// took idea of function from here https://stackoverflow.com/questions/2557846/checking-if-parsed-date-is-within-a-date-range
bool isDateInRange(CTimeStamp timestamp, CTimeStamp start, CTimeStamp end){
    int entryTime = timestamp.get_second() + timestamp.get_minute()*10 + timestamp.get_hour()*100 + timestamp.get_day()*1000 + timestamp.get_month()*10000 + timestamp.get_year()*100000;
    int startTime = start.get_second() + start.get_minute()*10 + start.get_hour()*100 + start.get_day()*1000 + start.get_month()*10000 + start.get_year()*100000;
    int endTime = end.get_second() + end.get_minute()*10 + end.get_hour()*100 + end.get_day()*1000 + end.get_month()*10000 + end.get_year()*100000;

    if (entryTime >= startTime && entryTime <= endTime) return true;
    return false;
}

vector<int> CEFaceMask::listContacts(int phone, const CTimeStamp &start, const CTimeStamp &end) const {
    vector <int> to_return;
    for (const auto &contact : contacts) {
        if (contact.get_phone1() == phone) {
            if (isDateInRange(contact.get_timestamp(), start, end)) {
                int check = contact.get_phone2();
                if (find(to_return.begin(), to_return.end(), check) == to_return.end() && check != phone)
                    to_return.push_back(check);
            }
        } else if (contact.get_phone2() == phone) {
            if (isDateInRange(contact.get_timestamp(), start, end)) {
                int check = contact.get_phone1();
                if (find(to_return.begin(), to_return.end(), check) == to_return.end() && check != phone)
                    to_return.push_back(check);
            }
        }
    }
    return to_return;
}


#ifndef __PROGTEST__
int main () {
    CEFaceMask test;
    test.addContact(CContact(CTimeStamp(2021,1,10,12, 40, 10), 123456789, 999888777));
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 12, 12, 40, 10 ), 123456789, 111222333 ) )
            . addContact ( CContact ( CTimeStamp ( 2021, 2, 5, 15, 30, 28 ), 999888777, 555000222 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 2, 21, 18, 0, 0 ), 123456789, 999888777 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), 123456789, 456456456 ) );
    test . addContact ( CContact ( CTimeStamp ( 2021, 2, 1, 0, 0, 0 ), 123456789, 123456789 ) );
    assert ( test . listContacts ( 123456789 ) == (vector<int> {999888777, 111222333, 456456456}) );
    assert ( test . listContacts ( 999888777 ) == (vector<int> {123456789, 555000222}) );
    assert ( test . listContacts ( 191919191 ) == (vector<int> {}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 0 ), CTimeStamp ( 2021, 2, 21, 18, 0, 0 ) ) == (vector<int> {999888777, 111222333, 456456456}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 5, 18, 0, 1 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {999888777, 111222333}) );
    assert ( test . listContacts ( 123456789, CTimeStamp ( 2021, 1, 10, 12, 41, 9 ), CTimeStamp ( 2021, 2, 21, 17, 59, 59 ) ) == (vector<int> {111222333}) );
    return 0;

}
#endif /* __PROGTEST__ */
