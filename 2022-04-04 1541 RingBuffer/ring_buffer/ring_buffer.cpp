#include "RingBuffer.h"

void show(const RingNode & rb)
{
    if (rb.next != nullptr)
        std::cout << "ch = " << rb.str << ", buffer: " << rb.next->str << std::endl;
    else
        std::cout << "ch = " << rb.str << ", buffer: empty" << std::endl;
}

int main()
{
    RingBuffer buffer(9);  // empty with size 9
    buffer.write("a");     // buffer: a
    buffer.write("b");     // buffer: ab
    buffer.write("c");     // buffer: abc

    std::cout << buffer.read() << "\n";    // ch = a, buffer: bc
    std::cout << buffer.read() << "\n";    // ch = b, buffer: c
    std::cout << buffer.read() << "\n";    // ch = c, buffer: empty

    try
    {
        std::cout << buffer.read() << "\n"; // buffer already empty - expect exception
    }
    catch(std::runtime_error & error)
    {
        std::cout << error.what() << "\n";
    }

    buffer.write("c");
    buffer.write("q");
    buffer.write("w");
    buffer.write("e");
    buffer.write("r");
    buffer.write("t");
    buffer.write("y");
    buffer.write("a");
    buffer.write("s");     // cqwertyas
                           // 123456789 - fully booked

    buffer.write("X");     // qwertyasX
    buffer.write("Y");     // wertyasXY
    buffer.write("Z");     // ertyasXYZ

    std::cout << buffer.read() << "\n";    // e
    std::cout << buffer.read() << "\n";    // r
    std::cout << buffer.read() << "\n";    // t
    std::cout << buffer.read() << "\n";    // y
    std::cout << buffer.read() << "\n";    // a
    std::cout << buffer.read() << "\n";    // s
    std::cout << buffer.read() << "\n";    // X
    std::cout << buffer.read() << "\n";    // Y
    std::cout << buffer.read() << "\n";    // Z

    try
    {
        std::cout << buffer.read() << "\n"; // buffer already empty - expect exception
    }
    catch(std::runtime_error & error)
    {
        std::cout << error.what() << "\n";
    }

    return 0;
}

// Output:
// a
// b
// c
// start pointer is nullptr
// e
// r
// t
// y
// a
// s
// X
// Y
// Z
// start pointer is nullptr