const int sensor = 8;
const int salida3 = 12;
const int salida = 10;
const int sensor2 = 3;
const int salida2 = 7;
boolean activado = false;
boolean disparar = false;
unsigned int presento1 = 0;
unsigned int presento2 = 0;

unsigned long tiempo = 0; //Control del tiempo
unsigned long espera = 6000; //Tiempo a esperar o temporizar en milisegundos
unsigned long redisparo = 1000;  // durante este tiempo si hay nuevos disparos del PIR reinicio la temporización.

boolean presento = false;

void setup(){
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(salida, OUTPUT);
  pinMode(sensor2, INPUT);
  pinMode(salida2, OUTPUT);
  pinMode(salida3, OUTPUT);
  digitalWrite(salida, LOW); // Logica inversa de usarse la directa cambiar a LOW
  digitalWrite(salida2, LOW);
  digitalWrite(salida3, LOW);
  //digitalWrite(sensor, LOW); // Resistencias PullUp internas

}

void loop(){

  if ((digitalRead(sensor2) == HIGH)){
    digitalWrite(salida2, LOW);
  }else{
    digitalWrite(salida2, HIGH);
    }
  
  if ((digitalRead(sensor) == LOW)) {
    presento1++;
    if (presento1 == 1) {
      Serial.println("Disparo sensor.");
    }
    activado = true;
    tiempo = millis();
  } else presento1 = 0;   
  
  
  if (activado) { 
      
     if ((digitalRead(sensor) == LOW) && ( millis() - tiempo < redisparo)) {
       tiempo = millis();
       presento2++;
       if (presento2 == 1) {
           Serial.print("Hubo redisparo. Tiempo =");
         Serial.println(tiempo);
           Serial.print("Faltan =");
           Serial.println(millis() - tiempo);
       }
     } else presento2 = 0;
       
     if (millis() - tiempo < espera) {
       digitalWrite(salida, LOW);
       digitalWrite(salida3, LOW);// Para lagica inversa
       
     } else {
       digitalWrite(salida, HIGH);
       digitalWrite(salida3, HIGH);
       activado = false;
     }
    

  }
    
