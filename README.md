# PARCIAL SPD (PRIMERA PARTE)

## Integrantes 
- Ezequiel Cura
- DNI: 44160534

## Proyecto: 2 DISPLAY SEGMENTOS, 3 BOTONES 
![Tinkercad](/Imagenes/primera_parte_componentes.png)

## Descripción
El código que has proporcionado es un programa en el lenguaje de programación C++, diseñado para controlar un display de siete segmentos y realizar algunas operaciones de conteo.

### Define 
En esta sección, se definen constantes para los pines de Arduino utilizados para conectar el display de siete segmentos, los botones de incremento, decremento y reset, así como algunas variables globales y constantes para el programa.


### Funcion setup

En la función setup(), se realiza la configuración inicial del programa y los pines de Arduino. Esto incluye configurar los pines como entrada o salida y habilitar las resistencias pull-up para los botones SUBE, BAJA y RESET. También se inicia la comunicación serial a una velocidad de 9600 baudios.

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
  pinMode(SUBE, INPUT_PULLUP);
  pinMode(BAJA, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP );
  pinMode(DECENA, OUTPUT);
  pinMode(UNIDAD, OUTPUT); 
  
  Serial.begin(9600);
}
~~~

### Función principal

La función loop() se ejecuta continuamente en un bucle infinito y realiza las siguientes acciones:

- Lee el estado de los botones SUBE, BAJA y RESET.
- Incrementa o decrementa el valor de la variable count en función de si se presionan los botones SUBE o BAJA. Se evita la repetición de incrementos o decrementos mientras se mantiene presionado un botón utilizando las variables prev_presiono_sube y prev_presiono_baja.
- Si se presiona el botón RESET, se restablece el valor de count a cero.
- Se asegura de que count esté en el rango de 0 a 99.
- Llama a la función mostrar_count(count) para mostrar el valor actual en el display de siete segmentos.

~~~ C++ (lenguaje en el que esta escrito)
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
~~~
### Funcion mostrar_count

Esta función se encarga de mostrar el valor de count en el display de siete segmentos. Divide el número en decenas y unidades, alternando la visualización de ambas. Luego, llama a la función prenderLeds() para activar los segmentos necesarios del display.

~~~ C++ (lenguaje en el que esta escrito)
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
~~~

### Prender leds

La función prenderLeds() se utiliza para encender los segmentos adecuados del display de siete segmentos para mostrar un dígito específico. Esto se logra mediante la manipulación de los pines de salida correspondientes a cada segmento. La función utiliza un switch-case para determinar cuáles pines deben estar en alto para mostrar el número proporcionado como argumento.

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


En resumen, este programa controla un display de siete segmentos para mostrar un valor numérico que puede incrementarse, decrementarse y restablecerse utilizando botones. El valor se muestra en el rango de 0 a 99, y se alternan las unidades y decenas en la visualización.



## Diagrama del proyecto
![Diagrama](/Imagenes/diagrama_primera_parte.png)



## :robot: Link al proyecto
- [proyecto](https://www.tinkercad.com/things/4uENUnsonR1-primera-parte-parcial-ezequiel-cura/editel?sharecode=Z6s_tFLZi58AiIqnglmsY78PJH6KQYSpwUFWbU9MSA8)
