#include <iostream>
#include <vector>
#include <memory>
#include <cstring>
#include <sstream>

using namespace std;

typedef unsigned char byte;
/**
 * address를 unsigned char로 변환하는 코드
 * example) vector<unsigned char>& byteVector = addressToBytes(reinterpret_cast<std::uintptr_t>(class_a));
 *
 * @param address 포인터를 담는 변수
 * @return 포인터를 쪼개서 담은 unsigned char형 vector
 */
std::vector<unsigned char> addressToBytes(std::uintptr_t address) {
    cout << "ref : " << address << endl;

    int size = sizeof(std::uintptr_t);
    std::vector<unsigned char> byteVector(size);
    for (int i = 0; i < size; i++) {
        byteVector[size - 1 - i] = (address >> (i * 8));
        //비트연산을 통해서 vector의 뒤부터 채워감
        //std::uintptr_t에서 unsigned char로 변환되면서 앞의 비트는 제거되기때문에
    }
    return byteVector;
}

std::uintptr_t byteToAddress(std::vector<unsigned char> vec){
    std::uintptr_t val=0;
    int size = vec.size();

    for(int i = 0; i< size ; i++){
        val = (val << 8) + vec[i];
    }

    return val;
}

int main() {

    class A{
    public:
        char a = 9;
        char b = 4;
        char c = 1;
        char d = 4;
    };

    shared_ptr<A> class_a = make_shared<A>();
    int size = sizeof(class_a.get());
    byte *addr = new byte[size];
    memset(addr, 0x00, size);

    cout << class_a.get() << endl;
    cout << size << endl;

    cout << "---- 바이트 버퍼에 쓰기 ----" << endl;

    /*
     *   ref(int) --> char
     */

    printf("before : %d ", class_a->a);
    cout << endl;

    // byte 변환1
    vector<byte> addr_vec = addressToBytes((unsigned long) class_a.get());
    addr = reinterpret_cast<byte*>(&addr_vec[0]);
    printf("before : %x ", &addr);
    cout << endl;


    cout << "---- 바이트 버퍼에서 읽어오기 ----" << endl;
    /*
     * byte --> class a
     */
    vector<byte> vector = std::vector<byte>(addr, addr+size);
    uintptr_t ref = byteToAddress(vector);
    cout << "ref : " << ref << endl;

    printf("after : %d ", ((A*) ref)->a);


    return 0;
}
