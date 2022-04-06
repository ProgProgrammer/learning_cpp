#include "RingBuffer.h"

int main()
{
    int n = 9;
    RingBuffer buffer(n);  // empty with size 9
    buffer.write('a');     // a
    buffer.write('b');     // ab
    std::cout << buffer.read() << std::endl;    // ch = a, buffer: b
    std::cout << buffer.read() << std::endl;    // ch = b, buffer: empty
    std::cout << buffer.read() << std::endl;    // exception occurs
    buffer.write('c');     // c
    buffer.write('q');     // q
    buffer.write('w');     // w
    buffer.write('e');     // e
    buffer.write('r');     // r
    buffer.write('t');     // t
    buffer.write('y');     // cqwertyas
                               // 123456789 - fully booked
    buffer.write('X');     // qwertyasX
    buffer.write('Y');     // wertyasXY
    buffer.write('Z');     // ertyasXYZ
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;
    std::cout << buffer.read() << std::endl;

    return 0;
}