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

struct person {
    int id;
    string name;
    string surname;
    string number;
};

bool check_if_number(const string &number) {
    for (auto &c : number)
        if (!isdigit(c)) return false;
    return true;
}

// errors:
// 1) more or less data in line
// 2) number has not 9 digits
// 3) some letter of number is not a digits
// 4) number starts with 0
// 5) does not have new line after list of l

bool report ( const string & fileName, ostream & out ) {
    ifstream in(fileName, ios::in);
    if (!in.is_open()) return false;
    string line;
    // get all data
    vector <person> people;
    int counter = 0;
    while(true) {
        getline(in, line);
        if (line.empty()) break;
        stringstream s(line);
        string name;
        string surname;
        string number;
        string more;
        s >> name;
        s >> surname;
        s >> number;
        if (!check_if_number(number)) return false;
        if (number.length() != 9) return false;
        if (number[0] == '0') return false;
        s >> more;
        if (!more.empty() or surname.empty() or number.empty()) return false;
        people.push_back({counter, name, surname, number});
        counter += 1;
        if (in.eof()) return false;
//        cout << "NAME: " << name << " LENGTH: " << name.length() << endl;
//        cout << "SURNAME: " << surname << " LENGTH: " << surname.length() << endl;
//        cout << "NUMBER: " << number << " LENGTH: " << number.length() << endl;
//        cout << "MORE: " << more << " LENGTH: " << more.length() << endl;
//        cout << "----------------\n";
    }
    // get requests
    int i = 0;
    while (true) {
        vector <int> ans;
        getline(in, line);
        if (line.empty()) break;
        stringstream s(line);
        string query;
        s >> query;
        for (auto &c : people) {
            if (c.name == query or c.surname == query) {
                out << c.name << " " << c.surname << " " << c.number << endl;
                ans.push_back(c.id);
            }
        }
        out << "-> " << ans.size() << endl;
        i++;
        if (in.eof()) break;
    }
    return true;
}

#ifndef __PROGTEST__
int main () {
    ostringstream oss;
    oss.str("");
//    if (!report( "tests/test0_in.txt", oss )) {
//        cout << "AN ERROR" << endl;
//    }
    assert(report( "tests/test0_in.txt", oss ) == true );
//    cout << oss.str();
    assert (oss.str() ==
             "John Christescu 258452362\n"
             "John Harmson 861647702\n"
             "-> 2\n"
             "-> 0\n"
             "Josh Dakhov 264112084\n"
             "Dakhov Speechley 865216101\n"
             "-> 2\n"
             "John Harmson 861647702\n"
             "-> 1\n" );
    oss.str( "" );
    assert ( report( "tests/test1_in.txt", oss ) == true );
    cout << oss.str();
    return 0;
}
#endif /* __PROGTEST__ */
