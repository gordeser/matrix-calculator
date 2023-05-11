#ifndef __PROGTEST__
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <memory>
using namespace std;

/** @class Represents date in format (year-month-day) */
class CDate {
    /** @var year */
    int16_t m_Year;
    /** @var month */
    int8_t m_Month;
    /** @var day */
    int8_t m_Day;
public:
    /**
     * Initialise date with given year month and day
     * @param year to set
     * @param month to set
     * @param day to set
     */
    CDate(int year, int month, int day);

    /**
     * Method that compares date with given date
     * @param date to compare with
     * @return
     * 1) Value > 0 if given date is less \n
     * 2) Value < 0 if given date is bigger
     * 3) Value == 0 if given date is equal
     */
    int compare(const CDate &date) const;

    /**
     * Method that gets year of date
     * @return year of date
     */
    int year() const;

    /**
     * Method that gets month of date
     * @return month of date
     */
    int month() const;

    /**
     * Method that gets day of date
     * @return day of date
     */
    int day() const;

    /**
     * Overloaded operator << to print date
     * @param out ostream to put date in
     * @param date to print
     * @return stream with printed date
     */
    friend ostream &operator << (ostream &out, const CDate &date);
};

CDate::CDate(int year, int month, int day) : m_Year(year), m_Month(month), m_Day(day) {}

int CDate::compare(const CDate &date) const {
    if (m_Year != date.m_Year) return m_Year - date.m_Year;
    if (m_Month != date.m_Month) return m_Month - date.m_Month;
    return m_Day - date.m_Day;
}

int CDate::year() const {
    return m_Year;
}

int CDate::month() const {
    return m_Month;
}

int CDate::day() const {
    return m_Day;
}

ostream &operator<<(ostream &out, const CDate &date) {
    char oldFill = out.fill(); // keep the old fill symbol
    return out << setfill('0') << setw(4) << date.m_Year << "-"
               << setw(2) << static_cast<int>(date.m_Month) << "-"
               << setw(2) << static_cast<int>(date.m_Day)
               << setfill(oldFill); // put it back
}

#endif /* __PROGTEST__ */

/**
 * Function that transforms string to lowercase
 * @param str to transform
 * @return transformed string
 */
string toLowercase(const string &str) {
    string modified = str;

    // transform all letters into lowercase
    transform(modified.begin(), modified.end(), modified.begin(), ::tolower);
    return modified;
}

/**
 * Function that deletes unnecessary spaces
 * (more than one space between words and spaces before and after all words)
 * @param str to modify
 * @return modified string
 */
string deleteSpaces(const string &str) {
    string modified = str;

    // delete all spaces before all words
    size_t pos_start = modified.find_first_not_of(" \t\n\v\f\r");
    if (pos_start != string::npos)
        modified.erase(0, pos_start);

    // delete all spaces after all words
    size_t pos_end = modified.find_last_not_of(" \t\n\v\f\r");
    if (pos_end != string::npos)
        modified.erase(pos_end+1);

    // delete all "more than one" spaces between words in str
    size_t pos_between = modified.find("  ");
    while (pos_between != string::npos) {
        modified.replace(pos_between, 2, " ");
        pos_between = modified.find("  ");
    }

    return modified;
}

/**
 * Function that applies functions toLowercase and deleteSpaces on given string
 * @param name to modify
 * @return modified string
 */
string updateName(const string &name) {
    string modified = deleteSpaces(name);
    modified = toLowercase(modified);
    return modified;
}

/** @class Represents some invoice */
class CInvoice {
    /** @var index of invoice */
    size_t m_Idx;

    /** @var date when invoice was made */
    CDate m_Date;

    /** @var name of seller company  */
    string m_Seller;

    /** @var name of buyer company */
    string m_Buyer;

    /** @var amount of invoice's money */
    unsigned int m_Amount;

