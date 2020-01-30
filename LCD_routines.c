#include "main.h"
#include "LCD_Routines.h"
#include "PORT.H"
#include "hardware_delay_1ms_T0.h"
#include "Outputs.h"


/***********************************************************************
DESC:    Writes data to the LCD with proper order for RS and E
INPUT: Uint8 for RS and Data to be written
       RS=0 instruction, RS=1 data
RETURNS: Nothing
CAUTION: None
************************************************************************/
void LCD_Write(bit RegSelect, uint8_t LCD_Data)
{
  if(RegSelect==0)     // Set or Clear RS before E is Set
  {
	Clear_P3_bit(RS_bit);
  }
  else
  {
    Set_P3_bit(RS_bit);
  }
  Set_P3_bit(E_bit);  // Set Enable before data written
  Output_P0(LCD_Data);         
  Clear_P3_bit(E_bit);   
  Output_P0(0xFF);
  Set_P3_bit(RS_bit);
}





/***********************************************************************
DESC:    Initializes LCD
INPUT: Nothing
RETURNS: Nothing
CAUTION: Uses timer 0 in delay functions
************************************************************************/
void LCD_Init(void)
{
  
  LCD_Write(COMMAND,function_set_8bit|two_line|set_5x8);   // 8-bit interface, 2 lines, 5x8 font
  DELAY_1ms_T0(5);
  LCD_Write(COMMAND,function_set_8bit|two_line|set_5x8);
  DELAY_1ms_T0(1);
  LCD_Write(COMMAND,function_set_8bit|two_line|set_5x8);
  DELAY_1ms_T0(1);
  LCD_Write(COMMAND,function_set_8bit|two_line|set_5x8);
  DELAY_1ms_T0(1);
  LCD_Write(COMMAND,display_control|display_on|cursor_off|blink_off);   // Display on, Cursor On and Not blinking
  DELAY_1ms_T0(1);
  LCD_Write(COMMAND,clear_display);   // Clear Display
  DELAY_1ms_T0(2);         // Must wait until this is complete
  LCD_Write(COMMAND,entry_mode|shift_right|cursor);   // DDRAM address increments with no scrolling
  DELAY_1ms_T0(1);

}



void LCD_print(uint8_t address, uint8_t num_bytes, uint8_t *array_name_p)
{
   uint8_t index,character;
   if(address!=no_addr_change)
   {
     LCD_Write(COMMAND,set_ddram_addr|address);
     DELAY_1ms_T0(1);
   }
   if(num_bytes==0)
   {
      index=0;
      character=*(array_name_p+index);
      while(character!=0)
      {
         LCD_Write(DDRAM,character);
         DELAY_1ms_T0(1);
         index++;
         character=*(array_name_p+index);
      }
    }
    else
    {
       for(index=0;index<num_bytes;index++)
       {
          character=*(array_name_p+index);
          LCD_Write(DDRAM,character);
          DELAY_1ms_T0(1);
       }
    }     
}	

