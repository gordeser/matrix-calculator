#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <functional>
#include <iterator>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

template <typename M_>
class CContest {
    struct Match {
        string contestant1;
        string contestant2;
        M_ result;
        Match(const string &contestant1, const string &contestant2, const M_ &result) : contestant1(contestant1), contestant2(contestant2), result(result) {}
    };

    vector <Match> matches;
public:
    // default constructor
    CContest() {}

    // destructor
    ~CContest() {}

    // addMatch ( contestant1, contestant2, result )
    CContest<M_> &addMatch(const string &contestant1, const string &contestant2, const M_ &result);

    // isOrdered ( comparator )
    template<typename Comparator>
    bool isOrdered(const Comparator cmp) const;

    // results ( comparator )
    template<typename Comparator>
    list <string> results(const Comparator cmp) const;
};

template<typename M_>
CContest<M_> &CContest<M_>::addMatch(const string &contestant1, const string &contestant2, const M_ &result) {
    // check if there is match with that pair of contestants
    for (const auto &m : matches) {
        if ((m.contestant1 == contestant1 and m.contestant2 == contestant2) or (m.contestant1 == contestant2 and m.contestant2 == contestant1))
            throw std::logic_error("Error");
    }

    Match match(contestant1, contestant2, result);
    matches.push_back(match);
    return *this;
}

template<typename M_>
template<typename Comparator>
bool CContest<M_>::isOrdered(const Comparator cmp) const {
    map <string, set<string>> graph; // [contestant, <defeated_contestants>]

    for (const auto &m : matches) { // create vertice for every contestant
        graph[m.contestant1] = set<string>();
        graph[m.contestant2] = set<string>();
    }

    // fill graph
    for (const auto &m : matches) {
        int res = cmp(m.result);

        if (res > 0) // first contestant won
            graph[m.contestant1].insert(m.contestant2);
        else if (res < 0)  // second contestant won
            graph[m.contestant2].insert(m.contestant1);
        else return false; // if draw
    }

    // khan's algorithm for topological sort https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
    map <string, int> indegree; // [contestant, indegree]

    // for every vertice set it's indegree to 0
    for (const auto &g : graph) {
        indegree[g.first] = 0;
    }

    // fill indegrees for every vertice
    for (const auto &g : graph) {
        for (const auto &neighbour : g.second) {
            indegree[neighbour]++;
        }
    }

    queue<string> q;

    // insert in queue all vertices with degree == 0
    for (const auto & d : indegree)
        if (d.second == 0)
            q.push(d.first);


    list<string> top; // result of topological sort

    // Dequeue vertices from the queue, and if the index of an adjacent vertex becomes 0, add it to the queue.
    while (!q.empty()) {

        // extract front element from queue
        string vertice = q.front();
        q.pop();

        // add it to result of topological sort
        top.push_back(vertice);

        // for each neighbour of this vertice, decrease it's indegree by one
        for (const auto &neighbour : graph[vertice])
            if (--indegree[neighbour] == 0) // if indgegree is zero, add it to queue
                q.push(neighbour);

        // sort must be unique, so it cant be more than one vertice at once
        if (q.size() > 1)
            return false;
    }
    return top.size() == graph.size(); // checking if there was a cycle
}

template<typename M_>
template<typename Comparator>
list<string> CContest<M_>::results(const Comparator cmp) const {
    map <string, set<string>> graph; // [contestant, <defeated_contestants>]

    for (const auto &m : matches) { // create vertice for every contestant
        graph[m.contestant1] = set<string>();
        graph[m.contestant2] = set<string>();
    }

    // fill graph
    for (const auto &m : matches) {
        int res = cmp(m.result);

        if (res > 0) // first contestant won
            graph[m.contestant1].insert(m.contestant2);
        else if (res < 0)  // second contestant won
            graph[m.contestant2].insert(m.contestant1);
        else throw std::logic_error("Error"); // if draw, we cannot define the order
    }

    // khan's algorithm for topological sort https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
    map <string, int> indegree; // [contestant, indegree]

    // for every vertice set it's indegree to 0
    for (const auto &g : graph) {
        indegree[g.first] = 0;
    }

    // fill indegrees for every vertice
    for (const auto &g : graph) {
        for (const auto &neighbour : g.second) {
            indegree[neighbour]++;
        }
    }

    queue<string> q;

    // insert in queue all vertices with degree == 0
    for (const auto & d : indegree)
        if (d.second == 0)
            q.push(d.first);


    list<string> top; // result of topological sort

    // Dequeue vertices from the queue, and if the index of an adjacent vertex becomes 0, add it to the queue.
    while (!q.empty()) {

        // extract front element from queue
        string vertice = q.front();
        q.pop();

        // add it to result of topological sort
        top.push_back(vertice);

        // for each neighbour of this vertice, decrease it's indegree by one
        for (const auto &neighbour : graph[vertice])
            if (--indegree[neighbour] == 0) // if indgegree is zero, add it to queue
                q.push(neighbour);

        // sort must be unique, so it cant be more than one vertice at once
        if (q.size() > 1)
            throw std::logic_error("Error");
    }

    // checking if there was a cycle
    if (top.size() != graph.size())
        throw std::logic_error("Error");

    return top;
}

