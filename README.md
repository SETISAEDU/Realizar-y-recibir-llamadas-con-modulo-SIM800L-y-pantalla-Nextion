# Realizar-y-recibir-llamadas-con-modulo-SIM800L-y-pantalla-Nextion
Repositorio de archivos utilizados en el proyecto para realizar y recibir llamadas con el modulo SIM800L combinado con la pantalla Nextion y Arduino

# Diagrama de conexión
![Diagrama](https://raw.githubusercontent.com/SETISAEDU/Realizar-y-recibir-llamadas-con-modulo-SIM800L-y-pantalla-Nextion/master/SIM800L_NEXTION_PhoneCall_Diagrama.png)


**Antes de iniciar, considere insertar una tarjeta SIM con saldo al módulo SIM800L para poder realizar el tutorial presentado acontinuacion**

En la continuacion de aplicaciones utilizando el modulo `SIM800L` y la pantalla Nextion es presentada una nueva propuesta de un sistema de comunicacion. Utilizando la funcion de llamadas de nuestro modulo SIM800L podemos realizar y recibir llamadas, alojar contactos, y poder identificar el numero de una llamada entrante. La aplicacion es muy sencilla de implementar gracias a los pines de entrada diferencial para microfono, al igual que los pines de salida diferencial para una bocina que posee nuestro modulo SIM800L.
Como en aplicaciones anteriores se desarrollo una interfaz grafica para ser mostrada en nuestra patalla Nextion, esto gracias al software de edicion `Nextion Editor`. Nuetro sistema carga un menu principal con 2 opciones. La primera para realizar llamadas por marcacion directa, haciendo uso de un teclado numerico. La segunda opcion nos permite alojar hasta 3 contactos con el nombre y numero telefonico. Estos contactos pueden ser editados o eliminados por completo si asi se desea. Cada contacto posee un boton de llamada directa al contacto lo cual hace mas facil la tarea de llamar a un numero telefonico.
