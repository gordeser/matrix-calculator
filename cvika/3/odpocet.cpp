#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

class CTimeTester;
#endif /* __PROGTEST__ */

class CTime {
    int m_Hour;
    int m_Minute;
    int m_Second;
public:
    // constructor, destructor
    CTime(): m_Hour(0), m_Minute(0), m_Second(0) {}
    CTime(int hour, int minute);
    CTime(int hour, int minute, int second);
    CTime(const CTime& time) : m_Hour(time.m_Hour), m_Minute(time.m_Minute), m_Second(time.m_Second) {}
    CTime &operator = (const CTime &time);
    ~CTime() {}

    // arithmetic operators
    CTime operator + (int seconds) const;
    CTime &operator += (int seconds);
    CTime operator - (int seconds) const;
    CTime &operator -= (int seconds);
    int operator - (const CTime &time) const;
    CTime &operator ++ (); // prefix increment
    CTime operator ++ (int); // postfix increment
    CTime &operator -- (); // prefix decrement
    CTime operator -- (int); // postfix decrement

    // comparison operators
    bool operator < (const CTime& time) const;
    bool operator <= (const CTime& time) const;
    bool operator > (const CTime& time) const;
    bool operator >= (const CTime& time) const;
    bool operator == (const CTime& time) const;
    bool operator != (const CTime& time) const;

    // output operator
    friend ostream &operator << (ostream &out, const CTime &time);

    friend class ::CTimeTester;
};

CTime::CTime(int hour, int minute) {
    if (hour < 0 or hour > 23 or minute < 0 or minute > 59)
        throw invalid_argument("Invalid arguments");
    this->m_Hour = hour;
    this->m_Minute = minute;
    this->m_Second = 0;
}

CTime::CTime(int hour, int minute, int second) {
    if (hour < 0 or hour > 23 or minute < 0 or minute > 59 or second < 0 or second > 59)
        throw invalid_argument("Invalid arguments");
    this->m_Hour = hour;
    this->m_Minute = minute;
    this->m_Second = second;
}

CTime &CTime::operator=(const CTime &time) {
    this->m_Hour = time.m_Hour;
    this->m_Minute = time.m_Minute;
    this->m_Second = time.m_Second;
    return *this;
}

CTime CTime::operator+(int seconds) const{
    CTime time = *this;
    int tmp = time.m_Second + time.m_Minute*60 + time.m_Hour*60*60 + seconds;
    while (tmp < 0) {tmp += 86400;}
    tmp %= 86400;
    time.m_Hour = tmp / (60*60);
    tmp %= (60*60);
    time.m_Minute = tmp / 60;
    tmp %= 60;
    time.m_Second = tmp;
    return time;
}

CTime &CTime::operator+=(int seconds) {
    int tmp = this->m_Second + this->m_Minute*60 + this->m_Hour*60*60 + seconds;
    while (tmp < 0) {tmp += 86400;}
    tmp %= 86400;
    this->m_Hour = tmp / (60*60);
    tmp %= (60*60);
    this->m_Minute = tmp / 60;
    tmp %= 60;
    this->m_Second = tmp;
    return *this;
}

CTime operator+(int seconds, CTime& time) {
    CTime result = time;
    result += seconds;
    return result;
}

CTime operator+(int seconds, const CTime& time) {
    CTime result = time;
    result += seconds;
    return result;
}

CTime CTime::operator-(int seconds) const {
    CTime time = *this;
    int tmp = time.m_Second + time.m_Minute*60 + time.m_Hour*60*60 - seconds;
    while (tmp < 0) {tmp += 86400;}
    tmp %= 86400;
    time.m_Hour = tmp / (60*60);
    tmp %= (60*60);
    time.m_Minute = tmp / 60;
    tmp %= 60;
    time.m_Second = tmp;
    return time;
}

