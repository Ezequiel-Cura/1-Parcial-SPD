# PARCIAL SPD ( CUARTA PARTE)

## Integrantes 
- Ezequiel Cura
- DNI: 44160534

## Proyecto: 3 DISPLAY SEGMENTOS, MOTOR, SENSOR DE TEMPERATURA, SLIDESWITCH & PHOTODIODE
![Tinkercad](/Imagenes/tercera_parte/tercera_parte_proyecto.png)

## Descripción
Este código es un programa escrito en el lenguaje de programación C++. Su objetivo es controlar una serie de displays LED de siete segmentos y realizar diferentes acciones basadas en la lectura de sensores y entradas de usuario.

#### Componentes agregados

Los componentes que agregue fueron un motor cc y el sensor de temperatura:
  - La funcion del motor cc es que cambia la direccion en la que gira el motor segun del estado del slideSwitch.
  - Para el sensor de temperatura tuve que agregar un display para poder mostrar la temperatura con 3 cifras, para poder ver la temperatura tenes que mantener apretado el pulsador.
  - Agregue un photodiode en el si hay suficiente luz se prende el sistema y si no la hay se apaga.

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
  pinMode(PHOTODIODE, INPUT_PULLUP);
  
  Serial.begin(9600);
  tiempo1 = millis();
}
~~~

### Función principal

Esta es la función principal del programa que se ejecuta continuamente en un bucle.
Esta función se ejecuta en un ciclo continuo después de la función setup(). Su principal tarea es leer un fotodiodo y, en función de su lectura, decidir si mostrar la temperatura, contar segundos o mostrar números impares.
- medir_tiempo(): Llama a la función medir_tiempo() que actualiza los contadores de tiempo.
- leer_temperatura(): Llama a la función leer_temperatura() para leer la temperatura del sensor analógico.
- que_mostrar_display(): LLama a la funcion y ahi se fija que mostrar en las displays, dependiendo de los valores leidos.

~~~ C++ (lenguaje en el que esta escrito)
void loop()
{ 
  int lectura_photodiode = digitalRead(PHOTODIODE);
 
  if ( lectura_photodiode == 1)
  {
    digitalWrite(CENTENA, HIGH);
    digitalWrite(DECENA, HIGH);
    digitalWrite(UNIDAD, HIGH);
  }else
  {
      medir_tiempo();
      leer_temperatura();
      que_mostrar_display();
   }
}
~~~
### Funcion cambiar_direccion_cc
Esta función se utiliza para cambiar la dirección de giro de un motor o dispositivo conectado a los pines 4 y 5. Si girar es verdadero, el motor gira en una dirección, de lo contrario, gira en la otra dirección.

~~~ C++ (lenguaje en el que esta escrito)
void cambiar_direccion_cc(bool girar)
{
  if (girar == true)
  {
    digitalWrite(4, HIGH);
    digitalWrite(5,LOW);
  }
  else
  {
    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
  }
}
~~~
### Funcion que_mostrar_display
Esta función decide qué se debe mostrar en el display de siete segmentos en función de la posición de un interruptor deslizante y el estado de un botón. Muestra la temperatura si el botón está presionado, muestra un contador si el interruptor está en una posición y muestra números impares si el interruptor está en la otra posición.

~~~ C++ (lenguaje en el que esta escrito)
void que_mostrar_display(){
  // Lee los valores del boton y del slideswitch
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
        // Aca pasamos el numero que queremos mostrar en los displays
        mostrar_count(count);
        // Cambiamos la direccion del motor
        cambiar_direccion_cc(true);
        // Reiniciamos el contador para numeros impares
        count_impares = 0;
     }
     else
     {
        bool num_impar = num_impares(count_impares);
        if (num_impar == true)
        {
          // Aca se guarda el numero impar previo y despues muestra el numero impar encontrado
          guardar_num = count_impares;
          mostrar_count(count_impares);
        }else{
          // Aca el numero impar previo se muestra hasta que se halla encontrado uno nuevo
          mostrar_count(guardar_num);
        }
        // Cambiamos la direccion del motor
        cambiar_direccion_cc(false);
        // Reiniciamos el contador para la secuencia de numeros
        count = 0;
     }
}
~~~