    /** @var vat of invoice */
    double m_Vat;
public:
    /**
     * Initialise invoice with given parameters
     * @param date to set
     * @param seller to set
     * @param buyer to set
     * @param amount to set
     * @param vat to set
     */
    CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double vat);

    /**
     * Method to get index of invoice
     * @return index of invoice
     */
    size_t idx() const;

    /**
     * Method to set invoice's index
     * @param idx to set
     */
    void setIdx(size_t idx);

    /**
     * Method to get date of invoice
     * @return date of invoice
     */
    CDate date() const;

    /**
     * Method to get seller company name
     * @return name of seller company
     */
    string seller() const;

    /**
     * Method to get buyer company name
     * @return name of buyer company
     */
    string buyer() const;

    /**
     * Method to get amount of invoice
     * @return amount of invoice
     */
    unsigned int amount() const;

    /**
     * Method to get vat of invoice
     * @return vat of invoice
     */
    double vat() const;

    /**
     * Overloaded operator < to compare two invoices
     * @param invoice to compare with
     * @return True if first invoice is "less" than given \n
     *         False if not
     */
    bool operator < (const CInvoice &invoice) const;

    /**
     * Overloaded operator == to compare two invoices
     * @param invoice to compare with
     * @return True if two invoices are identical \n False if not
     */
    bool operator == (const CInvoice &invoice) const;

    /**
     * Overloaded operator << to print all data of invoice
     * @param out ostream to put all data in
     * @param invoice to print
     * @return stream with all data of given invoice
     */
    friend ostream& operator << (ostream &out, const CInvoice &invoice);
};

CInvoice::CInvoice(const CDate &date, const string &seller, const string &buyer, unsigned int amount, double vat)
        : m_Date(date), m_Seller(seller), m_Buyer(buyer), m_Amount(amount), m_Vat(vat) {}

size_t CInvoice::idx() const {
    return m_Idx;
}

void CInvoice::setIdx(size_t idx) {
    m_Idx = idx;
}

CDate CInvoice::date() const {
    return m_Date;
}

string CInvoice::seller() const {
    return m_Seller;
}

string CInvoice::buyer() const {
    return m_Buyer;
}

unsigned int CInvoice::amount() const {
    return m_Amount;
}

double CInvoice::vat() const {
    return m_Vat;
}

bool CInvoice::operator < (const CInvoice &invoice) const {
    if (m_Date.compare(invoice.m_Date))
        return m_Date.compare(invoice.m_Date) < 0;

    if (m_Seller != invoice.m_Seller)
        return m_Seller < invoice.m_Seller;

    if (m_Buyer != invoice.m_Buyer)
        return m_Buyer < invoice.m_Buyer;

    if (m_Amount != invoice.m_Amount)
        return m_Amount < invoice.m_Amount;

    return m_Vat < invoice.m_Vat;
}

bool CInvoice::operator == (const CInvoice &invoice) const {
    if (this->m_Date.compare(invoice.m_Date))
        return false;

    if (this->m_Seller != invoice.m_Seller)
        return false;

    if (this->m_Buyer != invoice.m_Buyer)
        return false;

    if (this->m_Amount != invoice.m_Amount)
        return false;

    if (this->m_Vat != invoice.m_Vat)
        return false;

    return true;
}

ostream &operator << (ostream &out, const CInvoice &invoice) {
    out << invoice.m_Idx << " ";
    out << invoice.m_Date << " ";
    out << invoice.m_Seller << " ";
    out << invoice.m_Buyer << " ";
    out << invoice.m_Amount << " ";
    out << invoice.m_Vat;
    return out;
}

/** @class Represents sorting keys to sort invoices with */
class CSortOpt {
    /** @var vector of pairs, where \n
     * first element of pair - key to sort \n
     * second element of pair - whether to sort in ascending way */
    vector <pair<int, bool>> m_Keys;
public:
    /** @var key to sort by date  */
    static const int BY_DATE = 0;
    /** @var key to sort by buyer's name  */
    static const int BY_BUYER = 1;
    /** @var key to sort by seller's name  */
    static const int BY_SELLER = 2;
    /** @var key to sort by amount  */
    static const int BY_AMOUNT = 3;
    /** @var key to sort by vat  */
    static const int BY_VAT = 4;

