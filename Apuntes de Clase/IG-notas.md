
# Tema 1

## Sección 2: Proceso de visualización  
- Dos algoritmos para visualizar imágenes: rasterización y ray-tracing 
- __Programa gráfico__ --> almacena ED con modelo --> Salida: imagen
- __Imágenes Raster:__ array de pixeles por filas y columnas y cada pixel tiene un color RGB  
- __Imágenes vectoriales:__ archivos.svg. La información se codifica a un nivel más alto.
    - Una img vect tiene lista de segmentos o curvas con una serie de parámetros numéricos.
- __Interactive Grafic Program__ --> Visualiza una imagen que responde a eventos (acciones del usuario) --> Timepos de espera de ms
- __Non-Interactive Grafic Program:__ Modelo --> Salidas: imágenes con duración s<-->horas  
- __Proceso de visualización:__ producir una imagen a partir del Modelo de escena y parámetros
    - Modelo Escena: ED
        - Modelo geométrico: primitivas, modelos de frontera, representacion de la forma de objetos con poligonales.
        - Modelo de aspecto: Parámetros que definen el aspecto de objetos.  
    - Parámeeros de visualización: parámetros para ver donde está la cámara:
        - Cámara Virtual: posición, ángulo de visión y orientación  
        - Viewport: Resolución y posición de la imagen en la ventana


### Algoritmos: Rasterización y Ray-tracing  

- Rasterización:
    - Primitiva: elementos más pequeños que pueden ver visualizados. Punto, segmento, etc.
    - Complejidad: O(n*p)
    - Las GPUs con el hardware diseñado especialmente para este algoritmo.
    - Más eficiente que el Ray-Tracing
~~~
Inicializar el color de todos los pixeles
for each Primitiva,P del modelo a visualizar
    Encontrar el conjunto S de pixels cubiertos por P
    For each pixels q de S:
        Calcular el color de P en q
        actualizr el color de q
~~~  

- Ray-Tracing
    - Complejidad: O(p*log(n))
    - No se usa en 2D, pero sí en 3D
    - Consideramos todas las primitivas en todos los pixeles
~~~
Inicializar el color de todos los pixeles
For each pixel q de la imagen a producir
    Calcualr T, el conjunto de primitivas que cubren q (Método: Indexación espacial)
    para cada primitiva P del conjunto T
        Calcualr el color de P en q
        actualizra el color de q
~~~  
    - La diferencia en los dos está en que se intercambian los bucles, se hace el mismo cálculo pero en diferente orden.   
    - No se usa en videojuegos por ser menos eficiente que lo otro. 
    - Se usa en producción de películas
    - Dan realismo 

- __Cauce gráfico:__ conjunto de etapas
    - Entradas (inputs): Primitivas --> (triangulos, segmentos de líneas o puntos)   
        - Vértice: punto en el espacio 2D o 3D. Una o varias primitvas se representan con una lista de coordenadas de vértices, más alguna información adicional.
        - Framebuffer: zona de memoria en la GPU donde están los colores de los pixeles de la imagen que se está viendo en pantalla. 
    - Etapas de Calculo:
        - Transformación y proyección de primitivas.  
            - Proyección: perspectiva o paralela

### Las APIs de rasterización 
La escritura en el Framebuffer es lenta y se realiza pixel a pixel, ya que cada operación de acceso al buffer es lenta. Usando una API conseguimos separar la implementación del hardware, permitiendo portabilidad y acceso simultáneio.  
Hoy en día se usan GPU, Unidad de Procesamiento Gráfico con chips con unidades de operaciones en coma flotante, unidades de control, etc y que pueden trabajar en paralelo. Con capaces de implementar el cauce de rasterización con buena eficiencia.

APIs de rastericación:  
- OpenGL
    - OpenGL ES
    - WebGS
- DirectX
- Metal
- DirectX12
- Vulkan

El cauce gráfico tiene las siguiente etápas:  
- Procesado de vértices:
  - Transformación
  - Teselación y nivel de detalle
- Post-proceso de vértices y montaje de primitivas
- Rasterización
- Sombreado
## Sección 3: La librería OpenGL.- Visualización
- OpenGL: para visualizar 2D y 3D
  - GLFW: para gestión de ventanas y eventos de entrada  

### Programación y eventosd en GLFW  
- Eventos:
  - Teclado
  - Ratón
  - Cambio de tamaño 
- Funciones Gestoras de Eventos, FGE: son invocadas uando ocurre algún eventgo de algún tipo 

Estructura de un programa:
- Variables, ED, variables globales
- Código de las funcioens gestoras de evento
- Código de inicialización
  - Creación y configuración de las ventanas donde se visualizan las primitivas
  - Establecimiento de las funciones del programa que actuarán como gestoras de eventos
  - Configuración inicial de OpenGL
- Función de viusalización de un frame o cuadro
- Bucle principal     
<img src="ig1.jpg">   

### Tipos de primitivas
- Primitiva: punto, segmento o polígono que generalmente son triángulos. 
- Con una lista de n coordenadas se puede codificar:
  - puntos aislados
  - segmentos de recta
  - triangulos 
  - cuadriláteros
  - polígono
  - tira de triángulos
  - abanico de triángulos
  - tira de cuadriláteros
