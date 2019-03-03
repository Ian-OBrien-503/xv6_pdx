#define STRMAX 32
#include "types.h"

struct uproc {
  uint pid;
  uint uid;
  uint gid;
  uint ppid;
  uint priority;
  uint elapsed_ticks;
  uint CPU_total_ticks;
  char state[STRMAX];
  uint size;
  char name[STRMAX];
};

