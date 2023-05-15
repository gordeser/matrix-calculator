#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
#endif /* __PROGTEST__ */

vector<int> fibonacci_numbers(int n) {
    vector<int> fib(2, 1); // first two values are 1
    while (fib.back() < n) { // if last number of vector is less than needed number
        int size = fib.size();
        int next_fib = fib[size-1] + fib[size-2];
        fib.push_back(next_fib); // add to vector next number
    }
    return fib;
}

vector<int> fibonacci_bits(int n) {
    vector<int> fib = fibonacci_numbers(n);
    vector<int> result(fib.size(), 0); // maximum bits of fib number
    for (int i = fib.size() - 1; i >= 0; i--) {
        if (n >= fib[i]) { // if n fits into fib number
            result[i] = 1; // then
            n -= fib[i];
        }
    }
    return result;
}

// write bitstream to the file
bool write_to_fib(ofstream &out, string &bitstream) {
    string tmp = string(bitstream.rbegin(), bitstream.rend());
    char byte = 0;
    for (char bit : tmp) { // all bits from bitstream move into byte
        byte <<= 1;
        byte |= bit - '0';
    }
    out.put(byte); if (!out.good() || out.bad()) return false;
    bitstream = ""; // clear bitstream
    return true;
}

bool utf8ToFibonacci(const char *inFile, const char *outFile) {
    ifstream in(inFile, ios::in | ios::binary);
    ofstream out(outFile, ios::out | ios::binary);
    if (!in.is_open() || !out.is_open()) return false;

    unsigned char byte1, byte2, byte3, byte4;
    unsigned int num;
    string bitstring;
    // used reinterpret_cast like here https://stackoverflow.com/questions/41319180/what-does-reinterpret-castchar-st-and-1static-castint-mean
    while (in.read(reinterpret_cast<char*>(&byte1), 1)) {
        if ((byte1 & 0x80) == 0x00) { // 1 byte char 0xxxxxxx
            num = byte1;
        } else if ((byte1 & 0xE0) == 0xC0) { // 2 byte char 110xxxxx 10xxxxxx
            if (!in.read(reinterpret_cast<char*>(&byte2), 1)) return false; // if something was wrong
            if ((byte2 & 0xC0) != 0x80) return false; // if bytes are wrong
            num = ((byte1 & 0x1F) << 6) | (byte2 & 0x3F); // convert into decimal number
        } else if ((byte1 & 0xF0) == 0xE0) {  // 3 byte char 1110xxxx 10xxxxxx 10xxxxxx
            if (!in.read(reinterpret_cast<char*>(&byte2), 1) || !in.read(reinterpret_cast<char*>(&byte3), 1)) return false;
            if (((byte2 & 0xC0) != 0x80) || ((byte3 & 0xC0) != 0x80)) return false;
            num = ((byte1 & 0x0F) << 12) | ((byte2 & 0x3F) << 6) | (byte3 & 0x3F);
        } else if ((byte1 & 0xF8) == 0xF0) { // 4 byte char 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            if (!in.read(reinterpret_cast<char*>(&byte2), 1) || !in.read(reinterpret_cast<char*>(&byte3), 1) || !in.read(reinterpret_cast<char*>(&byte4), 1)) return false;
            if (((byte2 & 0xC0) != 0x80) || ((byte3 & 0xC0) != 0x80) || ((byte4 & 0xC0) != 0x80)) return false;
            num = ((byte1 & 0x07) << 18) | ((byte2 & 0x3F) << 12) | ((byte3 & 0x3F) << 6) | (byte4 & 0x3F);
        } else return false; // we have bad bytes
        vector <int> tmp = fibonacci_bits(num+1); // according to the task, we use fib_num + 1
        for (size_t i = 1; i < tmp.size()-1; ++i) {
            bitstring.push_back(tmp[i] + '0'); // push back into bitstring 1 or 0 in char type (we have ints)
            if (bitstring.length() == 8) {
                bool test = write_to_fib(out, bitstring); // if we have a ready byte (8 bits), we write it to the file
                if (!test) return false;
            }
        }
        if (tmp[tmp.size()-1] == 0) { // because of the algorithm, there may be 0 on the end of fib num
            bitstring.push_back('1'); // and replace it with 1 on the end
            if (bitstring.length() == 8) {
                bool test = write_to_fib(out, bitstring);
                if (!test) return false;
            }
        }
        else { // or put 1 on the end and additional 1
            bitstring.push_back('1');
            if (bitstring.length() == 8) {
                bool test = write_to_fib(out, bitstring);
                if (!test) return false;
            }
            bitstring.push_back('1');
            if (bitstring.length() == 8) {
                bool test = write_to_fib(out, bitstring);
                if (!test) return false;
            }
        }
    }
    if (bitstring.length() > 0 and bitstring.length() < 8) { // if we need add padding zeros
        for (;bitstring.length() != 8;) bitstring.push_back('0');
        bool test = write_to_fib(out, bitstring);
        if (!test) return false;
    }
    in.close();
    out.close();
    return true;
}

// algorithm to convert position of fib number into fib number
int pos_into_number(int pos) {
    if (pos == 0) return 1;
    int first = 1, second = 2, third;
    for (int i = 2; i <= pos; ++i) {
        third = second + first;
        first = second;
        second = third;
    }
    return second;
}

int fibonacci_bits_to_num(const string &fib) {
    int num = 0;
    for (size_t i = 0; i < fib.length()-1; ++i)
        if (fib[i] == '1') num += pos_into_number(i);
    return num-1;
}

