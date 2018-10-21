#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

template <typename T>
class TVector {
public:
    TVector(unsigned long long reserven=2);
    TVector(const TVector<T>& rhs);
    ~TVector();
    bool Empty();
    T& operator[](const unsigned long long&);
    unsigned long long Size();
    void Resize(const unsigned long long& newCap);
    void Push_back(const T& element);
    void Destroy();
    void Print();
    
private:
    unsigned long long capacity;
    unsigned long long  SizeV;
    T *data;
   
};

template <typename T>
TVector<T>::TVector(unsigned long long reserven):
            capacity(reserven),
            SizeV(0),
            data(new T[reserven]) {
                
}

template<typename T>
TVector<T>::TVector(const TVector& rhs){
    capacity = rhs.capacity;
    SizeV = rhs.SizeV;
    data = new T[SizeV];
    for(size_t i = 0; i < Size(); ++i){
        data[i] = rhs.data[i];
    }
}
template <typename T>
bool TVector<T>::Empty() {
    return SizeV == 0;
}
template <typename T>
unsigned long long TVector<T>::Size(){
    return SizeV;
}
template<typename T>
T& TVector<T>::operator[](const unsigned long long& index) {
    return data[index];
}

template <typename T>
void TVector<T>::Resize(const unsigned long long&  newCap){
    T* data2 = data;
    data = new T[newCap];
    
    for(size_t i = 0; i < SizeV; ++i){
            data[i] = data2[i];
    }
    capacity = newCap;
    delete[] data2;
}
template <typename T>
void TVector<T>::Destroy(){
    SizeV= 0;
    delete [] data;
}
template <typename T>
void TVector<T>::Push_back(const T& element){
    
    if (capacity == SizeV){
        Resize(capacity * 2);
    }
    data[SizeV++] = element;
}

template <typename T>
void TVector<T>::Print(){
    for(int i = 0; i < SizeV; i++){
        cout << data[i] << " ";
    }
    cout << endl;
}
template <typename T>
TVector<T>::~TVector(){
    delete[] data;
}
