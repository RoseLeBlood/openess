#ifndef _ESS_ERROR_H_
#define _ESS_ERROR_H_

/**
 * @brief OpenESS error codes
 */
typedef enum ess_error {
    ESS_OK = 0, 				/**< mo error. */
    ESS_ERROR_OUTOFMEM = -1,			/**< no more memory */
    ESS_ERROR_NOT_FOUND,			/**< hardware for backend not avaible */
    ESS_ERROR_WRONG_FORMAT,		/**< The format is not supported */
    ESS_ERROR_PAUSED,				/**< Don't read or write becourse backend is paused */
    ESS_ERROR_NULL, /**< backend is null */
    ESS_ERROR,				/**< unknown error */
    ESS_ERROR_NOT_IMP,    /** function no implantiert */
    ESS_ERROR_NOT_CREATED, /** <not created */
    ESS_ERROR_UNSPEC_PROTOKOL,      /**< unknown protokol */
    ESS_ERROR_WRONG_PROTOKOL,  /**< wrong protokol */
    ESS_ERROR_UNSPEC_FAMILY,              /**< unknown family */
    ESS_ERROR_GETADDR,                            /**<  getaddrinfo error see  ess_socket_t::retval */
    ESS_ERROR_BIND,                                     /**<  bind error see  ess_socket_t::retval  */
    ESS_ERROR_CONNECT,                            /** <  connect error */
    ESS_ERROR_CLOSE,                                     /**<  close error see  ess_socket_t::retval  */

    ESS_ERROR_NOBACKEND, /**< context has no backend */
    ESS_ERROR_ISPAUSED = -42,  /**< can write while context is paused  */
}ess_error_t;

#endif
