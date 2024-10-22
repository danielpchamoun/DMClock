/*
 * File:   main.c
 * Author: Daniel
 *
 * Created on June 11, 2024, 10:47 PM
 */

#include <xc.h>
#include "mcc_generated_files\system\system.h"
#include "mcc_generated_files\i2c_host\i2c_host_types.h"
#include "mcc_generated_files\i2c_host\mssp1.h"

#define _XTAL_FREQ 32000000


//saved in non volatile eeprom
extern __eeprom uint8_t alarm = 0xff;

//low drum 5 + 128 + 10 = 143 ticks of delay
void playLDrum(void){ 
    TMR6_Stop();
    TMR6_PeriodCountSet(128);
    TMR6_Start();
    __delay_ms(1);
    TMR6_Stop();
    TMR6_PeriodCountSet(100);
    TMR6_Start();
    __delay_ms(1);
    TMR6_Stop();
    TMR6_PeriodCountSet(80);
    TMR6_Start();
    __delay_ms(1);
    TMR6_Stop();
    TMR6_PeriodCountSet(50);
    TMR6_Start();
    __delay_ms(1);
    
    TMR6_Stop();
    TMR6_PeriodCountSet(30);
    TMR6_Start();
    __delay_ms(1);    
    for(int i = 0; i < 256; i+=2){
        TMR6_Stop();
        TMR6_PeriodCountSet(i);
        TMR6_Start();
        __delay_ms(1);
    }    
    TMR6_Stop();
    TMR6_PeriodCountSet(255);
    TMR6_Start();
    __delay_ms(10);    
    TMR6_Stop();
}
//hihat 128 ticks of delay
void playHH(void){ 
    for(int i = 255; i >= 0 ; i-=2){
        TMR6_Stop();
        TMR6_PeriodCountSet(i);
        TMR6_Start();
        __delay_ms(1);
    }
}

//fast hihat 32 ticks of delay
void fastHH(void){
    for(int i = 128; i >= 0 ; i-=4){
        TMR6_Stop();
        TMR6_PeriodCountSet(i);
        TMR6_Start();
        __delay_ms(1);
    }
    
}

//fast hihat 32 ticks of delay
void fastLH(void){
    for(int i = 128; i <= 256 ; i+=4){
        TMR6_Stop();
        TMR6_PeriodCountSet(i);
        TMR6_Start();
        __delay_ms(1);
    }
    
}

