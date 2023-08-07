
//some important things:
// 1) If using Serial monitor to read the value of inductor then select 115200 boud.
// 2) Adjust the value by using fixed inductor by changing 2.E-7 line.
// 3) We will get acuurate readings because of many iteratations.

//12 is the input to the circuit (connects to 150ohm resistor), 11 is the comparator/op-amp output.
double pulse, frequency, capacitance, inductance/*, inductance_mH*/;

int fan_pin = 13;

void setup(){
  
  pinMode(11, INPUT); //Input from the comparator output
  pinMode(12, OUTPUT);//output through a 150 ohm resistor to thr LC circuit
  pinMode(fan_pin, OUTPUT);
  delay(1500);
}
void loop(){
  digitalWrite(12, HIGH);
  delay(5);//give some time to charge inductor.
  digitalWrite(12,LOW);
  delayMicroseconds(100); //make sure resination is measured
  pulse = pulseIn(11,HIGH,5000);//returns 0 if timeout
  if(pulse > 0.1){ //if a timeout did not occur and it took a reading:
    
    
  capacitance = 1.E-7; // <- insert value here
  
  
  frequency = 1.E6/(2*pulse);
  inductance = 1./(capacitance*frequency*frequency*4.*3.14159*3.14159);
  inductance *= 1E6; //note that this is the same as saying inductance = inductance*1E6

  if(inductance > 6990){
    digitalWrite(fan_pin, HIGH);
  }
  if (inductance < 6981){
    digitalWrite(fan_pin, LOW);
  }
  delay(100);
  }
}
