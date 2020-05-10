
#include "config.h"

boolean newData = false;
uint8_t curkey = 0;
int cycles = 0;

extern "C" {
  #define SYSTEM_CALL -100
  //uint16_t getpc();
  //uint8_t getop();
  void m6809_init();
  int m6809_execute();
  void m6809_dumpregs();
  bool memory_init();
  int m6809_system(void);
  tt_u16 rpc;
  void memprog_init(const unsigned char *mem, int len);
 // void exec6502(int32_t tickcount);
 // void reset6502();
  void serout(tt_u8 val) {
    Serial.write(val & 0xff);
  } 

uint8_t getkey() {
  curkey = 0;
      if (Serial.available() > 0) {
        curkey = Serial.read();
        newData = true;
    }
    return(curkey);
}
  
  void clearkey() {
    curkey = 0;
  }
  void printhex(uint16_t val) {
    Serial.print(val, HEX);
    Serial.println();
  }
}

//RAM
#define RAM_START   0xF000
#define RAM_END     0xFFFF
byte    RAM[RAM_END-RAM_START+1];
#define WAVE_BANKA_START 0x0000
#define WAVE_BANKA_END   0x7FFF
byte    WAVE_BANKA[WAVE_BANKA_END-WAVE_BANKA_START+1];
#define WAVE_BANKB_START 0x0000
#define WAVE_BANKB_END   0x7FFF
byte    WAVE_BANKB[WAVE_BANKB_END-WAVE_BANKB_START+1];

// ROMs
#define ROM_START   0x8000
#define ROM_END     0xBFFF
byte    ROM[ROM_END-ROM_START+1];

////////////////////////////////////////////////////////////////////
// Example Code
////////////////////////////////////////////////////////////////////
const unsigned char example[] = {
0x8e, 0x00, 0x23, 0x86, 0x01, 0x3f, 0x8e, 0x00, 0x5f, 0xc6, 0x0a, 0x86, 0x02, 0x3f, 0x8e, 0x00, 
0x43, 0x86, 0x01, 0x3f, 0x8e, 0x00, 0x5f, 0x86, 0x01, 0x3f, 0x8e, 0x00, 0x41, 0x86, 0x01, 0x3f, 
0x86, 0x00, 0x3f, 0x45, 0x6e, 0x74, 0x65, 0x72, 0x20, 0x61, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 
0x67, 0x20, 0x28, 0x39, 0x20, 0x63, 0x68, 0x61, 0x72, 0x73, 0x20, 0x6d, 0x61, 0x78, 0x29, 0x3a, 
0x20, 0x0a, 0x00, 0x59, 0x6f, 0x75, 0x72, 0x20, 0x65, 0x6e, 0x74, 0x65, 0x72, 0x65, 0x64, 0x20, 
0x74, 0x68, 0x69, 0x73, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x20, 0x3a, 0x20, 0x00, 0x00
};


void setup() {

  
  Serial.begin (9600);
  Serial.println ();

   
  memprog_init(example, 128);
  delay(100);
  Serial.println("Memory Initialized");
  m6809_init();
  delay(100);
  Serial.println("6809 Initialized");
  Serial.println("Setup Completed"); 

  rpc = 0; // if program starts at 0000;
}

void loop() {
int n, r;

n=0;
r=0;

bool isWaitingForInput = false;
bool weAreDone = false;

if( !weAreDone ) {
    if (isWaitingForInput) 
            getkey();

    switch (r) {
      case 0:
            n = m6809_execute();
            if(n>0) cycles += n;
            break;
      case 1: 
            isWaitingForInput = true;
            weAreDone = true;
            Serial.println("Program Terminated. Close Serial Port. Good bye!");  
            break;
      case 2:
            isWaitingForInput = true;
            break;
      case 3:
            isWaitingForInput = false;
            break;
      default:
            break;
    }
   if (n == SYSTEM_CALL) 
         r = m6809_system();
    if (r == 1) {
            weAreDone = true;
            Serial.println("Program Terminated. Close Serial Port. Good bye!"); 
    }
      /*
        } else if (n < 0) {
                Serial.print("m6809 Run Time Error. ");
                isWaitingForInput = false;
                weAreDone = true;
                Serial.println("You need to close the Serial Port");  
              }}
              */
               
      }

}