//plays gate of steiner alarm
void playTheme1(void){
    // Note to Period Values
    // B, C, C#, D, D#, E, F, F#, G, G#, A, A#
    // 0  1  2   3  4   5  6  7   8  9   10 11
    size_t o1[] = {252,238,224,212,200,189,178,168,158,149,141,133};
    size_t o2[] = {126,118,112,105,99,94,88,83,79,74,70,66};
    size_t o3[] = {62,58,56,52,49,46,44,41,39,37,35,33};

    const int tempo = 565;
    const int drumdelay = 42;
    
    //start verse 1

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[1]); //C.
    TMR2_Start();


    TMR4_Stop();
    TMR4_PeriodCountSet(o1[1]); //C L
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - (2*(128)) - (1*(143)) - (2*drumdelay));
    TMR2_Stop();

    TMR2_PeriodCountSet(o1[11]); //A#
    TMR2_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();     
    __delay_ms(drumdelay);
    __delay_ms(70);
    playLDrum();

    __delay_ms(tempo - 2*(128) - 143 - 2*drumdelay - 70);
    TMR2_Stop();

    TMR2_PeriodCountSet(o2[4]); //D# 
    TMR2_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo  - 2*(128) - drumdelay - 200);
    TMR2_Stop();

    TMR2_PeriodCountSet(o2[1]); //C.
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[4]); //D# L
    TMR4_Start();
    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo - 128 - 2*(143) - 2*drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o1[11]); //A#
    TMR2_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(tempo - 220 - (2*128) - 2*drumdelay);
    TMR4_Stop();
    TMR2_Stop();        
    TMR2_PeriodCountSet(o1[8]); //G.
    TMR2_Start(); 
    TMR4_PeriodCountSet(o1[4]); //D# L
    TMR4_Start();

    playHH();
    __delay_ms(tempo - 350 - 128);


    TMR2_Stop();



    TMR2_PeriodCountSet(o1[9]); //G#.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[2]); //C# L
    TMR4_Start();
    playHH();

    __delay_ms(tempo - 350 - 128);

    TMR2_Stop();
    TMR2_PeriodCountSet(o1[11]); //A#.
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[1]); //C  L
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playHH();


    __delay_ms(tempo - 142 - 2*128 - 2*drumdelay);
    TMR2_Stop();
    TMR4_Stop();

    TMR2_PeriodCountSet(o1[9]); //G#
    TMR2_Start();
    TMR4_PeriodCountSet(o1[4]);  //D# L
    TMR4_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();

    __delay_ms(tempo - 142 - 2*128 - 2*drumdelay);
    TMR2_Stop();
    TMR4_Stop();

    TMR2_PeriodCountSet(o2[4]); //D#
    TMR2_Start();
    TMR4_PeriodCountSet(o1[6]); // F L 
    TMR4_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo-200 - 128*2 - drumdelay );
    TMR4_Stop();
    TMR2_Stop();


    TMR2_PeriodCountSet(o1[8]); //G
    TMR2_Start();
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - 2*drumdelay - 2*141 - 128);
    TMR2_Stop();
    TMR4_Stop();

    TMR2_PeriodCountSet(o1[9]); //G#
    TMR2_Start();
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();        
    __delay_ms(drumdelay);

    //finisher goes here
    fastHH();
    __delay_ms(33);
    fastHH();
    __delay_ms(33);
    fastHH();

    __delay_ms(tempo - 2*128 - 141 - 32*3 - 66); //subtract however long finisher takes from here
    TMR2_Stop();
    //end verse 1
    __delay_ms(tempo-400);


    //start verse 2 ------------------------------------------
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[1]); //C.
    TMR2_Start();


    TMR4_Stop();
    TMR4_PeriodCountSet(o1[1]); //C L
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - (2*(128)) - (1*(143)) - (2*drumdelay));
    TMR2_Stop();

    TMR2_PeriodCountSet(o1[11]); //A#
    TMR2_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();     
    __delay_ms(drumdelay);
    __delay_ms(35);
    playLDrum();
    __delay_ms(35);
    __delay_ms(tempo - 2*(128) - 143 - 2*drumdelay - 70);
    TMR2_Stop();

    TMR2_PeriodCountSet(o2[4]); //D# 
    TMR2_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - 150 - drumdelay - 2*128);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[6]); //F. 
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[4]);  //D# L
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();





    __delay_ms(tempo - 2*128 - 1*143 - 2*drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[6]);  //F L
    TMR4_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo-200 - 2*128 - drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[9]);      //G#
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[11]);  //A# L
    TMR4_Start();

    playLDrum();        
    __delay_ms(tempo-375 - 143);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[8]);      //G
    TMR2_Start();        

    playHH();
    __delay_ms(tempo- 400 - 64);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[1]);      //C
    TMR2_Start();
    playHH();

    //----

    __delay_ms(150-128);

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[11]);  //A# L //start of high finisher
    TMR4_Start();
    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo - 143 - 2*drumdelay - 2*128);


    TMR4_Stop();
    TMR4_PeriodCountSet(o3[1]);  //C L
    TMR4_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();

    __delay_ms(tempo - 143 - 2*drumdelay - 2*128);

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[11]);  //A# L
    TMR4_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo-250 -2*128 - drumdelay);

    TMR4_Stop();
    __delay_ms(100); //EDIT?
    TMR4_PeriodCountSet(o2[11]);  //A# L
    TMR4_Start();
    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo-128 - 2*drumdelay - 2*141);

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[10]);  //A L
    TMR4_Start();

    playHH();
    __delay_ms(drumdelay);
    //jubbly jubbly drums
    playHH();
    __delay_ms(20);
    fastHH();
    __delay_ms(20);
    fastHH();


    __delay_ms(tempo - 128*2 - 20*2 - 2*32 - drumdelay);

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[8]);  //G L
    TMR4_Start();
    playHH();
    __delay_ms(20);
    fastHH();
    __delay_ms(20);
    fastHH();
    __delay_ms(tempo - 200 - 128 - 32*2 - 20*2);


    //end verse 2


    //start verse 3
            TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();


    TMR4_Stop();
    TMR4_PeriodCountSet(o1[1]); //C L
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - (2*(128)) - (1*(143)) - (2*drumdelay));
    TMR2_Stop();

    TMR2_PeriodCountSet(o2[11]); //A#
    TMR2_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();     
    __delay_ms(drumdelay);
    __delay_ms(70);
    playLDrum();

    __delay_ms(tempo - 2*(128) - 143 - 2*drumdelay - 70);
    TMR2_Stop();

    TMR2_PeriodCountSet(o3[4]); //D# 
    TMR2_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo  - 2*(128) - drumdelay - 200);
    TMR2_Stop();

    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[4]); //D# L
    TMR4_Start();
    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo - 128 - 2*(143) - 2*drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[11]); //A#
    TMR2_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(tempo - 220 - (2*128) - 2*drumdelay);
    TMR4_Stop();
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start(); 
    TMR4_PeriodCountSet(o1[4]); //D# L
    TMR4_Start();

    playHH();
    __delay_ms(tempo - 350 - 128);


    TMR2_Stop();



    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[2]); //C# L
    TMR4_Start();
    playHH();

    __delay_ms(tempo - 350 - 128);

    TMR2_Stop();
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[1]); //C  L
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playHH();


    __delay_ms(tempo - 142 - 2*128 - 2*drumdelay);
    TMR2_Stop();
    TMR4_Stop();

    TMR2_PeriodCountSet(o2[9]); //G#
    TMR2_Start();
    TMR4_PeriodCountSet(o1[4]);  //D# L
    TMR4_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();

    __delay_ms(tempo - 142 - 2*128 - 2*drumdelay);
    TMR2_Stop();
    TMR4_Stop();

    TMR2_PeriodCountSet(o3[4]); //D#
    TMR2_Start();
    TMR4_PeriodCountSet(o1[6]); // F L 
    TMR4_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo-200 - 128*2 - drumdelay );
    TMR4_Stop();
    TMR2_Stop();


    TMR2_PeriodCountSet(o2[8]); //G
    TMR2_Start();
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - 2*drumdelay - 2*141 - 128);
    TMR2_Stop();
    TMR4_Stop();

    TMR2_PeriodCountSet(o2[9]); //G#
    TMR2_Start();
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();

    playHH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();        
    __delay_ms(drumdelay);

    //finisher goes here
    fastHH();
    __delay_ms(33);
    fastHH();
    __delay_ms(33);
    fastHH();

    __delay_ms(tempo - 2*128 - 141 - 32*3 - 66); //subtract however long finisher takes from here
    TMR4_Stop();
    //end verse 3
    __delay_ms(150);


    //start verse 4


    TMR2_Stop();
    TMR2_PeriodCountSet(o2[11]); //A#
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[7]); //F#
    TMR4_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo-150 - 128 - 141 - drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o3[1]); //C
    TMR2_Start();
    playHH();

    __delay_ms(tempo-350 - 128);

    TMR2_Stop();
    TMR2_PeriodCountSet(o3[2]); //C#
    TMR2_Start();
    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo-200 - 2*128 - drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o3[4]); //D#
    TMR2_Start();

    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(tempo-200 - 141 - drumdelay - 128);

    TMR2_Stop();
    TMR2_PeriodCountSet(o3[6]); //F
    TMR2_Start();
    playHH();
    //F# A# C C# D# F# F C F (C instead of F because no space)x

    __delay_ms(175 - 128);

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    playLDrum();
    __delay_ms(drumdelay);
    playLDrum();


    __delay_ms(tempo-155 - 2*141 - drumdelay);

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();  
    playHH();
    __delay_ms(tempo-432-128);
    TMR2_Stop(); 

    __delay_ms(95);  

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[2]); //C#
    TMR4_Start();
    playHH();
    __delay_ms(195-128);
    TMR2_PeriodCountSet(o3[6]); //F
    TMR2_Start();
    playHH();
    __delay_ms(tempo-350-128-20);


    TMR4_Stop();
    TMR4_PeriodCountSet(o2[4]); //D#
    TMR4_Start();    
    playLDrum();
    __delay_ms(160-141);

    TMR2_Stop();
    TMR2_PeriodCountSet(o3[11]); //A#
    TMR2_Start();
    playHH();
    __delay_ms(tempo-370-128);

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[7]); //F#
    TMR4_Start(); 
    playHH();
    //__delay_ms(100);
    TMR2_Stop();
    __delay_ms(120-28);
    TMR2_PeriodCountSet(o3[11]); //A#
    TMR2_Start(); 

    TMR4_Stop();
    TMR4_PeriodCountSet(o2[6]); //F
    TMR4_Start();    

    playLDrum();
    __delay_ms(drumdelay);

    playHH();
    __delay_ms(drumdelay+20);

    playHH();
    __delay_ms(drumdelay+20);

    playHH();
    __delay_ms(drumdelay+20);

    playHH();

    __delay_ms(drumdelay+20);

    playLDrum();
    //560 - 2*141 - 3*128 - 4 *(42) 
    //-274
    __delay_ms(tempo-274 - 128 - drumdelay-80);
    TMR4_Stop();
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start(); 
    playHH();
    __delay_ms(drumdelay);
    playHH();

    __delay_ms(tempo - 150 - 2*128 - drumdelay);

    TMR2_Stop();
    TMR2_PeriodCountSet(o3[10]); //A
    TMR2_Start();

    TMR4_Stop();
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start(); 

    playHH();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(drumdelay);
    playLDrum();
    __delay_ms(drumdelay);

    playHH();
    __delay_ms(33);
    fastHH();
    __delay_ms(33);
    fastLH();
    __delay_ms(20);
    fastLH();
    __delay_ms(drumdelay);
    playHH();
    __delay_ms(33);
    fastHH();
    __delay_ms(33);
    fastHH();
    __delay_ms(33);
    fastHH();
    //end verse 4
    TMR4_Stop();
    TMR2_Stop();
    __delay_ms(100);
}