bool fibonacciToUtf8(const char *inFile, const char *outFile) {
    ifstream in(inFile, ios::in | ios::binary);
    ofstream out(outFile, ios::out | ios::binary);
    if (!in.is_open() || !out.is_open()) return false;
    char byte;
    string buffer;
    string bitstring;
    while (in.get(byte)) {
        buffer = "";
        // convert char into bits
        for (int i = 7; i >= 0; i--) {
            if (((byte >> i) & 1) == 1) buffer.push_back('1');
            else buffer.push_back('0');
        }
        int len = buffer.length();
        for (int i = 0; i < len / 2; ++i) swap(buffer[i], buffer[len-i-1]); // reverse buffer
        buffer = bitstring + buffer; // add on start of buffer numbers that were left from previous byte
        while (true) {
            size_t pos = buffer.find("11");
            if (pos == string::npos) break; // if there are no 11
            string sub = buffer.substr(0, pos+2); // get first occurrence of 11 with them(+2)
            int num = fibonacci_bits_to_num(sub);
            if (num <= 0x7f) { // 1 byte char 0xxxxxxx
                char byte1 = num & 0x7f;
                out.write(&byte1, sizeof(byte1)); if (!out.good() || out.bad()) return false;
            } else if (num <= 0x7ff) { // 2 byte char 110xxxxx 10xxxxxx
                char byte1 = 0xC0 | (num >> 6);
                char byte2 = 0x80 | (num & 0x3F);
                out.write(&byte1, sizeof(byte1)); if (!out.good() || out.bad()) return false;
                out.write(&byte2, sizeof(byte2)); if (!out.good() || out.bad()) return false;
            } else if (num <= 0xffff) { // 3 byte char 1110xxxx 10xxxxxx 10xxxxxx
                char byte1 = 0xE0 | (num >> 12);
                char byte2 = 0x80 | ((num >> 6) & 0x3F);
                char byte3 = 0x80 | (num & 0x3F);
                out.write(&byte1, sizeof(byte1)); if (!out.good() || out.bad()) return false;
                out.write(&byte2, sizeof(byte2)); if (!out.good() || out.bad()) return false;
                out.write(&byte3, sizeof(byte3)); if (!out.good() || out.bad()) return false;
            } else if (num <= 0x10ffff) { // 4 byte char 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
                char byte1 = 0xF0 | (num >> 18);
                char byte2 = 0x80 | ((num >> 12) & 0x3F);
                char byte3 = 0x80 | ((num >> 6) & 0x3F);
                char byte4 = 0x80 | (num & 0x3F);
                out.write(&byte1, sizeof(byte1)); if (!out.good() || out.bad()) return false;
                out.write(&byte2, sizeof(byte2)); if (!out.good() || out.bad()) return false;
                out.write(&byte3, sizeof(byte3)); if (!out.good() || out.bad()) return false;
                out.write(&byte4, sizeof(byte4)); if (!out.good() || out.bad()) return false;
            } else return false; // there are bad bytes
            buffer.erase(0, pos+2); // remove written bytes
        }
        bitstring = buffer;
        if (bitstring.length() > 31) return false; // higher than 0x10ffff
    }
    if (bitstring.find("1") != string::npos) return false; // if there are left 1 in bitstring
    return true;
}

#ifndef __PROGTEST__

bool identicalFiles (const char *file1, const char *file2) {
    return true;
}

int main (int argc, char *argv[]) {
//    if (utf8ToFibonacci("example/src_5.utf8", "example/output.fib")) cout << "YES" << endl;
//    else cout << "NO" << endl;
    if (fibonacciToUtf8("example/in_5067440.fib", "output.utf8")) cout << "YES" << endl;
    else cout << "NO" << endl;
//    assert ( utf8ToFibonacci ( "example/src_0.utf8", "output.fib" )
//             && identicalFiles ( "output.fib", "example/dst_0.fib" ) );
//    assert ( utf8ToFibonacci ( "example/src_1.utf8", "output.fib" )
//             && identicalFiles ( "output.fib", "example/dst_1.fib" ) );
//    assert ( utf8ToFibonacci ( "example/src_2.utf8", "output.fib" )
//             && identicalFiles ( "output.fib", "example/dst_2.fib" ) );
//    assert ( utf8ToFibonacci ( "example/src_3.utf8", "output.fib" )
//             && identicalFiles ( "output.fib", "example/dst_3.fib" ) );
//    assert ( utf8ToFibonacci ( "example/src_4.utf8", "output.fib" )
//             && identicalFiles ( "output.fib", "example/dst_4.fib" ) );
//    assert ( ! utf8ToFibonacci ( "example/src_5.utf8", "output.fib" ) );
//    assert ( fibonacciToUtf8 ( "example/src_6.fib", "output.utf8" )
//             && identicalFiles ( "output.utf8", "example/dst_6.utf8" ) );
//    assert ( fibonacciToUtf8 ( "example/src_7.fib", "output.utf8" )
//             && identicalFiles ( "output.utf8", "example/dst_7.utf8" ) );
//    assert ( fibonacciToUtf8 ( "example/src_8.fib", "output.utf8" )
//             && identicalFiles ( "output.utf8", "example/dst_8.utf8" ) );
//    assert ( fibonacciToUtf8 ( "example/src_9.fib", "output.utf8" )
//             && identicalFiles ( "output.utf8", "example/dst_9.utf8" ) );
//    assert ( fibonacciToUtf8 ( "example/src_10.fib", "output.utf8" )
//             && identicalFiles ( "output.utf8", "example/dst_10.utf8" ) );
//    assert ( ! fibonacciToUtf8 ( "example/src_11.fib", "output.utf8" ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
