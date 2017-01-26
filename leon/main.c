///
/// @file
/// @copyright All code copyright Movidius Ltd 2012, all rights reserved.
///            For License Warranty see: common/license.txt
///
/// @brief     main leon file
///

// 1: Includes
// ----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <rtems.h>
#include "mv_types.h"       //UNUSED()
#include "rtems_config.h"
#include "temp_monitor.h"

// Static Function Prototypes
// ----------------------------------------------------------------------------

// Functions Implementation
// ----------------------------------------------------------------------------
void POSIX_Init(void *args)
{
    UNUSED(args);
	initClocksAndMemory();     // init clocks and memory needed for temp sensors

    TempInit();
    
	TempValues *values = malloc(sizeof(TempValues));
	char *json_string = calloc(MAX_STR_LEN, sizeof(char));

	do{
		sleep(1);

		TempSamples(values, json_string);
        
		printf("Temperatures are:\t%s\n", json_string);

	}while(1);

	free(values);
	free(json_string);
}

// User extension to be able to catch abnormal terminations
static void Fatal_extension(
                            Internal_errors_Source the_source,
                            bool is_internal,
                            uint32_t the_error
                            )
{
    switch (the_source)
    {
    case RTEMS_FATAL_SOURCE_EXIT:
        if (the_error)
            printk("Exited with error code %d\n", the_error);
        break; // normal exit
    case RTEMS_FATAL_SOURCE_ASSERT:
        printk("%s : %d in %s \n",
               ((rtems_assert_context * )the_error)->file,
               ((rtems_assert_context * )the_error)->line,
               ((rtems_assert_context * )the_error)->function);
        break;
    case RTEMS_FATAL_SOURCE_EXCEPTION:
        rtems_exception_frame_print((const rtems_exception_frame *) the_error);
        break;
    default:
        printk("\nSource %d Internal %d Error %d  0x%X:\n",
               the_source,
               is_internal, the_error, the_error);
        break;
    }
}