### Funcion num_impares

La funcion num_impares toma un numero int como argumento y dentro de la funcion verifica que el numero sea impar.
Se verifica de la siguiente manera:
- Se verifica si num % 2 no es igual a 0 (es decir, el residuo no es igual a 0). Esto se hace con la expresión num % 2 != 0.
- Si la condición es verdadera, significa que el número es impar, y en ese caso, la función devuelve true.
- Si la condición es falsa, significa que el número es par, y en ese caso, la función devuelve false.


~~~ C++ (lenguaje en el que esta escrito)
bool num_impares(int num)
{  
  // Si el resto es diferente a 0 significa que es impar
	if(num % 2 != 0)
    {
     return true ;
    }
  	else
    {
     return false ;
    }
}

~~~

### Funcion medir_tiempo

Esta función actualiza los contadores de tiempo count y count_impares cada medio segundo (500 ms). Se utiliza para controlar la velocidad de incremento de los números.
Se utiliza la funcion millis para conseguir y actualizar los segundos de ejecucion del programa.

~~~ C++ (lenguaje en el que esta escrito)
void medir_tiempo(){
  tiempo2 = millis();
  
  // Le suma 1 a los 2 contadores cada medio segundo 
  if( tiempo2 >  tiempo1 + 500 ){
    tiempo1 = millis();
	  count += 1;
    count_impares +=1;
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

### Funcion mostrar_count

Esta función muestra un número en los displays de siete segmentos. Recibe un número como argumento y utiliza pines de control (UNIDAD, DECENA, y CENTENA) para mostrar el número. Realiza la multiplexación de los displays para mostrar dígitos individuales.
- Aca hago la logica para mostrar en displays y hice para que mostrara los numeros negativos de la temperatura.

~~~ C++ (lenguaje en el que esta escrito)
void mostrar_count(int numero)
{
  // Aca pasa la logica de multiplexacion, donde usando pines creo una diferencia potencial para prender el display que yo quiero
  // Si el numero es negativo hago una cosa mas para sacar el numero
  // aca saco la unidad
  if (numero < 0)
  {
    int num = -numero;
    prenderLeds(num - 10 * ((int)num / 10));
  }else{
    prenderLeds(numero - 10 * ((int)numero / 10));
  }

  // Aca es donde se crea la diferencia de potencial LOW significa que es va a prender esa display, y el HIGH que esta apagado
 	digitalWrite(UNIDAD,LOW);
  digitalWrite(DECENA,HIGH);
  digitalWrite(CENTENA, HIGH);
  
  delay(15);
  
  // Aca tambien me fijo si el numero es mayor a 99 o si es negativo para hacer algo diferente y sacar la DECENA
  if ( numero > 99){
    prenderLeds(((int)numero / 10)-10);
  }else if(numero < 0)
  {
    int num = -numero;
    prenderLeds((int)num / 10);
  }
  else{
    prenderLeds((int)numero / 10);
  }
  
  digitalWrite(UNIDAD,HIGH);
  digitalWrite(DECENA,LOW);
  digitalWrite(CENTENA, HIGH);

  delay(15);
 //  Aca saco al DECENA
  if(numero < 0)
  {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  }else{
    prenderLeds((int)numero / 100);
  }
  digitalWrite(UNIDAD,HIGH);
  digitalWrite(DECENA,HIGH);
  digitalWrite(CENTENA, LOW);

  delay(15);
  
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

En resumen, el código controla la visualización de números en displays de siete segmentos en función de la posición de un interruptor y un botón, muestra temperaturas leídas de un sensor y realiza operaciones con números impares. También contiene funciones para determinar si un número es primo y para controlar la visualización en los displays.

## Diagrama del proyecto
![Diagrama](/Imagenes/tercera_parte/diagrama_tercera_parte_1.png)
![Diagrama](/Imagenes/tercera_parte/diagrama_tercera_parte_2.png)



## :robot: Link al proyecto
- [Proyecto](https://www.tinkercad.com/things/kiYpaf3eyQz-4-parte-parcial-ezequiel-cura/editel?sharecode=mgPzwsFieqlfpKbYVlydK5DRLxCf0Vo5KQw5JGIvAVw)