    /** Initialise empty object of CSortOpt */
    CSortOpt();

    /**
     * Method that adds sorting key in vector of keys
     * @param key to sort
     * @param ascending
     * @return reference of the same CSortOpt object
     */
    CSortOpt &addKey (int key, bool ascending = true);

    /**
     * Overloaded operator () that compares two invoices (helps to sort some container of invoices)
     * @param first invoice to compare
     * @param second invoice to compare with
     * @return True if first invoice is "less" than second \n
     *         False if second is "less" than first
     */
    bool operator () (const CInvoice &first, const CInvoice &second) const;
};

CSortOpt::CSortOpt() {}

CSortOpt &CSortOpt::addKey(int key, bool ascending) {
    auto keyPair = make_pair(key, ascending);
    m_Keys.push_back(keyPair);
    return *this;
}

bool CSortOpt::operator () (const CInvoice &first, const CInvoice &second) const {
    // for each sorting key
    for (const auto &key :m_Keys) {
        int criterion = key.first;
        bool ascending = key.second;

        if (criterion == CSortOpt::BY_DATE) {
            int result = first.date().compare(second.date()); // compare first and second date

            if (result == 0) // if dates are equal then go to the next key
                continue;

            if (ascending) return result < 0;
            else return result > 0;
        } else if (criterion == CSortOpt::BY_BUYER) {
            string firstBuyer = toLowercase(first.buyer());
            string secondBuyer = toLowercase(second.buyer());

            if (firstBuyer == secondBuyer)
                continue;

            if (ascending) return firstBuyer < secondBuyer;
            else return secondBuyer < firstBuyer;
        } else if (criterion == CSortOpt::BY_SELLER) {
            string firstSeller = toLowercase(first.seller());
            string secondSeller = toLowercase(second.seller());

            if (firstSeller == secondSeller)
                continue;

            if (ascending) return firstSeller < secondSeller;
            else return secondSeller < firstSeller;
        } else if (criterion == CSortOpt::BY_AMOUNT) {
            unsigned int firstAmount = first.amount();
            unsigned int secondAmount = second.amount();

            if (firstAmount == secondAmount)
                continue;

            if (ascending) return firstAmount < secondAmount;
            else return secondAmount < firstAmount;
        } else if (criterion == CSortOpt::BY_VAT) {
            double firstVat = first.vat();
            double secondVat = second.vat();

            if (firstVat == secondVat)
                continue;

            if (ascending) return firstVat < secondVat;
            else return secondVat < firstVat;
        }
    }
    // if we cant compare with given sorting keys, we sort by indexes of invoices
    return first.idx() < second.idx();
}

/** @class Represents database of registered companies and their invoices */
class CVATRegister {
    /**
     * @struct Struct that will be used as comparator to compare two company names
     */
    struct Cmp {
        /**
         * Comparator that compares two company names in lowercase and without unnecessary spaces
         * @param first company name
         * @param second company name
         * @return True if first string is "less" than second \n False if not
         */
        bool operator () (const string &first, const string &second) const {
            string tmp_a = updateName(first);
            string tmp_b = updateName(second);
            return tmp_a < tmp_b;
        }
    };

    /** @var index that will be set for next invoice */
    size_t m_Idx = 0;

    /** @var map of names where key is updatedName (in lowercase without unnecessary spaces) and value is the original name */
    map <string, string> m_Names;

    /**
     * @var map of invoices where key is updatedName \n
     * value is pair of sets of invoices \n
     * 1) first set is set of issued invoices connected with that company \n
     * 2) second set is set of accepted invoices connected with that company
     * */
    map <string, pair <set <CInvoice>, set <CInvoice>>, Cmp> m_Invoices;
public:
    /**
     * Initialize empty object of class CVATRegister
     */
    CVATRegister ();

    /**
     * Method that registers company in database
     * @param name of company
     * @return True if company has been successfully registered \n False if company has been already registered
     */
    bool registerCompany(const string &name);