void playTheme2Part1(void){

    // B, C, C#, D, D#, E, F, F#, G, G#, A, A#
    // 0  1  2   3  4   5  6  7   8  9   10 11
    size_t o1[] = {252,238,224,212,200,189,178,168,158,149,141,133};
    size_t o2[] = {126,118,112,105,99,94,88,83,79,74,70,66};
    size_t o3[] = {62,58,56,52,49,46,44,41,39,37,35,33};

    const int tempo = 300;
    const int drumdelay = 42;
    TMR6_Stop();
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();    
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    
    __delay_ms(tempo-20);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();    
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();    
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    TMR6_Stop();  
    __delay_ms(20);
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    
    __delay_ms(tempo/2);

    TMR6_Stop();  

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    
    __delay_ms(tempo);
        
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();
    
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();
    
    __delay_ms(20);
    
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();
    TMR6_Stop();  
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
    
    
    __delay_ms(tempo-20);
    
            
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[8]); //G
    TMR4_Start();
    TMR6_Stop();  
    __delay_ms(20);
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
    
    __delay_ms(tempo);

    TMR6_Stop();
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    TMR6_Stop();
    __delay_ms(20);
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo);
    
    TMR6_Stop();
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
    
    
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[4]); //D#
    TMR6_Start();
    
    __delay_ms(tempo);
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[4]); //D#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[2]); //C#
    TMR6_Start();
    
    
    __delay_ms(tempo-20);
    TMR2_Stop();
    TMR4_Stop();
    TMR6_Stop();        


}

