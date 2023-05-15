#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect {
public:
    CRect(double x, double y, double w, double h) : m_X (x), m_Y (y), m_W(w), m_H(h){}
    friend ostream& operator << (ostream &os, const CRect &x) {
        return os << '(' << x . m_X << ',' << x . m_Y << ',' << x . m_W << ',' << x . m_H << ')';
    }
    double m_X;
    double m_Y;
    double m_W;
    double m_H;
};
#endif /* __PROGTEST__ */

class Base {
protected:
    int id;
    CRect pos;
    string name;
    CRect relPos;
public:
    Base(int id, const CRect &pos, const string &name) : id(id), pos(pos), name(name), relPos(0, 0, 0, 0) {}
    virtual ~Base() {}
    virtual Base *clone() const = 0; // took from Jan Matousek tutorial
    virtual void print(ostream &out, bool isLast, int indent = 0) const = 0;
    int getId() { return id; }
    void setRelPos(CRect &position) { relPos = position; }
    CRect getPos() { return pos; }
    friend ostream &operator << (ostream &out, const Base &elem);
};


class CWindow : public Base {
    std::vector<std::unique_ptr<Base>> elements; // took from Jan Matousek tutorial

    void changePositions(Base &elem);
public:
    CWindow(int id, const string &title, const CRect &absPos) : Base(id, absPos, title) {}
    CWindow(const CWindow &other); // took from Jan Matousek tutorial
    CWindow &operator = (const CWindow &other); // took from Jan Matousek tutorial
    CWindow* clone() const override;
    void print(ostream &out, bool isLast, int indent = 0) const override;
    // add
    CWindow &add(const Base &elem);
    // search
    Base* search(int id);
    // setPosition
    void setPosition(const CRect &pos);
};

// done
CWindow *CWindow::clone() const {
    return new CWindow(*this);
}

// done
CWindow::CWindow(const CWindow &other) : Base(other.id, other.pos, other.name) {
    for (auto &elem : other.elements) {
        add(*elem);
    }
}

// done
CWindow &CWindow::operator=(const CWindow &other) {
    if (this == &other) return *this;
    id = other.id;
    pos = other.pos;
    name = other.name;

    CWindow copy(other);
    swap(elements, copy.elements);
    return *this;
}

void CWindow::print(ostream &out, bool isLast, int indent) const {
    out << "[" << id << "] ";
    out << "Window ";
    out << "\"" << name << "\" ";
    out << pos << "\n";
    for (size_t i = 0; i < elements.size()-1; ++i) {
        out << "+- ";
        elements[i]->print(out, false, indent+1);
    }
    out << "+- ";
    elements[elements.size()-1]->print(out, true, indent+1);
}

CWindow &CWindow::add(const Base &elem) {
    auto tmp = elem.clone();
    changePositions(*tmp);
    elements.emplace_back(tmp); // took from Jan Matousek tutorial
    return *this;
}

Base *CWindow::search(int id) {
    for (auto &elem : elements) {
        if (elem->getId() == id)
            return elem.get();
    }
    return nullptr;
}

void CWindow::setPosition(const CRect &pos) {
    this->pos = pos;
    for (auto &elem : elements) {
        changePositions(*elem);
    }
}

void CWindow::changePositions(Base &elem) {
    double x = pos.m_X + pos.m_W * elem.getPos().m_X;
    double y = pos.m_Y + pos.m_H * elem.getPos().m_Y;
    double w = pos.m_W * elem.getPos().m_W;
    double h = pos.m_H * elem.getPos().m_H;
    CRect tmp(x, y, w, h);
    elem.setRelPos(tmp);
}

class CButton : public Base {
    int kek;
public:
    CButton(int id, const CRect &relPos, const string &name) : Base(id, relPos, name) {}
    CButton* clone() const override;
    void print(ostream &out, bool isLast, int indent = 0) const override;
};

CButton *CButton::clone() const {
    return new CButton(*this);
}

void CButton::print(ostream &out, bool isLast, int indent) const {
    out << "[" << id << "] ";
    out << "Button ";
    out << "\"" << name << "\" ";
    out << relPos << "\n";
}

class CInput : public Base {
    int kek;
public:
    CInput (int id, const CRect &relPos, const string &value) : Base(id, relPos, value) {}
    CInput* clone() const override;
    void print(ostream &out, bool isLast, int indent = 0) const override;
    // setValue
    void setValue(const string &value) { this->name = value; }
    // getValue
    string getValue() const { return name; }
};

CInput *CInput::clone() const {
    return new CInput(*this);
}

