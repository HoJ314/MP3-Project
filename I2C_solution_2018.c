#include <stdio.h>
#include "main.h"
#include "PORT.H"
#include "UART.h"
#include "print_bytes.h"
#include "SPI.h"
#include "SDcard.h"
#include "Long_Serial_In.h"
#include "STA013_Config.h"
#include "LCD_routines.h"
#include "Outputs.h"




uint8_t xdata buf1[512];
uint8_t xdata buf2[512];

uint8_t code SD_Card_string[]="SD Card...";
uint8_t code High_Cap_string[]="HC";
uint8_t code Standard_Cap_string[]="SC";
uint8_t code Drive_string[]="Drive...";
uint8_t code Root_string[]="Root Found     ";
uint8_t code SDSC[]="Std. Capacity";
uint8_t code SDHC[]="High Capacity";

// Private Function Prototypes
//void Play_Song(uint32_t Start_Cluster);


main()
{
   uint32_t block_num,LBA;
   uint16_t i;
   uint8_t error_flag,SD_stat;
   


   Set_P2_bit(Amber_LED);
   Set_P2_bit(Yellow_LED);
   Set_P2_bit(Green_LED);
   Clear_P2_bit(Red_LED);
   
   i=0;
   while(i<=60000) i++;
   Set_P2_bit(Red_LED);
   AUXR=0x0c;   // make all of XRAM available
   if(OSC_PER_INST==6)
   {
      CKCON0=0x01;  // set X2 clock mode
   }
   else if(OSC_PER_INST==12)
   {
      CKCON0=0x00;  // set standard clock mode
   } 
   uart_init();
   LCD_Init();
   printf("I2C Test Program\n\r\n\n");
   error_flag=SPI_Master_Init(400000UL);
   if(error_flag!=no_errors)
   {
      Clear_P2_bit(Red_LED);
      while(1);
   }
   LCD_Print(line1,10,SD_Card_string);
   printf("SD Card Initialization ... \n\r");
   error_flag=SD_card_init();
   if(error_flag!=no_errors)
   {
      Clear_P2_bit(Red_LED);   
      print_error(error_flag);
      while(1);
   }
   SD_stat=Return_SD_Card_Type();
   if(SD_stat==Standard_Capacity)
   {
      LCD_Print(no_addr_change,2,Standard_Cap_string);
   }
   else
   {
      LCD_Print(no_addr_change,2,High_Cap_string);
   }
   error_flag=SPI_Master_Init(20000000UL);
   if(error_flag!=no_errors)
   {
      Clear_P2_bit(Red_LED); 
      while(1);
   }
   for(i=0;i<512;i++)
   {
      buf1[i]=0xff;  // erase valout for debug
      buf2[i]=0xff;
   }
   // STA013 Initialization: Reads ID register and if it is 0xAC, then sends config data
    STA013_init();   
   // Main Loop

   while(1)
   {
      printf("Input Block#: ");
      block_num=long_serial_input();
      LBA=block_num<<SD_stat;
	  GREENLED=0;
	  nCS0=0;
      error_flag=SEND_COMMAND(CMD17,LBA);
      if(error_flag!=no_errors)
      {
         REDLED=0;  // An error causes the program to stop
         while(1);
      }
      error_flag=read_block(512,buf1);
	  GREENLED=1;
	  nCS0=1;
      if(error_flag!=no_errors)
      {
         REDLED=0;  // An error causes the program to stop
         while(1);
      }
      print_memory(512, buf1);
   }
} 




