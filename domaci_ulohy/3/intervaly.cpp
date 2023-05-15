#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

// uncomment if your code implements initializer lists
#define EXTENDED_SYNTAX

class CRangeList;

class CRange {
    long long lo;
    long long hi;
public:
    // constructor
    CRange(long long lo, long long hi);
    long long get_lo() const { return lo; }
    CRange &set_hi(long long hi);
    long long get_hi() const { return hi; }
    bool operator == (const CRange &r) const;
    bool operator != (const CRange &r) const;
    friend CRangeList operator + (const CRange &r1, const CRange &r2);
    friend CRangeList operator - (const CRange &r1, const CRange &r2);
    friend CRangeList operator + (const CRange &range, const CRangeList &list);
    friend CRangeList operator - (const CRange &range, const CRangeList &list);
};


CRange::CRange(long long lo, long long hi) {
    if (lo > hi)
        throw logic_error("Error");
    this->lo = lo;
    this->hi = hi;
}

CRange &CRange::set_hi(long long int set_hi) {
    this->hi = set_hi;
    return *this;
}

bool CRange::operator==(const CRange &r) const {
    return this->get_lo() == r.get_lo() and this->get_hi() == r.get_hi();
}

bool CRange::operator!=(const CRange &r) const {
    return this->get_lo() != r.get_lo() or this->get_hi() != r.get_hi();
}

class CRangeList {
    vector <CRange> ranges;
public:
    // constructor
    CRangeList() {}
    ~CRangeList() {}
    CRangeList(const CRangeList &list);

    // extended syntax
    CRangeList(initializer_list<CRange> list); // list initialization
    vector <CRange>::iterator begin(); // for in loop
    vector <CRange>::iterator end(); // for in loop

    // includes long long / range
    bool includes (long long num) const;
    bool includes (const CRange &range) const;

    // += range / range list
    CRangeList operator + (const CRange &range) const; // must be n
    CRangeList operator + (const CRangeList &new_list) const; // must be n^2
    CRangeList &operator += (const CRange &range);
    CRangeList &operator += (const CRangeList &list);

    // -= range / range list
    CRangeList operator - (const CRange &range) const;
    CRangeList operator - (const CRangeList &new_list) const;
    CRangeList operator -= (const CRange &range);
    CRangeList operator -= (const CRangeList &list);

    // = range / range list
    CRangeList &operator = (const CRange &range);
    CRangeList &operator = (const CRangeList &list);

    // operator ==
    bool operator == (const CRangeList &list) const;

    // operator !=
    bool operator != (const CRangeList &list) const;

    // operator <<
    friend ostream &operator << (ostream &out, const CRangeList &list);
    friend ostream &operator << (ostream &out, const CRange &range);
};

bool cmp(const CRange &r1, const CRange &r2) {
    if (r1.get_lo() != r2.get_lo()) return r1.get_lo() < r2.get_lo();
    return r1.get_hi() < r2.get_hi();
}

CRangeList::CRangeList(const CRangeList &list) {
    this->ranges = list.ranges;
}

// took from here
// https://en.cppreference.com/w/cpp/language/list_initialization
// https://en.cppreference.com/w/cpp/utility/initializer_list
CRangeList::CRangeList(initializer_list<CRange> list) {
    for (const auto &range : list) {
        *this = *this + range;
    }
}

// thanks for inner-CLion warnings
// and
// https://en.cppreference.com/w/cpp/language/range-for
vector<CRange>::iterator CRangeList::begin() {
    return ranges.begin();
}

vector<CRange>::iterator CRangeList::end() {
    return ranges.end();
}

