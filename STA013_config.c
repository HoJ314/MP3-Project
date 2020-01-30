#include "main.h"
#include "PORT.H"
#include "I2C.h"
#include "STA013_Config.h"
#include "Outputs.h"
#include <stdio.h>



/***********************************************************************
DESC:    Initializes the STA013 with the following steps:
         Applies a hardware reset signal, checks the ID register for an 0xAC
		 response and then sends the configuration data.
RETURNS: error flag
CAUTION: 
          
************************************************************************/


uint8_t STA013_init(void)
{
   uint8_t error_flag, timeout, reg_addr;
   uint8_t idata send[3], rcv[3];
   uint8_t * config_data_p;
   uint16_t j;

   uint8_t code STA_cfg_addr[18]={0x54, 0x55,  6, 11,  82,  81, 101, 100, 80, 97, 0x05, 0x0d, 0x18, 0x0c, 0x46, 0x48, 0x7d, 0x72};
   uint8_t code STA_cfg_data[18]={0x07, 0x10,  9,  2, 184,   0,   0,   0,  6,  5, 0xa1, 0x00, 0x04, 0x05, 0x07, 0x07, 0x07, 0x01};

   extern uint8_t code CONFIG;
   extern uint8_t code CONFIG2;

   Clear_P3_bit(STA013_RESET_bit);

   send[0]=0x01;   // address of the ID reg.  
   timeout=50;

   Set_P3_bit(STA013_RESET_bit);    // make STA013 active
   //Clear_P3_bit(Trigger_bit);    //Trigger for debug

/*   do
   {
      error_flag=I2C_Write(STA013,1,send);
      timeout--;
      if(timeout==0) AMBERLED=0;
   }while((error_flag!=no_errors)&&(timeout!=0));
   if(timeout!=0)
   {
      timeout=50;
	  do
	  {
        error_flag=I2C_Read(STA013,1,rcv);
        timeout--;
	  }while((error_flag!=no_errors)&&(timeout!=0));
	  if(timeout!=0)
	  {
         printf("Output from ID register: %2.2bX \n\r",rcv[0]);
	  }
   }  */
   do
   {
      Clear_P3_bit(Trigger_bit);    //Trigger for debug
      error_flag=I2C_Read(STA013,1,1,1,rcv);
      timeout--;
      Set_P3_bit(Trigger_bit);
   }while((error_flag!=no_errors)&&(timeout!=0));
   
   if(timeout!=0)
   {
       printf("Output from ID register: %2.2bX \n\r",rcv[0]);
   }



   if(rcv[0]==0xAC)
   {
     //send[0]=0x71;
     //error_flag=I2C_Write(STA013,1,send);
     //error_flag=I2C_Read(STA013,1,rcv);
	 error_flag=I2C_Read(STA013,0x71,1,1,rcv);
     printf("STA013 SoftVersion: %2.2bX \n\r",rcv[0]); 
     j=0;
     config_data_p=&CONFIG;  // point to STA013 configuration file
     do
     {
        //reg_addr=*(config_data_p+j);
        reg_addr=config_data_p[j];
        j++;
        //send[0]=*(config_data_p+j);
        send[0]=config_data_p[j];
        j++;
        if(reg_addr!=0xff)
        {
          
           timeout=50;
           do
           {
               error_flag=I2C_Write(STA013,reg_addr,1,1,send);
               timeout--;
               if(timeout==0) AMBERLED=0;
           }while((error_flag!=no_errors)&&(timeout!=0));
        }
     }while((reg_addr!=0xff) && (timeout!=0));
     printf("First configuration file sent...\n\r");
     printf("Number of values written: %d \n\r",j>>1);
     j=0;
     config_data_p=&CONFIG2;  // point to STA013 configuration file
     do
     {
        reg_addr=*(config_data_p+j);
        j++;
        send[0]=*(config_data_p+j);
        j++;
        if(reg_addr!=0xff)
        {
           timeout=50;
           do
           {
               error_flag=I2C_Write(STA013,reg_addr,1,1,send);
               timeout--;
               if(timeout==0) AMBERLED=0;
           }while((error_flag!=no_errors)&&(timeout!=0));
        }
     }while((reg_addr!=0xff) && (timeout!=0));
     //send[0]=0x71;
     //error_flag=I2C_Write(STA013,1,send);
     //error_flag=I2C_Read(STA013,1,rcv);
	 error_flag=I2C_Read(STA013,0x71,1,1,rcv);
     printf("STA013 SoftVersion: %2.2bX \n\r",rcv[0]);            
        
     for(j=0;j<18;j++)
	  {
	    reg_addr=STA_cfg_addr[j];
	    send[0]=STA_cfg_data[j];
        timeout=50;
        do
        {
            error_flag=I2C_Write(STA013,reg_addr,1,1,send);
            timeout--;
            if(timeout==0) AMBERLED=0;
        }while((error_flag!=no_errors)&&(timeout!=0));
		printf("Sent to STA013: %2.2bX  %2.2bX \n\r",reg_addr,send[0]);
		reg_addr=STA_cfg_addr[j];
        //error_flag=I2C_Write(STA013,1,send);
        error_flag=I2C_Read(STA013,reg_addr,1,1,rcv);
        printf("Output from register: %2.2bX  %2.2bX %2.2bX \n\r",reg_addr,rcv[0],error_flag);
	  }
      printf("Configuration Complete\n\r");
   }      
   return error_flag;
}
