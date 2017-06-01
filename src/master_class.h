#ifndef __RSHELL_H__
#define __RSHELL_H__

class Rshell
{
    private:
    
    public:
    
    Rshell() {};
    virtual ~Rshell() {};                            
    virtual void execute(int &status, bool &exit_now) = 0;            //used to execute the various commands; 
                                                                      //uses status to see if it worked or not
                                             
                                                                      //may need to add more as the project progresses.
};

#endif