CTime &CTime::operator-=(int seconds) {
    long long tmp = this->m_Second + this->m_Minute*60 + this->m_Hour*60*60 - seconds;
    while (tmp < 0) {tmp += 86400;}
    tmp %= 86400;
    this->m_Hour = tmp / (60*60);
    tmp %= (60*60);
    this->m_Minute = tmp / 60;
    tmp %= 60;
    this->m_Second = tmp;
    return *this;
}

int CTime::operator-(const CTime &time) const {
    long long first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    long long second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return min(abs(second-first), 86400-abs(second-first));
}

CTime &CTime::operator++() {
    int tmp = this->m_Second + this->m_Minute*60 + this->m_Hour*60*60 + 1;
    while (tmp < 0) {tmp += 86400;}
    tmp %= 86400;
    this->m_Hour = tmp / (60*60);
    tmp %= (60*60);
    this->m_Minute = tmp / 60;
    tmp %= 60;
    this->m_Second = tmp;
    return *this;
}

CTime CTime::operator++(int) {
    CTime time = *this;
    ++(*this);
    return time;
}

CTime &CTime::operator--() {
    int tmp = this->m_Second + this->m_Minute*60 + this->m_Hour*60*60 - 1;
    while (tmp < 0) {tmp += 86400;}
    tmp %= 86400;
    this->m_Hour = tmp / (60*60);
    tmp %= (60*60);
    this->m_Minute = tmp / 60;
    tmp %= 60;
    this->m_Second = tmp;
    return *this;
}

CTime CTime::operator--(int) {
    CTime time = *this;
    --(*this);
    return time;
}

bool CTime::operator<(const CTime &time) const {
    int first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    int second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return first < second;
}

bool CTime::operator<=(const CTime &time) const {
    int first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    int second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return first <= second;
}

bool CTime::operator>(const CTime &time) const {
    int first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    int second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return first > second;
}

bool CTime::operator>=(const CTime &time) const {
    int first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    int second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return first >= second;
}

bool CTime::operator==(const CTime &time) const {
    int first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    int second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return first == second;
}

bool CTime::operator!=(const CTime &time) const {
    int first = this->m_Hour*60*60 + this->m_Minute*60 + this->m_Second;
    int second = time.m_Hour*60*60 + time.m_Minute*60 + time.m_Second;
    return first != second;
}

ostream &operator<<(ostream &out, const CTime &time) {
    out << setw(2) << time.m_Hour << ":";
    out << setfill('0') << setw(2) << time.m_Minute << ":";
    out << setfill('0') << setw(2) << time.m_Second;
    return out;
}


#ifndef __PROGTEST__
struct CTimeTester
{
    static bool test ( const CTime & time, int hour, int minute, int second )
    {
        return time.m_Hour == hour
               && time.m_Minute == minute
               && time.m_Second == second;
    }
};

#include <cassert>
#include <sstream>

int main () {
    CTime kek {12, 30};

    CTime a { 12, 30 };
    assert( CTimeTester::test( a, 12, 30, 0 ) );
    CTime lol = 10 + kek;
    cout << lol;

    CTime b { 13, 30 };
    assert( CTimeTester::test( b, 13, 30, 0 ) );

    assert( b - a == 3600 );
    assert( CTimeTester::test( a + 60, 12, 31, 0 ) );
    assert( CTimeTester::test( a - 60, 12, 29, 0 ) );

    assert( a < b );
    assert( a <= b );
    assert( a != b );
    assert( !( a > b ) );
    assert( !( a >= b ) );
    assert( !( a == b ) );

    while ( ++a != b );
    assert( a == b );

    std::ostringstream output;
    assert( static_cast<bool>( output << a ) );
    assert( output.str() == "13:30:00" );

    assert( a++ == b++ );
    assert( a == b );

    assert( --a == --b );
    assert( a == b );

    assert( a-- == b-- );
    assert( a == b );

    return 0;
}
#endif /* __PROGTEST__ */
