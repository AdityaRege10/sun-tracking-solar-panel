#include "N76E003.h"
#include "lcd.h"


//unit16_t voltage;
uint16_t LDR1;
uint16_t LDR2;
uint32_t mapValue(uint32_t inputValue, uint32_t inputMin, uint32_t inputMax, uint32_t outputMin, uint32_t outputMax) ;

void setup (void);


void rotateStepper(int steps, int direction);
void stepMotor(int step);



//char str_voltage[20];




sbit STEPPER_PIN1 = P1^1;
sbit STEPPER_PIN2 = P1^2;
sbit STEPPER_PIN3 = P1^3;
sbit STEPPER_PIN4 = P1^4;



unsigned int ADC_read_0(void){
  register unsigned int adc_value = 0x0000;
	Enable_ADC_AIN6;
	P03_Input_Mode;
  clr_ADCF;
  set_ADCS;                  
  while(ADCF == 0);
  adc_value = ADCRH;
  adc_value <<= 4;
  adc_value |= ADCRL;
  return adc_value;
}

unsigned int ADC_read_1(void){
  register unsigned int adc_value = 0x0000;
	Enable_ADC_AIN0;
	P17_Input_Mode;
  clr_ADCF;
  set_ADCS;                  
  while(ADCF == 0);
  adc_value = ADCRH;
  adc_value <<= 4;
  adc_value |= ADCRL;
  return adc_value;
}

unsigned int ADC_read_2(void){
  register unsigned int adc_value = 0x0000;
	Enable_ADC_AIN1;
	P30_Input_Mode;
  clr_ADCF;
  set_ADCS;                  
  while(ADCF == 0);
  adc_value = ADCRH;
  adc_value <<= 4;
  adc_value |= ADCRL;
  return adc_value;
}


void main(void){
	float Voltage;
	float  mappedvalue;
	float volt;
		char str_voltage[20];
	//InitialUART0_Timer3(115200);
	//  TI = 1;
	
BIT A =0;
BIT C =0;

            setup();            
             while(1){
             
							Enable_ADC_AIN0;
            Voltage = ADC_read_0();
							mappedvalue = mapValue(Voltage,0, 4095,0,5000);
							 
							volt = mappedvalue/1000;
							 
							  LDR1 = ADC_read_1();
							 
							 LDR2 = ADC_read_2();
							 sprintf( str_voltage, "%0.2fV", volt);
					lcd_com(0x80);
             lcd_puts("Voltage:");
						 lcd_com(0x88);
             lcd_puts(str_voltage);;
							 
							if (LDR1 >= LDR2 && A==0)
							{
									
								 rotateStepper(512, 1);
								Timer3_Delay10us(1000);
									rotateStepper(0, 0);
								A=1;
								C=0;
							
								
							}
							else if(LDR1 <= LDR2 && C==0)
							{
								rotateStepper(512, -1); // Rotate 512 steps counterclockwise
								Timer3_Delay10us(1000);
								rotateStepper(0, 0);
								C=1;
								A=0;
							
							}
    }
  }
void setup(void){
	P00_Quasi_Mode;
	P01_Quasi_Mode;
	P02_Quasi_Mode;
	P04_Quasi_Mode;
	P05_Quasi_Mode;
	P06_Quasi_Mode;
	P07_Quasi_Mode;
	
  P11_PushPull_Mode;
	P12_PushPull_Mode;
	P13_PushPull_Mode;
	P14_PushPull_Mode;
	P17_Input_Mode;		//Enable_ADC_AIN0;
	P30_Input_Mode;		//Enable_ADC_AIN1;
	P03_Input_Mode;		//Enable_ADC_AIN6;
	//Set_All_GPIO_Quasi_Mode;

    lcd_init();
		InitialUART0_Timer3(115200);
	
    lcd_com (0x80);
    lcd_puts("Solar panel");
    lcd_com (0xC0);
    lcd_puts ("Tracking System");
    Timer3_Delay100ms(10);
	  lcd_com(0x80);
	  lcd_clr();
  	lcd_com (0xC0);
	  lcd_clr();

}

uint32_t mapValue(uint32_t inputValue, uint32_t inputMin, uint32_t inputMax, uint32_t outputMin, uint32_t outputMax) {
    return ((inputValue - inputMin) * (outputMax - outputMin)) / (inputMax - inputMin) + outputMin;
}


void stepMotor(int step) {
  switch (step) {
    case 0:
      STEPPER_PIN1 = 1;
      STEPPER_PIN2 = 0;
      STEPPER_PIN3 = 0;
      STEPPER_PIN4 = 0;
      break;
    case 1:
      STEPPER_PIN1 = 0;
      STEPPER_PIN2 = 1;
      STEPPER_PIN3 = 0;
      STEPPER_PIN4 = 0;
      break;
    case 2:
      STEPPER_PIN1 = 0;
      STEPPER_PIN2 = 0;
      STEPPER_PIN3 = 1;
      STEPPER_PIN4 = 0;
      break;
    case 3:
      STEPPER_PIN1 = 0;
      STEPPER_PIN2 = 0;
      STEPPER_PIN3 = 0;
      STEPPER_PIN4 = 1;
      break;
  }
}

void rotateStepper(int steps, int direction) {
  int stepNumber = 0;
int i;
  for ( i= 0; i < steps; i++) {
    stepMotor(stepNumber);
    stepNumber += direction;
    if (stepNumber > 3) {
      stepNumber = 0;
    } else if (stepNumber < 0) {
      stepNumber = 3;
    }
   Timer3_Delay10us(20); // Adjust delay to control speed
  }
}