#ifndef __DOMOTICS_DEBUG_H__
#define __DOMOTICS_DEBUG_H__

#ifdef DOMOTICS_DEBUG_LOG_ENABLED
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x) 
#define DEBUG_PRINTLN(x) 
#endif

#endif