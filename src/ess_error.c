#include "ess_error.h"

typedef struct error2human {
  ess_error_t error;
  const char* text;
}error2human_t;

error2human_t error_parse[] = {
  { ESS_OK, "ESS_OK" },
  { ESS_ERROR_OUTOFMEM, "ESS_ERROR_OUTOFMEM"},			/**< no more memory */
  { ESS_ERROR_NOT_FOUND, "ESS_ERROR_NOT_FOUND"},			/**< hardware for backend not avaible */
  { ESS_ERROR_WRONG_FORMAT , "ESS_ERROR_WRONG_FORMAT"},		/**< The format is not supported */
  { ESS_ERROR_PAUSED, "ESS_ERROR_PAUSED"},				/**< Don't read or write becourse backend is paused */
  { ESS_ERROR_NULL, "ESS_ERROR_NULL"}, /**< backend is null */
  { ESS_ERROR, "ESS_ERROR"},				/**< unknown error */
  { ESS_ERROR_NOT_IMP, "ESS_ERROR_NOT_IMP"},    /** function no implantiert */
  { ESS_ERROR_NOT_CREATED, "ESS_ERROR_NOT_CREATED"}, /** <not created */
  { ESS_ERROR_UNSPEC_PROTOKOL, "ESS_ERROR_UNSPEC_PROTOKOL"},      /**< unknown protokol */
  { ESS_ERROR_WRONG_PROTOKOL, "ESS_ERROR_WRONG_PROTOKOL"},  /**< wrong protokol */
  { ESS_ERROR_UNSPEC_FAMILY, "ESS_ERROR_UNSPEC_FAMILY"},              /**< unknown family */
  { ESS_ERROR_GETADDR, "ESS_ERROR_GETADDR"},                            /**<  getaddrinfo error see  ess_socket_t::retval */
  { ESS_ERROR_BIND, "ESS_ERROR_BIND"},                                     /**<  bind error see  ess_socket_t::retval  */
  { ESS_ERROR_CONNECT, "ESS_ERROR_CONNECT"},                            /** <  connect error */
  { ESS_ERROR_CLOSE, "ESS_ERROR_CLOSE"},                                     /**<  close error see  ess_socket_t::retval  */

  { ESS_ERROR_NOBACKEND, "ESS_ERROR_NOBACKEND"}, /**< context has no backend */
  { ESS_ERROR_ISPAUSED, "ESS_ERROR_ISPAUSED"},  /**< can write while context is paused  */

  { ESS_ERROR_TASK_CREAT, "ESS_ERROR_TASK_CREAT"}, /**< can't create task mutex */
};

const char* ess_error_to_string(const ess_error_t error) {
  const char* text = "UNKNOWN_ERROR";
  for(int i = 0; i < ESS_ERROR_MAX; i++) {
    if(error_parse[i].error == error) { text = error_parse[i].text; break; }
  }
  return text;
}
