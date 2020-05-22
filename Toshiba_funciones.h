#include "derivative.h"

//bits de control
#define wr		PTCD_PTCD2	
#define rd		PTCD_PTCD3	
#define cs		PTCD_PTCD4	
#define cd		PTCD_PTCD5	
#define rst		PTCD_PTCD6

//#define LED		
#define Datos		PTFD
#define Datos_ES	PTFDD 		//si PTFDD = 0x00 IN
								//si PTFDD = 0xFF OUT
//modo 8 bit
#define DB0 		PTFD_PTFD0 
#define DB1			PTFD_PTFD1
#define DB2	 		PTFD_PTFD2
#define DB3	 		PTFD_PTFD3 
#define DB4 		PTFD_PTFD4					
#define DB5			PTFD_PTFD5
#define DB6	 		PTFD_PTFD6
#define DB7	 		PTFD_PTFD7 

#define STA0		PTFD_PTFD0
#define STA1		PTFD_PTFD1
#define STA2		PTFD_PTFD2
#define STA3		PTFD_PTFD3

//Declaración de prototipos

void lcd_init(void);

void delay (void);
void delay2 (void);

void send_d(unsigned char x);
void send2_d(unsigned char x);
void send_i(unsigned char x);

void chk_busy(void);
void chk_busy2(void);

void txt_hm(void);
void gr_hm (void);

void lcd_cl(void);
void gr_clear(void);
void lcd_cl_linea (int linea);
void lcd_cl_columna (int columna);

void put_char(char a,unsigned int a1, unsigned int a2);
void putsLCD(char *s, unsigned int a1, unsigned int a2);