void playTheme2Part2(void){

    // B, C, C#, D, D#, E, F, F#, G, G#, A, A#
    // 0  1  2   3  4   5  6  7   8  9   10 11
    size_t o1[] = {252,238,224,212,200,189,178,168,158,149,141,133};
    size_t o2[] = {126,118,112,105,99,94,88,83,79,74,70,66};
    size_t o3[] = {62,58,56,52,49,46,44,41,39,37,35,33};

    const int tempo = 300;
    const int drumdelay = 42;
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    
    __delay_ms(tempo-10);
    
    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop(); 
    __delay_ms(10);
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    
    TMR6_Stop();
    __delay_ms(20);
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo/2);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    
    __delay_ms(tempo/2);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    TMR6_Stop();
    
    __delay_ms(tempo);    
    
    
        
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();

    __delay_ms(tempo-10);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();  
    __delay_ms(10);
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
    
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[8]); //G
    TMR4_Start();
    TMR6_Stop();
    __delay_ms(20);
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
    
    __delay_ms(tempo);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    TMR6_Stop();
    __delay_ms(tempo);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();

    __delay_ms(tempo-20);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    TMR4_Stop(); 
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();

    __delay_ms(tempo-20);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    TMR6_Stop();
    __delay_ms(20);
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    __delay_ms(tempo/2);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    TMR6_Stop();
    
    __delay_ms(tempo/2);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    __delay_ms(tempo/2);    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o1[4]); //D#
    TMR6_Start();
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o1[2]); //C#
    TMR6_Start();
    __delay_ms(tempo/2);
    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[2]); //C#
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o1[1]); //C
    TMR6_Start();
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    
    TMR6_Stop();
    TMR6_PeriodCountSet(o1[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo*2-20);
    TMR2_Stop();
    TMR4_Stop();
    TMR6_Stop();

    
}

