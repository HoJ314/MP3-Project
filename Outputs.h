#ifndef _Outputs_H
#define _Outputs_H

#include "Main.H"

// Port Output Functions

void Output_P0(uint8_t Port_Data);
// void Output_P1(uint8_t Port_Data);
// void Output_P2(uint8_t Port_Data);
// void Output_P3(uint8_t Port_Data);

// Bit Output Functions

// void Clear_P0_bit(uint8_t Bit_Data);
void Clear_P1_bit(uint8_t Bit_Data);
void Clear_P2_bit(uint8_t Bit_Data);
void Clear_P3_bit(uint8_t Bit_Data);

// void Set_P0_bit(uint8_t Bit_Data);
void Set_P1_bit(uint8_t Bit_Data);
void Set_P2_bit(uint8_t Bit_Data);
void Set_P3_bit(uint8_t Bit_Data);


#endif