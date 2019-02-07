#include "ess_context.h"
#include "ess_backend.h"
#include "ess_format.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



/**
 * @brief probe the given backend
 * @param [in] the backend to probe
 *
 */
void probe_backend(ess_backend_facktory_t* backend) {

  printf("Probe backend: %s ----------------------------------------------------\n", backend->get_name() );

  for(int y = 0; y < ESS_FORMAT_MAX; y++)  {
    error = ess_backend_probe(y, backend);

    // ++ => support | !! => no support
     printf("\t\t  %s (%s)   \n", (error == ESS_BACKEND_OK) ? "++" : "!!" ,
       ess_format_to_string(y) );
    }
}

void app_main() {

  ess_backend_facktory_t* backend;
  ess_backend_error_t error;

  // get number of platform backends
  unsigned int  number_of_backends = ess_backend_get_size();

   for(int i= 0; i < number_of_backends; i++ ) {
     // get backend from the platform list by index
     backend = ess_backend_get_by_index(i);
     // if backend NULL?
     if(backend == 0) continue; // then next
     // call probe_backend with the backend
     probe_backend(backend);
   }
  for(;;) { usleep(100000); }
}

/* Example Output
Probe backend: uart1 backend ----------------------------------------------------
		  ++ (ESS_FORMAT_MONO_44100_8)
		  ++ (ESS_FORMAT_MONO_48000_8)
		  ++ (ESS_FORMAT_MONO_96000_8)
		  ++ (ESS_FORMAT_STEREO_44100_8)
		  ++ (ESS_FORMAT_STEREO_48000_8)
		  ++ (ESS_FORMAT_STEREO_96000_8)
		  ++ (ESS_FORMAT_MONO_48000_16)
		  ++ ( ESS_FORMAT_MONO_44100_16)
		  ++ ( ESS_FORMAT_MONO_96000_16)
		  ++ (ESS_FORMAT_STEREO_44100_16)
		  ++ (ESS_FORMAT_STEREO_48000_16)
		  ++ (ESS_FORMAT_STEREO_96000_16)
		  ++ (ESS_FORMAT_MONO_44100_24)
		  ++ (ESS_FORMAT_MONO_48000_24)
		  ++ (ESS_FORMAT_MONO_96000_24)
		  ++ (ESS_FORMAT_STEREO_44100_24)
		  ++ (ESS_FORMAT_STEREO_48000_24)
		  ++ (ESS_FORMAT_STEREO_96000_24)
Probe backend: i2s_generic backend ----------------------------------------------------
		  ++ (ESS_FORMAT_MONO_44100_8)
		  ++ (ESS_FORMAT_MONO_48000_8)
		  ++ (ESS_FORMAT_MONO_96000_8)
		  ++ (ESS_FORMAT_STEREO_44100_8)
		  ++ (ESS_FORMAT_STEREO_48000_8)
		  ++ (ESS_FORMAT_STEREO_96000_8)
		  ++ (ESS_FORMAT_MONO_48000_16)
		  ++ ( ESS_FORMAT_MONO_44100_16)
		  ++ ( ESS_FORMAT_MONO_96000_16)
		  ++ (ESS_FORMAT_STEREO_44100_16)
		  ++ (ESS_FORMAT_STEREO_48000_16)
		  ++ (ESS_FORMAT_STEREO_96000_16)
		  ++ (ESS_FORMAT_MONO_44100_24)
		  ++ (ESS_FORMAT_MONO_48000_24)
		  ++ (ESS_FORMAT_MONO_96000_24)
		  ++ (ESS_FORMAT_STEREO_44100_24)
		  ++ (ESS_FORMAT_STEREO_48000_24)
		  ++ (ESS_FORMAT_STEREO_96000_24)
Probe backend: udp_both-backend ----------------------------------------------------
		  ++ (ESS_FORMAT_MONO_44100_8)
		  ++ (ESS_FORMAT_MONO_48000_8)
		  ++ (ESS_FORMAT_MONO_96000_8)
		  ++ (ESS_FORMAT_STEREO_44100_8)
		  ++ (ESS_FORMAT_STEREO_48000_8)
		  ++ (ESS_FORMAT_STEREO_96000_8)
		  !! (ESS_FORMAT_MONO_48000_16)
		  !! ( ESS_FORMAT_MONO_44100_16)
		  !! ( ESS_FORMAT_MONO_96000_16)
		  ++ (ESS_FORMAT_STEREO_44100_16)
		  ++ (ESS_FORMAT_STEREO_48000_16)
		  ++ (ESS_FORMAT_STEREO_96000_16)
		  ++ (ESS_FORMAT_MONO_44100_24)
		  ++ (ESS_FORMAT_MONO_48000_24)
		  ++ (ESS_FORMAT_MONO_96000_24)
		  !! (ESS_FORMAT_STEREO_44100_24)
		  !! (ESS_FORMAT_STEREO_48000_24)
		  !! (ESS_FORMAT_STEREO_96000_24)
Probe backend: null ----------------------------------------------------
		  ++ (ESS_FORMAT_MONO_44100_8)
		  ++ (ESS_FORMAT_MONO_48000_8)
		  ++ (ESS_FORMAT_MONO_96000_8)
		  ++ (ESS_FORMAT_STEREO_44100_8)
		  ++ (ESS_FORMAT_STEREO_48000_8)
		  ++ (ESS_FORMAT_STEREO_96000_8)
		  ++ (ESS_FORMAT_MONO_48000_16)
		  ++ ( ESS_FORMAT_MONO_44100_16)
		  ++ ( ESS_FORMAT_MONO_96000_16)
		  ++ (ESS_FORMAT_STEREO_44100_16)
		  ++ (ESS_FORMAT_STEREO_48000_16)
		  ++ (ESS_FORMAT_STEREO_96000_16)
		  ++ (ESS_FORMAT_MONO_44100_24)
		  ++ (ESS_FORMAT_MONO_48000_24)
		  ++ (ESS_FORMAT_MONO_96000_24)
		  ++ (ESS_FORMAT_STEREO_44100_24)
		  ++ (ESS_FORMAT_STEREO_48000_24)
		  ++ (ESS_FORMAT_STEREO_96000_24)
*/
