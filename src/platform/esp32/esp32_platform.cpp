/****************************************************************************
 * Copyright (C) 2019 by Anna Sopdia Schröck                                *
 *                                                                          *
 * This file is part of ess.                                                *
 *                                                                          *
 *   ess is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   ess is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file esp32_platform.cpp
 * @author Anna Sopdia Schröck
 * @date 10 Februar 2019
 * @brief all esp32 generic platform functions source
 *
 */
#include "ess.h"
#include "ess_platform.h"
#include  "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "sdkconfig.h"

#include "esp_attr.h"
#include "esp_partition.h"
#include <sys/time.h>


unsigned int ess_platform_get_tick_count() {
  return (uint32_t) (xTaskGetTickCount() * portTICK_PERIOD_MS);
}
unsigned int ess_platform_get_ccount() {
  return xthal_get_ccount();
}
ess_error_t ess_platform_sleep(unsigned int secs) {
  vTaskDelay( (secs * 1000) / ((TickType_t) 1000 / configTICK_RATE_HZ));
  return ESS_OK;
}

int ess_platform_usleep(unsigned int usec) {
	vTaskDelay(usec / ((TickType_t) 1000000 / configTICK_RATE_HZ));
	return ESS_OK;
}

int IRAM_ATTR ess_platform_nsleep(const struct timespec *req, struct timespec *rem) {
	struct timeval start, end;

	if ((req->tv_nsec < 0) || (req->tv_nsec > 999999999)) {
		errno = EINVAL;

		return -1;
	}

	// Get time in msecs
	uint32_t msecs;

	msecs  = req->tv_sec * 1000;
	msecs += (req->tv_nsec + 999999) / 1000000;

	if (rem != NULL) {
		gettimeofday(&start, NULL);
	}

	vTaskDelay(msecs / portTICK_PERIOD_MS);
	if (rem != NULL) {
		rem->tv_sec = 0;
		rem->tv_nsec = 0;

		gettimeofday(&end, NULL);

		uint32_t elapsed = (end.tv_sec - start.tv_sec) * 1000
						 + ((end.tv_usec - start.tv_usec) / 1000000);

		if (elapsed < msecs) {
			if (elapsed > 1000) {
				rem->tv_sec = elapsed / 1000;
				elapsed -= rem->tv_sec * 1000;
				rem->tv_nsec = elapsed * 1000000;
			}
		}
	}
	errno = EINTR;
	return ESS_OK;
}

portMUX_TYPE microsMux = portMUX_INITIALIZER_UNLOCKED;

unsigned long IRAM_ATTR ess_platform_micros() {
  static unsigned long lccount = 0;
    static unsigned long overflow = 0;
    unsigned long ccount;
    portENTER_CRITICAL_ISR(&microsMux);
    __asm__ __volatile__ ( "rsr %0, ccount" : "=a" (ccount) );
    if(ccount < lccount){
        overflow += UINT32_MAX / CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ;
    }
    lccount = ccount;
    portEXIT_CRITICAL_ISR(&microsMux);
    return overflow + (ccount / CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ);
}
unsigned long ess_platform_millis() {
  return xTaskGetTickCount() * portTICK_PERIOD_MS;
}
