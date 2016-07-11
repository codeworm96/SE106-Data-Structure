#include "bitstream.h"
#include <string>
#include <fstream>
#include <stdexcept>

ibitstream::ibitstream(std::string filename):is(filename.c_str(), std::ios::in | std::ios::binary), pos(0)
{
    load();
}

void ibitstream::load()
{
    if (pos) //buffer is not empty
        return ;
    if (is.get(buf)){ //input successfully
        pos = BYTE_LEN; //update position
    }
}

bool ibitstream::get_bit()
{
    if(pos == 0)
        throw std::runtime_error("end of file");
    --pos;
    bool res = buf & (1 << pos); //extract bit
    if (pos == 0) //buffer is empty?
        load();
    return res;
}

bool ibitstream::has_more()
{
    return pos;
}


obitstream::obitstream(std::string filename):os(filename.c_str(), std::ios::out | std::ios::binary), buf(0), pos(BYTE_LEN) {}

void obitstream::put_bit(bool c)
{
    --pos;
    if (c)
        buf |= (1 << pos); //set the bit in buffer
    if (pos == 0) //buffer is full
        flush();
}

//output buffer to filestream
void obitstream::flush()
{
    os.put(buf);
    pos = BYTE_LEN;
    buf = 0;
}
