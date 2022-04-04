#include "RingBuffer.h"

int main()
{
    RingBuffer buffer(9);  // empty with size 9
    buffer.write("a");     // a
    buffer.write("b");     // ab
    buffer.write("c");     // abc
    std::cout << buffer.read() << std::endl;    // ch = a, buffer: b
    std::cout << buffer.read() << std::endl;    // ch = b, buffer: ñ
    std::cout << buffer.read() << std::endl;    // ch = ñ, buffer: empty
    std::cout << buffer.read() << std::endl;    // exception occurs
    buffer.write("c");     // c
    buffer.write("q");     // q
    buffer.write("w");     // w
    buffer.write("e");     // e
    buffer.write("r");     // r
    buffer.write("t");     // t
    buffer.write("y");     // y
    buffer.write("a");     // a
    buffer.write("s");     // cqwertyas
                               // 123456789 - fully booked
    buffer.write("X");     // qwertyasX
    buffer.write("Y");     // wertyasXY
    buffer.write("Z");     // ertyasXYZ
    std::cout << buffer.read() << std::endl;    // e
    std::cout << buffer.read() << std::endl;    // r
    std::cout << buffer.read() << std::endl;    // t
    std::cout << buffer.read() << std::endl;    // y
    std::cout << buffer.read() << std::endl;    // a
    std::cout << buffer.read() << std::endl;    // s
    std::cout << buffer.read() << std::endl;    // X
    std::cout << buffer.read() << std::endl;    // Y
    std::cout << buffer.read() << std::endl;    // Z
    std::cout << buffer.read() << std::endl;    // exception occurs

    return 0;
}
