/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdint.h>

int parity_bits[4]={1,2,4,8};
int parity_bits_value[4]={0}; //1011001
int _8bit_[8];
int data_bits[]={10,0,0,1,0,1,0,0,0,0,1,0,0};
int err_count, index;
int pw1=0, pw2=0;
uint8_t _parity1_ = 0b0010;
uint8_t _parity2_ = 0b0100;
uint8_t _parity3_ = 0b1000;
int sent_bits, check_bits;
int i;
int _8bit_input_number;

int main()
{
    SenderEnd();
    ErrorInduce();
    ReceiveEnd();
    ErrorDetect();
    
    return 0;
}
void SenderEnd(void)
{
    printf("Enter the 8-bit number\n"); //11000100
    scanf("%d", &_8bit_input_number);
    while(_8bit_input_number != 0)
    {
        _8bit_[7-i] = _8bit_input_number%2;
        _8bit_input_number = _8bit_input_number/2;
        i+=1;
    }
    
    _8bit_[0] = 0;
    data_bits[3]=_8bit_[0];
    data_bits[5]=_8bit_[1];
    data_bits[6]=_8bit_[2];
    data_bits[7]=_8bit_[3];
    data_bits[9]=_8bit_[4];
    data_bits[10]=_8bit_[5];
    data_bits[11]=_8bit_[6];
    data_bits[12]=_8bit_[7];
    
    
    for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=2)
    {
       parity_bits_value[0] += data_bits[i];
    }
    parity_bits_value[0] %= 2;
    data_bits[parity_bits[0]] = (parity_bits_value[0]);
    printf("Parity 0: %d\n",data_bits[parity_bits[0]]);

    for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=1)
    {
       if(_parity1_ & i)
       {
            parity_bits_value[1] += data_bits[i];
       }
    }
    parity_bits_value[1] %= 2;
    data_bits[parity_bits[1]] = (parity_bits_value[1]);
    printf("Parity 1: %d\n",parity_bits_value[1]); //_parity2_
    
    for(i=1;i<(sizeof(data_bits)/sizeof(int))-1;i+=1)
    {
       if(_parity2_ & i)
       {
            parity_bits_value[2] += data_bits[i];
       }
    }
    parity_bits_value[2] %= 2;
    data_bits[parity_bits[2]] = (parity_bits_value[2]);
    printf("Parity 2: %d\n",parity_bits_value[2]);
    
    for(i=1;i<(sizeof(data_bits)/sizeof(int))-1;i+=1)
    {
       if(_parity3_ & i)
       {
            parity_bits_value[3] += data_bits[i];
       }
    }
    parity_bits_value[3] %= 2;
    data_bits[parity_bits[3]] = (parity_bits_value[3]);
    printf("Parity 3: %d\n",parity_bits_value[3]);

    sent_bits = (parity_bits_value[3]*8) + (parity_bits_value[2]*4) + (parity_bits_value[1]*2) + (parity_bits_value[0]*1);
    
    printf("Parity Sum: %d\n", sent_bits);
    
    printf("Sent:[");
    for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=1)
    {
       printf("%d ", data_bits[i]);
       data_bits[0]+=data_bits[i];
    }
    printf("]");
    data_bits[0] %= 2;
    pw1 = data_bits[0];
    printf("\nSent pW = %d\n", pw1);
}   
    
void ErrorInduce(void)
{


        printf("Enter the number of error bits\n");
        scanf("%d",&err_count);

   
    for(i=0;i<err_count;i+=1)
    {
        printf("Enter the index value\n");
        scanf("%d",&index);
        data_bits[index]^=1;
    }
}

void ReceiveEnd(void)
{
    for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=1)
    {
      pw2+=data_bits[i];
    }
    
    pw2 %= 2;
    printf("\nReceived pW = %d\n", pw2);
    
    for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=2)
    {
       parity_bits_value[0] += data_bits[i];
    }
    parity_bits_value[0] %= 2;
    //data_bits[parity_bits[0]] = (parity_bits_value[0]);
    printf("Received Parity 0: %d\n",data_bits[parity_bits[0]]);

    for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=1)
    {
       if(_parity1_ & i)
       {
            parity_bits_value[1] += data_bits[i];
       }
    }
    parity_bits_value[1] %= 2;
    //data_bits[parity_bits[1]] = (parity_bits_value[1]);
    printf("Received Parity 1: %d\n",parity_bits_value[1]); //_parity2_
    
    for(i=1;i<(sizeof(data_bits)/sizeof(int))-1;i+=1)
    {
       if(_parity2_ & i)
       {
            parity_bits_value[2] += data_bits[i];
       }
    }
    parity_bits_value[2] %= 2;
    //data_bits[parity_bits[2]] = (parity_bits_value[2]);
    printf("Received Parity 2: %d\n",parity_bits_value[2]);
    
    for(i=1;i<(sizeof(data_bits)/sizeof(int))-1;i+=1)
    {
       if(_parity3_ & i)
       {
            parity_bits_value[3] += data_bits[i];
       }
    }
    parity_bits_value[3] %= 2;
    //data_bits[parity_bits[3]] = (parity_bits_value[3]);
    printf("Received Parity 3: %d\n",parity_bits_value[3]);

}

void ErrorDetect(void)
{
    check_bits = (parity_bits_value[3]*8) + (parity_bits_value[2]*4) + (parity_bits_value[1]*2) + (parity_bits_value[0]*1);
    printf("Parity Sum: %d\n", check_bits); 
    if(check_bits == sent_bits && pw1 != pw2)
       printf("PW Word error\n");
    else if(check_bits == sent_bits && pw1 == pw2)
        printf("No error in transmission\n");
    else if((check_bits^sent_bits) == 0 && pw1 != pw2)
    {
        printf("Error in bit 12 \n");
        data_bits[12]^=1;
        printf("Corrected value:[ ");
        
        for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=1)
        {
            printf("%d ", data_bits[i]);
        }
        printf("]");
    }
        
    else if(check_bits^sent_bits != 0 && pw1 != pw2)
    {
        printf("Error in bit %d \n", sent_bits^check_bits);
        data_bits[(sent_bits^check_bits)]^=1;
        printf("Corrected value:[ ");
       
        for(i=1;i<(sizeof(data_bits)/sizeof(int));i+=1)
        {
            printf("%d ", data_bits[i]);
        }
        printf(" ]");
    }
    else if(check_bits != sent_bits && pw1 == pw2)
       printf("MBE detected. Cannot be corrected\n");
   
}    

