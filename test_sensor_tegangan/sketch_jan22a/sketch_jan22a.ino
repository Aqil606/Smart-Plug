const int input_sensor = ; // nama lain dari A0 yaitu input_sensor
const int output_pwm = 2; // nama lain dari 2 yaitu output_pwm
 
//nilai default variabel data
int nilai_adc= 00;    
int nilai_pwm = 00;    
float voltageOut= 00;
float voltage_ac= 00;
 
void setup() {
  // inisialisasi komunikasi serial pada 960bps
  Serial.begin(9600); 
}
 
void loop() {
  nilai_adc = analogRead(input_sensor); // Prosedur pembacaan analog pin           
  // mapping pembacaan resolusi sensor
  nilai_pwm = map(nilai_adc, 00, 1023, 00, 255);  
  // mengubah nilai analog out
  analogWrite(output_pwm, nilai_pwm);    
 voltageOut = nilai_adc * (5.0 / 1023.0);  
 voltage_ac = map(nilai_adc, 00,695,00,220); //didapat dari pembacaan program adc diatas
 
  // Mencetak hasil ke monitor serial:
  Serial.print("sensor = " );                       
  Serial.println(nilai_adc);      
  Serial.print("output pwm= ");      
  Serial.println(nilai_pwm);   
  Serial.print("Voltage ADC = ");      
  Serial.println(voltageOut);
  Serial.print("Voltage AC = ");      
  Serial.println(voltage_ac);
  delay(1500);  //jeda 2ms   
  Serial.println();
