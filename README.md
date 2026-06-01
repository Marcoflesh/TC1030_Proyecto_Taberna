# TC1030_Proyecto_Taberna

**Marco Antonio Hernández Roque**  
Sistema de gestión para una taberna/bar desarrollado en C++ como proyecto final de la materia **TC1030 (Programación Orientada a Objetos)**. 

---

## ¿De qué trata?
Es un juego/sistema de gestión de una taberna/bar en el que se podría ser tanto cliente como empleado. Dependiendo la opción que se escoja se implementará un listado de opciones por hacer, en el caso de los `Empleado` se podría agregar/quitar/modificar cualquier bebida que esté dentro del inventario, se puede ver la información de cada bebida, se puede contratar/modificar a un empleado al igual que registrar/modificar un cliente nuevo. Si se escoge la opción de `Cliente`, este puede interactuar con el bar mediante ver la carta, comprar x cantidad de bebidas, pagar su cuenta o inclusive ver información más detallada de una bebida en específico.
##### Todo esto es realizado mediante el manejo de archivos .txt para la permanencia de los cambios de los datos, al igual que el manejo de la programación orientada a objetos en C++ mediante el uso de clases. 

---

## Requisitos

- Compilador **g++**
- Preferentemente sistema operativo **Windows** (para mostrar correctamente acentos y caracteres especiales en la consola)
- Todos los archivos `.txt` deben estar en la **misma carpeta** que el ejecutable al momento de correr el programa
- En caso de ejecutar el programa en Linux, se tiene que entrar al archivo `main.cpp` y eliminar el código de abajo para poder ejecutar debidamente el programa
  ```
  #include <Windows.h>
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  setlocale(LC_NUMERIC, "C");
  ```

---

## Instalación `g++` para Compilar código

Link de tutorial para instalar el compilador g++ para poder ejecutar el proyecto
- https://code.visualstudio.com/docs/languages/cpp#_example-install-mingwx64

---

## Instalación y ejecución del programa

1. Descarga el repositorio como `.zip` y descomprimirlo.
  
2. Abre una terminal (PowerShell o CMD) y navega a la carpeta:
   ```
   cd ruta\a\la\carpeta
   ```
3. Compila:
   ```
   g++ main.cpp -o taberna
   ```
4. Ejecuta:
   ```
   .\taberna.exe
   ```

---

## Acceso administrador

|        |             |
|-------------|------------------|
| Usuario     | `Marcoflecha`    |
| Contraseña  | `TabernaMou123`  |

---

## Estructura del proyecto

```
── main.cpp        — Punto de entrada y menús de navegación
── Bebidas.h       — Clase base Bebida y 7 subclases (Cerveza, Mezcal, Ron, Tequila, Vino, Vodka, Whiskey)
── Personas.h      — Clase base Persona, Cliente y Empleado
── Licoreria.h     — Clase central: gestión de inventario, personal y clientes
── Bebidas.txt     — Inventario persistente
── Clientes.txt    — Registro persistente de clientes
── Empleados.txt   — Registro persistente de empleados
```

---

## Formato de los archivos `.txt`

Los archivos se reescriben completos al guardar usando un archivo temporal (`_tmp.txt`) para evitar pérdida de datos si el programa falla a mitad del proceso.

---

## Casos que hacen que el programa deje de funcionar

### Uso de Linux

| Situación | Efecto |
|---|---|
|**Compilar el código sin haber cambiado main** | Al no borrar las líneas de código que se mencionaron en los `Requisitos`, el programa no compila y por ende, no se puede ejecutar |

### Entradas inválidas desde la consola

| Situación | Efecto |
|---|---|
| **Escribir una letra donde se espera un número** (edad, stock, índice, opción de menú) | `cin` entra en estado de error. Los siguientes `cin >>` se saltan sin leer nada, causando que variables queden sin inicializar o con basura, lo que puede crashear el programa en la siguiente operación |
| **Escribir espacios en campos de texto** usando `cin >>` | `cin` corta en el primer espacio. El resto de la palabra queda en el buffer y se lee como el siguiente campo, desalineando todos los inputs siguientes |
| **Dejar el campo vacío** y presionar Enter en un `cin >>` numérico | `cin` espera indefinidamente provocando un bucle infinito |

### Archivos `.txt`

| Situación | Efecto |
|---|---|
| **Falta un archivo `.txt`** al iniciar el programa | `cargar` detecta `!is_open()` y retorna; el vector queda vacío. Cualquier intento de acceder crashea con comportamiento indefinido |
| **Una línea del archivo tiene menos columnas de las esperadas** | `stoi()` / `stod()` recibe un `string` vacío y lanza `std::invalid_argument`, terminando el programa abruptamente |
| **El archivo contiene una coma dentro de un campo** (ej. `Vino, Cerveza y Whiskey`) | El `getline(ss, campo, ',')` lo parte en dos, desalineando todos los campos siguientes de esa línea |
| **Ejecutar el programa desde una carpeta diferente a donde están los `.txt`** | Los archivos no se encuentran, los vectores quedan vacíos y el programa corre sin datos |

---

## Referencias bibliográficas

- GeeksforGeeks. (2023). *File handling in C++*. https://www.geeksforgeeks.org/file-handling-c-classes/
- GeeksforGeeks. (2023). *Vector in C++ STL*. https://www.geeksforgeeks.org/vector-in-cpp-stl/
- GeeksforGeeks. (2023). *getline() function in C++*. https://www.geeksforgeeks.org/getline-string-c/
- Stack Overflow. (2012). *How to read a file line by line in C++*. https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
- Stack Overflow. (2011). *Why does cin >> skip leading whitespace but getline does not?* https://stackoverflow.com/questions/5739937/using-getlinecin-s-after-cin
- Stack Overflow en Español. (2018). *Leer/escribir caracteres especiales del español (acentos, ñ) en una aplicación C++ en Windows*. https://es.stackoverflow.com/questions/151363/leer-escribir-caracteres-especiales-del-espa%C3%B1ol-acentos-%C3%B1-en-una-aplicaci
