#include "platform/esp32/ess_platform_esp32.h"

#ifdef ESS_ENABLE_BACKEND_I2S
#include "platform/esp32/i2s_gerneric_backend.h"
#endif

ess_backend_esp32::ess_backend_esp32() {

}
void ess_backend_esp32::create() {
  #ifdef ESS_ENABLE_BACKEND_I2S
  add_backend(new ess_i2s_generic_backend());
  #endif
}
std::string ess_backend_esp32::get_platform_name() {
  return std::string("ESP32");
}
std::string ess_backend_esp32::get_factory_creater() {
  return std::string("Anna_Sophia Schroeck - annasophia.schroeck@gmail.com");
}
