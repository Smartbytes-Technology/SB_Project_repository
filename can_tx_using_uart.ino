#include<SPI.h>
#include<mcp2515.h>

const  unsigned int MAX_MESSAGE_LENGTH =12;

struct can_frame canMsg1;

uint32_t num;
int can_data[8];

char temp;
char Startbit;
int i,j;
int ipdata[8];

char flag_CAN;

MCP2515 mcp2515(10);

void setup()
{
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x8E;
  canMsg1.data[1] = 0x87;
  canMsg1.data[2] = 0x32;
  canMsg1.data[3] = 0xFA;
  canMsg1.data[4] = 0x26;
  canMsg1.data[5] = 0x8E;
  canMsg1.data[6] = 0xBE;
  canMsg1.data[7] = 0x86;
  
  
  
  while (!Serial);
  Serial.begin(9600);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");

}



void loop()
{
  mcp2515.sendMessage(&canMsg1);
  delay(1000);
    while(Serial.available()>0)
    {
      flag_CAN=Serial.read();
      Serial.println(flag_CAN);
      switch(flag_CAN)
      {
  
      case '$':
      {
        
        read_string();
        delay(3000);
         mcp2515.sendMessage(&canMsg1);
         delay(1000);
         break;
      }
      case '&':
      {
        
        c_data();
        delay(3000);
        mcp2515.sendMessage(&canMsg1);
        delay(1000);
        break;
      }
      }
      Serial.println("breaked");
    }
   mcp2515.sendMessage(&canMsg1);
   delay(1000);
}


char read_string()
{
  Serial.println("Enter the Can_id");
  delay(8000);
  while(Serial.available()>0)
  {
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

        char inByte = Serial.read();  
      if(inByte !='\n'&&(message_pos<MAX_MESSAGE_LENGTH-1))
        {
          message[message_pos] = inByte;
          message_pos++;
        }
      else
        {
          message[message_pos]='\0';
          //Serial.println(message);
          // canMsg.can_id=message;
          num = atoi(message);
          // canMsg1.can_id=num;
          message_pos=0;
        }
      }
      canMsg1.can_id=num;
      Serial.print(num);
      
 }


int c_data()
{
  Serial.println("Enter the Payload Values");
  delay(5000);
  
       while(Serial.available()>0)
  {
    temp = Serial.read();
    delay(1000);
    Serial.println(temp);
    while(temp=='*'&&temp!='#')
    {
      while( i!=8)
      {
      while(Serial.available()==0)
      {
        
      }
      can_data[i]=Serial.parseInt();
      Serial.println(can_data[i]);
      delay(2000);
      i++;
      }
      
      while(j!=8)
      {
       Serial.print("the entered payload values are: ");
       Serial.println(can_data[j]);
       delay(2000);
      canMsg1.data[j]=can_data[j];
       j++; 
      }
      delay(1000);
      mcp2515.sendMessage(&canMsg1);
      while(Serial.available()==0)
      {
        
      }
      temp=Serial.read();
      j=0;
      i=0;
      
    }
    
    // mcp2515.sendMessage(&canMsg1);
     
}

} 
