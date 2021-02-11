# PRACTICA 8: Automatas Finitos No Deterministas 
8.1. Objetivos
Consolidar los conocimientos adquiridos sobre Automatas Finitos No Deterministas ´
(NFAs).
Implementar en C++ una clase para representar NFAs.
Profundizar en las capacidades de disenar y desarrollar programas orientados a ˜
objetos en C++.
8.2. Rúbrica de evaluacion del ejercicio ´
Se senalan a continuaci ˜ on los aspectos m ´ as relevantes (la lista no es exhaustiva) ´
que el profesorado tendra en cuenta a la hora de evaluar el trabajo que el alumnado ´
presentara en la sesi ´ on de evaluaci ´ on de la pr ´ actica: ´
El alumnado ha de acreditar conocimientos para trabajar con la shell de GNU/Linux
en su VM.
El alumnado ha de acreditar capacidad para editar ficheros remotos en la VM de la
asignatura usando VSC.
El codigo ha de estar escrito de acuerdo al est ´ andar de la gu ´ ´ıa de Estilo de Google
para C++
El programa desarrollado debera compilarse utilizando la herramienta make y un ´
fichero Makefile, separando los ficheros de declaracion ( ´ *.h) y definicion ( ´ *.cc) de
clases.
El comportamiento del programa debe ajustarse a lo solicitado en este documento.
Ha de acreditarse capacidad para introducir cambios en el programa desarrollado.
1
Modularidad: el programa ha de escribirse de modo que las diferentes funcionalidades
que se precisen sean encapsuladas en funciones y/o metodos cuya extensi ´ on´
textual se mantenga acotada.
El programa ha de ser fiel al paradigma de programacion orientada a objetos. ´
Se requiere que, en la sesion de evaluaci ´ on de la misma, todos los ficheros con ´
codido fuente se alojen en un ´ unico directorio junto con el fichero Makefile de ´
compilacion. ´
Se requiere que todos los atributos de las clases definidas en el proyecto tengan
un comentario descriptivo de la finalidad del atributo en cuestion. ´
Se requiere que los comentarios del codigo fuente sigan el formato especificado ´
por Doxygen [1].
Utilice asimismo esta [2] referencia para mejorar la calidad de la documentacion de ´
su codigo fuente. ´
Si el alumnado tiene dudas respecto a cualquiera de estos aspectos, debiera acudir al
foro de discusiones de la asignatura para plantearlas all´ı. Se espera que, a traves de ese ´
foro, el alumnado intercambie experiencias y conocimientos, ayudandose mutuamente ´
a resolver dichas dudas. Tambien el profesorado de la asignatura intervendr ´ a en las ´
discusiones que pudieran suscitarse, si fuera necesario.
8.3. Introduccion´
Un Automata Finito No Determinista ´ , AFN (o NFA de su denominacion en ingl ´ es´
Non-Deterministic Finite Automaton) suele introducirse como una modificacion de un ´
Automata Finito Determinista (DFA) en el que se permitir ´ an cero, una o m ´ as transiciones ´
desde un estado con un mismo s´ımbolo del alfabeto de entrada.
Formalmente, un Automata Finito No Determinista ´ se define por una qu´ıntupla
(Σ, Q, q0, F, δ) donde cada uno de estos elementos tiene el siguiente significado:
Σ es el alfabeto de entrada del automata. Se trata del conjunto de s ´ ´ımbolos que el
automata acepta como entradas. ´
Q es el conjunto finito y no vac´ıo de los estados del automata. El aut ´ omata siempre ´
se encontrara en uno de los estados de este conjunto. ´
q0 es el estado inicial o de arranque del automata ( ´ q0 ∈ Q). Se trata de un estado
distinguido. El automata se encuentra en este estado al comienzo de la ejecuci ´ on. ´
F es el conjunto de estados finales o de aceptacion del aut ´ omata ( ´ F ⊆ Q). Al final
de una ejecucion, si el estado en que se encuentra el aut ´ omata es un estado final, ´
se dira que el aut ´ omata ha aceptado la cadena de s ´ ´ımbolos de entrada.
2
δ es la funcion de transici ´ on. En este caso, y a diferencia de lo que ocurre en los ´
DFAs, la funcion de transici ´ on es una relaci ´ on: ´
δ : Q × (Σ ∪ {}) → 2
Q;
(q, σ) → {q1, q2, . . . , qn} tal que q ∈ Q, σ ∈ (Σ ∪ {})
Esto es, se asigna a un par (q, σ) un elemento de 2
Q (partes de Q, es decir, el
conjunto de todos los subconjuntos de Q).
8.4. Objetivo
Esta practica consistir ´ a en la realizaci ´ on de un programa escrito en C++ que ´
lea desde un fichero las especificaciones de un NFA y, a continuacion, simule el ´
comportamiento del automata para una cadena que se suministre como entrada. ´
Tal y como ya se ha mencionado, se puede considerar un NFA como una modificacion´
de un DFA en el que se permiten cero, una o varias transiciones desde un estado con
un s´ımbolo del alfabeto. Otra diferencia de los NFAs con respecto a los DFAs es que los
NFAs pueden tener transiciones vac´ıas (transiciones etiquetadas con la cadena vac´ıa),
permitiendo al automata transitar de un estado a otro sin necesidad de entrada, esto es, ´
sin consumir s´ımbolos de la cadena de entrada. El no determinismo viene dado porque
el automata puede transitar con una misma entrada hacia un conjunto de diferentes ´
estados. Este conjunto de estados puede incluso ser vac´ıo.
8.5. Especificacion de NFAs ´
Un NFA vendra definido en un fichero de texto con extensi ´ on´ .nfa. Un fichero .nfa
debera tener el siguiente formato: ´
L´ınea 1: Numero total de estados del NFA ´
L´ınea 2: Estado de arranque del NFA
A continuacion figurar ´ a una l ´ ´ınea para cada uno de los estados. Cada l´ınea
contendra los siguientes n ´ umeros, separados entre s ´ ´ı por espacios en blanco:
• Numero identificador del estado. Los estados del aut ´ omata se representar ´ an´
mediante numeros naturales. La numeraci ´ on de los estados corresponder ´ a a ´
los primeros numeros comenzando en 0. ´
• Un 1 si se trata de un estado de aceptacion y un 0 en caso contrario. ´
• Numero de transiciones que posee el estado. ´
• A continuacion, para cada una de las transiciones, y utilizando espacios en ´
blanco como separadores, se detallara la informaci ´ on siguiente: ´
3
◦ S´ımbolo de entrada necesario para que se produzca la transicion. Para ´
representar la cadena vac´ıa (el no consumir s´ımbolo de la entrada) se
utilizara el car ´ acter (c ´ odigo ASCII 126). ´
◦ Estado destino de la transicion. ´
A modo de ejemplo, en la Figura 8.1 se muestra un NFA junto con la definicion del ´
mismo especificada mediante un fichero .nfa
Figura 8.1: Especificacion de un NFA de ejemplo ´
El programa debera detectar (y notificar al usuario de forma adecuada) si existe alg ´ un´
error en la definicion del aut ´ omata. Esto es, habr ´ ´ıa que analizar que se cumplen las
siguientes condiciones:
Existe uno y solo un estado inicial para el aut ´ omata. ´
Hay una l´ınea en el fichero por cada uno de los estados del automata. Esto ´
implica que para aquellos estados que no tengan transiciones salientes, debera´
indicarse en la l´ınea correspondiente del fichero, que el estado en cuestion tiene ´
cero transiciones.
8.6. Funcionamiento del programa
El programa debe ejecutarse como:
$ . / nfa_simulation input . nfa input . txt output . txt
Donde los tres parametros pasados en la l ´ ´ınea de comandos corresponden en este
orden con:
Un fichero de texto con extension´ .nfa en el que figura la especificacion de un NFA. ´
Un fichero de texto con extension´ .txt en el que figura una serie de cadenas (una
cadena por l´ınea) sobre el alfabeto del NFA especificado en el fichero input.nfa.
4
Un fichero de texto de salida con extension´ .txt en el que el programa ha de
escribir las mismas cadenas del fichero de entrada seguidas de un texto -- S´ı /
No indicativo de la aceptacion (o no) de la cadena en cuesti ´ on. Este fichero debe ´
ser sobreescrito por el programa en cada ejecucion. ´
Tal y como se ha solicitado en practicas anteriores, el comportamiento del programa ´
al ejecutarse en l´ınea de comandos debiera ser similar al de los comandos de Unix. As´ı
por ejemplo, si se ejecuta sin parametros el comando ´ grep en una terminal Unix (se
recomienda estudiar este programa) se obtiene:
$ grep
Modo de empleo: grep [OPCI´ON]... PATR´ON [FICHERO]...
Pruebe ’grep --help’ para m´as informaci´on.
En el caso del programa a desarrollar:
$ ./nfa_simulation
Modo de empleo: ./nfa_simulation input.nfa input.txt output.txt
Pruebe ’nfa_simulation --help’ para m´as informaci´on.
La opcion´ --help en l´ınea de comandos ha de producir que se imprima en pantalla
un breve texto explicativo del funcionamiento del programa.
8.7. Detalles de implementacion´
La idea central de la Programacion Orientada a Objetos, OOP ( ´ Object Oriented
Programming) es dividir los programas en piezas mas peque ´ nas y hacer que cada ˜
pieza sea responsable de gestionar su propio estado. De este modo, el conocimiento
sobre la forma en que funciona una pieza del programa puede mantenerse local a esa
pieza. Alguien que trabaje en el resto del programa no tiene que recordar o incluso ser
consciente de ese conocimiento. Siempre que estos detalles locales cambien, solo el ´
codigo directamente relacionado con esos detalles precisa ser actualizado. ´
Las diferentes piezas de un programa de este tipo interactuan entre s ´ ´ı a traves´
de lo que se llama interfaces: conjuntos limitados de funciones que proporcionan una
funcionalidad util a un nivel m ´ as abstracto, ocultando su implementaci ´ on precisa. Tales ´
piezas que constituyen los programas se modelan usando objetos. Su interfaz consiste
en un conjunto espec´ıfico de metodos y atributos. Los atributos que forman parte de ´
la interfaz se dicen publicos. Los que no deben ser visibles al c ´ odigo externo, se ´
denominan privados. Separar la interfaz de la implementacion es una buena idea. Se ´
suele denominar encapsulamiento.
C++ es un lenguaje orientado a objetos. Si se hace programacion orientada a objetos, ´
los programas forzosamente han de contemplar objetos, y por tanto clases. Cualquier
programa que se haga ha de modelar el problema que se aborda mediante la definicion´
de clases y los correspondientes objetos. Los objetos pueden componerse: un objeto
5
“coche” esta constituido por objetos “ruedas”, “carrocer ´ ´ıa” o “motor”. La herencia es
otro potente mecanismo que permite hacer que las clases (objetos) herederas de una
determinada clase posean todas las funcionalidades (metodos) y datos (atributos) de la ´
clase de la que descienden. De forma inicial es mas simple la composici ´ on de objetos ´
que la herencia, pero ambos conceptos son de enorme utilidad a la hora de desarrollar
aplicaciones complejas. Cuanto mas compleja es la aplicaci ´ on que se desarrolla mayor ´
es el numero de clases involucradas. En los programas que desarrollar ´ a en esta ´
asignatura sera frecuente la necesidad de componer objetos, mientras que la herencia ´
tal vez tenga menos oportunidades de ser necesaria.
Tenga en cuenta las siguientes consideraciones:
No traslade a su programa la notacion que se utiliza en este documento, ni en la ´
teor´ıa de Automatas Finitos. Por ejemplo, el cardinal del alfabeto de su aut ´ omata ´
no debiera almacenarse en una variable cuyo identificador sea N. Al menos por
dos razones: porque no sigue lo especificado en la Gu´ıa de Estilo respecto a la
eleccion de identificadores y m ´ as importante a ´ un, porque no es significativo. No ´
utilice identificadores de un unico car ´ acter, salvo para situaciones muy concretas. ´
Favorezca el uso de las clases de la STL, particularmente std::array, std::vector
o std::string frente al uso de estructuras dinamicas de memoria gestionadas a ´
traves de punteros. ´
Construya su programa de forma incremental y depure las diferentes funcionalidades
que vaya introduciendo.
En el programa parece ineludible la necesidad de desarrollar una clase Nfa. Estudie
las componentes que definen a un NFA y vea como trasladar esas componentes a ´
su clase Nfa.
Valore analogamente qu ´ e otras clases identifica Ud. en el marco del problema ´
que se considera en este ejercicio. Estudie esta referencia [3] para practicar la
identificacion de clases y objetos en su programa. ´
6
Bibliograf´ıa
[1] Doxygen http://www.doxygen.nl/index.html
[2] Diez consejos para mejorar tus comentarios de
codigo fuente ´ https://www.genbeta.com/desarrollo/
diez-consejos-para-mejorar-tus-comentarios-de-codigo-fuente
[3] Como identificar clases y objetos ´ http://www.comscigate.com/uml/DeitelUML/
Deitel01/Deitel02/ch03.htm
