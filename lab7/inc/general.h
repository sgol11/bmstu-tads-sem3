#ifndef __GENERAL__H__
#define __GENERAL__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include <inttypes.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define OK                   0
#define ERR_MEMORY          -1
#define ERR_READ            -2
#define NO_PATHS            -3

#endif