void playTheme2Part3(void){

    // B, C, C#, D, D#, E, F, F#, G, G#, A, A#
    // 0  1  2   3  4   5  6  7   8  9   10 11
    size_t o1[] = {252,238,224,212,200,189,178,168,158,149,141,133};
    size_t o2[] = {126,118,112,105,99,94,88,83,79,74,70,66};
    size_t o3[] = {62,58,56,52,49,46,44,41,39,37,35,33};

    const int tempo = 300;
    const int drumdelay = 42;
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
   
    __delay_ms(tempo);    
    __delay_ms(tempo);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo-20);
    TMR4_Stop();   
    
    __delay_ms(20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();

    

    
    
    __delay_ms(tempo);
    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[4]); //D#
    TMR6_Start();
    
    __delay_ms(tempo*2);
    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();   
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start();
    
    __delay_ms(tempo/2);

    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[11]); //A#
    TMR6_Start();

    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    TMR4_Stop();        
    TMR4_PeriodCountSet(o1[1]); //C
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();    
    __delay_ms(tempo);    
    __delay_ms(tempo/2);
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[4]); //D#
    TMR6_Start();

    __delay_ms(tempo/2);    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    
    __delay_ms(tempo-20);
    TMR4_Stop();       
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[1]); //C
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();
    
    
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start(); 
    
    __delay_ms(tempo);

    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[8]); //G ..
    TMR6_Start();    
    
    __delay_ms(tempo/2-20);

    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    
    __delay_ms(tempo/2);
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[4]); //D#
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[4]); //D#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[2]); //C#
    TMR4_Start();

    
    __delay_ms(tempo/2);
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[1]); //C
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();
    
    __delay_ms(tempo/2);
    TMR2_Stop();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();    
    __delay_ms(tempo/2);       
    TMR6_Stop();        

}