    /**
     * Method that add invoice to issued invoices of two companies that connected with that invoice
     * @param invoice to add
     * @return True if invoice has been successfully added \n
     * False if \n
     * 1) That invoice is already in database \n
     * or \n
     * 2) Companies in invoice are not registered \n
     * or \n
     * 3) Buyer and seller in invoice are the same company
     */
    bool addIssued(const CInvoice &invoice);

    /**
     * Method that add invoice to accepted invoices of two companies that connected with that invoice
     * @param invoice to add
     * @return True if invoice has been successfully added \n
     * False if \n
     * 1) That invoice is already in database \n
     * or \n
     * 2) Companies in invoice are not registered \n
     * or \n
     * 3) Buyer and seller in invoice are the same company
     */
    bool addAccepted(const CInvoice &invoice);

    /**
     * Method that removes invoice from issued invoices of two companies that connected with that invoice
     * @param invoice to remove
     * @return True if invoice has been successfully removed \n
     * False if that invoice is not registered in database
     */
    bool delIssued(const CInvoice &invoice);

    /**
     * Method that removes invoice from accepted invoices of two companies that connected with that invoice
     * @param invoice to remove
     * @return True if invoice has been successfully removed \n
     * False if that invoice is not registered in database
     */
    bool delAccepted(const CInvoice &invoice);

    /**
     * Method that finds unmatched invoices (registered only either as issued or as accepted)
     * of given company and then sort it with given sorting keys
     * @param company to find their unmatched invoices
     * @param sortBy sorting keys to sort unmatched invoices with them
     * @return sorted list of unmatched companies \n
     * If there is no unmatched invoices, list will be empty
     */
    list<CInvoice> unmatched(const string &company, const CSortOpt &sortBy) const;
};

CVATRegister::CVATRegister() {}

bool CVATRegister::registerCompany(const string &name) {
    // if company with that name is already registered
    if (m_Invoices.count(name) != 0) return false;

    // register the company
    string updated = updateName(name);

    // give them a pair of issued and accepted invoices to save in
    auto pairSetInvoices = make_pair(set<CInvoice> (), set<CInvoice> ());
    m_Invoices[updated] = pairSetInvoices;

    m_Names[updated] = name; // keep the original name of company
    return true;
}

bool CVATRegister::addIssued(const CInvoice &invoice) {
    // check if seller and buyer aren't the same company
    string sellerName = updateName(invoice.seller());
    string buyerName = updateName(invoice.buyer());
    if (sellerName == buyerName) return false;

    // check if seller is registered
    auto sellerIt = m_Names.find(sellerName);
    if (sellerIt == m_Names.end()) return false;

    // check if buyer is registered
    auto buyerIt = m_Names.find(buyerName);
    if (buyerIt == m_Names.end()) return false;

    // get the registered names of buyer and seller
    string registeredNameSeller = sellerIt->second;
    string registeredNameBuyer = buyerIt->second;

    // create the invoice that will be inserted in set of issued invoices for seller and buyer
    CInvoice issued(invoice.date(), registeredNameSeller, registeredNameBuyer, invoice.amount(), invoice.vat());
    issued.setIdx(m_Idx);

    // try to insert invoice into set of issued invoices for seller
    auto insertedSeller = m_Invoices[registeredNameSeller].first.insert(issued);
    if (!insertedSeller.second) return false; // check if that invoice already was

    // try to insert invoice into set of issued invoices for buyer
    auto insertedBuyer = m_Invoices[registeredNameBuyer].first.insert(issued);
    if (!insertedBuyer.second) return false; // check if that invoice already was

    m_Idx++;
    return true;
}

