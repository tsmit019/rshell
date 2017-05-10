#include "or.h"
#include "single_command.h"

void Or::execute(int &status)
{
    Single * left_junk = new Single(left);
    left_junk -> Single::execute(status);
   
   if(status == -1)
   {
      Single * right_junk = new Single(right);
      right_junk -> Single::execute(status);
      
      delete[] right_junk;
   }
   
   delete[] left_junk;
}
