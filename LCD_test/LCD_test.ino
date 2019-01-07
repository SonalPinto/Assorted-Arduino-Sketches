/*
  LCD test
  
 */
 
 #include <LiquidCrystal.h>
 
// LCD Shield mapping
// 4-bit mode : D4-7
// int LCD_RS = 8;
// int LCD_E = 9
// int LCD_D[4] = {10,11,12,13};

// Create LCD object
LiquidCrystal lcd(8,9,10,11,12,13);
char str[]= "Hello World!";
int x = 0;


void setup() {
  lcd.begin(16,2); // auto clear at begin. Cursor at 0,0
  
  lcd.print(str);
  //lcd.setCursor(9,1);
  //lcd.print("-spinto");
  delay(1000);
}


void loop() {
  
  lcd.clear();
  delay(100);
  
  lcd.setCursor(x,0);
  if(x<=4){  // 16-12 = 4 length required on screen for a rightmost full display 
    lcd.print(str);
  } else {
    int tx=x;
    for(int i=0;i<12;i++) {
      lcd.write(str[i]);
      tx++;
      tx%=16;
      lcd.setCursor(tx,0);
    }
  }
  x++;
  x%=16;
  delay(600);
}
