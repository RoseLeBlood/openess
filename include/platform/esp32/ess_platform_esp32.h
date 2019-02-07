#ifndef _ESS_PLATFORM_INC_ESP32_H_
#define _ESS_PLATFORM_INC_ESP32_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ESS_ENABLE_BACKEND_UART
  ess_backend_facktory_t* ess_backend_uart_getFactory();
#endif
#ifdef ESS_ENABLE_BACKEND_I2S
  ess_backend_facktory_t* ess_backend_i2s_generic_getFactory();
#endif


typedef struct ess_backends_entry {
    const char* name;
    ess_backend_facktory_t* (* getFactory)(void);
}ess_backends_entry_t;

ess_backends_entry_t backends_list[] = {


#ifdef ESS_ENABLE_BACKEND_UART
  { ESS_BACKEND_NAME_UART_ESP32 , ess_backend_uart_getFactory},
#endif //ESS_ENABLE_BACKEND_UART
#ifdef ESS_ENABLE_BACKEND_I2S
  { ESS_BACKEND_NAME_I2S_ESP32, ess_backend_i2s_generic_getFactory},
#endif // ESS_ENABLE_BACKEND_I2S

#ifdef ESS_ENABLE_BACKEND_UDP
  { ESS_BACKEND_NAME_UDP, ess_backend_udp_getFactory},
#endif //ESS_ENABLE_BACKEND_UDP
  { ESS_BACKEND_NAME_NULL, ess_backend_null_getFactory},
};


#ifdef __cplusplus
}
#endif

#endif
