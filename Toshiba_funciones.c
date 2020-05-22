#include "Toshiba_funciones.h"
#include "derivative.h"

//funcion de inicio de GLCD
void lcd_init(void){	
	
	wr = 1;		rd = 1;		cs = 1;		cd = 1;
	//fs = 0;
	rst = 1;
	
	delay2();
	rst = 0;
	delay2();
	rst = 1;
	delay2();
	
	
	txt_hm();
	gr_hm();
	
	send_i(0x80);	//80 >> OR mode____83 >> AND mode
	send_i(0x98);	//graph on>>>>VER SI SE PUEDE DESACTIVAR
	
	gr_clear();
	
	lcd_cl();
	
}
//funciones de delays
void delay(void){
	int m;
	for(m=0;m<5;m++);
}
void delay2(void){
	unsigned int m2;
	for(m2=0;m2<100;m2++);
	
}

//text home
void txt_hm (void){
	send_d(0x00);
	send_d(0x00);
	send_i(0x40);//set text home address
	
	send_d(0x3C);
	send_d(0x00);
	send_i(0x41);//set text area
}
void send_d(unsigned char x){
	chk_busy();
	cd = 0;		cs = 0;		wr = 0;
	
	//Datos_ES = 0xFF;
	Datos = x;
	
	delay();
	delay();
	
	wr = 1;		cs = 1;
}
void send2_d(unsigned char x){
	chk_busy2();
	cd = 0;		cs = 0;		wr = 0;
	
	//Datos_ES = 0xFF;
	Datos = x;
	
	delay();
	delay();
	
	wr = 1;		cs = 1;
}
void send_i(unsigned char x){
	chk_busy();
	cd = 1;		cs = 0;		wr = 0;
	
	//Datos_ES = 0xFF;
	Datos = x;
	
	delay();
	delay();
	
	wr = 1;		cs = 1;
}
void chk_busy(void){
	cd = 1;		wr = 1;
	//Datos = 0x00;
	Datos_ES = 0x00;		//puerto datos como entrada
	
	do{
		cs = 1;		rd = 1;
		
		//delay();
		
		cs = 0;		rd = 0;
		
		delay();
		delay();
	
	}while((STA0!=1) || (STA1!=1)); 

	cs = 1;		rd = 1;
	Datos_ES = 0xFF;//puerto datos como salida
}
void chk_busy2(void){
	cd = 1;		wr = 1;
	//Datos = 0x00;
	Datos_ES = 0x00;//puerto datos como entrada
		
	do{
		cs = 1;		rd = 1;
		
		//delay();
		
		cs = 0;		rd = 0;
		
		delay();
		delay();
		
	}while(STA3!=1); //CHEQUEAR ESTE PASO

	cs = 1;		rd = 1;
	Datos_ES = 0xFF;//puerto datos como salida
}
void gr_hm(void){
	send_d(0x00);
	send_d(0x10);
	send_i(0x42);//set graphic home address
		
	send_d(0x1E);
	send_d(0x00);
	send_i(0x43);//set graphic area
}
void lcd_cl (void){
	int i,j;
	for(i=0;i<8;i++)
		{for(j=0;j<60;j++)
			{put_char(' ',j,i);}}
}
void put_char(char a, unsigned int a1,unsigned int a2){
	unsigned int adr;
	adr = 60 * a2 + a1;
	txt_hm();
	
	//send_i(0x94);  //text on
	
	send_d(adr % 256);
	send_d(adr / 256);
	send_i(0x24);		//set address pointer
	
	send_d(a - 32);  //ASCII offset
	send_i(0xC0);	 //data write, increment address
	send_i(0x9C);	 //text and graph on		
}
void putsLCD(char *s, unsigned int a1, unsigned int a2){
	int i = 0;
	while(*s){
		put_char(*s++,a1 + i,a2);
		i++;
		delay();
		
	}		
}
void gr_clear(void){
	int i,j;
	send_d(0x00);
	send_d(0x10);
	send_i(0x24);
	
	send_i(0x98);		//text off, graphic on
	
	for(i=0;i<30;i++)
		{for(j=0;j<128;j++)
		{
			send_d(0x00);
			send_i(0xC0);		//data write, increment addr
		}
		}
}
void lcd_cl_linea (int linea){
	int i,j;
	i=linea;
	
	for(j=0;j<30;j++)
			put_char(' ',j,i);
}
void lcd_cl_columna (int columna){
	int i,j;
	j=columna;
	
	for(i=0;i<30;i++)
		put_char(' ',j,i);
}
