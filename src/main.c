#include <p24Fxxxx.h>

void init_adcs(void)
{
        // Configure ports for analog input
        ANSA = 0;
        ANSB = 0xFFFF;

        AD1CON1 = 0x0070;
        AD1CON2 = 0x0800;
        AD1CON3 = 0x1F01;

        AD1CON1bits.ADON = 1;       // Enable
}

int main(void)
{
        unsigned long int adval;
        init_adcs();

        while(1) {
                AD1CHSbits.CH0SA = 14;
                AD1CON1bits.SAMP = 1;
                while(!AD1CON1bits.DONE);
                adval = *((&ADC1BUF0) + 14);
                adval = ((3300L*adval)/4096L);
                //adval = 3*((4096L/adval)*3.3);
                __builtin_nop();
        }       
        return 0;
}