void playTheme2(void){
    // Note to Period Values
    // B, C, C#, D, D#, E, F, F#, G, G#, A, A#
    // 0  1  2   3  4   5  6  7   8  9   10 11
    size_t o1[] = {252,238,224,212,200,189,178,168,158,149,141,133};
    size_t o2[] = {126,118,112,105,99,94,88,83,79,74,70,66};
    size_t o3[] = {62,58,56,52,49,46,44,41,39,37,35,33};

    const int tempo = 300;

    //verse 1
    playTheme2Part1();
    __delay_ms(20);
    
    //verse 2
    playTheme2Part2();
    __delay_ms(20);
    
    playTheme2Part1();
    __delay_ms(20);
    //verse 2
    playTheme2Part2();
    __delay_ms(20);    
    
    //verse 3
    playTheme2Part3();


    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo*2-20);
        

    TMR2_Stop();
    __delay_ms(20);
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();    

    __delay_ms(tempo/2);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[2]); //C#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o2[4]); //D#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[4]); //D#
    TMR6_Start();
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();

    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[4]); //D#.
    TMR2_Start();
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o2[4]); //D#
    TMR4_Start();
    
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[6]); //F.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[6]); //F
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o2[4]); //D#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();
    __delay_ms(tempo/2);
    TMR6_Stop();        
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();    
    __delay_ms(tempo/2);
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[4]); //D#
    TMR6_Start();    
    __delay_ms(tempo/2);
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o2[2]); //C#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start();
    __delay_ms(tempo/2);

    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();    
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms((tempo/2) - 20);
    TMR2_Stop(); 
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o2[2]); //C#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[11]); //A#
    TMR6_Start();
    
    __delay_ms(tempo/2);

    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[1]); //C
    TMR6_Start();
    
    
    __delay_ms(tempo/2-20);
    

    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[11]); //A#
    TMR6_Start();
    
    __delay_ms(tempo/2);
        
    playTheme2Part3();
    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();

    TMR6_Stop();        
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo*2 - 20);
    
    TMR2_Stop();   
    TMR6_Stop();
    __delay_ms(20);
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();    
    
    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[2]); //C#.
    TMR2_Start();
    
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[8]); //G
    TMR4_Start();
    
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[9]); //G#
    TMR6_Start();    
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[11]); //A#
    TMR6_Start();    
    __delay_ms(tempo/2-20);
    
    TMR2_Stop();
    __delay_ms(20);
    TMR2_PeriodCountSet(o3[2]); //C#.
    TMR2_Start();
    
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo/2-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[4]); //D#.
    TMR2_Start();
    TMR4_Stop();
    __delay_ms(20);
    TMR4_PeriodCountSet(o1[8]); //G
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[2]); //C#.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[2]); //C#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo/2-20);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o1[11]); //A#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[2]); //C#
    TMR6_Start();
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();    
    TMR4_Stop();
    TMR4_PeriodCountSet(o2[1]); //C
    TMR4_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();
    
    __delay_ms(tempo*2);
            
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[11]); //A#
    TMR4_Start();

    __delay_ms(tempo);    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[2]); //C#.
    TMR2_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[8]); //G
    TMR6_Start(); 
    
    __delay_ms(tempo/2);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o3[1]); //C.
    TMR2_Start();
    TMR6_Stop();
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();    
    
    __delay_ms(tempo/2-20);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[11]); //A#.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[9]); //G#
    TMR4_Start();  
    TMR6_Stop();
    __delay_ms(20);
    TMR6_PeriodCountSet(o2[6]); //F
    TMR6_Start();    

    __delay_ms(tempo);

    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[9]); //G#.
    TMR2_Start();
    TMR6_Stop();    
    TMR6_PeriodCountSet(o2[5]); //E
    TMR6_Start();    

    __delay_ms(tempo/2);

    TMR6_Stop();    
    TMR6_PeriodCountSet(o2[3]); //D
    TMR6_Start();  
    
    __delay_ms(tempo/2);    
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[8]); //G.
    TMR2_Start();
    TMR4_Stop();
    TMR4_PeriodCountSet(o1[8]); //G
    TMR4_Start();
    TMR6_Stop();    
    TMR6_PeriodCountSet(o2[5]); //E
    TMR6_Start();    

    __delay_ms(tempo);
    
    TMR2_Stop();        
    TMR2_PeriodCountSet(o2[5]); //E.
    TMR2_Start();

    __delay_ms(tempo);
}

i2c_host_interface_t I2C;

uint16_t SLAVE_ADDR = 0x68;
uint8_t SECONDS_REG = 0x00;
uint8_t MINUTES_REG = 0x01;
uint8_t HOURS_REG = 0x02;

uint8_t BCDToDecimal(uint8_t bcd) {
    return ((bcd / 16 * 10) + (bcd % 16));
}

void RTC_ReadTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
    uint8_t rtcData[3];
    if (I2C.WriteRead(SLAVE_ADDR, &SECONDS_REG, 1, rtcData, 3)) {
        *seconds = BCDToDecimal(rtcData[0]);
        *minutes = BCDToDecimal(rtcData[1]);
        *hours   = BCDToDecimal(rtcData[2]);
    }
}


