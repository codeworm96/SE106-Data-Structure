#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bitstream.h"
#include <fstream>
#include <map>
#include <vector>

const int EOF_SIGN = 256; //pseudo end of file
const int INNER_SIGN = 257; //mark for inner node

typedef std::vector<bool> Code;

//Note: using visitor pattern
class Visitor;

//Base class for huffman tree node
class HuffmanTree
{
    public:
        virtual ~HuffmanTree() {} 
        virtual void accept(Visitor * obj) =0;
};

class InnerNode :public HuffmanTree
{
    public:
        InnerNode(HuffmanTree * lc, HuffmanTree * rc):lchild(lc), rchild(rc) {}
        ~InnerNode();
        void accept(Visitor * obj);
        HuffmanTree * get_left() { return lchild; }
        HuffmanTree * get_right() { return rchild; }
    private:
        HuffmanTree * lchild; //left child
        HuffmanTree * rchild; //right child
};

class Leaf :public HuffmanTree
{
    public:
        Leaf(int c):id(c) {}
        ~Leaf() {}
        void accept(Visitor * obj);
        int get_id() { return id; }
    private:
        int id;
};

//base class for visitors
class Visitor
{
    public:
        virtual void visit_inner(InnerNode * node) =0;
        virtual void visit_leaf(Leaf * node) =0;
};

//visitor for encoding
//table of char and Code will be store in ans
class EncodeVisitor :public Visitor
{
    public:
        EncodeVisitor(std::map<int, Code> & ans);
        void visit_inner(InnerNode * node);
        void visit_leaf(Leaf * node);
    private:
         Code cur; //current code
         std::map<int, Code> * res; //keep reference to ans
};

//dump huffman tree to file
//output_file : out
class DumpVisitor :public Visitor
{
    public:
        DumpVisitor(obitstream & out);
        void visit_inner(InnerNode * node);
        void visit_leaf(Leaf * node);
    private:
         obitstream * os;
};

//decoding a character (in -> out)
//fin : when hitting eof_sign, fin will be true. otherwise it will be false.
class DecodeVisitor :public Visitor
{
    public:
        DecodeVisitor(ibitstream & in, std::ofstream & out, bool & fin);
        void visit_inner(InnerNode * node);
        void visit_leaf(Leaf * node);
    private:
         ibitstream * is;
         std::ofstream * os;
         bool * finish;
};

//build a huffman tree from char, frequency map
HuffmanTree * build(const std::map<int, int> & stat);

//load huffman tree from file
HuffmanTree * load(ibitstream & is);

#endif
