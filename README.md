# Wordle - Clon
## Introducción
Wordle ([enlace a la página del juego](https://www.nytimes.com/games/wordle/index.html)) es un juego de adivinanza de navegador, en el cual el jugador debe adivinar la palabra secreta realizando suposiciones. Fue desarrollado por Josh Wardle en 2021.

![MostrarImg1](readme-rsc/Wordle1.png)

## Reglas
El jugador tiene seis intentos para adivinar la palabra. Al introducir una suposición, las letras de la palabra cambiarán de color de acuerdo con las siguientes reglas:
- Verde: Si la palabra secreta contiene la letra y además se encuentra en el lugar correcto, la letra cambia de color a verde.
- Amarillo: Si la palabra secreta contiene la letra, pero se encuentra en el lugar incorrecto, la letra cambia de color a amarillo.
- Negro: Si la palabra secreta no contiene la letra, esta cambiará de color a negro.

ACLARACIÓN: siguiendo las reglas del juego original, cuando la palabra insertada tenga una letra repetida y esta letra se encuentre en la palabra solo una vez (por ejemplo, armar y vista), se contará una sola de estas letras al cambiar el color a verde/amarillo, ya que solo aparece una vez en la palabra secreta (en el caso del ejemplo, solo cambiaría de color a amarillo la primera 'a' de la palabra "armar", la segunda cambiaría a color negro).
  
![MostrarImg2](readme-rsc/Wordle2.png)

## Cómo jugar
Se utiliza el teclado para introducir las distintas letras para formar la palabra, pudiendo solo insertar letras. 
  
Por conveniencia, se omitió el uso de palabras con la letra 'ñ', y las vocales no pueden llevar tilde (puede haber palabras con tilde como "había", pero al escribirla debe hacerse sin tilde).
  
Para borrar una letra, debe utilizarse la tecla de backspace/retroceso. 
  
Para introducir una palabra, se debe pulsar la tecla Enter. Para que el programa acepte la palabra, se debe de haber introducido una palabra de 5 letras, y la palabra debe además estar contenida en el diccionario del programa. Caso contrario, mostrará un mensaje indicando cuál de las dos excepciones ha sucedido.
  
Al terminarse los intentos o adivinar la palabra, se habilitará un botón de reinicio, que debe ser presionado con el mouse.
  
## Estructura del código
El código se basa en el patrón de arquitectura MVC. 
### Modelo
El apartado de Modelo está formado por dos clases y un archivo de texto:
- `Palabras.txt`: contiene el diccionario de las palabras utilizadas por el programa (todas las palabras fueron extraídas de la siguiente página web: https://www.diccionariodedudas.com).
- `ListaPalabras`: se encarga de retornar la palabra secreta para ser asignada, y de verificar que la palabra insertada por el usuario sea válida.
- `WordleModel`: contiene la información del estado actual del juego, como la palabra secreta, la palabra insertada por el usuario, la fila y columna actual de la cuadrícula, etc. Se encarga de retoranr y actualizar la información del juego, así como realizar la comparación de la palabra secreta con la palabra del usuario.
### Vista
El apartado Vista está formado por siete clases:
- `Bordes`, `Colores`, y `Fuentes`: Contienen información sobre los distintos elementos de interfaz de usuario. Son utilizadas para actualizar la vista de manera más fácil.
- `PanelTitulo`: Muestra el título del juego y los distintos mensajes que el programa envía a la vista.
- `PanelCuadricula`: Muestra la cuadrícula en la cual el usuario inserta las distintas palabras. Actualiza las letras y colores de la cuadrícula cuando se le solicita.
-  `PanelTeclado`: Muestra un teclado debajo de la cuadrícula el cual funciona como guía del usuario para saber qué letras ya han sido usadas y cuáles son correctas.
-  `WordleView`: Se encarga de mostrar todos los paneles en pantalla, así como de actualizar la vista cuando se le es solicitado. Envía mensajes a las distintas clases `Panel` para que estas actualicen su información.

La vista utiliza la biblioteca gráfica Swing para generar la interfaz de usuario.

### Controlador
El controlador está formado por una clase:
- `WordleController`: Se encarga responder a los eventos del usuario. Envía mensajes a `WordleView` y `WordleModel` para que realicen una serie de acciones según sea necesario. 
