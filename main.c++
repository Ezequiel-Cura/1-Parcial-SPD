#define A 12
#define B 13
#define C 7
#define D 8
#define E 9
#define F 11
#define G 10 

#define CENTENA A5
#define DECENA A4
#define UNIDAD A3

#define TIEMPO 10
#define SENSOR A0
#define BOTON_SENSOR 3

#define NUMEROS 2

int tiempo1 = 0;
int tiempo2 = 0;

int count = 0;
int count_primos = 2;
int guardar_num ;

int lectura;
int temperatura;


void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  
  pinMode(DECENA, OUTPUT);
  pinMode(UNIDAD, OUTPUT); 
  pinMode(CENTENA, OUTPUT);
  
  pinMode(NUMEROS, INPUT);
  pinMode(BOTON_SENSOR, INPUT_PULLUP);
  
  Serial.begin(9600);
  tiempo1 = millis();
}


void loop()
{
  medir_tiempo();
  leer_temperatura();
 
  int slide_valor = digitalRead(NUMEROS);
  int boton_sensor = digitalRead(BOTON_SENSOR);

  // Se fija que tiene que mostrar en los displays dependiendo del estado del slideSwitch o del pulsador
  if(boton_sensor == 0){
    mostrar_count(temperatura); 
  }
  else if (slide_valor == 0){
    // Si el contador es mayor a 99 el contador se reinicia a 0
    if(count > 99)
    {
     count = 0; 
    }
    mostrar_count(count);
    
    digitalWrite(4, HIGH);
    digitalWrite(5,LOW);
    count_primos = 0;

  }
  else
  {
  
    bool num_primo = num_primos(count_primos);
    if (num_primo == true)
    {
      guardar_num = count_primos;
      mostrar_count(count_primos);
    }else{
      mostrar_count(guardar_num);
    }

    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
    count = 0;
  }
}

bool num_primos(int num)
{
  if (num <= 1) {
    return false;
  }

  for (int i = 2; i <= num / 2; i++) {
    if (num % i == 0) {
      return false; 
    }
  }
  return true;
  
}

void medir_tiempo(){
  tiempo2 = millis();
  
  // Le suma 1 a los 2 contadores cada medio segundo 
  if( tiempo2 >  tiempo1 + 500 ){
    tiempo1 = millis();
	  count += 1;
    count_primos +=1;
  }
  
}


void leer_temperatura(){
  lectura = analogRead(SENSOR);
  temperatura = map(lectura,20,358,-40,125);
  
}

void mostrar_count(int numero)
{
  // Aca pasa la logica de multiplexacion, donde usando pines creo una diferencia potencial para prender el display
  // que yo quiero
  prenderLeds(numero - 10 * ((int)numero / 10));
  digitalWrite(UNIDAD,LOW);
  digitalWrite(DECENA,HIGH);
  digitalWrite(CENTENA, HIGH);
  
  delay(15);
  
  if ( numero > 99){
      prenderLeds(((int)numero / 10)-10);
  }else{
    prenderLeds((int)numero / 10);
  }
  
  digitalWrite(UNIDAD,HIGH);
  digitalWrite(DECENA,LOW);
  digitalWrite(CENTENA, HIGH);

  delay(15);
  
  prenderLeds((int)numero / 100);
  digitalWrite(UNIDAD,HIGH);
  digitalWrite(DECENA,HIGH);
  digitalWrite(CENTENA, LOW);

  delay(15);
  
}



void prenderLeds(int count)
{
  // Apaga todas las leds, como un reset para luego prender las leds correspondientes
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
  
  switch (count)
  {
    case 0:
    	digitalWrite(A, HIGH); // prendo las leds que forman un cero
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
    	break;
    
    case 1:
    	digitalWrite(B, HIGH); // prendo las leds que forman un uno
  		digitalWrite(C, HIGH);
  		break;

    case 2:
    	digitalWrite(A, HIGH); // prendo las leds que forman un dos
      digitalWrite(B, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      break;

    case 3:
    	digitalWrite(A, HIGH); // prendo las leds que forman un tres
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;

    case 4:
      digitalWrite(B, HIGH); // prendo las leds que forman un cuatro
      digitalWrite(C, HIGH);
      digitalWrite(G, HIGH);
      digitalWrite(F, HIGH);
      break;

    case 5:
      digitalWrite(A, HIGH); // prendo las leds que forman un cinco
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case 6:
      digitalWrite(A, HIGH); // prendo las leds que forman un seis
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case 7:
      digitalWrite(A, HIGH); // prendo las leds que forman un siete
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;

    case 8:
      digitalWrite(A, HIGH); // prendo las leds que forman un ocho
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

    case 9:
      digitalWrite(A, HIGH); // prendo las leds que forman un nueve
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;

  }
  
}
