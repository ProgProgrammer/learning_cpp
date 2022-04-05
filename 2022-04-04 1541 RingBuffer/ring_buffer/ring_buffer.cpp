#include "RingBuffer.h"

int main()
{
    RingBuffer buffer(9);  // empty with size 9
    buffer.write("a");     // a
    buffer.write("b");     // ab
    buffer.write("c");     // abc
    buffer.read();    // ch = a, buffer: b
    buffer.read();    // ch = b, buffer: �
    buffer.read();    // ch = �, buffer: empty
    buffer.read();    // exception occurs
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
    buffer.read();    // e
    buffer.read();    // r
    buffer.read();    // t
    buffer.read();    // y
    buffer.read();    // a
    buffer.read();    // s
    buffer.read();    // X
    buffer.read();    // Y
    buffer.read();    // Z
    buffer.read();    // exception occurs

    return 0;
}