bool CVATRegister::addAccepted(const CInvoice &invoice) {
    // check if seller and buyer aren't the same company
    string sellerName = updateName(invoice.seller());
    string buyerName = updateName(invoice.buyer());
    if (sellerName == buyerName) return false;

    // check if seller is registered
    auto sellerIt = m_Names.find(sellerName);
    if (sellerIt == m_Names.end()) return false;

    // check if buyer is registered
    auto buyerIt = m_Names.find(buyerName);
    if (buyerIt == m_Names.end()) return false;

    // get the registered names of buyer and seller
    string registeredNameSeller = sellerIt->second;
    string registeredNameBuyer = buyerIt->second;

    // create the invoice that will be inserted in set of accepted invoices for seller and buyer
    CInvoice accepted(invoice.date(), registeredNameSeller, registeredNameBuyer, invoice.amount(), invoice.vat());
    accepted.setIdx(m_Idx);

    // try to insert invoice into set of accepted invoices for seller
    auto insertedSeller = m_Invoices[registeredNameSeller].second.insert(accepted);
    if (!insertedSeller.second) return false; // check if that invoice already was

    // try to insert invoice into set of accepted invoices for buyer
    auto insertedBuyer = m_Invoices[registeredNameBuyer].second.insert(accepted);
    if (!insertedBuyer.second) return false; // check if that invoice already was

    m_Idx++;
    return true;
}

bool CVATRegister::delIssued(const CInvoice &invoice) {
    string seller = updateName(invoice.seller());
    string buyer = updateName(invoice.buyer());

    // check if seller is registered
    auto sellerIt = m_Names.find(seller);
    if (sellerIt == m_Names.end()) return false;

    // check if buyer is registered
    auto buyerIt = m_Names.find(buyer);
    if (buyerIt == m_Names.end()) return false;

    // get the registered names of buyer and seller
    string registeredNameSeller = sellerIt->second;
    string registeredNameBuyer = buyerIt->second;

    // create a copy of invoice that will be erased out of set of issued invoices for seller and buyer
    CInvoice issued(invoice.date(), registeredNameSeller, registeredNameBuyer, invoice.amount(), invoice.vat());

    // try to erase invoice out of set of issued invoices for seller
    size_t countErasedSeller = m_Invoices[seller].first.erase(issued);
    if (!countErasedSeller) return false; // if we didn't find invoice to erase for seller

    // try to erase invoice out of set of issued invoices for buyer
    size_t countErasedBuyer = m_Invoices[buyer].first.erase(issued);
    if (!countErasedBuyer) return false; // if we didn't find invoice to erase for buyer

    return true;
}

bool CVATRegister::delAccepted(const CInvoice &invoice) {
    string seller = updateName(invoice.seller());
    string buyer = updateName(invoice.buyer());

    // check if seller is registered
    auto sellerIt = m_Names.find(seller);
    if (sellerIt == m_Names.end()) return false;

    // check if buyer is registered
    auto buyerIt = m_Names.find(buyer);
    if (buyerIt == m_Names.end()) return false;

    // get the registered names of buyer and seller
    string registeredNameSeller = sellerIt->second;
    string registeredNameBuyer = buyerIt->second;

    // create a copy of invoice that will be erased out of set of accepted invoices for seller and buyer
    CInvoice accepted(invoice.date(), registeredNameSeller, registeredNameBuyer, invoice.amount(), invoice.vat());

    // try to erase invoice out of set of accepted invoices for seller
    size_t countErasedSeller = m_Invoices[seller].second.erase(accepted);
    if (!countErasedSeller) return false; // if we didn't find invoice to erase for seller

    // try to erase invoice out of set of accepted invoices for buyer
    size_t countErasedBuyer = m_Invoices[buyer].second.erase(accepted);
    if (!countErasedBuyer) return false; // if we didn't find invoice to erase for buyer

    return true;
}

