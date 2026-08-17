#include "core.h"
#include "log.h"

int main(void) {
  Result r = core_run();
  if (!RESULT_IS_OK(r)) {
    log_error("Fatal: %s", r.message);
    return 1;
  }
  return 0;
}
