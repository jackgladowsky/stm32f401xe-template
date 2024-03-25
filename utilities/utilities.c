#include "utilities.h"

/**
 * Quick 'n' dirty delay
 *
 * @param time the larger it is the longer it will block
 */
void delay(unsigned time) 
{
    for (unsigned i=0; i<time; i++)
        for (volatile unsigned j=0; j<20000; j++);
}