void CInput::print(ostream &out, bool isLast, int indent) const {
    out << "[" << id << "] ";
    out << "Input ";
    out << "\"" << name << "\" ";
    out << relPos << "\n";
}

class CLabel : public Base {
    int kek;
public:
    CLabel (int id, const CRect &relPos, const string &label) : Base(id, relPos, label) {}
    CLabel* clone() const override;
    void print(ostream &out, bool isLast, int indent = 0) const override;
};

CLabel *CLabel::clone() const {
    return new CLabel(*this);
}

void CLabel::print(ostream &out, bool isLast, int indent) const {
    out << "[" << id << "] ";
    out << "Label ";
    out << "\"" << name << "\" ";
    out << relPos << "\n";
}

class CComboBox : public Base {
    vector <string> options;
    size_t selected = 0;
public:
    CComboBox (int id, const CRect &relPos) : Base(id, relPos, "") {}
    CComboBox *clone() const override;
    void print(ostream &out, bool isLast, int indent = 0) const override;
    // add
    CComboBox &add(const string &option);
    // setSelected
    void setSelected(size_t idx) { this->selected = idx; }
    // getSelected
    size_t getSelected() const { return selected; }
};

CComboBox *CComboBox::clone() const {
    return new CComboBox(*this);
}

void CComboBox::print(ostream &out, bool isLast, int indent) const {
    out << "[" << id << "] ";
    out << "ComboBox ";
    out << relPos << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        if (!isLast) {
            out << "|";
            for (int j = 0; j < indent; ++j) out << "  ";
        } else for (int j = 0; j < indent; ++j) out << "   ";

        out << "+-";

        if (i == selected) out << ">" << options[i] << "<\n";
        else out << " " << options[i] << "\n";
    }
}

CComboBox &CComboBox::add(const string &option) {
    options.push_back(option);
    return *this;
}

// output operators
ostream &operator<<(ostream &out, const Base &elem) {
    elem.print(out, true);
    return out;
}

#ifndef __PROGTEST__
template <typename _T>
string toString ( const _T & x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int main ( void )
{
    assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
    assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
    assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
    CWindow a ( 0, "Sample window", CRect ( 10, 10, 600, 480 ) );
    a . add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
    a . add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
    a . add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
    a . add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . add ( "Karate" ) . add ( "Judo" ) . add ( "Box" ) . add ( "Progtest" ) );
    assert ( toString ( a ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
             "+- [20] ComboBox (70,154,480,48)\n"
             "   +->Karate<\n"
             "   +- Judo\n"
             "   +- Box\n"
             "   +- Progtest\n" );
    CWindow b = a;
    assert ( toString ( *b . search ( 20 ) ) ==
             "[20] ComboBox (70,154,480,48)\n"
             "+->Karate<\n"
             "+- Judo\n"
             "+- Box\n"
             "+- Progtest\n" );
    assert ( dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . getSelected () == 0 );
    dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . setSelected ( 3 );
    assert ( dynamic_cast<CInput &> ( *b . search ( 11 ) ) . getValue () == "chucknorris" );
    dynamic_cast<CInput &> ( *b . search ( 11 ) ) . setValue ( "chucknorris@fit.cvut.cz" );
    b . add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . add ( "PA2" ) . add ( "OSY" ) . add ( "Both" ) );
    auto onemore = toString(b);
//    cout << onemore;
    assert ( toString ( b ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
             "+- [20] ComboBox (70,154,480,48)\n"
             "|  +- Karate\n"
             "|  +- Judo\n"
             "|  +- Box\n"
             "|  +->Progtest<\n"
             "+- [21] ComboBox (70,250,480,48)\n"
             "   +->PA2<\n"
             "   +- OSY\n"
             "   +- Both\n" );
    assert ( toString ( a ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
             "+- [20] ComboBox (70,154,480,48)\n"
             "   +->Karate<\n"
             "   +- Judo\n"
             "   +- Box\n"
             "   +- Progtest\n" );
    b . setPosition ( CRect ( 20, 30, 640, 520 ) );
    assert ( toString ( b ) ==
             "[0] Window \"Sample window\" (20,30,640,520)\n"
             "+- [1] Button \"Ok\" (84,446,192,52)\n"
             "+- [2] Button \"Cancel\" (404,446,192,52)\n"
             "+- [10] Label \"Username:\" (84,82,128,52)\n"
             "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
             "+- [20] ComboBox (84,186,512,52)\n"
             "|  +- Karate\n"
             "|  +- Judo\n"
             "|  +- Box\n"
             "|  +->Progtest<\n"
             "+- [21] ComboBox (84,290,512,52)\n"
             "   +->PA2<\n"
             "   +- OSY\n"
             "   +- Both\n" );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
