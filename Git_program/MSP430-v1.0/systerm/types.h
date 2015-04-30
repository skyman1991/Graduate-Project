/***********************************************************************************
    Filename: types.h

    Copyright 2007 Texas Instruments, Inc.
***********************************************************************************/

#ifndef TYPES_H
#define TYPES_H


//----------------------------------------------------------------------------------
// Types
//----------------------------------------------------------------------------------

typedef signed   char   int8;
typedef unsigned char   uint8;

typedef signed   short  int16;
typedef unsigned short  uint16;

typedef unsigned int    Uint16;
typedef signed int      Sint16;

typedef signed   long   int32;
typedef unsigned long   uint32;

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;

typedef void (*ISR_FUNC_PTR)(void);


//----------------------------------------------------------------------------------
// Memory Attributes
//----------------------------------------------------------------------------------

#ifdef __IAR_SYSTEMS_ICC__

#if defined __ICC430__

#define  CODE
#define  XDATA

#elif defined __ICC8051__

#define  CODE   __code
#define  XDATA  __xdata

#else
#error "Unsupported architecture"
#endif

#elif defined __KEIL__

#define  CODE   code
#define  XDATA  xdata

#else
#error "Unsupported compiler"
#endif

/**********************************************************************************/
#endif
