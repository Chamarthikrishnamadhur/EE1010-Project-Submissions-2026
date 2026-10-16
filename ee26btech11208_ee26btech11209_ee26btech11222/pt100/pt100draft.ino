#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
double a=182.886793;
double b=-666.900992;
double c=567.135426;
double temper(double v){
  return ((a*v*v)+b*v+c);
}
void setup(){
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Pt100 sys");
}
void loop(){
  double vout=analogRead(A0)*(5.0/1024);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Temp ");
  lcd.print(temper(vout));
  delay(2000);
}