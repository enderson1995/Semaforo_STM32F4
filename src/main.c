/******************************************************************************/
/********************       STM32F407VG DISCOVERY   ***************************/
/********************               AN              ***************************/
/*****************************************************************************

    El presente codigo es para cumplir con el proyecto propuesto en clase de 
    un semaforo con posibilidad de pedir paso peatonal.

    Reglas a seguir: 
    -comentado del codigo estricto y necesario para este proyecto colaborativo
    -Los objetos y variables a definir se deben escribir con la primera letra en minuscula y las que definan espacios en mayusculas, sin _ ni -
    Ejmplo de variable a definir.. holaSoyUnaVariable o tambien epaSoyUnObjeto


*******************************************************************************/


/*********************************************************************************************/
/**************** Sección Inicialización Variables y definiciones  ***************************/
/***********  Metan todas las variables aqui, indiquen pa q las usan ************************/
/*********************************************************************************************/


#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_rcc.h"

static TIM_HandleTypeDef timerInstance = { 
    .Instance = TIM2
};

int t2Counter = 0;
 

/*******************************************************************************/

/*********************************************************************************************/
/**************** Sección declaracion de funciones a usar  ***************************/
/***********  Metan todas las funciones aqui, indiquen pa q las usan ************************/
/*********************************************************************************************/

void SysTick_Handler(void)    //Esto me mantiene el micro corriendo al reiniciar o desconectar
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}

//Función que inicializa el/los timers
void initializeTimers(){
  __TIM2_CLK_ENABLE();                //Habilito el timer1
  timerInstance.Init.Prescaler=999;                     //Prescaler de 40000 
  timerInstance.Init.CounterMode = TIM_COUNTERMODE_UP;    //Cuento para arriba
  timerInstance.Init.Period = 15999;                       //Periodo de 1 segundo
  timerInstance.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  timerInstance.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&timerInstance);                 //
  // HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  // HAL_NVIC_EnableIRQ(TIM2_IRQn);
  HAL_TIM_Base_Start_IT(&timerInstance);
  
}
  
//Función que inicializa los Leds
void initializeLeds(){
  BSP_LED_Init(LED3);   //Led Rojo
  BSP_LED_Init(LED5);   //Led Amarillo
  BSP_LED_Init(LED4);   //Segundero
  BSP_LED_Init(LED6);   //Led Verde
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *timerInstance)
{
 BSP_LED_Toggle(LED4);
}
// void TIM2_IRQHandler(void){
//   if (TIM_GetITStatus(TIM9, TIM_IT_UPDATE) != RESET){
//     //HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);
//     BSP_LED_Toggle(LED4);
//   }
    
// }


int main (){

  HAL_Init();
  initializeLeds();
  initializeTimers();


while (1)
{
  BSP_LED_Off(LED3);
  BSP_LED_Off(LED5);
  BSP_LED_On(LED6);
  HAL_Delay(10000);
  BSP_LED_Off(LED6);
  BSP_LED_On (LED5);
  HAL_Delay(2000);
  BSP_LED_Off(LED5);
  BSP_LED_On (LED3);
  HAL_Delay(15000);
  BSP_LED_Off(LED3);
}
}
