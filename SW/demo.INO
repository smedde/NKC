/*
 *  Arduino Mega am NKC bus mit GDP64, ROA und SOUND
 *  
 */

int LA, RD_, WR_, IORQ_, MREQ_, BANKEN;

void setup() {
 
  //NKC 8-bit data bus, Port A[0..7]
  DDRA=0x00 ;     // Arduino pin numbers 22..29, NKC D0..D7
  //PORTA = 0x0;  // internal pull-ups
 
  //NKC 20-bit address bus, Port F[0..7] & K[0..7] & B[0..3] output
  DDRF=0xFF ;     // Arduino pin numbers A0...A7,  NKC A0..A7
  DDRK=0xFF ;     // Arduino pin numbers A8...A15, NKC A8..A15
  DDRB=0xFF ;     // Arduino pin numbers 50...53,  NKC A16..A19
  
  //NKC div. bus signals, Port C, output
  DDRC=0xFF ;     // Arduino pin numbers 30..37
   
  //NKC RD signal, Port L, output
  DDRL=0xFF ;     // Arduino pin numbers 42..49
  
  Serial.begin(19200); 
  while (!Serial) {}
  Serial.println(""); Serial.flush();
   
  LA = 31;      //Arduino pin 31, clk for Logic Analyzer
  WR_ = 33;     //Arduino pin 33, grey
  IORQ_ = 34;   //Arduino pin 34, black
  MREQ_ = 35;   //Arduino pin 35, white
  BANKEN = 36;  //Arduino pin 36, grey
  RD_ = 42;     //Arduino pin 42, purple
  
  //configure Arduino ports
  pinMode(LA, OUTPUT);  
  pinMode(RD_, OUTPUT);  
  pinMode(WR_, OUTPUT);  
  pinMode(IORQ_, OUTPUT);  
  pinMode(MREQ_, OUTPUT);  
  pinMode(BANKEN, OUTPUT);  
  
  //init bus signals
  digitalWrite(LA, LOW);
  digitalWrite(RD_, LOW); 
  digitalWrite(WR_, HIGH);
  digitalWrite(IORQ_, HIGH); 
  digitalWrite(MREQ_, HIGH);
  digitalWrite(BANKEN, LOW);
}

void print0() {GDP_CMD(0x70, 0x01); GDP_CMD(0x70, 0b10100000); }
void print1() {GDP_CMD(0x70, 0x00); GDP_CMD(0x70, 0b10100000); }

void loop() {

   int a=6;
   int b=3;

   //ROA
   readHexdump(0x0000, 0x2000);
   
    /*//Compare EEPROM and EPROM
    int count = 0;
    int error = 0;
    for (int adr=0x0000; adr < 0x1FFF; adr++) {
       if (readAddress(adr) != readAddress(adr + 0x8000)) {
         error++;
       }
       count++;
    }
    Serial.print("Count: "); Serial.println(count, HEX);
    Serial.print("Error: "); Serial.println(error);*/

  for (int i=0; i<10; i++) {
    Sound(random(100, 200), 50);
  }
    
    //GDP
    initGDP();
    GDP_CLS();
    GDP_PAGE(0, 0); 
    GDP_MOVETO(200, 130);
    GDP_CSIZE(2, 1);
    
    String myString = "1984";
    GDP_TEXT(myString);
    
    GDP_TEXT(200, 140, "2018");

    GDP_MOVETO(0, 0); GDP_DRAWTO(511, 255);
  
    GDP_MOVETO(200, 128); GDP_FASTREC(50, 25);
   
    for (int i=0; i<100; i++) {
      GDP_MOVETO(random(10, 170), random(150, 230));
      GDP_DRAWTO(random(10, 170), random(150, 230));
    }

   GDP_STRICH(0);
   GDP_MOVETO(130, 50); GDP_DRAWTO(500, 50);
   GDP_MOVETO(450, 60); GDP_DRAWTO(450, 200);
   
   GDP_STRICH(1);
   GDP_MOVETO(130, 40); GDP_DRAWTO(500, 40);
   GDP_MOVETO(460, 60); GDP_DRAWTO(460, 200);
  
   GDP_STRICH(2);
   GDP_MOVETO(130, 30); GDP_DRAWTO(500, 30);
   GDP_MOVETO(470, 60); GDP_DRAWTO(470, 200);
  
   GDP_STRICH(3);
   GDP_MOVETO(130, 20); GDP_DRAWTO(500, 20);
   GDP_MOVETO(480, 60); GDP_DRAWTO(480, 200);

   delay(2000);
   
   Beep();
   GDP_CSIZE(a, b);
   GDP_PAGE(0, 0);
   GDP_TEXT(200, 180, "NKC");
   Beep(); delay(1000);
   
   GDP_PAGE(1, 1);
   GDP_TEXT(50, 100, "Hello");
   Beep(); 
   delay(500);

   GDP_PAGE(2, 2);
   GDP_TEXT(270, 100, "World");
   Beep(); delay(500);

   for (int i=0; i<3; i++) {
      GDP_PAGE(1, 1);
      Beep(); delay(500);
      GDP_PAGE(2, 2);
      Beep(); delay(500);
   }
   GDP_PAGE(0, 0);

   for (int i=0; i<500; i++) {
     int rnd = random(0, 5);
     if (rnd == 1) a++;if (rnd == 2) a--;if (rnd == 3) b++;if (rnd == 4) b--;
     if (a == 0) a=1;if (b == 0) b=1;if (a == 11) a=10;if (b == 11) b=10;

     GDP_CSIZE(a, b);
     GDP_TEXT(300, 80, "NKC");
     GDP_SYNC();
     GDP_CMD(0x70, 0x01); //loeschen
     GDP_TEXT(300, 80, "NKC");
   }
}
