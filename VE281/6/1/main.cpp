#include <iostream>
#include <vector>
using namespace std;

struct compare_t
{
    bool operator()(int a, int b) const
    {
        return a > b;
    }
};
template<typename TYPE, typename COMP = std::less<TYPE> >
class binary_heap{
public:
    typedef unsigned size_type;

    binary_heap(COMP comp = COMP());

    void enqueue(const TYPE &val);

    TYPE dequeue_min();

    const TYPE &get_min() const;

    virtual size_type size() const;

    virtual bool empty() const;

private:
    std::vector<TYPE> data;
    COMP compare;

private:
    void percolateUp(int id);
    void swap(TYPE &a, TYPE &b);
    void percolateDown(int id);
};

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP> :: binary_heap(COMP comp) {
    compare = comp;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE,COMP>::swap(TYPE &a, TYPE &b){
    TYPE temp;
    temp = a;
    a = b;
    b = temp;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE,COMP>::percolateUp(int id){
    while(id > 0 && compare(data[id],data[(id-1)/2])){
        swap(data[id],data[(id - 1)/2]);
        id = (id - 1)/2;
    }
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP> :: enqueue(const TYPE &val) {
    data.push_back(val);
    percolateUp(data.size() - 1);
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE,COMP>::percolateDown(int id){
    int size = data.size();
    for(int j = 2*id + 1; j < size;j = 2*id + 1){
        if(j < size - 1 && compare(data[j + 1],data[j])) j++;
        if(!compare(data[j],data[id])) break;
        swap(data[id], data[j]);
        id = j;
    }
}

template<typename TYPE, typename COMP>
TYPE binary_heap<TYPE, COMP> :: dequeue_min() {
    int size = data.size();
    TYPE min = data[0];
    swap(data[0],data[size - 1]);
    data.pop_back();
    percolateDown(0);
    return min;
}

template<typename TYPE, typename COMP>
const TYPE &binary_heap<TYPE, COMP> :: get_min() const {
    return data[0];
}

template<typename TYPE, typename COMP>
bool binary_heap<TYPE, COMP> :: empty() const {
    if(data.size() == 0) return true;
    else return false;
}

template<typename TYPE, typename COMP>
unsigned binary_heap<TYPE, COMP> :: size() const {
    return data.size();
}

int main() {
    binary_heap<float,compare_t> MAX_HEAP;
    binary_heap<float> MIN_HEAP;
    vector<float> data;
    int count = 0;
    while(true){
        int number;
        cout<<"Please input one number: "<<endl;
        cin>>number;
        if(count == 0){
            MAX_HEAP.enqueue(number);
            cout<<"The median is: "<<MAX_HEAP.get_min()<<endl;
        }
        else if(count%2 == 0){
            //count is even.
            if(number <= MIN_HEAP.get_min()) MAX_HEAP.enqueue(number);
            else {
                MAX_HEAP.enqueue(MIN_HEAP.dequeue_min());
                MIN_HEAP.enqueue(number);
            }
            cout<<"The median is: "<<MAX_HEAP.get_min()<<endl;
        }
        else{
            //count is odd
            if(number >= MAX_HEAP.get_min()) MIN_HEAP.enqueue(number);
            else{
                MIN_HEAP.enqueue(MAX_HEAP.dequeue_min());
                MAX_HEAP.enqueue(number);
            }
            cout<<"The median is: "<<(MAX_HEAP.get_min()+MIN_HEAP.get_min())/2<<endl;
        }
        count++;
    }
    return 0;
}