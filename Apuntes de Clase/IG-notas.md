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

# Algoritmos: Rasterización y Ray-tracing  

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

## Sección 3
## Sección 4
## Sección 5