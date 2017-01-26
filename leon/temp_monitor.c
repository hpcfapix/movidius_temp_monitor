#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "DrvTempSensor.h"
#include "temp_monitor.h"

void TempInit(void)
{
    DrvTempSensConfig tempParam = {1};

    DrvTempSensorInitialise(&tempParam);
    DrvTempSensorSetMode(TSENS_CSS, TSENS_CONTINUOUS_MODE, TSENS_SAMPLE_TEMP);
    DrvTempSensorSetMode(TSENS_MSS, TSENS_CONTINUOUS_MODE, TSENS_SAMPLE_TEMP);
    DrvTempSensorSetMode(TSENS_UPA0, TSENS_CONTINUOUS_MODE, TSENS_SAMPLE_TEMP);
    DrvTempSensorSetMode(TSENS_UPA1, TSENS_CONTINUOUS_MODE, TSENS_SAMPLE_TEMP);
}

void TempSamples(TempValues *x, char *string)
{
	DrvTempSensorGetSample(TSENS_CSS, &x->temperature_CSS);
	DrvTempSensorGetSample(TSENS_MSS, &x->temperature_MSS);
	DrvTempSensorGetSample(TSENS_UPA0, &x->temperature_UPA0);
	DrvTempSensorGetSample(TSENS_UPA1, &x->temperature_UPA1);

    memset(string, '\0', strlen(string));

    sprintf(string, "{\"temperature_CSS\":%f,\"temperature_MSS\":%f,\"temperature_UPA0\":%f,\"temperature_UPA1\":%f}",
                     x->temperature_CSS, x->temperature_MSS, x->temperature_UPA0, x->temperature_UPA1);
}
