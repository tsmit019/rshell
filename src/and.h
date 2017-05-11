#ifndef AND_H
#define AND_H
#include "master_class.h"
#include "connector.h"

using namespace std;

class And : public Connector {
  public:
  And(vector<char*> left, vector<char*> right) : Connector(left, right) {};
  ~And() {}; 
  void execute(int& status);
};

#endif
