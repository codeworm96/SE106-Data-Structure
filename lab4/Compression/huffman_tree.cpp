#include "huffman_tree.h"
#include "bitstream.h"
#include <fstream>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>

//Note: because there are 256+2(EOF_SIGN, INNER_SIGN) cases for a node, it takes 9 bits to store a node
//below are helper function to handle 9 bits
void output_9bit(obitstream & os, int x)
{
    for (int i = 8; i >= 0; --i){
        os.put_bit(x & (1 << i));
    }
}

int input_9bit(ibitstream & in)
{
    int res = 0;
    for (int i = 0; i < 9; ++i){
      res <<= 1;
      res |= in.get_bit();
    }
    return res;
}

InnerNode::~InnerNode()
{
    delete lchild;
    delete rchild;
}

void InnerNode::accept(Visitor * obj)
{
    obj->visit_inner(this);
}

void Leaf::accept(Visitor * obj)
{
    obj->visit_leaf(this);
}

HuffmanTree * build(const std::map<int, int> & stat)
{
    //heap
    typedef std::pair<int, HuffmanTree *> Elem;
    std::priority_queue<Elem, std::deque<Elem>, std::greater<Elem> > heap;
    //building heap
    for (std::map<int, int>::const_iterator iter = stat.begin(); iter != stat.end(); ++iter){
        heap.push(std::make_pair(iter->second, static_cast<HuffmanTree *>(new Leaf(iter->first))));
    }
    //building huffman tree
    while(heap.size() > 1){
        //extract two min elem and combine them
        Elem l = heap.top();
        heap.pop();
        Elem r = heap.top();
        heap.pop();
        heap.push(std::make_pair(l.first + r.first, static_cast<HuffmanTree *>(new InnerNode(l.second, r.second))));
    }
    return heap.top().second;
}

HuffmanTree * load(ibitstream & is)
{
    int t = input_9bit(is);
    if (t == INNER_SIGN){ //inner node
        HuffmanTree * l = load(is);
        HuffmanTree * r = load(is);
        return new InnerNode(l, r);
    }else{ //leaf
        return new Leaf(t);
    }
}

EncodeVisitor::EncodeVisitor(std::map<int, Code> & ans)
{
    res = &ans;
}

void EncodeVisitor::visit_inner(InnerNode * node)
{
    cur.push_back(false);
    node->get_left()->accept(this);
    cur.pop_back();
    cur.push_back(true);
    node->get_right()->accept(this);
    cur.pop_back();
}

void EncodeVisitor::visit_leaf(Leaf * node)
{
    res->insert(make_pair(node->get_id(), cur));
}

DumpVisitor::DumpVisitor(obitstream & out)
{
    os = &out;
}

void DumpVisitor::visit_inner(InnerNode * node)
{
    output_9bit(*os, INNER_SIGN);
    node->get_left()->accept(this);
    node->get_right()->accept(this);
}

void DumpVisitor::visit_leaf(Leaf * node)
{
    output_9bit(*os, node->get_id());
}

DecodeVisitor::DecodeVisitor(ibitstream & in, std::ofstream & out, bool & fin)
{
    is = &in;
    os = &out;
    finish = &fin;
}

//Note: 1 for right && 0 for left
void DecodeVisitor::visit_inner(InnerNode * node)
{
    if (is->get_bit()){
        node->get_right()->accept(this);
    }else{
        node->get_left()->accept(this);
    }
}

void DecodeVisitor::visit_leaf(Leaf * node)
{
    int t = node->get_id();
    if (t == EOF_SIGN){
        (*finish) = true;
    }else{
        os->put(t);
    }
}
