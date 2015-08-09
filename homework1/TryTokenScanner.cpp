#include "TryTokenScanner.h"

#include "tokenscanner.h"

using namespace std;

// Part I
Vector<string> TryTokenScanner::allTokens(string text) {
  Vector<string> tokens;
  
  TokenScanner scanner(text);                //scanner for tokenize
  while (scanner.hasMoreTokens()){
      tokens.push_back(scanner.nextToken()); //restore the token in the Vector
  }

  return tokens;
}

// Part II
Vector<string> TryTokenScanner::noWhitespaces(string text) {
  Vector<string> tokens;

  TokenScanner scanner(text);                //scanner for tokenize
  scanner.ignoreWhitespace();                //uses API for ignoring whitespaces
  while (scanner.hasMoreTokens()){
      tokens.push_back(scanner.nextToken()); //restore the token in the Vector
  }

  return tokens;
}

// Part III
Vector<string> TryTokenScanner::noComments(string text) {
  Vector<string> tokens;

  TokenScanner scanner(text);                //scanner for tokenize
  scanner.ignoreComments();                  //uses API for ignoring comments
  while (scanner.hasMoreTokens()){
      tokens.push_back(scanner.nextToken()); //restore the token in the Vector
  }

  return tokens;
}