// check with upper/lower bound
bool CRangeList::includes(long long int num) const {
    if (this->ranges.size() == 0) return false;

    CRange tmp(num, num);
    auto it = upper_bound(this->ranges.begin(), this->ranges.end(), tmp, cmp);

    if (it == this->ranges.end()) {
        bool check1 = ((it-1)->get_lo() <= num and num <= (it-1)->get_hi());

        if (check1)
            return true;

    } else if (it == this->ranges.begin()) {
        bool check1 = (it->get_lo() <= num and num <= it->get_hi());
        bool check2 = ((it+1) != this->ranges.end() and (it+1)->get_lo() <= num and num <= (it+1)->get_hi());

        if (check1 or check2)
            return true;

    } else {
        bool check1 = ((it-1)->get_lo() <= num and num <= (it-1)->get_hi());
        bool check2 = (it->get_lo() <= num and num <= it->get_hi());
        bool check3 = ((it+1) != this->ranges.end() and (it+1)->get_lo() <= num and num <= (it+1)->get_hi());

        if (check1 or check2 or check3)
            return true;

    }
    return false;
}

// check with upper/lower bound
bool CRangeList::includes(const CRange &range) const {
    if (this->ranges.size() == 0) return false;

    auto it = lower_bound(this->ranges.begin(), this->ranges.end(), range, cmp);

    if (it == this->ranges.end()) {
        bool check1 = ((it-1)->get_lo() <= range.get_lo() and range.get_hi() <= (it-1)->get_hi());

        if (check1)
            return true;
    } else if (it == this->ranges.begin()) {
        bool check1 = (it->get_lo() <= range.get_lo() and range.get_hi() <= it->get_hi());
        bool check2 = ((it+1) != this->ranges.end() and (it+1)->get_lo() <= range.get_lo() and (it+1)->get_hi() <= (it+1)->get_hi());

        if (check1 or check2)
            return true;
    } else {
        bool check1 = ((it-1)->get_lo() <= range.get_lo() and range.get_hi() <= (it-1)->get_hi());
        bool check2 = (it->get_lo() <= range.get_lo() and range.get_hi() <= it->get_hi());
        bool check3 = ((it+1) != this->ranges.end() and (it+1)->get_lo() <= range.get_lo() and range.get_hi() <= (it+1)->get_hi());

        if (check1 or check2 or check3)
            return true;
    }
    return false;
}

CRangeList CRangeList::operator+(const CRange &range) const {
    CRangeList list = *this;

    auto it = lower_bound(list.ranges.begin(), list.ranges.end(), range, cmp);
    list.ranges.insert(it, range);

    size_t size = list.ranges.size();
    for (size_t i = 1; i < size; ++i) { // o(n)
        auto &prev = list.ranges[i-1];
        auto &curr = list.ranges[i];

        long long hi_prev = prev.get_hi() + 1;
        long long lo_curr = curr.get_lo();
        if (hi_prev == LLONG_MIN) // if there is overflow
            hi_prev = LLONG_MAX;

        if (hi_prev >= lo_curr) {
            prev.set_hi(max(prev.get_hi(), curr.get_hi()));
            list.ranges.erase(list.ranges.begin()+i);
            i--;
            size = list.ranges.size();
        }
    }
    return list;
}

CRangeList CRangeList::operator+(const CRangeList &new_list) const {
    CRangeList list = *this;
    for (const auto &range : new_list.ranges) {
        auto it = lower_bound(list.ranges.begin(), list.ranges.end(), range, cmp);
        list.ranges.insert(it, range);

        size_t size = list.ranges.size();
        for (size_t i = 1; i < size; ++i) {
            auto &prev = list.ranges[i-1];
            auto &curr = list.ranges[i];

            long long hi_prev = prev.get_hi() + 1;
            long long lo_curr = curr.get_lo();
            if (hi_prev == LLONG_MIN) // if there is overflow
                hi_prev = LLONG_MAX;

            if (hi_prev >= lo_curr) {
                prev.set_hi(max(prev.get_hi(), curr.get_hi()));
                list.ranges.erase(list.ranges.begin()+i);
                i--;
                size = list.ranges.size();
            }
        }
    }
    return list;
}

