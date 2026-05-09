# EDA_PF_PosadaSamuel_ValenciaJuan

Proyecto final del curso **Estructuras de Datos y Algoritmos** – Universidad EAFIT.

Este proyecto implementa distintos algoritmos sobre el dataset real **roadNet-PA** de SNAP (Stanford Network Analysis Project), representando la red vial del estado de Pennsylvania, Estados Unidos.

El objetivo principal es analizar el comportamiento de algoritmos de grafos sobre una red de gran escala, utilizando estructuras eficientes y comparando resultados con los valores oficiales publicados por SNAP.

---

# Integrantes

* Samuel Posada Londoño
* Juan Miguel Valencia Herrera

---

# Dataset utilizado

* Dataset: `roadNet-PA`
* Fuente: SNAP – Stanford Network Analysis Project


Estadísticas del dataset:

* 1,088,092 nodos
* 1,541,898 aristas no dirigidas
* Grafo disperso de red vial real

---

# Estructura del repositorio

```text
EDA_PF_PosadaSamuel_ValenciaJuan/
│
├── data/
│   └── roadNet-PA.txt
│
├── results/
│   ├── analisis_estructural.txt
│   ├── consultas_p2p.csv
│   ├── caminos_q01_q06.txt
│   ├── analisis_subgrafo.txt
│   └── subgrafo_caminos.txt
│
├── src/
│   ├── bfs.cpp
│   ├── consultas.cpp
│   ├── dijkstra.cpp
│   ├── graph.cpp
│   ├── graph.hpp
│   ├── loader.cpp
│   ├── main.cpp
│   ├── structural.cpp
│   └── subgraph.cpp
│
├── report/
│   └── Informe.pdf
│
└── README.md
```

---

# Representación del grafo

El grafo fue implementado utilizando **listas de adyacencia**, ya que una matriz de adyacencia para un grafo de este tamaño requeriría varios terabytes de memoria, siendo completamente inviable para un computador convencional.

Los identificadores originales del dataset fueron reindexados internamente a valores consecutivos para optimizar el acceso y el uso de memoria.

---

# Algoritmos implementados

## Módulo A — Análisis estructural

* Carga y parseo del dataset SNAP
* Construcción del grafo no dirigido
* Estadísticas estructurales
* Conteo de componentes conexas
* BFS para estimar diámetro aproximado

Salida generada:

```text
results/analisis_estructural.txt
```

---

## Módulo B — Consultas P2P

* Dijkstra con heap mínimo
* BFS no ponderado
* Comparación de tiempos
* Reconstrucción de caminos Q01 y Q06

Salida generada:

```text
results/consultas_p2p.csv
results/caminos_q01_q06.txt
```

---

## Módulo C — Subgrafo inducido

* Construcción de subgrafo usando caminos Q01 y Q06
* MST usando Kruskal
* Verificación DAG usando DFS

Salida generada:

```text
results/analisis_subgrafo.txt
results/subgrafo_caminos.txt
```

---

# Compilación

Compilar el proyecto con:

```bash
g++ -std=c++17 -O2 -o eda_pf src/main.cpp src/graph.cpp src/loader.cpp src/bfs.cpp src/dijkstra.cpp src/structural.cpp src/consultas.cpp src/subgraph.cpp
```

---

# Ejecución

## Módulo A

```bash
./eda_pf.exe A data/roadNet-PA.txt
```

## Módulo B

```bash
./eda_pf.exe B data/roadNet-PA.txt
```

## Módulo C

```bash
./eda_pf.exe C data/roadNet-PA.txt
```

---

# Ejecutar todos los módulos

```bash
./eda_pf.exe A data/roadNet-PA.txt && \
./eda_pf.exe B data/roadNet-PA.txt && \
./eda_pf.exe C data/roadNet-PA.txt
```

---

# Resultados obtenidos

Resultados estructurales principales:

| Métrica                     | Resultado |
| --------------------------- | --------- |
| Nodos                       | 1,088,092 |
| Aristas                     | 1,541,898 |
| Componente conexa principal | 1,087,562 |
| Grado promedio              | 2.834     |
| Nodo de mayor grado         | 683267    |
| Diámetro aproximado         | 782       |

---

# Herramientas utilizadas

Durante el desarrollo del proyecto se utilizaron herramientas de inteligencia artificial como apoyo técnico y de depuración.

Se utilizó:

* ChatGPT (OpenAI)
* Claude AI (Anthropic)

Principalmente para:

* Corrección de errores de compilación
* Depuración de los módulos `structural.cpp`, `consultas.cpp` y `subgraph.cpp`
* Verificación de errores de linking
* Apoyo en la construcción del README
* Retroalimentación sobre organización y redacción técnica

Todo el código fue revisado y comprendido manualmente antes de ser incorporado al proyecto final.

---

# Referencias

* Leskovec, J. & Krevl, A. (2014). SNAP Datasets: Stanford Large Network Dataset Collection.
  [http://snap.stanford.edu/data](http://snap.stanford.edu/data)

* 9th DIMACS Implementation Challenge – Shortest Paths

* Material del curso Estructuras de Datos y Algoritmos – Universidad EAFIT
