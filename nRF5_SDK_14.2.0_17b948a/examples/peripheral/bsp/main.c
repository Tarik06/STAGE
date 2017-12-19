/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 *
 * @defgroup bsp_example_main main.c
 * @{
 * @ingroup bsp_example
 * @brief BSP Example Application main file.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "nordic_common.h"
#include "nrf_error.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define BUTTON_PREV_ID           0                           /**< Button used to switch the state. */
#define BUTTON_NEXT_ID           1                           /**< Button used to switch the state. */

#define BSP_BTN {                \
        "BSP_INDICATE_IDLE",     \
        "BTN_1 Pressed",         \
        "BTN_2 Pressed",         \
        "BTN_3 Pressed",         \
        "BTN_4 Pressed"  \
}
#define BSP_LED {                \
        "BSP_INDICATE_IDLE",     \
        "LED_1 ON ",         \
        "LED_2 ON ",         \
        "LED_3 ON ",         \
        "LED_4 ON ",  \
				"LED_1 OFF ",         \
        "LED_2 OFF ",         \
        "LED_3 OFF ",         \
        "LED_4 OFF"  \
}
static uint8_t actual_bt_state = 0;
static uint8_t actual_led_state = 0;
static const char * indications_list[] = BSP_BTN;
static const char * indications_list_led[] = BSP_LED;
static uint8_t led1_state = 0;
static 	uint8_t led2_state = 0;
static 	uint8_t led3_state = 0;
static 	uint8_t led4_state = 0;
/**@brief Function for handling bsp events.
 */
void bsp_evt_handler(bsp_event_t evt)
{

	
        switch (evt)
        {
            case BSP_EVENT_KEY_0: //On Button 1 press
							if (led1_state == 0){
									led1_state++;
									actual_led_state= 1;
							}else{
									led1_state--;
									actual_led_state= 5;
							}
                LEDS_INVERT(BSP_LED_0_MASK); //Changes the current state of LED_1
								actual_bt_state = 1;
                break;

            case BSP_EVENT_KEY_1: //On Button 2 press
                LEDS_INVERT(BSP_LED_1_MASK); //Changes the current state of LED_2
								actual_bt_state = 2;                
								break;

            case BSP_EVENT_KEY_2: //On Button 3 press
                LEDS_INVERT(BSP_LED_2_MASK); //Changes the current state of LED_3
                actual_bt_state = 3;
								break;

            case BSP_EVENT_KEY_3:    //On Button 4 press                
                LEDS_INVERT(BSP_LED_3_MASK); //Changes the current state of LED_4
                actual_bt_state = 4;
								break;

            default:
                return; // no implementation needed
        }
				
        
   // uint32_t err_code = bsp_indication_set(actual_state);
    NRF_LOG_INFO("%s", (uint32_t)indications_list[actual_bt_state]);
		NRF_LOG_INFO("%s", (uint32_t)indications_list_led[actual_led_state]);
   // APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing low frequency clock.
 */
void clock_initialization()
{
    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    NRF_CLOCK->TASKS_LFCLKSTART    = 1;

    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0)
    {
        // Do nothing.
    }
}


/**@brief Function for initializing bsp module.
 */
void bsp_configuration()
{
    uint32_t err_code;

    err_code = bsp_init(BSP_INIT_LED | BSP_INIT_BUTTONS, bsp_evt_handler);
    APP_ERROR_CHECK(err_code);
}


/**
 * @brief Function for application main entry.
 */
int main(void)
{
    clock_initialization();

    uint32_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("BSP example started.");
    bsp_configuration();

    while (true)
    {
        NRF_LOG_FLUSH();
        __SEV();
        __WFE();
        __WFE();
        // no implementation needed
    }
}


/** @} */