- En OpenGL se definen varias constante de tipo __GLenum__ para identificar los distintos tipos de primitivas (puntos y segmento):
  - GL_POINTS
  - GL_LINES
  - GL_LINE_STRIP (polilínea abierta)
  - GL_LINE_LOOP  (polilínea cerrada)
- Primitivas tipo polígono:

<img src="ig2.jpg"> 
<img src="ig3.jpg">  

- Los polígonos se pueden visualizar como:  
  - Puntos  
  - Líneas (polilínea cerrada)
  - Relleno 
- Polígonos con más de tres vértices
  - Deben tener todos sus vértices en el mismo plano 
  - No se deben intersecar las aristas  
  - Deben ser convexos
- Problema de vértices replicados: se repiten coordenadas
  - Solución: Secuencias indexadas
    - Vn --> Secuencia con los vértices
    - Im --> secuencia de índices (enteros) que dicta la unión de puntos de Vn  

__IMPORTANTE__: no confundir la constante __GL_Line__ con __GL_Lines__
### Atributos de vértices   
- **Coordenadas de su posición**
- **color**: vector terna RGB entre 0 y 1, con posible valor de transparencia
- **Normal**: vector que determina la orientación (para iluminacion), tres posiciones  
- **Coordenadas de textura:** se usan imágenes en vez de colores 
- **Valores:**
  - Todo vertice --> (posicion,color,normal,coord_textura)  
- A **cada vértice** siempre se le asocia una tupla por cada atributo:
  - Todo vértice tiene asociado una posición, un color, una normal y unas coordenadas de texturas que se usarán o no. 

### Modos de envío  
Si queremos visualizar la secuencia de vertices o atributos:  
- **Modo inmediato**
  - Una llamada por vértice y atributo:
    - Lento
    - Cordenadas y atributos vértice a vértice
  - Una llamada para varios vérties con todos sus atributos
  - No almacena coordenadas, por tanto, para visualizar más de una vez es necesario enviar las mismas coordenadas cad vez  
- **Modo diferido:**
  - Una única llamda, previamente trasladar las cosas de la RAM a la GPU
  - Reservar memoria en la GPU  
  - Se indica que se deben primero leer la GPU en vez de la RAM

### Almacenamiento de vértices y atributos  
- **Array de estructuras (AOS):**
  - Array o vector  
  - Cada entrada tiene:
    - Coordenadas de sus vertices
    - Atributos
- **Estructura de Arrays (SOA):**
  - Estructura con punteros a arrays 
  - Los arrays contienen:
    - uno para coordenadas
    - otros para los atributos tales como colores, normalex, texturas, etc
    - Echarle un ojo a lo de los descriptores de la tabla
<img src="ig4.png" with="200" heigh="200">
------------------------------------------------- 
- Vertex Array Objects:   
      - Estructura de datos    
      - Para modo diferido:  
        - Crea tantos VAOs como sean necesarios  
      - Para modo inmediato:  
        - guarda un único VAO  
  
### Envío de vértices y atributos  

10-10-20
### Visualización y parámetros
- **glPolygonMode(GL_FRONT_AND_BACK, nuevo_modo)**: cambia el modo de visualización de polígonos.
  - Por defecto, __GL_GILL__
  - **nuevo_modo** es de tipo **GLenum**
- ---
- Para los errores, declaramos una macro  
  - Si hay mucho código, se pone una en principio y otra al final
    - Si da error al final, ponemos una en medo a ver que tal 

- **glViewport:** De todos los pixeles de la ventana, en cuales vamos a dibujar (rasterizar)
  - La función se llama en la __FGE_CambiaTamano__
- Inicialmente, OpenGL usa una proyección paralela al eje Z.  
- 

## Sección 4: Programación básica del Cauce
En la practicas esto no lo haremos 
### Cauce Gráfico. Tipos. Shaders.  
- **Transformación:** 
- **Sombreado:**
  - Shaders:
      - Procesador de vértices (vertex shader)
      - Procesador de fragmentos (pixeles) (fragment shader)  
- **Tipos de cauce gŕafico:**  
  - **Cauce de funcionalidad fija**
    - shaders predefinidos en OpenGL
  - **Cauce programable**
    - Se programan los shaders; Se compilan y enlazan en tiempo de ejecución; más flexible y eficiente

## Sección 5: Apéndice matemático  



# Tema2:  

### Mayas indexadas  
Una ED que contiene información sobre una maya de triángulos en 3d. 
- contiene:
  - Tabla de vertices
  - Tabla de triáungos  

# PRÁCTICAS
## Práctica 1  
- Crear ED derivados de maya indexada
- Inicializar el constructor 
- Implementar tres métodos de viisualización 
- El código fuente está dado en Teoria --> copiarlos entendiendo
- No tenemos el método de visualización de la maya --> Pensarlo 
- En función del modo de envío actual, llamar a una de las funcioens del array de vérties
- Pensar la topología y la geometría de la maya del tetraedro --> vértices, tuplas etc para construir la tabla de triángulos
- 