#include "BluetoothSerial.h"


BluetoothSerial SerialBT;

const int pwm_channel_1 = 0;
const int pwm_channel_2 = 1;
const int pwm_freq = 5000;
const int pwm_resol = 8;

const int pwm_pin1 = 15;
const int pwm_pin2 = 13;

const int max_duty= (int)(pow(2,pwm_resol)-1);


int pin_in1= 18;    // fot in1
int pin_in2 =19;     // fot in2
int pin_in3 =21;     // fot in3
int pin_in4 =22;    // fot in4 

int input;
int duty_cycle=0;
int duty_cycle2=0;

void setup() {
  Serial.begin(115200);

  SerialBT.begin();
  SerialBT.println("device is ready");
  pinMode(pin_in1,OUTPUT);
  pinMode(pin_in2,OUTPUT);
  pinMode(pin_in3,OUTPUT);
  pinMode(pin_in4,OUTPUT);

  ledcAttachChannel(pwm_pin1, pwm_freq, pwm_resol, pwm_channel_1);
  ledcAttachChannel(pwm_pin2, pwm_freq, pwm_resol, pwm_channel_2);
}

void loop() { 
  if(SerialBT.available()){
    input = (int)(SerialBT.read());
    Serial.write(input);
    if(input=='0'){
      stop_Both();
    }
    // if(input=='1'){
    //   st_C_A();
    // }
    if(input=='1'){
      st_C_A();
      st_C_B();
      duty_cycle=0;
    ledcWriteChannel(pwm_channel_1, duty_cycle);
    ledcWriteChannel(pwm_channel_2, duty_cycle);
    }
    
    if(input=='2'){
      st_AC_A();
      st_AC_B();
        duty_cycle=0;
    ledcWriteChannel(pwm_channel_1, duty_cycle);      
    ledcWriteChannel(pwm_channel_2, duty_cycle);      
    }

    if(input=='3'){
      // stop_A();
        duty_cycle=128;
        duty_cycle2=0;
    ledcWriteChannel(pwm_channel_1, duty_cycle);
    ledcWriteChannel(pwm_channel_2, duty_cycle2);
    }

    if(input=='4'){
        duty_cycle2=128;
         duty_cycle=0;
    ledcWriteChannel(pwm_channel_1, duty_cycle);
    ledcWriteChannel(pwm_channel_2, duty_cycle2);
    }
    
    if(input=='5'){
         duty_cycle=255;
    ledcWriteChannel(pwm_channel_1, duty_cycle);
    ledcWriteChannel(pwm_channel_2, duty_cycle);
  }
  
    if(input=='6'){
      duty_cycle=128;
    ledcWriteChannel(pwm_channel_1, duty_cycle);  

    ledcWriteChannel(pwm_channel_2, duty_cycle);
    }

    if(input=='7'){
      duty_cycle=192;
      ledcWriteChannel(pwm_channel_1, duty_cycle);
    ledcWriteChannel(pwm_channel_2, duty_cycle);
    }
    
  //   if(input=='8'){
  //     st_AC_Both();
  //   }
  //   if(input=='9'){
  //     st_CAC_Both();
  //   }

  // if(input>2 && input<=9){
  //   int duty_cycle= input;
  //   duty_cycle=map(duty_cycle,3,9,0,max_duty);
    // ledcWrite(pwm_channel,duty_cycle);

  // }
  }
    // ledcWriteChannel(pwm_channel, duty_cycle);

}

void st_AC_A(){
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
}
void st_C_A(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
}
void st_AC_B(){
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}
void st_C_B(){
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}
void st_AC_Both(){
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}
void st_C_Both(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}
void st_ACC_Both(){
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, HIGH);
}
void st_CAC_Both(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, HIGH);
  digitalWrite(pin_in3, HIGH);
  digitalWrite(pin_in4, LOW);
}
void stop_A(){
  digitalWrite(pin_in1, HIGH);
  digitalWrite(pin_in2, HIGH);
}
void stop_B(){
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, LOW);
}
void stop_Both(){
  digitalWrite(pin_in1, LOW);
  digitalWrite(pin_in2, LOW);
  digitalWrite(pin_in3, LOW);
  digitalWrite(pin_in4, LOW);
}