list<CInvoice> CVATRegister::unmatched(const string &company, const CSortOpt &sortBy) const {
    list <CInvoice> unmatched;
    string name = updateName(company);

    // check if company is registered
    if (m_Names.find(name) == m_Names.end()) return unmatched;

    // set the iterator on the found company
    auto companyIt = m_Invoices.find(name);

    // check all issued invoices to be paired
    for (const auto &issued : companyIt->second.first) {

        // try to find the same invoice (issued) in accepted invoices
        auto acceptedIt = companyIt->second.second.find(issued);

        // if we didn't find this invoice in accepted invoices, add it to unmatched
        if (acceptedIt == companyIt->second.second.end())
            unmatched.push_back(issued);
    }

    // check all accepted invoices to be paired
    for (const auto &accepted : companyIt->second.second) {

        // try to find the same invoice (accepted) in issued invoices
        auto issuedIt = companyIt->second.first.find(accepted);

        // if we didn't find this invoice in issued invoices, add it to unmatched
        if (issuedIt == companyIt->second.first.end())
            unmatched.push_back(accepted);
    }

    // if size of unmatched is less than 1 then we don't need to sort the list of unmatched
    if (unmatched.size() <= 1) return unmatched;

    unmatched.sort(sortBy);
    return unmatched;
}


#ifndef __PROGTEST__
/**
 * Function that compares two lists of invoices
 * @param first list of invoices
 * @param second list of invoices
 * @return True if two lists are equal \n False if not
 */
bool equalLists(const list<CInvoice> &first, const list<CInvoice> &second) {
    return equal(first.begin(), first.end(), second.begin(), second.end());
}

/**
 * Function with basic tests from Progtest
 */
void testProgtest() {
    CVATRegister r;
    assert ( r . registerCompany ( "first Company" ) );
    assert ( r . registerCompany ( "Second     Company" ) );
    assert ( r . registerCompany ( "ThirdCompany, Ltd." ) );
    assert ( r . registerCompany ( "Third Company, Ltd." ) );
    assert ( !r . registerCompany ( "Third Company, Ltd." ) );
    assert ( !r . registerCompany ( " Third  Company,  Ltd.  " ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 20 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "FirSt Company", "Second Company ", 200, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 100, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Second Company ", "First Company", 300, 30 ) ) );
    assert ( r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "Third  Company,  Ltd.", "  Second    COMPANY ", 400, 34 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company ", 300, 30 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "First Company", "First   Company", 200, 30 ) ) );
    assert ( !r . addIssued ( CInvoice ( CDate ( 2000, 1, 4 ), "      Another Company       ", "  First   Company     ", 200, 30 ) ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, false ) . addKey ( CSortOpt::BY_DATE, false ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_DATE, true ) . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_VAT, true ) . addKey ( CSortOpt::BY_AMOUNT, true ) . addKey ( CSortOpt::BY_DATE, true ) . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "second company", CSortOpt () . addKey ( CSortOpt::BY_DATE, false ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Third Company, Ltd.", "Second     Company", 400, 34.000000 )
                                  } ) );
    assert ( equalLists ( r . unmatched ( "last company", CSortOpt () . addKey ( CSortOpt::BY_VAT, true ) ),
                          list<CInvoice>
                                  {
                                  } ) );
    assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( r . addAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "Second company ", "First Company", 300, 32 ) ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2001, 1, 1 ), "First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "A First Company", "Second Company ", 200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Hand", 200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 1200, 30 ) ) );
    assert ( !r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", "Second Company", 200, 130 ) ) );
    assert ( r . delIssued ( CInvoice ( CDate ( 2000, 1, 2 ), "First Company", "Second Company", 200, 30 ) ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    assert ( r . delAccepted ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Third Company, Ltd.", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
    assert ( r . delIssued ( CInvoice ( CDate ( 2000, 1, 1 ), "First Company", " Third  Company,  Ltd.   ", 200, 30 ) ) );
    assert ( equalLists ( r . unmatched ( "First Company", CSortOpt () . addKey ( CSortOpt::BY_SELLER, true ) . addKey ( CSortOpt::BY_BUYER, true ) . addKey ( CSortOpt::BY_DATE, true ) ),
                          list<CInvoice>
                                  {
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 20.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 100, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "first Company", "Second     Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 2 ), "first Company", "Second     Company", 200, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 30.000000 ),
                                          CInvoice ( CDate ( 2000, 1, 1 ), "Second     Company", "first Company", 300, 32.000000 )
                                  } ) );
}


int main () {
    testProgtest();
    cout << "DONE testProgtest" << endl;
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
