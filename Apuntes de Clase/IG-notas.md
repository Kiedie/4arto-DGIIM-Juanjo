# Ingeniería Gráfica  

# Tema 1

## Sección 2: Proceso de visualización  
- Dos algoritmos para visualizar imágenes: rasterización y ray-tracing 
- __Programa gráfico__ --> almacena ED con modelo --> Salida: imagen
- __Imágenes Raster:__ array de pixeles por filas y columnas y cada pixel tiene un color RGB  
- __Imágenes vectoriales:__ archivos.svg. La información se codifica a un nivel más alto.
    - Una img vect tiene lista de segmentos o curvas con una serie de parámetros numéricos.
- __Interactive Grafic Program__ --> Visualiza una imagen que responde a eventos (acciones del usuario) --> Timepos de espera de ms
- __Non-Interactive Grafic Program:__ Modelo --> Salidas: imágenes con duración s<-->horas  
- __Proceso de visualización:__ Modelo de escena y parámetros
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
            -Proyección: perspectiva o paralela

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
- Los polígonos se pueden visualizar como:
  - Puntos
  - Líneas
  - Relleno  
- Se debe cumlir:
  - Vertices en el mismo plano
  - No se deben intersecar las aristas
  - Deben ser convexos
- Problema de vértices replicados: se repiten coordenadas
  - Solución: Secuencias indexadas
    - Vn --> Secuencia con los vértices
    - Im --> secuencia de índices (enteros) que dicta la unión de puntos de Vn  

__IMPORTANTE__: no confundir la constante __GL_Line__ con __GL_Lines__
### Atributos de vértices   
- **Coordenadas de su posición**
- **color**: RGB entre 0 y 1
- **Normal**: vector qued etermina la orientación (para iluminacion)  
- **Coordenadas de textura**
- **Valores:**
  - Todo vertice --> (posicion,color,normal,coord_textura)  

### Modos de envío  
Si queremos visualizar la secuencia de vertices o atributos:  
- Modo inmediato
  - Una llamada por vértice y atributo:
    - Lento
    - Cordenadas y atributos vértice a vértice
  - Una llamada para varios vérties con todos sus atributos
  - No almacena coordenadas, por tanto, para visualizar más de una vez es necesario enviar las mismas coordenadas cad vez  
- Modo diferido: 
  - Una única llamda, previamente trasladar las cosas de la RAM a la GPU
  - Reservar memoria en la GPU  

### Almacenamiento de vértices y atributos  
- Array de estructuras (AOS):
  - Array o vector  
  - Cada entrada tiene:
    - Coordenadas de sus vertices
    - Atributos
- Estructura de Arrays (SOA):
  - Estructura con punteros a arrays 
  - Los arrays contienen:
    - uno para coordenadas
    - otros para los atributos  
    - Echarle un ojo a lo de los descriptores de la tabla
------------------------------------------------- 
- Vertex Array Objects:   
      - Estructura de datos    
      - Para modo diferido:  
        - Crea tantos VAOs como sean necesarios  
      - Para modo inmediato:  
        - guarda un único VAO  
  
### Envío de vértices y atributos  



## Sección 4
## Sección 5  

# Tema2:  

### Mayas indexadas  
Una ED que contiene información sobre una maya de triángulos en 3d. 
- contiene:
  - Tabla de vertices
  - Tabla de triáungos