void main(void) {
    // Initialize PWM, I/O pins, and I2C modules
    SYSTEM_Initialize();
 
    //interrupt settings
    PIE0bits.IOCIE = 1; //enable I/O change interrupt flag
    PIR0bits.IOCIF = 0; //clearing I/O change interrupt flag program starts
    PIR0bits.INTF = 0; //clearing interrupt flag before program starts
    
    playTheme2();    
    playTheme1();

    /*
    while(1){
        uint8_t hours;
        uint8_t minutes;
        uint8_t seconds;
        RTC_ReadTime(&hours,&minutes,&seconds);
        if(seconds == 0){
            TMR4_Stop();
            TMR4_PeriodCountSet(127);
            TMR4_Start();
            __delay_ms(50);
            TMR4_Stop();
        }
        __delay_ms(50);
    }    
      */
}




//interrupt service routine
void __interrupt() ISR(){
    if(PIR0bits.IOCIF){
        if(IOCAPbits.IOCAP0){ //change to DM Mode
            PIR0bits.IOCIF = 0;
        }
        if(IOCAPbits.IOCAP1){ //change to Clock Mode (Alarm Off)
            PIR0bits.IOCIF = 0;
        }
        if(IOCAPbits.IOCAP2){ //change to Clock Mode (Alarm On)
            PIR0bits.IOCIF = 0;
        }
        
        if(PORTAbits.RA0 == 1){ //in DM Mode
             
            if(PORTCbits.RC4 == 1 && PORTCbits.RC6 == 1){ //both time and alarm are held down
                playTheme1();

                if(IOCBPbits.IOCBP5){ //
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //
                    PIR0bits.IOCIF = 0;
                }
            }
            if(PORTCbits.RC4 == 1){ //time button held down
                if(IOCBPbits.IOCBP5){ //increment worldline index
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //toggle time leap animation
                    PIR0bits.IOCIF = 0;
                }
            }
            if(PORTCbits.RC6 == 1){ //alarm button held down
                if(IOCBPbits.IOCBP5){ //cycle song track left
                    //future development: play a sample of the song while the alarm button is held down, stopping when letting go of the button
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //cycle song track right
                    //future development: play a sample of the song while the alarm button is held down, stopping when letting go of the button
                    PIR0bits.IOCIF = 0;
                }
            }
            
            if(IOCBPbits.IOCBP5){ //toggle song track
                PIR0bits.IOCIF = 0;
            }
            if(IOCBPbits.IOCBP7){ //toggle song track
                PIR0bits.IOCIF = 0;
            }
        }
        
        if(PORTAbits.RA1 == 1 || PORTAbits.RA2 == 1){//in Clock Mode 
            if(PORTCbits.RC4 == 1 && PORTCbits.RC6 == 1){
                if(IOCBPbits.IOCBP5){ //reset alarm to 12:00 (midnight)
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //increment song index that plays when alarm goes off?
                    PIR0bits.IOCIF = 0;
                    //future development: play a sample of the song while the alarm button is held down, stopping when letting go of the button
                }
            }
            if(PORTCbits.RC4 == 1){ //time button held down
                if(IOCBPbits.IOCBP5){ //increment minutes
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //increment hours
                    PIR0bits.IOCIF = 0;
                }
            }
            if(PORTCbits.RC6 == 1){ //alarm button held down
                if(IOCBPbits.IOCBP5){ //increment minutes
                    PIR0bits.IOCIF = 0;
                }
                if(IOCBPbits.IOCBP7){ //increment hours
                    PIR0bits.IOCIF = 0;
                }
            }
            
            if(IOCBPbits.IOCBP5){ //add feature here, only minutes button pressed
                PIR0bits.IOCIF = 0;
            }
            if(IOCBPbits.IOCBP7){ //add feature here, only hours button pressed
                PIR0bits.IOCIF = 0;
            }
        }   
    }
    //exit interrupt and set INT flag back to 0 to allow for additional interrupts
    //PIR0bits.INTF = 0;
    PIR0bits.IOCIF = 0;
}