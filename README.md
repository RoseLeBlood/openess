<div>
 <img src="https://roseleblood.github.io/openess/Logo-OpenESS.png" width="256" align="left"> 
 <div align="left">
  <h1>Open Embedded Sound Server</h1>
   <h3>
       Website
     </a>
     <span> | </span>
     <a href="https://github.com/RoseLeBlood/openess/wiki">
       Wiki
     </a>
     <span> | </span>
     <a href="https://github.com/RoseLeBlood/openess/blob/master/CONTRIBUTING.md">
       Contributing
     </a>
     <span> | </span>
     <a href="https://roseleblood.github.io/openess/html/d3/dcc/md__r_e_a_d_m_e.html">
       Documentation
     </a>
     <span> | </span>
     <a href="https://webchat.freenode.net/?channels=openess">
       Chat
     </a>
   </h3>
   
 </div>
 
</div>

**OpenESS**  is a network-capable sound server libary mainly for embedded systems and other operatins systems. 
OpenESS is free and open-source software, and is licensed under the terms of the GNU Lesser General Public License.

## Usage example
_create the server_ 
```c
#include "ess.h"
#include "ess_backend.h"
#include "ess_context.h"
#include "ess_format.h"



ess_context_t context;
ess_backend_facktory_t* backend_list;

extern "C" void app_main() {

  //WORK IN PROGRESSS


  for(;;) { usleep(100000); }
}


```
_create the audio context_ 
```cpp
#include "ess.h"
#include "ess_backend.h"
#include "ess_context.h"
#include "ess_format.h"



ess_context_t context;
ess_backend_facktory_t* backend_list;

extern "C" void app_main() {
  backend_list =ess_backend_create_factory_list();

  ess_backend_probe_all(ESS_FORMAT_STEREO_96000_24,  &backend_list);
  ess_context_create(&context, ESS_FORMAT_STEREO_96000_24);
  ess_context_init_ex(&context, &backend_list[0]);

  ess_backend_destroy_factory_list(backend_list);

  //TODO anythings


  for(;;) { usleep(100000); }
}

```
_For more examples and usage, please refer to the [Wiki][wiki]


## Release History

* 0.2
  * rename headers
  * add platform abstraction layer
* 0.0.1
    * Work in progress

[wiki]: https://github.com/RoseLeBlood/openess/wiki