#ifndef __PROGTEST__
struct CMatch {
public:
    CMatch(int a, int b) : m_A(a), m_B(b) {}
    int m_A;
    int m_B;
};

class HigherScoreThreshold {
    int m_DiffAtLeast;
public:
    HigherScoreThreshold (int diffAtLeast) : m_DiffAtLeast(diffAtLeast) {}
    int operator () (const CMatch &x) const {
        return (x.m_A > x.m_B + m_DiffAtLeast) - (x.m_B > x.m_A + m_DiffAtLeast);
    }
};

int HigherScore (const CMatch &x) {
    return (x.m_A > x.m_B) - (x.m_B > x.m_A);
}

int main () {
    CContest<CMatch>  x;

    x . addMatch ( "C++", "Pascal", CMatch ( 10, 3 ) )
            . addMatch ( "C++", "Java", CMatch ( 8, 1 ) )
            . addMatch ( "Pascal", "Basic", CMatch ( 40, 0 ) )
            . addMatch ( "Java", "PHP", CMatch ( 6, 2 ) )
            . addMatch ( "Java", "Pascal", CMatch ( 7, 3 ) )
            . addMatch ( "PHP", "Basic", CMatch ( 10, 0 ) );


    assert ( ! x . isOrdered ( HigherScore ) );
    try
    {
        list<string> res = x . results ( HigherScore );
        assert ( "Exception missing!" == nullptr );
    }
    catch ( const logic_error & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == nullptr );
    }

    x . addMatch ( "PHP", "Pascal", CMatch ( 3, 6 ) );

    assert ( x . isOrdered ( HigherScore ) );
    try
    {
        list<string> res = x . results ( HigherScore );
        assert ( ( res == list<string>{ "C++", "Java", "Pascal", "PHP", "Basic" } ) );
    }
    catch ( ... )
    {
        assert ( "Unexpected exception!" == nullptr );
    }


    assert ( ! x . isOrdered ( HigherScoreThreshold ( 3 ) ) );
    try
    {
        list<string> res = x . results ( HigherScoreThreshold ( 3 ) );
        assert ( "Exception missing!" == nullptr );
    }
    catch ( const logic_error & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == nullptr );
    }

    assert ( x . isOrdered ( [] ( const CMatch & x )
                             {
                                 return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A );
                             } ) );
    try
    {
        list<string> res = x . results ( [] ( const CMatch & x )
                                         {
                                             return ( x . m_A < x . m_B ) - ( x . m_B < x . m_A );
                                         } );
        assert ( ( res == list<string>{ "Basic", "PHP", "Pascal", "Java", "C++" } ) );
    }
    catch ( ... )
    {
        assert ( "Unexpected exception!" == nullptr );
    }

    CContest<bool>  y;

    y . addMatch ( "Python", "PHP", true )
            . addMatch ( "PHP", "Perl", true )
            . addMatch ( "Perl", "Bash", true )
            . addMatch ( "Bash", "JavaScript", true )
            . addMatch ( "JavaScript", "VBScript", true );

    assert ( y . isOrdered ( [] ( bool v )
                             {
                                 return v ? 10 : - 10;
                             } ) );
    try
    {
        list<string> res = y . results ( [] ( bool v )
                                         {
                                             return v ? 10 : - 10;
                                         });
        assert ( ( res == list<string>{ "Python", "PHP", "Perl", "Bash", "JavaScript", "VBScript" } ) );
    }
    catch ( ... )
    {
        assert ( "Unexpected exception!" == nullptr );
    }

    y . addMatch ( "PHP", "JavaScript", false );
    assert ( !y . isOrdered ( [] ( bool v )
                              {
                                  return v ? 10 : - 10;
                              } ) );
    try
    {
        list<string> res = y . results ( [] ( bool v )
                                         {
                                             return v ? 10 : - 10;
                                         } );
        assert ( "Exception missing!" == nullptr );
    }
    catch ( const logic_error & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == nullptr );
    }

    try
    {
        y . addMatch ( "PHP", "JavaScript", false );
        assert ( "Exception missing!" == nullptr );
    }
    catch ( const logic_error & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == nullptr );
    }

    try
    {
        y . addMatch ( "JavaScript", "PHP", true );
        assert ( "Exception missing!" == nullptr );
    }
    catch ( const logic_error & e )
    {
    }
    catch ( ... )
    {
        assert ( "Invalid exception thrown!" == nullptr );
    }
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
