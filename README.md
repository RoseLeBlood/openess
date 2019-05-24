**OpenESS 0.86.0**   is a network-capable sound server libary mainly for embedded systems and other operatins systems.
OpenESS is free and open-source software, and is licensed under the terms of the GNU Lesser General Public License.

<a href="https://www.codacy.com/app/RoseLeBlood/openess?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=RoseLeBlood/openess&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/4f0ba2c68a904b8da2f1d45d5f3596d4"/></a>
<img src="https://img.shields.io/github/license/RoseLeBlood/Openess.svg"/>
<img src="https://img.shields.io/github/last-commit/roseleblood/openess.svg"/>
<a href="https://twitter.com/padersophia">
<img src="https://img.shields.io/twitter/follow/padersophia.svg"></a>


_For informations, examples and usage, please refer to the [Wiki][wiki]_

## Current Features

* Powerful core that allows for easy to port
* Powerful socket abscrations layer (SAL) only dram and dramlite at the moment
* Easy to use platform configuration
* mutex, spinlock, task and ringbuffer handling on various platform (current only esp32)
* generic backends:  i2s, more work in progress
* task are multitaskin safe
* code style min B
* C++ System

## Progressed features (when ready than leave beta phase)

* running example server on esp32 and linux
* MQTT status upport and logging (abscrations layer)
* Mini Webserver  - TCP for status (Port 8080)

## Planned features

* Improve documentation

* **Suggestions?** Feel free to create an issue and tag it with feature request.


## Release History
See [CHANGELOG.md][changelog]



[wiki]: https://github.com/RoseLeBlood/openess/wiki
[changelog]:CHANGELOG.md
