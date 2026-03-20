/*
 * SysTasks.c
 *
 *  Created on: 26.03.2025
 *      Author: Lenovo
 */

#include "SysTasks.h"
#include "stm32f3xx_hal.h"

struct SysCtx_t{
	uint32_t IdleCounter;
	uint32_t HeartBeatState : 1,
	         Reserved       : 31;
};

struct SysCtx_t SysCtx;

SysCtxHandle_t GetSysCtxHande(void)
{
	return &SysCtx;
}

void ResetIdleCnt(SysCtxHandle_t SysCtxHandle)
{
	SysCtxHandle->IdleCounter = 0;
}

void IncIdleCnt(SysCtxHandle_t SysCtxHandle)
{
	SysCtxHandle->IdleCounter++;
}

void vApplicationIdleHook(void)
{
	IncIdleCnt(GetSysCtxHande());
}

void vApplicationMallocFailedHook(void)
{
	uint32_t i;

	//HAL already initialized GPIO
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);

	while(1)
	{
		for(i=1000000; i>0; i--);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
	}
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
	uint32_t i;

	//HAL already initialized GPIO
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);

	while(1)
	{
		for(i=1000000; i>0; i--);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
	}
}

void HeartBeatTask(void *pvParameters)
{
	const TickType_t xDelay = pdMS_TO_TICKS(500);//500 / portTICK_PERIOD_MS;

	//HAL already initialized GPIO
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
		vTaskDelay(xDelay);
	}
}
