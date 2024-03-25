#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

// Asserts the condition 'exp' is true, else prints the error message 'msg' and exits
#define validate(exp, msg) if(exp) {} else {\
printf(1, "Error in %s at line %d: check (" #exp ") failed: %s\n", __FILE__, __LINE__, msg);\
exit();}

void computeWorkload()
{
  int loopCounter1 = 0;
  int loopCounter2 = 0;
  int tempCounter = 0;

  for(loopCounter1 = 0; loopCounter1 < 25; loopCounter1++){
    for(loopCounter2 = 0; loopCounter2 < 1000000; loopCounter2++){
      tempCounter = loopCounter2 % 10;
      tempCounter++;
    }
  }
}

int main(int argc, char *argv[]){
  int childProcesses[3];
  int iter;

  validate(settickets(10) == 0, "settickets");

  for(iter = 0; iter < 2; iter++){
    childProcesses[iter] = fork();
    if(childProcesses[iter] == 0) {
      validate(settickets((iter + 2) * 10) == 0, "settickets in child");
      computeWorkload();
      exit();
    }
  }

  computeWorkload();

  for(iter = 0; iter < 2; iter++) {
    wait();
  }

  exit();
}
