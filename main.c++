#define A 12
#define B 13
#define C 7
#define D 8
#define E 9
#define F 11
#define G 10
#define SUBE 5
#define BAJA 4
#define RESET 6  
#define DECENA A5
#define UNIDAD A4
#define TIEMPO 10

int count = 0;
int prev_presiono_sube = 0;
int prev_presiono_baja = 0;
int prev_presiono_reset = 0;
 
void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(SUBE, INPUT_PULLUP);
  pinMode(BAJA, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP );
  pinMode(DECENA, OUTPUT);
  pinMode(UNIDAD, OUTPUT); 
  
  Serial.begin(9600);
}

void loop()
{
  int press_sube = digitalRead(SUBE);
  int press_baja = digitalRead(BAJA);
  int press_reset = digitalRead(RESET);
  
  //Aca se fija si presionamos el boton de SUBE, leyendo con el digitalRead.
  // Aca tambien esta el anti rebote para que al apretar una vez solo suba 1 vez.
  // El anti-rebote funciona gracias a una variable que nos guardamos el estado previo del boton, empieza en 0.
  // al presionar el boton por primera vez el estado previo lo vamos a poner a 1 y va a ser asi hasta 
  // que suelte el boton que le volvemos a igualar a 0
  if(press_sube == 0)
  {
    if (prev_presiono_sube == 0)
    {
       count += 1;
       prev_presiono_sube = 1;
    }
  }else
   {
     prev_presiono_sube = 0; 
   }
  //-------------------------------------------
  if (press_baja == 0)
  {
    if(prev_presiono_baja == 0)
    {
      count-=1;
      prev_presiono_baja = 1;
    }
  }else
  {
    prev_presiono_baja = 0; 
  }
    
  //--------------------------------------------
  // Aca tenemos las logicas para que no se pase de un numero de 9 cifras y que el boton reset vuelva el contador a 0
  if (press_reset == 0)
  {
   count = 0; 
  }
  
  if (count > 99 )
  {
   count = 0 ;
  }
  if(count < 0)
  {
   count = 99 ;
  }
  
  mostrar_count(count) ;
  
}

void mostrar_count(int count)
{
  // Aca pasa la logica de multiplexacion, donde usando pines creo una diferencia potencial 
  //para prender el display que yo quiero
  prenderLeds(count - 10 * ((int)count / 10));
  digitalWrite(UNIDAD,LOW);
  digitalWrite(DECENA,HIGH);
  
  delay(50);
  
  digitalWrite(UNIDAD,HIGH);
  digitalWrite(DECENA,LOW);
  prenderLeds((int)count / 10);

  delay(50);
  
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