// make this shit without using + operator
CRangeList &CRangeList::operator+=(const CRange &range) {
    auto it = lower_bound((*this).ranges.begin(), (*this).ranges.end(), range, cmp);
    (*this).ranges.insert(it, range);

    size_t size = (*this).ranges.size();
    for (size_t i = 1; i < size; ++i) {
        auto &prev = (*this).ranges[i-1];
        auto &curr = (*this).ranges[i];

        long long hi_prev = prev.get_hi() + 1;
        long long lo_curr = curr.get_lo();
        if (hi_prev == LLONG_MIN) // if there is overflow
            hi_prev = LLONG_MAX;

        if (hi_prev >= lo_curr) {
            prev.set_hi(max(prev.get_hi(), curr.get_hi()));
            (*this).ranges.erase((*this).ranges.begin()+i);
            i--;
            size = (*this).ranges.size();
        }
    }
    return *this;
}

CRangeList &CRangeList::operator+=(const CRangeList &new_list) {
    for (const auto &range : new_list.ranges) {
        auto it = lower_bound((*this).ranges.begin(), (*this).ranges.end(), range, cmp);
        (*this).ranges.insert(it, range);

        size_t size = (*this).ranges.size();
        for (size_t i = 1; i < size; ++i) {
            auto &prev = (*this).ranges[i - 1];
            auto &curr = (*this).ranges[i];

            long long hi_prev = prev.get_hi() + 1;
            long long lo_curr = curr.get_lo();
            if (hi_prev == LLONG_MIN) // if there is overflow
                hi_prev = LLONG_MAX;

            if (hi_prev >= lo_curr) {
                prev.set_hi(max(prev.get_hi(), curr.get_hi()));
                (*this).ranges.erase((*this).ranges.begin() + i);
                i--;
                size = (*this).ranges.size();
            }
        }
    }
    return *this;
}

CRangeList CRangeList::operator-(const CRange &range) const {
    CRangeList list;
    for (const auto &r : this->ranges) {

        // it is fully intersected (5)
        if (r.get_lo() >= range.get_lo() && r.get_hi() <= range.get_hi())
            continue;

            // they are equal (4)
        else if (r.get_lo() == range.get_lo() && r.get_hi() == range.get_hi())
            continue;

            // no intersection (0)
        else if (range.get_hi() < r.get_lo() or r.get_hi() < range.get_lo())
            list += r;

            // full intersection (1)
        else if (r.get_lo() < range.get_lo() and range.get_hi() < r.get_hi()) {
            CRange r1(r.get_lo(), range.get_lo()-1), r2(range.get_hi()+1, r.get_hi());
            list += r1 + r2;
        }

            // partial intersection left-side (3)
        else if (range.get_lo() <= r.get_lo() and range.get_hi() <= r.get_hi()) {
            CRange r1(range.get_hi()+1, r.get_hi());
            list += r1;
        }
            // partial intersection right-side (2)
        else if (range.get_lo() >= r.get_lo() and r.get_hi() <= range.get_hi()) {
            CRange r1(r.get_lo(), range.get_lo()-1);
            list += r1;
        }
    }

    // try to make merge intervals here
    size_t size = list.ranges.size();
    for (size_t i = 1; i < size; ++i) { // o(n)
        auto &prev = list.ranges[i-1];
        auto &curr = list.ranges[i];

        long long hi_prev = prev.get_hi() + 1;
        long long lo_curr = curr.get_lo();
        if (hi_prev == LLONG_MIN) // if there is overflow
            hi_prev = LLONG_MAX;

        if (hi_prev >= lo_curr) {
            prev.set_hi(max(prev.get_hi(), curr.get_hi()));
            list.ranges.erase(list.ranges.begin()+i);
            i--;
            size = list.ranges.size();
        }
    }
    return list;
}

