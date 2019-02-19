#include "ess.h"
#include "ess_server.h"
#include "ess_dram_server.h"

#include "esp_log.h"

#define LOG_TAG "ess_dram_server"

ess_dram_server::ess_dram_server(std::string name,  ess_format_t format)
  : ess_server(name, format) {

}
ess_error_t ess_dram_server::create(std::string backend_name, std::string host, std::string port, ess_socket_fam fam, bool lite) {
  m_pServerSocket = new ess_inet_dram_server(host, port, fam, lite);
  if(m_pServerSocket == 0) {
    ESP_LOGE(LOG_TAG, "ess_inet_dram_server - Out of Mem");
     return ESS_ERROR_OUTOFMEM;
   }
  ESP_LOGI(LOG_TAG, "OpenESS dram%d socket opened", fam == ESS_SOCKET_FAMILY_IP4 ? 4 : 6);

  m_pContext = new ess_context();
  if(m_pContext == 0) {
    ESP_LOGE(LOG_TAG, "ess_context - Out of Mem");
     return ESS_ERROR_OUTOFMEM;
   }
   ess_error_t error = m_pContext->create(backend_name.c_str(), m_eFormat);
   ESS_ERROR(error);

  return error;
}
