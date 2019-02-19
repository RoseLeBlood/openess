#include "ess.h"
#include "ess_server.h"



ess_server::ess_server(std::string name, ess_format_t format) {
  m_eFormat = format;
  m_strName = name;
  m_eStatus = ESS_SERVER_STATUS_INIT;
}
