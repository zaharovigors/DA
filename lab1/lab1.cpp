#include <cstdlib>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "vector.hpp"
using namespace std;

struct Index1
{
    unsigned long long keys;
    unsigned long long value;
    
    friend istream& operator>>(istream& is, Index& rhs){
        is >> rhs.keys >> rhs.value;
        return is;
    }
    
    Index() {}
    Index(const Index& rhs){
        keys = rhs.keys;
        value = rhs.value;
    }
    
    Index& operator=(const Index& rhs){
        Index cp(rhs);
        swap(cp);
        return *this;
    }
    void swap(Index& rhs){
        std::swap(keys, rhs.keys);
        std::swap(value, rhs.value);
    }
};

int main(int argc, char** argv){
    TVector<Index> data;
    unsigned long long size = 0, max = 0;
    Index idx;
    while(cin >> idx) {
        if(idx.keys > max) {
            max = idx.keys;
        }
        data.Push_back(idx);
        size++;
    }
    
    unsigned long long *C = new unsigned long long[max+1];
    for (unsigned long long i = 0; i < max+1; i++) {
        C[i] = 0;
    }
    for (unsigned long long i = 0; i < size; i++) {
        C[data[i].keys]++;
    }
    TVector<Index> answer(size);
    for (unsigned long long j=1; j < max+1; j++) {
        C[j] = C[j] + C[j-1];
    }
    for (long long i = size-1; i >= 0; i--) {
        C[data[i].keys]--;
        answer[C[data[i].keys]].operator=(data[i]);
    }
    
    for (unsigned long long i = 0; i < size; i++) {
        cout << setfill('0') << setw(6) << answer[i].keys << "\t";
        cout << answer[i].value << endl;
        
    }
    
    delete[] C;
    
    return 0;
}
