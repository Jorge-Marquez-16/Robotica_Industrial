/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <TimerOne.h>


void messageCb( const std_msgs::Int16& toggle_msg);

ros::NodeHandle  nh;

std_msgs::Float32 str_msg;
ros::Publisher chatter("encoder_signal", &str_msg);
ros::Subscriber<std_msgs::Int16> sub("control_signal", &messageCb );

int IN3 = 4;    // Input3 conectada al pin 5
int IN4 = 5;    // Input4 conectada al pin 4 
int ENB = 3;    // ENB conectada al pin 3 de Arduino


//Periodo de muestreo
float periodo_muestreo = 3000;



// Pin 2 para señal de encoder
const int interruptPin = 2; 
const int B = 6;   

// Contador: cuenta las interrupciones debido a un flanco de subida en el encoder
long signed int counter = 0;       
     
// Variable para registrar la posicion del motor.
float posicion = 0;

// Tiempo transcurrido 
float tiempo=0.0;   

//Relación de engranes motor
float relacion_engranes = 46.8;

//Pulsos por revolución encoder
float pulsos_r = 11.0;

//Resolución 
float resolucion = relacion_engranes*pulsos_r;


int  u;

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);

  pinMode (ENB, OUTPUT); 
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (B, INPUT);

  // El Pin interruptPin es entrada, se conecta a la señal del encoder Canal A (tren de pulsos).
  pinMode(interruptPin, INPUT);    
  // Interrupción Encoder: cada vez que haya un flanco de subida en el interruptPin se ejecutará la
  // función counting que es una Interrupt Service Routine (ISR).

  attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_counting, RISING);  

  // Timer1: Se dispara cada 20000 microsegundos=0.02 Segundos.
  Timer1.initialize(periodo_muestreo); 
  // Activa la interrupción: Ejecuta la función Posicion            
  Timer1.attachInterrupt(ISR_Posicion); 
                                        
  
}

void loop()
{

  nh.spinOnce();
}

void ISR_counting() {
  //Contador
  if (digitalRead(B) == LOW)
    counter++;
  else
    counter--;                            
}

void ISR_Posicion(){
  
  // Velocidad en Revoluciones por minuto: esta parte "(counter/CuentasPorRevolucion)/Ts" 
  // da las revoluciones por segundo a las que gira el encoder, 
  // se multiplica por 60 segundos para obtener esta velocidad en RPM
  if (posicion>360){
    counter=0;
  }
  if (posicion<-360){
    counter=0;
  }
  posicion = (counter*180)/resolucion; 
  

  str_msg.data = posicion;
  chatter.publish( &str_msg );


                                                       
}

void sentidoGiro(const std_msgs::Int16& toggle_msg){
  
  u=toggle_msg.data;
  //Posiciona el ángulo con tolerancia +- 2
   if(u > 0){
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      if(u>255) u=255;
      analogWrite(ENB,u);
    }
    else if (u < 0){
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      if(u<-255)u=-255;
      analogWrite(ENB,(int)(-u));
    }
}


void messageCb( const std_msgs::Int16& toggle_msg){
    sentidoGiro(toggle_msg);
}
