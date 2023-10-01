#include <stdio.h>

// Global stuff
unsigned short msCount = 0;
unsigned short	setAlarmFlag = 0;
unsigned short	timerflag = 0;
int set = 0;
int option;

const char dispData[10][8] = {{0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF},
                              {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
                              {0xFF,0x01,0x01,0XFF,0X80,0X80,0X80,0XFF},
                              {0XFF,0x01,0x01,0xFF,0x01,0x01,0x01,0xFF},
                              {0X81,0x81,0x81,0xFF,0x01,0x01,0x01,0x01},
                              {0XFF,0x80,0x80,0xFF,0x01,0x01,0x01,0xFF},
                              {0XFF,0x80,0x80,0xFF,0x81,0x81,0x81,0xFF},
                              {0XFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
                              {0XFF,0x81,0x81,0xFF,0x81,0x81,0x81,0xFF},
                              {0XFF,0x81,0x81,0xFF,0x01,0x01,0x01,0xFF},
};

typedef struct{
	unsigned short sec:6;
	unsigned short min:6;
	unsigned short hr:4;
} timeRecord;

#define MAXMS0 500
#define MAXMS  500
#define MAMSCOUNT 1000
#define MAXSEC 59
#define MAXMIN 59
#define MAXHR 12

timeRecord currTime,setAlarm;

int getkey(){
	int temp,num;
	temp=num=0;
	do
	{
	   temp=getchar();
	   if ((temp >='0') && (temp <='9') )
	   {
	     num=(num*10)+ (temp-'0');
	   }
	   else if(temp != '\n')
		 num=temp;
	}while(temp != '\n');
	return num;

}

 void getoption(){
	printf("Select one of the following option:\n") ;
	printf("-> Press 1 to set time \n");
	printf("-> Press 2 to Start \n");
    scanf("%d", &set);
}

void delayms(){
	int i,j;
	int data=0;

	for(i=0;i<MAXMS ; i++)
	{
		for(j=0;j<MAXMS0 ; j++)
		{
			data++;
		}
	}
	msCount++;
}

void setAlarmTime()
{
        	option = -1;
        	do{
        		printf("Enter 0-12 for HH:\n");
        		scanf("%d", &option);
        	}
        	while(!(option <= 12 && option >=0));
        	setAlarm.hr = option;

        	do{
				 printf("Enter 0-59 for MM:\n") ;
				 scanf("%d", &option);
        	}
        	while(!(option <= 59 && option >=0));
        	setAlarm.min = option;

        	do{
				 printf("Enter 0-59 for SS:\n") ;
				 scanf("%d", &option);
        	}
        	while(!(option <= 59 && option >=0));
        	setAlarm.sec = option;
        	
        	setAlarmFlag = 1;
}

void number_printer(int num, int row, int col){
    int mask;
   int  x = row;
   int y = col;
        for(int j = 0; j < 8; j++){
        mask = 0x80;
        printf("\e[%d;%dH",x++,y);
            for(int k = 0; k < 8; k++){
                if(dispData[num][j] & mask)
    		     printf("*");
    	        else
    		     printf(" ");
    		    mask = mask >> 1;
            }
            printf("\n");
        }

}

void starDisplay(int num, int row, int col){
        number_printer(num/10,row,col);
        number_printer(num%10,row,col+10);
}

void processTime(){
   delayms();
   if(msCount > MAMSCOUNT)
   {
	   msCount=0;
	   currTime.sec++;
	   printf("\e[1;1H\e[2J");
	   starDisplay(currTime.sec, 5, 70);
	   starDisplay(currTime.min, 5, 50);
	   starDisplay(currTime.hr, 5, 30);
	   if(currTime.sec > MAXSEC)
	   {
		   currTime.sec =0;
		   currTime.min++;
		  // starDisplay(currTime.min, 5, 40);
		   if (currTime.min > MAXMIN)
		   {
			   currTime.min=0;
			   currTime.hr ++;
			//   starDisplay(currTime.hr, 5, 20);
			   if (currTime.hr > MAXHR)
				   currTime.hr = 0;
		   }
	   }
   }

}

void processState(){
    
    while(!(set == 1 || set == 2 || timerflag == 1)){
        getoption();
    }
    
    if(set == 1){
       setAlarmTime();  
       set = 0;
    }
    
    	if(set == 2 && setAlarmFlag == 1){
	     printf("%d:%d:%d is being the time set \n",setAlarm.hr,setAlarm.min,setAlarm.sec);
	     timerflag = 1;
	     while(timerflag == 1){
	         
	     processTime();
	     if( (currTime.hr==setAlarm.hr) && (currTime.min==setAlarm.min) && (currTime.sec == setAlarm.sec))
	     {
		   printf("Timer is up \n");
		   setAlarmFlag = 0;
		   set = 0;
		   timerflag = 0;
		   currTime.hr = 0;
		   currTime.min = 0;
		   currTime.sec = 0;
	     }
	     
	     } 
	    
	} else {
	         getoption();
	     }
}


int main(){
    
    while(1){
       processState(); 
    }
	return 0;

}

