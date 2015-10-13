#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <tft.h>
#include <inttypes.h>
#include "include/rfm12_config.h"
#include "rfm12.h"
using namespace std;
/* Colour definitions RGB565 */
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F      
#define GREEN       0x07E0      
#define CYAN        0x07FF      
#define RED         0xF800      
#define MAGENTA     0xF81F      
#define YELLOW      0xFFE0      
void Initialize_Screen();
void Initialize_Data();
void Update_Screen();
void Update_Data();

class tft_t tft;

void init(void)
{
	//RFM12_
	srand(0);
	DDRB |= 0x00; // set Port B as an input
	
	// Set up pin change interrupt
	PCICR = _BV(PCIE2); // Enable Port B
	PCMSK1 = _BV(PCINT16) | _BV(PCINT17); ; // enable pin 3 //| _BV(PCINT10);
	sei(); // enable global interrupts




	tft.init();
	tft.setOrient(tft.FlipLandscape);
	tft.setBackground(BLACK);
	tft.setForeground(WHITE);
	tft.clean();
	stdout = tftout(&tft);
	tft.setBGLight(true);
	sei();
}

void Initialize_Data(){

}

void Initialize_Screen(){
	//decorations
	tft.clean();
	tft.setZoom(2);
	tft.setXY(10,5);
	puts("Computer Networks Lab");
	
	tft.rectangle(0,25,320,2,BLUE);

	tft.setForeground(WHITE);
	tft.setZoom(2);
    tft.setXY(5,60);
    puts("RFM Input Data :");
    
    tft.setXY(5,80);
    puts("RFM Output Data:");
	

	
}

void Update_Data(){

}

void Send_Data(){

	

}


void Update_Screen(){
//	if (CLK) tft.setForeground(GREEN); else tft.setForeground(RED);
//    tft.setXY(150,105);
//    puts("CLK");
	
	//if (EncoderStart) tft.setForeground(GREEN); else tft.setForeground(RED);
	tft.setXY(50,35);
	puts("Start");
	
	//if (DataReady) tft.setForeground(GREEN); else tft.setForeground(RED);
	tft.setXY(170,35);
	puts("Data Ready");
	
	tft.setForeground(WHITE);
	tft.setXY(247,60);
	
	//fix,puts wasnt working
	for (int i=0;i<4;i++){
		//tft.putch(EncoderInputData[i]);
		tft.d.x += 12;
	}
	
	tft.setXY(247,80);
	//printf(DecoderOutputData);
	
	//if (DataIsValid) tft.setForeground(GREEN); else tft.setForeground(RED);
    tft.setXY(65,120);
    //puts("Valid");
	
	//if (Error) tft.setForeground(GREEN); else tft.setForeground(RED);
    tft.setXY(185,120);
    //puts("Error");
    
	tft.setForeground(WHITE);
    tft.setXY(255,160);
    //printf("%.2f%%",Raw_Error_Ratio);
    
	tft.setForeground(WHITE);
    tft.setXY(255,190);
   // printf("%.2f%%",Decoded_Error_Ratio);

}



int main(void)
{
	init();
	Initialize_Data();
	Initialize_Screen();

	uint8_t teststring[] = "Hello From Grisha\r\n";
    uint8_t packettype = 0xEE;
	
	rfm12_init();  /* initialize the library */
	
	sei();

	while (1)
	{
		/* ... */
		unsigned char r = rfm12_tx(sizeof(teststring), packettype, teststring);
		rfm12_tick();  /* periodic tick function - call that one once in a while */
		printf("%x", r);
	}
	return 1;
}

void dec2bin(int dec,char *bin)
{
   int i = 0;
   for(i = 0; i<4; i++){
     if((dec & (1 << i)) != 0){
       bin[3-i] = 49;
     }else{
       bin[3-i] = 48;
     } 
   }
}
