#ifndef __PROGTEST__
#include <cstring>
#include <iostream>
using namespace std;

class CLinkedSetTester;
#endif /* __PROGTEST__ */


class CLinkedSet {
    struct CNode {
        CNode *m_Next;
        const char *Value () const;
        char *m_Data;
    };

    CNode *m_Begin;

public:
    // default constructor
    CLinkedSet() : m_Begin(nullptr) {}
    // copy constructor
    CLinkedSet(const CLinkedSet &set);
    // operator=
    CLinkedSet &operator =(const CLinkedSet &set);
    // destructor
    ~CLinkedSet();

    bool Insert (const char *value);
    bool Remove (const char *value);
    bool Empty () const;
    size_t Size () const;
    bool Contains (const char *value) const;

    friend class ::CLinkedSetTester;
};

const char *CLinkedSet::CNode::Value() const {
    return m_Data;
}

CLinkedSet::CLinkedSet(const CLinkedSet &set) : m_Begin(nullptr) {
    CNode *tmp = set.m_Begin;
    while (tmp) { // for all elements from other set
        Insert(tmp->Value()); // insert to our linked list element from another set
        tmp = tmp->m_Next;
    }
}

CLinkedSet &CLinkedSet::operator=(const CLinkedSet &set) {
    if (this == &set) return *this; // if we have the same set

    while (m_Begin) Remove(m_Begin->Value()); // remove all data from our linked list starting with beginning

    // insert all data from another list to our like in copy constructor
    CNode *tmp = set.m_Begin;
    while (tmp) {
        Insert(tmp->Value());
        tmp = tmp->m_Next;
    }
    return *this;
}

CLinkedSet::~CLinkedSet() {
    while (m_Begin) {
        CNode *tmp = m_Begin->m_Next;
        delete[] m_Begin->Value();
        delete m_Begin;
        m_Begin = tmp;
    }
}

bool CLinkedSet::Insert(const char *value) {
    CNode *prev = nullptr;
    CNode *curr = m_Begin;
    // finding position to insert new element
    while (curr && strcmp(curr->Value(), value) < 0) {
        prev = curr;
        curr = curr->m_Next;
    }
    if (curr && strcmp(curr->Value(), value) == 0) return false; // if element is already in set

    CNode *to_insert = new CNode;
    to_insert->m_Data = new char[strlen(value)+1];
    strncpy(to_insert->m_Data, value, strlen(value)+1);

    to_insert->m_Next = curr; // change the connection between new element and current

    if (prev) prev->m_Next = to_insert; // change the connection between previous element
    else m_Begin = to_insert; // or we at the beginning

    return true;
}

bool CLinkedSet::Remove(const char *value) {
    CNode *prev = nullptr;
    CNode *curr = m_Begin;

    // while current string is not bigger than searching string AND curr ptr is not end of linked list
    while (curr && strcmp(curr->Value(), value) < 0) {
        prev = curr;
        curr = curr->m_Next;
    }

    if (curr && strcmp(curr->Value(), value) == 0) { // if we found the value
        if (prev) prev->m_Next = curr->m_Next; // we need to change connection between two nodes
        else m_Begin = curr->m_Next; // or if we at the beginning of node, we change begin ptr

        delete[] curr->Value(); // delete string
        delete curr; // delete node
        return true;
    }
    return false;
}

bool CLinkedSet::Empty() const {
    return m_Begin == nullptr;
}

size_t CLinkedSet::Size() const {
    size_t n = 0;
    CNode *tmp = m_Begin;
    while (tmp) {
        tmp = tmp->m_Next;
        n++;
    }
    return n;
}

bool CLinkedSet::Contains(const char *value) const {
    CNode *tmp = m_Begin;
    // while current string is not bigger than searching string AND tmp is not end of linked list
    while (tmp && strcmp(tmp->Value(), value) < 0)
        tmp = tmp->m_Next;

    if (tmp && strcmp(tmp->Value(), value) == 0) return true; // if they are equal
    return false;
}

#ifndef __PROGTEST__
#include <cassert>

struct CLinkedSetTester {
    static void test0() {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert(x0 . Contains( "Dusek Zikmund"));
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        assert( !x0 . Empty() );
    }

    static void test1()
    {
        CLinkedSet x0;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        CLinkedSet x1 ( x0 );
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

    static void test2()
    {
        CLinkedSet x0;
        CLinkedSet x1;
        assert( x0 . Insert( "Jerabek Michal" ) );
        assert( x0 . Insert( "Pavlik Ales" ) );
        assert( x0 . Insert( "Dusek Zikmund" ) );
        assert( x0 . Size() == 3 );
        assert( x0 . Contains( "Dusek Zikmund" ) );
        assert( !x0 . Contains( "Pavlik Jan" ) );
        assert( x0 . Remove( "Jerabek Michal" ) );
        assert( !x0 . Remove( "Pavlik Jan" ) );
        x1 = x0;
        assert( x0 . Insert( "Vodickova Saskie" ) );
        assert( x1 . Insert( "Kadlecova Kvetslava" ) );
        assert( x0 . Size() == 3 );
        assert( x1 . Size() == 3 );
        assert( x0 . Contains( "Vodickova Saskie" ) );
        assert( !x1 . Contains( "Vodickova Saskie" ) );
        assert( !x0 . Contains( "Kadlecova Kvetslava" ) );
        assert( x1 . Contains( "Kadlecova Kvetslava" ) );
    }

};

int main ()
{
    CLinkedSetTester::test0();
    CLinkedSetTester::test1();
    CLinkedSetTester::test2();
    return 0;
}
#endif /* __PROGTEST__ */
