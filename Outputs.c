#include "main.h"
#include "PORT.H"

/*********************************************************************
*    Port Output Functions
********************************************************************/

/***********************************************************************
DESC:  Writes the value passed as a parameter to the specified port
INPUT: uint8_t value to be written to a port
RETURNS: Nothing
CAUTION: Only uncomment the functions that are to be used
************************************************************************/
void Output_P0(uint8_t Port_Data)
{
  P0=Port_Data;
}

/* void Output_P1(uint8_t Port_Data)
{
  P1=Port_Data;
}  */

/* void Output_P2(uint8_t Port_Data)
{
  P2=Port_Data;
}  */

/* void Output_P3(uint8_t Port_Data)
{
  P3=Port_Data;
} */

/*********************************************************************
*    Bit Output Functions
********************************************************************/


/***********************************************************************
DESC:  Clears the specified bits on a specified port
INPUT: 8-bit pattern with '1' bits for the bits to be cleared
RETURNS: Nothing
CAUTION: Only uncomment the functions that are to be used
************************************************************************/
/* void Clear_P0_bit(uint8_t Bit_Data)
{
  P0&=(~Bit_Data);
} */

void Clear_P1_bit(uint8_t Bit_Data)
{
  P1&=(~Bit_Data);
} 

void Clear_P2_bit(uint8_t Bit_Data)
{
  P2&=(~Bit_Data);
} 

void Clear_P3_bit(uint8_t Bit_Data)
{
  P3&=(~Bit_Data);
}

/***********************************************************************
DESC:  Set the specified bits on a specified port
INPUT: 8-bit pattern with '1' bits for the bits to be set
RETURNS: Nothing
CAUTION: Only uncomment the functions that are to be used
************************************************************************/
/* void Set_P0_bit(uint8_t Bit_Data)
{
  P0|=Bit_Data;
} */

void Set_P1_bit(uint8_t Bit_Data)
{
  P1|=Bit_Data;
}

 void Set_P2_bit(uint8_t Bit_Data)
{
  P2|=Bit_Data;
}

void Set_P3_bit(uint8_t Bit_Data)
{
  P3|=Bit_Data;
}