CRangeList CRangeList::operator-(const CRangeList &new_list) const {
    CRangeList list = *this;
    for (const auto &range : new_list.ranges)
        for (const auto &r : this->ranges) {

            // it is fully intersected (5)
            if (r.get_lo() >= range.get_lo() && r.get_hi() <= range.get_hi())
                continue;

                // they are equal (4)
            else if (r.get_lo() == range.get_lo() && r.get_hi() == range.get_hi())
                continue;

                // no intersection (0)
            else if (range.get_hi() < r.get_lo() or r.get_hi() < range.get_lo())
                list += r;

                // full intersection (1)
            else if (r.get_lo() < range.get_lo() and range.get_hi() < r.get_hi()) {
                CRange r1(r.get_lo(), range.get_lo()-1), r2(range.get_hi()+1, r.get_hi());
                list += r1 + r2;
            }

                // partial intersection left-side (3)
            else if (range.get_lo() <= r.get_lo() and range.get_hi() <= r.get_hi()) {
                CRange r1(range.get_hi()+1, r.get_hi());
                list += r1;
            }
                // partial intersection right-side (2)
            else if (range.get_lo() >= r.get_lo() and r.get_hi() <= range.get_hi()) {
                CRange r1(r.get_lo(), range.get_lo()-1);
                list += r1;
            }
        }

    size_t size = list.ranges.size();
    for (size_t i = 1; i < size; ++i) { // o(n)
        auto &prev = list.ranges[i-1];
        auto &curr = list.ranges[i];

        long long hi_prev = prev.get_hi() + 1;
        long long lo_curr = curr.get_lo();
        if (hi_prev == LLONG_MIN) // if there is overflow
            hi_prev = LLONG_MAX;

        if (hi_prev >= lo_curr) {
            prev.set_hi(max(prev.get_hi(), curr.get_hi()));
            list.ranges.erase(list.ranges.begin()+i);
            i--;
            size = list.ranges.size();
        }
    }
    return list;
}

CRangeList CRangeList::operator-=(const CRange &range) {
    *this = *this - range;
    return *this;
}

CRangeList CRangeList::operator-=(const CRangeList &new_list) {
    if (this == &new_list) *this = CRangeList();
    else
        for (const auto &range : new_list.ranges)
            *this = *this - range;
    return *this;
}

CRangeList &CRangeList::operator=(const CRange &range) {
    this->ranges.clear();
    this->ranges.push_back(range);
    return *this;
}

CRangeList &CRangeList::operator=(const CRangeList &list) {
    if (this != &list) this->ranges = list.ranges;
    return *this;
}

bool CRangeList::operator==(const CRangeList &list) const {
    if (this->ranges.size() != list.ranges.size()) return false;

    for (size_t i = 0; i < this->ranges.size(); ++i)
        if (this->ranges[i] != list.ranges[i]) return false;

    return true;
}

bool CRangeList::operator!=(const CRangeList &list) const {
    if (this->ranges.size() != list.ranges.size()) return true;

    for (size_t i = 0; i < this->ranges.size(); ++i)
        if (this->ranges[i] == list.ranges[i]) return false;
    return true;
}


