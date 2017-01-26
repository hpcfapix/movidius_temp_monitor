#ifndef _TEMP_MONITOR_H_
#define _TEMP_MONITOR_H_

#define MAX_STR_LEN 1024

typedef struct
{
    float temperature_CSS;
    float temperature_MSS;
    float temperature_UPA0;
    float temperature_UPA1;
} TempValues;

void TempInit(void);

void TempSamples(TempValues *x, char *string);

#endif