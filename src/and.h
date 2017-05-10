#ifndef AND_H
#define AND_H
#include "connector.h"

using namespace std;

class And : public Connector {
  public:
  And(vector<char*> left, vector<char*> right) : Connector(left, right) {};
  void execute(int& status);
};

#endif