ostream &operator<<(ostream &out, const CRangeList &list) {
    auto flags = out.flags();
    char fill = out.fill();

    // unset all flags - https://en.cppreference.com/w/cpp/io/ios_base/unsetf
    out.unsetf(ios_base::basefield);
    out.unsetf(ios_base::adjustfield);
    out.unsetf(ios_base::floatfield);
    out.unsetf(ios_base::boolalpha);
    out.unsetf(ios_base::showbase);
    out.unsetf(ios_base::showpoint);
    out.unsetf(ios_base::showpos);
    out.unsetf(ios_base::skipws);
    out.unsetf(ios_base::unitbuf);
    out.unsetf(ios_base::uppercase);

    CRangeList tmp = list;
    size_t size = tmp.ranges.size();
    for (size_t i = 1; i < size; ++i) { // o(n)
        auto &prev = tmp.ranges[i-1];
        auto &curr = tmp.ranges[i];

        long long hi_prev = prev.get_hi() + 1;
        long long lo_curr = curr.get_lo();
        if (hi_prev == LLONG_MIN) // if there is overflow
            hi_prev = LLONG_MAX;

        if (hi_prev >= lo_curr) {
            prev.set_hi(max(prev.get_hi(), curr.get_hi()));
            tmp.ranges.erase(tmp.ranges.begin()+i);
            i--;
            size = tmp.ranges.size();
        }
    }

    out << dec << "{";
    size = tmp.ranges.size();
    for (size_t i = 0; i < size; ++i) {
        if (tmp.ranges[i].get_lo() == tmp.ranges[i].get_hi()) out << tmp.ranges[i].get_lo();
        else out << "<" << tmp.ranges[i].get_lo() << ".." << tmp.ranges[i].get_hi() << ">";

        if (i != size-1) out << ",";
    }
    out << "}";

    out.flags(flags);
    out.fill(fill);
    return out;
}

ostream &operator<<(ostream &out, const CRange &range) {
    auto flags = out.flags();
    char fill = out.fill();

    // unset all flags - https://en.cppreference.com/w/cpp/io/ios_base/unsetf
    out.unsetf(ios_base::basefield);
    out.unsetf(ios_base::adjustfield);
    out.unsetf(ios_base::floatfield);
    out.unsetf(ios_base::boolalpha);
    out.unsetf(ios_base::showbase);
    out.unsetf(ios_base::showpoint);
    out.unsetf(ios_base::showpos);
    out.unsetf(ios_base::skipws);
    out.unsetf(ios_base::unitbuf);
    out.unsetf(ios_base::uppercase);

    if (range.get_lo() == range.get_hi()) out << range.get_lo();
    else out << dec << "<" << range.get_lo() << ".." << range.get_hi() << ">";

    out.flags(flags);
    out.fill(fill);
    return out;
}

CRangeList operator+(const CRange &r1, const CRange &r2) {
    CRangeList tmp;
    tmp += r1;
    tmp += r2;
    return tmp;
}

CRangeList operator-(const CRange &r1, const CRange &r2) {
    CRangeList tmp;
    tmp += r1;
    tmp = tmp - r2;
    return tmp;
}

CRangeList operator+(const CRange &range, const CRangeList &list) {
    CRangeList tmp;
    tmp += range;
    tmp += list;
    return tmp;
}

CRangeList operator-(const CRange &range, const CRangeList &list) {
    CRangeList tmp;
    tmp += range;
    tmp = tmp - list;
    return tmp;
}


#ifndef __PROGTEST__
string toString (const CRangeList& x) {
    ostringstream oss;
    oss << x;
    return oss.str();
}

