# PARCIAL SPD ( SEGUNDA PARTE)

## Integrantes 
- Ezequiel Cura
- DNI: 44160534

## Proyecto: 3 DISPLAY SEGMENTOS, MOTOR, SENSOR DE TEMPERATURA & SLIDESWITCH
![Tinkercad](/Imagenes/Imagen_proyecto.png)

## Descripción
Este código es un programa escrito en el lenguaje de programación C++. Su objetivo es controlar una serie de displays LED de siete segmentos y realizar diferentes acciones basadas en la lectura de sensores y entradas de usuario.

#### Componentes agregados

Los componentes que agregue fueron un motor cc y el sensor de temperatura:
  - La funcion del motor cc es que cambia la direccion en la que gira el motor segun del estado del slideSwitch.
  - Para el sensor de temperatura tuve que agregar un display para poder mostrar la temperatura con 3 cifras, para poder ver la temperatura tenes que mantener apretado el pulsador.

### Funcion setup

Esta función se ejecuta una sola vez al principio del programa. Su objetivo es configurar los pines de entrada y salida y establecer la velocidad de comunicación serial.
En la función setup(), se configuran los pines de salida y entrada según sea necesario. Los pines de siete segmentos se configuran como salidas, mientras que los pines para el sensor y el botón se configuran como entradas. También se inicia la comunicación serial a una velocidad de 9600 baudios, para poder ver por terminal. Tambien se inicializa la variable tiempo1 con el valor actual del tiempo de ejecución del programa.

~~~ C++ (lenguaje en el que esta escrito)
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

~~~

### Función principal

Esta es la función principal del programa que se ejecuta continuamente en un bucle.
- medir_tiempo(): Llama a la función medir_tiempo() que actualiza los contadores de tiempo.
- leer_temperatura(): Llama a la función leer_temperatura() para leer la temperatura del sensor analógico.
- Luego, se leen los estados de un interruptor (slide_valor) y un botón (boton_sensor).
- Dependiendo de los estados del interruptor y el botón, se llama a la función mostrar_count() para mostrar números en los displays de siete segmentos.
- Si el botón está presionado, muestra la temperatura. Si el interruptor está en una posición, muestra números que incrementan. Si está en la otra posición, muestra números primos.

~~~ C++ (lenguaje en el que esta escrito)
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
    // Si el slideswitch tiene valor 0 muestro el contador 
    if(count > 99)
    {
     count = 0; 
    }
    mostrar_count(count);
    
    //Aca hace que el motor cc gire en sentido horario
    digitalWrite(4, HIGH);
    digitalWrite(5,LOW);
    count_primos = 0;

  }
  else
  {
    // Aca me fijo que numeros del count_primos son primos, la funcion num_primos retorna un booleano segun si el numero es primo o no
    bool num_primo = num_primos(count_primos);
    if (num_primo == true)
    {
      // Si el numero es primo lo muestro en los displays y me guardo en una variable el ultimo primo
      guardar_num = count_primos;
      mostrar_count(count_primos);
    }else{
      // Si el numero no es primo muestro el ultimo primo hasta encontrar uno nuevo
      mostrar_count(guardar_num);
    }

    //Aca hace que el motor cc gire en sentido anti horario
    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
    count = 0;
  }
}
~~~
### Funcion mostrar_count

Esta función muestra un número en los displays de siete segmentos. Recibe un número como argumento y utiliza pines de control (UNIDAD, DECENA, y CENTENA) para mostrar el número. Realiza la multiplexación de los displays para mostrar dígitos individuales.

~~~ C++ (lenguaje en el que esta escrito)
void mostrar_count(int numero)
{
  // Aca pasa la logica de multiplexacion, donde usando pines creo una diferencia potencial para prender el display
  // que yo quiero
  prenderLeds(numero - 10 * ((int)numero / 10));
  digitalWrite(UNIDAD,LOW);
  digitalWrite(DECENA,HIGH);
  digitalWrite(CENTENA, HIGH);
  
  delay(15);
  // Lo que pasa aca es que cuando el numero es de 3 cifras tengo un error para conseguir la CENTENA entonces hice un if para corregirlo
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
~~~

### Funcion num_primos

Esta función toma un número entero num como argumento y devuelve true si es un número primo, y false si no lo es. Utiliza un bucle para verificar si el número es divisible por otros números, y si no lo es, se considera primo.

~~~ C++ (lenguaje en el que esta escrito)
bool num_primos(int num)
{
  // Aca hay una verificacion por si llega un numero negativo
  if (num <= 1) {
    return false;
  }
  // Este for se fija si hay algun divisor ademas del 1 y el numero mismo
  // Si lo encuentra significa que ya no es primo
  for (int i = 2; i <= num / 2; i++) {
    if (num % i == 0) {
      return false; 
    }
  }
  return true;
  
}

~~~

### Funcion medir_tiempo

Esta función actualiza los contadores de tiempo count y count_primos cada medio segundo (500 ms). Se utiliza para controlar la velocidad de incremento de los números.
Se utiliza la funcion millis para conseguir y actualizar los segundos de ejecucion del programa.

~~~ C++ (lenguaje en el que esta escrito)
void medir_tiempo(){
  tiempo2 = millis();
  
  // Le suma 1 a los 2 contadores cada medio segundo 
  if( tiempo2 >  tiempo1 + 500 ){
    tiempo1 = millis();
	  count += 1;
    count_primos +=1;
  }
  
}

~~~

### Funcion leer_temperatura

Esta función lee un valor analógico del sensor conectado al pin SENSOR y lo mapea para convertirlo en una temperatura en grados Celsius. El valor leído se almacena en las variables lectura y temperatura.

~~~ C++ (lenguaje en el que esta escrito)
void leer_temperatura(){
  // Esta funcion simplemente lee el valor del sensor de temperatura
  // Luego con el metodo map lo transformamos a celcius
  lectura = analogRead(SENSOR);
  temperatura = map(lectura,20,358,-40,125);
  
}
~~~

### Funcion prenderLeds

Esta función enciende los segmentos LED correspondientes en los displays de siete segmentos para representar dígitos numéricos. Recibe un número como argumento y configura los pines de segmento para mostrar ese número en los displays.

~~~ C++ (lenguaje en el que esta escrito)

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

~~~

En resumen, el código controla la visualización de números en displays de siete segmentos en función de la posición de un interruptor y un botón, muestra temperaturas leídas de un sensor y realiza operaciones con números primos. También contiene funciones para determinar si un número es primo y para controlar la visualización en los displays.

## Diagrama del proyecto
![Diagrama](/Imagenes/Diagrama_del_proyecto.png)



## :robot: Link al proyecto
- [proyecto](https://www.tinkercad.com/things/65sPpmw0BxS-copy-of-segunda-parte-parcial-ezequiel-cura/editel?sharecode=uu9OWa0VeYLR6PSS4rqcE32mPV5wVpjMcVhsprEm2hs)
