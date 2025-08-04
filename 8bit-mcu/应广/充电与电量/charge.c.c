/******************************************************************************
 * Copyright (C) 2025 CHINAIC SEMICONDUCTOR, Co., Ltd. or its affiliates.
 * 
 * All Rights Reserved.
 * 
 * @file charge.c
 * 
 * @par dependencies 
 * - extern.h
 * 
 * @author Zenon | R&D Dept. | 
 * 
 * @brief Provide the functions of charging detection and battery level display.
 * 
 * Processing flow:
 * 
 * call directly.
 * 
 * @version V1.0 2025-2-14
 *
 * @note 1 tab == 4 spaces!
 * 
 *****************************************************************************/
 
/*--------------------------- charging_detection -----------------------------*/
#include"extern.h"


#define CHRG_FILTER_THRESHOLD 10
#define STDBY_FILTER_THRESHOLD 20

CHRG	=>	PA.3
STDBY	=>	PA.4

word	stdby_filter_cnt;
byte	chrg_filter_cnt;
bit		chrg_flag;
bit		stdby_flag;


void handle_charging_start(void) {
    /* USER CODE BEGIN */

    /* USER CODE END */
}

void handle_charging_complete(void) {
    /* USER CODE BEGIN */

    /* USER CODE END */
}

void handle_charging_cancel(void) {
    /* USER CODE BEGIN */

    /* USER CODE END */
}

/**
 * @brief Scan the charging status based on the states of CHRG and STDBY pins.
 * 
 * This function continuously monitors the states of the CHRG and STDBY pins to determine
 * the current charging status, including charging in progress, fully charged, and charging canceled.
 * It uses filtering counters to avoid false detections caused by pin state jitters.
 * 
 * Steps:
 *  1. Read the states of CHRG and STDBY pins.
 *  2. Check the states and update the corresponding filtering counters.
 *  3. When the filtering counter reaches the threshold, determine the charging status change
 *     and call the corresponding event - handling functions.
 *  4. Reset the flags and counters when the charging is canceled.
 * 
 * @return None
 */
void charging_detection(void)
{
    /* Get CHRG & STDBY pin status */
    bit chrg_state;
    bit stdby_state;
	if(CHRG == 0)
	{
		chrg_state = 1;
	}
	else if(CHRG == 1)
	{
		chrg_state = 0;
	}
	if(STDBY == 0)
	{
		chrg_state = 1;
	}
	else if(STDBY == 1)
	{
		chrg_state = 0;
	}

	if(chrg_state && !stdby_state) /* Charging detection */
	{
		chrg_filter_cnt++;
		if(chrg_filter_cnt >= CHRG_FILTER_THRESHOLD)
		{
			chrg_filter_cnt = 0;
			if(!chrg_flag) 
			{
				/* The moment of plugging in for charging */
				handle_charging_start(); 
			}	
			chrg_flag = 1;
			stdby_flag = 0;
		}
	}
	else if(!chrg_state && !stdby_state) /* Full power detection */
	{
		stdby_filter_cnt++;
		if(stdby_filter_cnt >= STDBY_FILTER_THRESHOLD)
		{
			stdby_filter_cnt = 0;
			if(!stdby_flag)
			{
				/* The moment of fully charged */
				handle_charging_complete(); 
			}	
			chrg_flag = 0;
			stdby_flag = 1;
		}		
	}
	else if(chrg_state && stdby_state)  /* No charging */
	{
		if(chrg_flag || stdby_flag)
		{
			/* The moment of cancel charging */
			handle_charging_cancel(); 
		}
		chrg_filter_cnt = 0;
		stdby_filter_cnt = 0;
		chrg_flag = 0;
		stdby_flag = 0;
	}
}

/*--------------------------- battery_level_display -----------------------------*/
// Mode definitions
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
// Current flashing mode, can be switched by modifying this macro
#define CURRENT_MODE MODE_1
#define LOW_POWER_THRESHOLD 10
#define FLASH_TIME 500

// Vars definitions
word	flash_cnt;
word 	sub_filt_cnt;
word 	add_filt_cnt;
word	low_power_filt_cnt;
byte	baterry_level_temp;
byte 	baterry_level;
byte	battery_level_disp;

bit power_flag;
bit low_power_flag;


/**
 * @brief Convert ADC value to battery level.
 * 
 * This function determines the battery level based on the ADC value and charging status.
 * It updates the battery level and display value accordingly.
 * 
 * @param[in] filt_ad_val: The value of filtered ADC value.
 *
 * @return None
 */
