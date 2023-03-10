#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <ads1110.h>

int main(void)
{
  ADS1110_Handler_t Handler = {0};
  ADS1110_Sample_t  Sample = {0};

  ADS1110_Init(&Handler, ADS1110_ADDRESS_A0);
  ADS1110_SetMode(&Handler, ADS1110_MODE_SINGLESHOT);
  ADS1110_SetGain(&Handler, ADS1110_GAIN_1);
  ADS1110_SetRate(&Handler, ADS1110_RATE_15MPS);

  while (1)
  {
    ADS1110_StartConversion(&Handler);
    while (ADS1110_CheckDataReady(&Handler) == ADS1110_DATA_NOT_READY);
    ADS1110_ReadSample(&Handler, &Sample);
    printf("Voltage: %fLux\r\n\r\n",
           Sample.Voltage);
  }

  ADS1110_DeInit(&Handler);
  return 0;
}
