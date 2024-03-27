#include "encoder.h"

int currentRad = 0;



void key1_interupt_routine(void)
{
		currentRad = 0U;
}

    
uint8_t encoder_read_position(void){
    //if(!ENCODER_READ_Z){currentRad = 0;}
    static uint8_t state = 0;
    static uint8_t lastState = 0;
//    if(currentRad > ENCODER_RESOLUTION || currentRad <(-ENCODER_RESOLUTION)){
//        currentRad = 0;
//    }  
    
    //A->B: 00-10-01-00
    //B->A: 00-01-10-00    
    switch(state){
        case 0:{
            if(ENCODER_READ_A && ENCODER_READ_B && lastState != 0){
                currentRad = currentRad + (lastState == 1?(-1):(1));
                lastState = 0;
            }
            if(!ENCODER_READ_A){state = 1U;}
            if(!ENCODER_READ_B){state = 2U;}
            break;
        }
        case 1:{
            if(ENCODER_READ_A && ENCODER_READ_B){state = 0;}
            if(ENCODER_READ_A && (!ENCODER_READ_B)){
                lastState = state; 
                state = 2U;
            }
            break;
        }
        case 2:{
            if(ENCODER_READ_A && ENCODER_READ_B){state = 0;}
            if((!ENCODER_READ_A) && ENCODER_READ_B){
                lastState = state; 
                state = 1U;
            }
            break;
        }
        default: state = 0;
    }                
    return 0;
}
   
