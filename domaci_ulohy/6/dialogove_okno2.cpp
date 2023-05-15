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
    virtual void print(ostream &out, string details = "") const = 0;
    int getId() { return id; }
    void setRelPos(CRect &position) { relPos = position; }
    CRect getPos() { return pos; }
    CRect getRelPos() { return relPos; }
    friend ostream &operator << (ostream &out, const Base &elem);
};

class CPanel : public Base {
public:
    CPanel (int id, const CRect &relPos) : Base(id, relPos, "") {}
    CPanel(const CPanel &other);
    CPanel *clone() const override;
    void print(ostream &out, string details = "") const override;
    CPanel &operator = (const CPanel &other);
    // add
    CPanel &add(const Base &elem);
    vector<unique_ptr<Base>> elements;
    void changePositions(Base &elem);
    Base* search(int id);
    void changeAllPositions() {
        for (auto &e : elements) {
            changePositions(*e);
            auto panel = dynamic_cast<CPanel*>(e.get());
            if (panel != nullptr) {
                panel->changeAllPositions();
            }
        }
    }
};


class CWindow : public Base {
    vector<unique_ptr<Base>> elements; // took from Jan Matousek tutorial

    void changePositions(Base &elem);
public:
    CWindow(int id, const string &title, const CRect &absPos) : Base(id, absPos, title) {}
    CWindow(const CWindow &other); // took from Jan Matousek tutorial
    CWindow &operator = (const CWindow &other); // took from Jan Matousek tutorial
    CWindow* clone() const override;
    void print(ostream &out, string details = "") const override;
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



CWindow &CWindow::add(const Base &elem) {
    auto tmp = elem.clone();
    changePositions(*tmp);
    auto panel = dynamic_cast<CPanel*>(tmp);
    if (panel != nullptr) {
        for (auto &e : panel->elements) {
            panel->changePositions(*e);
        }
    }
    elements.emplace_back(tmp); // took from Jan Matousek tutorial
    return *this;
}

Base *CWindow::search(int id) {
    for (auto &elem : elements) {
        if (elem->getId() == id)
            return elem.get();

        auto panel = dynamic_cast<CPanel*>(elem.get());
        if (panel != nullptr) {
            auto to_search = panel->search(id);
            if (to_search != nullptr) return to_search;
        }
    }
    return nullptr;
}

void CWindow::setPosition(const CRect &pos) {
    this->pos = pos;
    for (auto &elem : elements) {
        changePositions(*elem);
        auto panel = dynamic_cast<CPanel*>(elem.get());
        if (panel != nullptr) {
            for (auto &e : panel->elements) {
                panel->changePositions(*e);
            }
        }
    }
}

void CWindow::changePositions(Base &elem) {
    double x = pos.m_X + pos.m_W * elem.getPos().m_X;
    double y = pos.m_Y + pos.m_H * elem.getPos().m_Y;
    double w = pos.m_W * elem.getPos().m_W;
    double h = pos.m_H * elem.getPos().m_H;
    CRect tmp(x, y, w, h);
    elem.setRelPos(tmp);
    auto panel = dynamic_cast<CPanel*>(&elem);
    if (panel != nullptr) panel->changeAllPositions();
}


CPanel::CPanel(const CPanel &other) : Base(other) {
    for (auto &elem: other.elements) {
        add(*elem);
    }
}

CPanel *CPanel::clone() const {
    return new CPanel(*this);
}

CPanel &CPanel::operator=(const CPanel &other) {
    if (this == &other) return *this;
    id = other.id;
    pos = other.pos;
    name = other.name;
    relPos = other.relPos;

    CPanel copy(other);
    swap(elements, copy.elements);
    return *this;
}

CPanel &CPanel::add(const Base &elem) {
    auto tmp = elem.clone();
    changePositions(*tmp);
    auto panel = dynamic_cast<CPanel*>(tmp);
    if (panel != nullptr) {
        panel->changeAllPositions();
        for (auto &e : panel->elements) {
            panel->changePositions(*e);
        }
    }
    elements.emplace_back(tmp); // took from Jan Matousek tutorial
    return *this;
}

void CPanel::changePositions(Base &elem) {


    double x = relPos.m_X + relPos.m_W * elem.getPos().m_X;
    double y = relPos.m_Y + relPos.m_H * elem.getPos().m_Y;
    double w = relPos.m_W * elem.getPos().m_W;
    double h = relPos.m_H * elem.getPos().m_H;
    CRect tmp(x, y, w, h);
    elem.setRelPos(tmp);
    auto panel = dynamic_cast<CPanel*>(&elem);
    if (panel != nullptr) panel->changeAllPositions();
}

Base *CPanel::search(int id) {
    for (auto &elem : elements) {
        if (elem->getId() == id)
            return elem.get();

        auto panel = dynamic_cast<CPanel*>(elem.get());
        if  (panel != nullptr) {
            auto to_search = panel->search(id);
            if (to_search != nullptr) return to_search;
        }
    }
    return nullptr;
}

class CButton : public Base {
    int kek;
public:
    CButton(int id, const CRect &relPos, const string &name) : Base(id, relPos, name) {}
    CButton* clone() const override;
    void print(ostream &out, string details = "") const override;
};

CButton *CButton::clone() const {
    return new CButton(*this);
}

void CButton::print(ostream &out, string details) const {
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
    void print(ostream &out, string details = "") const override;
    // setValue
    void setValue(const string &value) { this->name = value; }
    // getValue
    string getValue() const { return name; }
};

CInput *CInput::clone() const {
    return new CInput(*this);
}

void CInput::print(ostream &out, string details) const {
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
    void print(ostream &out, string details = "") const override;
};

CLabel *CLabel::clone() const {
    return new CLabel(*this);
}

void CLabel::print(ostream &out, string details) const {
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
    void print(ostream &out, string details = "") const override;
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

CComboBox &CComboBox::add(const string &option) {
    options.push_back(option);
    return *this;
}


void CWindow::print(ostream &out, string details) const {
    out << "[" << id << "] ";
    out << "Window ";
    out << "\"" << name << "\" ";
    out << pos << "\n";
    for (size_t i = 0; i < elements.size()-1; ++i) {
        out << "+- ";
        elements[i]->print(out, details + "|  ");
    }
    out << "+- ";
    elements[elements.size()-1]->print(out, details + "   ");
}

void CPanel::print(ostream &out, string details) const {
    out << "[" << id << "] ";
    out << "Panel ";
    out << relPos << "\n";
    for (size_t i = 0; i < elements.size()-1; ++i) {
        out << details;
        out << "+- ";
        elements[i]->print(out, details + "|  ");
    }
    out << details;
    out << "+- ";
    elements[elements.size()-1]->print(out, details + "   ");
}

void CComboBox::print(ostream &out, string details) const {
    out << "[" << id << "] ";
    out << "ComboBox ";
    out << relPos << "\n";

    for (size_t i = 0; i < options.size(); ++i) {
        out << details;
        out << "+-";
        if (i == selected) out << ">" << options[i] << "<\n";
        else out << " " << options[i] << "\n";
    }
}


// output operators
ostream &operator<<(ostream &out, const Base &elem) {
    elem.print(out);
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

int main () {
    assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
    assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
    assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
    assert ( sizeof ( CButton ) - sizeof ( string ) <= sizeof ( CPanel ) - sizeof ( vector<void*> ) );
    assert ( sizeof ( CInput ) - sizeof ( string ) <= sizeof ( CPanel ) - sizeof ( vector<void*> ) );
    assert ( sizeof ( CLabel ) - sizeof ( string ) <= sizeof ( CPanel ) - sizeof ( vector<void*> ) );
    CWindow a ( 0, "Sample window", CRect ( 10, 10, 600, 480 ) );
    a . add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
    a . add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
    a . add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
    a . add ( CPanel ( 12, CRect ( 0.1, 0.3, 0.8, 0.7 ) ) . add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . add ( "Karate" ) . add ( "Judo" ) . add ( "Box" ) . add ( "Progtest" ) ) );
//    cout << toString(a);
    assert ( toString ( a ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
             "+- [12] Panel (70,154,480,336)\n"
             "   +- [20] ComboBox (118,254.8,384,33.6)\n"
             "      +->Karate<\n"
             "      +- Judo\n"
             "      +- Box\n"
             "      +- Progtest\n" );
    CWindow b = a;
//    cout << toString(*b.search(20));
    assert ( toString ( *b . search ( 20 ) ) ==
             "[20] ComboBox (118,254.8,384,33.6)\n"
             "+->Karate<\n"
             "+- Judo\n"
             "+- Box\n"
             "+- Progtest\n" );
    assert ( dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . getSelected () == 0 );
    dynamic_cast<CComboBox &> ( *b . search ( 20 ) ) . setSelected ( 3 );
//    cout << toString(*b.search(20));
    assert ( dynamic_cast<CInput &> ( *b . search ( 11 ) ) . getValue () == "chucknorris" );
    dynamic_cast<CInput &> ( *b . search ( 11 ) ) . setValue ( "chucknorris@fit.cvut.cz" );
    CPanel & p = dynamic_cast<CPanel &> ( *b . search ( 12 ) );
    p . add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . add ( "PA2" ) . add ( "OSY" ) . add ( "Both" ) );
//    cout << toString(b);
    assert ( toString ( b ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
             "+- [12] Panel (70,154,480,336)\n"
             "   +- [20] ComboBox (118,254.8,384,33.6)\n"
             "   |  +- Karate\n"
             "   |  +- Judo\n"
             "   |  +- Box\n"
             "   |  +->Progtest<\n"
             "   +- [21] ComboBox (118,322,384,33.6)\n"
             "      +->PA2<\n"
             "      +- OSY\n"
             "      +- Both\n" );
    assert ( toString ( a ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
             "+- [12] Panel (70,154,480,336)\n"
             "   +- [20] ComboBox (118,254.8,384,33.6)\n"
             "      +->Karate<\n"
             "      +- Judo\n"
             "      +- Box\n"
             "      +- Progtest\n" );
    assert ( toString ( p ) ==
             "[12] Panel (70,154,480,336)\n"
             "+- [20] ComboBox (118,254.8,384,33.6)\n"
             "|  +- Karate\n"
             "|  +- Judo\n"
             "|  +- Box\n"
             "|  +->Progtest<\n"
             "+- [21] ComboBox (118,322,384,33.6)\n"
             "   +->PA2<\n"
             "   +- OSY\n"
             "   +- Both\n" );
    b . setPosition ( CRect ( 20, 30, 640, 520 ) );
//    cout << toString(b);
    assert ( toString ( b ) ==
             "[0] Window \"Sample window\" (20,30,640,520)\n"
             "+- [1] Button \"Ok\" (84,446,192,52)\n"
             "+- [2] Button \"Cancel\" (404,446,192,52)\n"
             "+- [10] Label \"Username:\" (84,82,128,52)\n"
             "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
             "+- [12] Panel (84,186,512,364)\n"
             "   +- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
             "   |  +- Karate\n"
             "   |  +- Judo\n"
             "   |  +- Box\n"
             "   |  +->Progtest<\n"
             "   +- [21] ComboBox (135.2,368,409.6,36.4)\n"
             "      +->PA2<\n"
             "      +- OSY\n"
             "      +- Both\n" );
    p . add ( p );
//    cout << toString(p);
    assert ( toString ( p ) ==
             "[12] Panel (84,186,512,364)\n"
             "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
             "|  +- Karate\n"
             "|  +- Judo\n"
             "|  +- Box\n"
             "|  +->Progtest<\n"
             "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
             "|  +->PA2<\n"
             "|  +- OSY\n"
             "|  +- Both\n"
             "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "   |  +- Karate\n"
             "   |  +- Judo\n"
             "   |  +- Box\n"
             "   |  +->Progtest<\n"
             "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "      +->PA2<\n"
             "      +- OSY\n"
             "      +- Both\n" );
    p . add ( p );
//    cout << toString(p);
    assert ( toString ( p ) ==
             "[12] Panel (84,186,512,364)\n"
             "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
             "|  +- Karate\n"
             "|  +- Judo\n"
             "|  +- Box\n"
             "|  +->Progtest<\n"
             "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
             "|  +->PA2<\n"
             "|  +- OSY\n"
             "|  +- Both\n"
             "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "|  |  +- Karate\n"
             "|  |  +- Judo\n"
             "|  |  +- Box\n"
             "|  |  +->Progtest<\n"
             "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "|     +->PA2<\n"
             "|     +- OSY\n"
             "|     +- Both\n"
             "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "   |  +- Karate\n"
             "   |  +- Judo\n"
             "   |  +- Box\n"
             "   |  +->Progtest<\n"
             "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "   |  +->PA2<\n"
             "   |  +- OSY\n"
             "   |  +- Both\n"
             "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "      +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "      |  +- Karate\n"
             "      |  +- Judo\n"
             "      |  +- Box\n"
             "      |  +->Progtest<\n"
             "      +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "         +->PA2<\n"
             "         +- OSY\n"
             "         +- Both\n" );
    p . add ( p );
//    cout << toString(p);
    assert ( toString ( p ) ==
             "[12] Panel (84,186,512,364)\n"
             "+- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
             "|  +- Karate\n"
             "|  +- Judo\n"
             "|  +- Box\n"
             "|  +->Progtest<\n"
             "+- [21] ComboBox (135.2,368,409.6,36.4)\n"
             "|  +->PA2<\n"
             "|  +- OSY\n"
             "|  +- Both\n"
             "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "|  |  +- Karate\n"
             "|  |  +- Judo\n"
             "|  |  +- Box\n"
             "|  |  +->Progtest<\n"
             "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "|     +->PA2<\n"
             "|     +- OSY\n"
             "|     +- Both\n"
             "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "|  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "|  |  +- Karate\n"
             "|  |  +- Judo\n"
             "|  |  +- Box\n"
             "|  |  +->Progtest<\n"
             "|  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "|  |  +->PA2<\n"
             "|  |  +- OSY\n"
             "|  |  +- Both\n"
             "|  +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "|     +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "|     |  +- Karate\n"
             "|     |  +- Judo\n"
             "|     |  +- Box\n"
             "|     |  +->Progtest<\n"
             "|     +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "|        +->PA2<\n"
             "|        +- OSY\n"
             "|        +- Both\n"
             "+- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "   +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "   |  +- Karate\n"
             "   |  +- Judo\n"
             "   |  +- Box\n"
             "   |  +->Progtest<\n"
             "   +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "   |  +->PA2<\n"
             "   |  +- OSY\n"
             "   |  +- Both\n"
             "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "   |  +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "   |  |  +- Karate\n"
             "   |  |  +- Judo\n"
             "   |  |  +- Box\n"
             "   |  |  +->Progtest<\n"
             "   |  +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "   |     +->PA2<\n"
             "   |     +- OSY\n"
             "   |     +- Both\n"
             "   +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "      +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "      |  +- Karate\n"
             "      |  +- Judo\n"
             "      |  +- Box\n"
             "      |  +->Progtest<\n"
             "      +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "      |  +->PA2<\n"
             "      |  +- OSY\n"
             "      |  +- Both\n"
             "      +- [12] Panel (208.928,425.148,262.144,124.852)\n"
             "         +- [20] ComboBox (235.142,462.604,209.715,12.4852)\n"
             "         |  +- Karate\n"
             "         |  +- Judo\n"
             "         |  +- Box\n"
             "         |  +->Progtest<\n"
             "         +- [21] ComboBox (235.142,487.574,209.715,12.4852)\n"
             "            +->PA2<\n"
             "            +- OSY\n"
             "            +- Both\n" );
//    cout << toString(b);
    assert ( toString ( b ) ==
             "[0] Window \"Sample window\" (20,30,640,520)\n"
             "+- [1] Button \"Ok\" (84,446,192,52)\n"
             "+- [2] Button \"Cancel\" (404,446,192,52)\n"
             "+- [10] Label \"Username:\" (84,82,128,52)\n"
             "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
             "+- [12] Panel (84,186,512,364)\n"
             "   +- [20] ComboBox (135.2,295.2,409.6,36.4)\n"
             "   |  +- Karate\n"
             "   |  +- Judo\n"
             "   |  +- Box\n"
             "   |  +->Progtest<\n"
             "   +- [21] ComboBox (135.2,368,409.6,36.4)\n"
             "   |  +->PA2<\n"
             "   |  +- OSY\n"
             "   |  +- Both\n"
             "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "   |  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "   |  |  +- Karate\n"
             "   |  |  +- Judo\n"
             "   |  |  +- Box\n"
             "   |  |  +->Progtest<\n"
             "   |  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "   |     +->PA2<\n"
             "   |     +- OSY\n"
             "   |     +- Both\n"
             "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "   |  +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "   |  |  +- Karate\n"
             "   |  |  +- Judo\n"
             "   |  |  +- Box\n"
             "   |  |  +->Progtest<\n"
             "   |  +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "   |  |  +->PA2<\n"
             "   |  |  +- OSY\n"
             "   |  |  +- Both\n"
             "   |  +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "   |     +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "   |     |  +- Karate\n"
             "   |     |  +- Judo\n"
             "   |     |  +- Box\n"
             "   |     |  +->Progtest<\n"
             "   |     +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "   |        +->PA2<\n"
             "   |        +- OSY\n"
             "   |        +- Both\n"
             "   +- [12] Panel (135.2,295.2,409.6,254.8)\n"
             "      +- [20] ComboBox (176.16,371.64,327.68,25.48)\n"
             "      |  +- Karate\n"
             "      |  +- Judo\n"
             "      |  +- Box\n"
             "      |  +->Progtest<\n"
             "      +- [21] ComboBox (176.16,422.6,327.68,25.48)\n"
             "      |  +->PA2<\n"
             "      |  +- OSY\n"
             "      |  +- Both\n"
             "      +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "      |  +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "      |  |  +- Karate\n"
             "      |  |  +- Judo\n"
             "      |  |  +- Box\n"
             "      |  |  +->Progtest<\n"
             "      |  +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "      |     +->PA2<\n"
             "      |     +- OSY\n"
             "      |     +- Both\n"
             "      +- [12] Panel (176.16,371.64,327.68,178.36)\n"
             "         +- [20] ComboBox (208.928,425.148,262.144,17.836)\n"
             "         |  +- Karate\n"
             "         |  +- Judo\n"
             "         |  +- Box\n"
             "         |  +->Progtest<\n"
             "         +- [21] ComboBox (208.928,460.82,262.144,17.836)\n"
             "         |  +->PA2<\n"
             "         |  +- OSY\n"
             "         |  +- Both\n"
             "         +- [12] Panel (208.928,425.148,262.144,124.852)\n"
             "            +- [20] ComboBox (235.142,462.604,209.715,12.4852)\n"
             "            |  +- Karate\n"
             "            |  +- Judo\n"
             "            |  +- Box\n"
             "            |  +->Progtest<\n"
             "            +- [21] ComboBox (235.142,487.574,209.715,12.4852)\n"
             "               +->PA2<\n"
             "               +- OSY\n"
             "               +- Both\n" );
//    cout << toString(a);
    assert ( toString ( a ) ==
             "[0] Window \"Sample window\" (10,10,600,480)\n"
             "+- [1] Button \"Ok\" (70,394,180,48)\n"
             "+- [2] Button \"Cancel\" (370,394,180,48)\n"
             "+- [10] Label \"Username:\" (70,58,120,48)\n"
             "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
             "+- [12] Panel (70,154,480,336)\n"
             "   +- [20] ComboBox (118,254.8,384,33.6)\n"
             "      +->Karate<\n"
             "      +- Judo\n"
             "      +- Box\n"
             "      +- Progtest\n" );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
