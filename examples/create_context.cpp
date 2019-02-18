#include "ess.h"
#include "ess_context.h"

ess_context context;
ess_error_t error;


#if ESS_PLATFORM_ESP32 == 1
extern "C" void app_main() {
#else
int main() {
#endif
  error = context.create(ESS_BACKEND_NAME_NULL, ESS_FORMAT_STEREO_44100_24);
  ESS_ERROR(error);

  for(;;)  { ess_platform_sleep(10); }
}
