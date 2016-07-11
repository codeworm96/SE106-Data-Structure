#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include "bitstream.h"
#include "huffman_tree.h"
using namespace std;

//output code for a char
void output_code(obitstream & os, const Code & code)
{
    for (Code::const_iterator iter = code.begin(); iter != code.end(); ++iter){
        os.put_bit(*iter);
    }
}

//counting characters in the input file
map<int, int> stat_char(string inputFilename)
{
    //init
    map<int, int> res;
    res[EOF_SIGN] = 1;

    //counting
    ifstream fin(inputFilename.c_str(), ios::in | ios::binary);
    char t;
    while(fin.get(t)){
        ++res[t];
    }

    return res;
}

void compress(string inputFilename, string outputFilename) {
    ifstream is(inputFilename.c_str(), ios::binary);
    obitstream os(outputFilename);

    //build tree
    HuffmanTree * root = build(stat_char(inputFilename));
    map<int, Code> table;
    EncodeVisitor encode_visitor(table);
    DumpVisitor dump_visitor(os);

    //make encoding table
    root->accept(&encode_visitor);

    //dump tree to file
    root->accept(&dump_visitor);

    delete root; //remove huffman_tree

    //encoding
    char c;
    while(is.get(c)){
        output_code(os, table[c]);
    }
    output_code(os, table[EOF_SIGN]);
};

void decompress(string inputFilename, string outputFilename) {
    ibitstream is(inputFilename);
    ofstream os(outputFilename.c_str(), ios::binary);

    //load the tree
    HuffmanTree * root = load(is);

    //decode until meet the end of file
    bool finish = false;
    DecodeVisitor visitor(is, os, finish);
    while(!finish){
        root->accept(&visitor);
    }

    delete root;//remove the tree
}

void useage(string prog) {
  cerr << "Useage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

int main(int argc, char* argv[]) {
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) {
    if (argv[i] == string("-d")) isDecompress = true;
    else if (inputFilename == "") inputFilename = argv[i];
    else if (outputFilename == "") outputFilename = argv[i];
    else useage(argv[0]);
  }
  if (outputFilename == "") useage(argv[0]);
  if (isDecompress) decompress(inputFilename, outputFilename);
  else compress(inputFilename, outputFilename);
  return 0;
}