void ad_to_battery_level(byte filt_ad_val)
{
	if(chrg_flag || stdby_flag) // Charging or fully charged
	{
		if(chrg_flag) // Charging
		{
			if(filt_ad_val >= 200)
			{
				baterry_level_temp = 2;
			}
			else if(filt_ad_val >= 190 && filt_ad_val < 200)
			{
				baterry_level_temp = 1;
			}
			else if(filt_ad_val < 190)
			{
				baterry_level_temp = 0;
			}
			/* Only add */
			if(baterry_level <= baterry_level_temp)
			{
				sub_filt_cnt = 0;
				add_filt_cnt ++;
				if(add_filt_cnt >= 1000)
				{
					add_filt_cnt = 0;
					baterry_level ++;
				}
			}
			else
			{
				add_filt_cnt = 0;
			}
		}
		else if(stdby_flag) // Fully charged
		{
			battery_level_disp = 3;
		}
	}
	else if(power_flag) // Discharging state (power on without charging)
	{
		if(filt_ad_val >= 200)
		{
			baterry_level_temp = 3;
		}
		else if(filt_ad_val >= 190 && filt_ad_val < 200)
		{
			baterry_level_temp = 2;
		}
		else if(filt_ad_val >= 170 && filt_ad_val < 190)
		{
			baterry_level_temp = 1;
		}
		else if(filt_ad_val >= 165 && filt_ad_val < 170)
		{
			baterry_level_temp = 0;
		}
		else if(filt_ad_val < 165)
		{
			if(low_power_filt_cnt >= LOW_POWER_THRESHOLD)
			{
				low_power_filt_cnt = 500;
				// low_power_flag = 1;
			}
			else
			{	
				low_power_filt_cnt ++;
			}
		}
		/* Only sub */
		if(baterry_level > baterry_level_temp)
		{
			add_filt_cnt = 0;
			sub_filt_cnt ++;
			if(sub_filt_cnt >= 500)
			{
				sub_filt_cnt = 0;
		
				baterry_level --;
			}
		}
		else
		{
			sub_filt_cnt = 0;
		}
	}
	else
	{
		battery_level_disp = 0;
	}
}

/**
 * @brief Display the charging status with different flashing modes.
 * 
 * This function updates the display value according to the current flashing mode and battery level.
 */
void battery_level_display(void) 
{
	flash_cnt ++;
	/* Low power flashing */
	if(baterry_level == 0)
	{
		if(flash_cnt >= 2*FLASH_TIME)
		{
			flash_cnt = 0;
		}

		if(flash_cnt >= FLASH_TIME)
		{
			battery_level_disp = 1;
		}
		else
		{
			battery_level_disp = 0;
		}
	}
	else
	{
		battery_level_disp = baterry_level;
		#if CURRENT_MODE == MODE_1
		/* 充电显示方式1：始终逐灯流水闪烁 */
		if(flash_cnt >= 4*FLASH_TIME)
		{
			flash_cnt = 0;
		}
		if(flash_cnt >= 3*FLASH_TIME)
		{
			battery_level_disp = 3;
		}
		else if(flash_cnt >= 2*FLASH_TIME)
		{
			battery_level_disp = 2;
		}
		else if(flash_cnt >= FLASH_TIME)
		{
			battery_level_disp = 1;
		}
		else
		{
			battery_level_disp = 0;
		}
		#elif CURRENT_MODE == MODE_2
		/* 充电显示方式2：根据电量档位流水闪烁 */	
		if(baterry_level == 1)
		{
			if(flash_cnt >= 2*FLASH_TIME)
			{
				flash_cnt = 0;
			}
			else if(flash_cnt >= FLASH_TIME)
			{
				battery_level_disp = 1;
			}
			else
			{
				battery_level_disp = 0;
			}

		}
		else if(baterry_level == 2)
		{
			if(flash_cnt >= 3*FLASH_TIME)
			{
				flash_cnt = 0;
			}
			if(flash_cnt >= 2*FLASH_TIME)
			{
				battery_level_disp = 2;
			}
			else if(flash_cnt >= FLASH_TIME)
			{
				battery_level_disp = 1;
			}
			else
			{
				battery_level_disp = 0;
			}
		}
		else if(baterry_level == 3)
		{
			if(flash_cnt >= 4*FLASH_TIME)
			{
				flash_cnt = 0;
			}
			if(flash_cnt >= 3*FLASH_TIME)
			{
				battery_level_disp = 3;
			}
			else if(flash_cnt >= 2*FLASH_TIME)
			{
				battery_level_disp = 2;
			}
			else if(flash_cnt >= FLASH_TIME)
			{
				battery_level_disp = 1;
			}
			else
			{
				battery_level_disp = 0;
			}
		}
		#elif CURRENT_MODE == MODE_3
		/* 充电显示方式3：充满档位常亮，仅在充档位闪灯 */
		if(flash_cnt >= 2*FLASH_TIME)
		{
			flash_cnt = 0;
		}
		if(baterry_level == 1)
		{
			if(flash_cnt >= FLASH_TIME)
			{
				battery_level_disp = 1;
			}
			else
			{
				battery_level_disp = 0;
			}
		}
		else if(baterry_level == 2)
		{
			if(flash_cnt >= FLASH_TIME)
			{
				battery_level_disp = 2;
			}
			else
			{
				battery_level_disp = 1;
			}
		}
		else if(baterry_level == 3)
		{
			if(flash_cnt >= FLASH_TIME)
			{
				battery_level_disp = 3;
			}
			else
			{
				battery_level_disp = 2;
			}
		}		
		#endif
	}

	if(battery_level_disp == 0)
	{
		// All LEDs off

	}
	else if(battery_level_disp == 1)
	{
		// Only LED_1 on

	}
	else if(battery_level_disp == 2)
	{
		// Only LED_1、LED_2 on

	}
	else if(battery_level_disp == 3)
	{
		// Only LED_1、LED_2、LED_3 on

	}
}




