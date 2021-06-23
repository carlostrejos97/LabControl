// Asignaciones pins
const int PIN_INPUT = A0;
const int motor1 = 5;
const int motor2 = 6;

// Constantes del controlador
double Kp=10, Ki=200, Kd=160;
//double Kp=10, Ki=100, Kd=100;
///double Kp=5.33, Ki=16, Kd=0.4444;
// variables externas del controlador
double Input, Output, Setpoint, posicion, posicion_anterior, deltaP, velocidad;
 
// variables internas del controlador
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError, cumError=0, rateError;
double charral;
bool Out;
 
void setup()
{
   previousTime = -1;
   currentTime = millis();                               // obtener el tiempo actual
   elapsedTime = (double)(currentTime - previousTime);
   Input = analogRead(PIN_INPUT);
   Setpoint = 0;
   Serial.begin(9600);
   cumError=0;
   error=0;
   velocidad=0;
}    
 
void loop(){
   
   //pidController.Compute();
   
   Input = analogRead(PIN_INPUT);         // leer una entrada del controlador
   Output = computePID(Input);      // calcular el controlador

   analogWrite(motor1, Output);         // escribir la salida del controlador
   //Serial.println(cumError);
     //signo de la salida
     
  if(Output >0){
    analogWrite(motor1,0);
    //analogWrite(motor2,(5*abs(Output)/12));
    //analogWrite(motor2,map(abs(Output),0,1000,0,255));
    if(abs(Output)>255){
      analogWrite(motor2,255);
    }else{
      analogWrite(motor2,abs(Output));
    }
    //Serial.println(map(abs(Output),0,1000,0,255));
    Serial.println(Output);
  }else if(Output < 0){
    analogWrite(motor2,0);
    //analogWrite(motor1,map(abs(Output),0,1000,0,255));
    if(abs(Output)>255){
      analogWrite(motor1,255);
    }else{
      analogWrite(motor1,abs(Output));
    }
    //Serial.println(-map(abs(Output),0,1000,0,255));
    Serial.println(Output);
    }else{
      analogWrite(motor1,0);
      analogWrite(motor2,0);
      Serial.println(Output);
    }
}
 
double computePID(double inp){
        //posicion = -69.984*5*double(Input)/1024+208.06; 118; 290
        posicion = 69.984*5*double(Input)/1024-123.6;
        deltaP= posicion - posicion_anterior;     
        currentTime = millis();                               // obtener el tiempo actual
        elapsedTime = (double)(currentTime - previousTime);     // calcular el tiempo transcurrido
        velocidad= deltaP/elapsedTime;
        error = Setpoint - velocidad;                               // determinar el error entre la consigna y la medición
        //Serial.println(charral);
        cumError = error * elapsedTime + cumError;                      // calcular la integral del error
        //Serial.println(Output);
        //Serial.println(elapsedTime);
        rateError = (error - lastError) / elapsedTime;         // calcular la derivada del error
 
        double output = Kp*error + Ki*cumError + Kd*rateError;     // calcular la salida del PID
        delayMicroseconds(200);
        //delay(10);
        lastError = error;                                      // almacenar error anterior
        previousTime = currentTime;                             // almacenar el tiempo anterior
        posicion_anterior=posicion;
        return output;
}