int main() {
    CRangeList a, b;
    string kek;

    a += CRange(LLONG_MIN, LLONG_MAX);
    a += CRange(LLONG_MAX, LLONG_MAX);
//    cout << a;


//    a += CRange(LLONG_MIN, LLONG_MAX-1);
//    a += CRange(LLONG_MAX, LLONG_MAX);
//    cout << a;

//    a += CRange(LLONG_MIN, 0);
//    a += CRange(0, LLONG_MAX);
//    a += CRange(LLONG_MAX, LLONG_MAX);
//    a += CRange(LLONG_MIN, LLONG_MIN);
//    cout << a;

    assert ( sizeof ( CRange ) <= 2 * sizeof ( long long ) );
    a = CRange ( 5, 10 );
    a += CRange ( 25, 100 );
    assert ( toString ( a ) == "{<5..10>,<25..100>}" );
    a += CRange ( -5, 0 );
    a += CRange ( 8, 50 );
    assert ( toString ( a ) == "{<-5..0>,<5..100>}" );
    a += CRange ( 101, 105 ) + CRange ( 120, 150 ) + CRange ( 160, 180 ) + CRange ( 190, 210 );
    assert ( toString ( a ) == "{<-5..0>,<5..105>,<120..150>,<160..180>,<190..210>}" );
    a += CRange ( 106, 119 ) + CRange ( 152, 158 );
    assert ( toString ( a ) == "{<-5..0>,<5..150>,<152..158>,<160..180>,<190..210>}" );
    a += CRange ( -3, 170 );
    a += CRange ( -30, 1000 );
    assert ( toString ( a ) == "{<-30..1000>}" );
    b = CRange ( -500, -300 ) + CRange ( 2000, 3000 ) + CRange ( 700, 1001 );
    a += b;
    assert ( toString ( a ) == "{<-500..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( -400, -400 );
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..1001>,<2000..3000>}" );
    a -= CRange ( 10, 20 ) + CRange ( 900, 2500 ) + CRange ( 30, 40 ) + CRange ( 10000, 20000 );
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    try {
        a += CRange ( 15, 18 ) + CRange ( 10, 0 ) + CRange ( 35, 38 );
        assert ( "Exception not thrown" == nullptr );
    } catch ( const std::logic_error & e ){ }
    catch ( ... ) {
        assert ( "Invalid exception thrown" == nullptr );
    }
    assert ( toString ( a ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    b = a;
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 2600, 2700 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,<21..29>,<41..899>,<2501..3000>}" );
    assert ( a == b );
    assert ( !( a != b ) );
    b += CRange ( 15, 15 );
    assert ( toString ( b ) == "{<-500..-401>,<-399..-300>,<-30..9>,15,<21..29>,<41..899>,<2501..3000>}" );
    assert ( !( a == b ) );
    assert ( a != b );
    assert ( b . includes ( 15 ) );
    assert ( b . includes ( 2900 ) );
    assert ( b . includes ( CRange ( 15, 15 ) ) );
    assert ( b . includes ( CRange ( -350, -350 ) ) );
    assert ( b . includes ( CRange ( 100, 200 ) ) );
    assert ( !b . includes ( CRange ( 800, 900 ) ) );
    assert ( !b . includes ( CRange ( -1000, -450 ) ) );
    assert ( !b . includes ( CRange ( 0, 500 ) ) );
    a += CRange ( -10000, 10000 ) + CRange ( 10000000, 1000000000 );
    assert ( toString ( a ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b += a;
    assert ( toString ( b ) == "{<-10000..10000>,<10000000..1000000000>}" );
    b -= a;
    assert ( toString ( b ) == "{}" );
    b += CRange ( 0, 100 ) + CRange ( 200, 300 ) - CRange ( 150, 250 ) + CRange ( 160, 180 ) - CRange ( 170, 170 );
    assert ( toString ( b ) == "{<0..100>,<160..169>,<171..180>,<251..300>}" );
    b -= CRange ( 10, 90 ) - CRange ( 20, 30 ) - CRange ( 40, 50 ) - CRange ( 60, 90 ) + CRange ( 70, 80 );
    assert ( toString ( b ) == "{<0..9>,<20..30>,<40..50>,<60..69>,<81..100>,<160..169>,<171..180>,<251..300>}" );
#ifdef EXTENDED_SYNTAX
    CRangeList x { { 5, 20 }, { 150, 200 }, { -9, 12 }, { 48, 93 } };
    assert ( toString ( x ) == "{<-9..20>,<48..93>,<150..200>}" );
    ostringstream oss;
    oss << setfill ( '=' ) << hex << left;
    for ( const auto & v : x + CRange ( -100, -100 ) ) {
        oss << v << endl;
    }
    oss << setw ( 10 ) << 1024;
    assert ( oss . str () == "-100\n<-9..20>\n<48..93>\n<150..200>\n400=======" );
#endif /* EXTENDED_SYNTAX */
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
