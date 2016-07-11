#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <fstream>
#include <string>

const int BYTE_LEN = 8; // # of bits in a byte

//input from file bit by bit
class ibitstream
{
    public:
        ibitstream(std::string filename);
        bool get_bit(); //read a bit
        bool has_more();
    private:
        std::ifstream is;
        char buf; //buffer
        char pos; //position in buffer
        void load(); //load a byte to buffer
};

//output to file bit by bit
class obitstream
{
    public:
        obitstream(std::string filename);
        ~obitstream()
        {
            if (pos < BYTE_LEN) //buffer is not empty
                flush();
        }

        void put_bit(bool b);//output a bit
        void flush(); //output the buffer to the filestream
    private:
        std::ofstream os;
        char buf; //buffer
        char pos; //position in buffer
};

#endif

