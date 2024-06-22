# sun-tracking-solar-panel
This repository consists code, instructions and a ppt describing my mini project from semester 4. The code was developed on Keil and run on an 8051. 



Components:
1) N76E003
2) 2 LDR sensors.
3) Resistors to create a volage divider circuit. The stepper motor required 12V and the microcontroller needed 5V so we used avoltage divider circuit to bring 12V down to 5V to power the microcontroller.
4) 16x2 LCD Display.
5) Functional Solar Panel.
6) 1 small LED to test whether the solar panel works.
7) 1 Stepper Motor and driver (ULN2003)



The light intensity is detected by the LDR sensors attached beside the solar panel and a voltage divider circuit is created to convert LDRs' resistance output into voltage. This is then connected to an input port of the microcontroller and based on the input signals, digital output signals are sent to the motor driver which turns the stepper motor and the solar panel attached to it. We used an N76E003 for this project. The solar panel always shifted in the direction of the sun and we made sure it moved back to face the east when the sun set and the LDRs stopped detecting any sunlight. 



This was created within a week and we submitted a working model on time.
