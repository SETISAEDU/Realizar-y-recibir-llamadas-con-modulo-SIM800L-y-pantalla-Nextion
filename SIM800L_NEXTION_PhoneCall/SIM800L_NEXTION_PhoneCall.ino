String LlamadaEntrante;
String LlamadaSaliente;
String Modo;
String EstadoDeLlamada;
bool inicio = true;
bool fin = true;


void setup()
{
  Serial.begin(19200);
  Serial1.begin(19200);             //Velocidad de comunicacion con el modulo SIM800L 
  Serial2.begin(19200);              //Velocidad de comunicacion con la Pantalla Nextion
  Serial.println("Inicializando..."); 
  Serial1.println("AT");
  HandShake();
}

void loop()
{
  if (Serial2.available())   //Comprobamos disponibilidad de datos provenientes de la pantalla Nextion.
  {
    Modo = Serial2.readStringUntil("\n");
    if(Modo.indexOf ("nuevallamada") >= 0) //Comando para realizar una nueva llamada
    {
      NuevaLlamada();       
      Modo = "";      
    } 
  }        
  else 
  {
    RecepcionDeLlamadas();
  } 
  inicio = true;  
  fin = true;
}

void HandShake() // Funcion para la lectura de comandos del SIM800L luego de relizar un handshake
{ 
  delay(500);
       
  while (Serial1.available())
  {
    String lectura=Serial1.readStringUntil("\n");
    Serial.println(lectura);        
  }  
}

void NuevaLlamada() //Funcion para realizar llamadas
{   
  while (inicio) 
  { 
    if (Serial2.available()) 
    {  
      String Numero = Serial2.readStringUntil("\n");           
      Serial1.println("ATD+ +503" + Numero + ";"); //"+503" es el codigo de area que se asigna previo al numero de telefono en El Salvador. 
                                                   //Este codigo cambia segun tu pais.
           
      while (fin) 
      {
        if (Serial2.available()) 
        {
          EstadoDeLlamada = Serial2.readStringUntil("\n");  
          if (EstadoDeLlamada.indexOf ("colgar") >= 0) 
          {
            Serial1.println("ATH");      
            inicio = false;
            fin = false; 
          }
        } 
        else if (Serial1.available()) 
        {
          EstadoDeLlamada = Serial1.readStringUntil("\n");
          if (EstadoDeLlamada.indexOf ("NO CARRIER") >= 0) //Las palabras "NO CARRIER" son datos provenientes del SIM800L 
          {                                                //cuando la llamada es finalizada por la persona con la cual nos contactamos
            Serial2.print("page 1");             
            Serial2.write(0xff);
            Serial2.write(0xff);
            Serial2.write(0xff);                                
            inicio = false;
            fin = false; 
          }               
        }                                            
      }
    }
  }
}

void RecepcionDeLlamadas() //Funcion para recibir llamadas
{
  if (Serial1.available()) 
  {
    String LlamadaEntrante = Serial1.readStringUntil("\n");      
    if (LlamadaEntrante.indexOf ("RING") >= 0 ) //Palabra RING dato proveniente del SIM800L cuando existe una llamada entrante
    {                                           //Seguido de la palabra RING se anexa el numero de la persona que emite la llamada.
      String a = LlamadaEntrante.substring(18, 26);     
      Serial2.print("page 13");             
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.print("NumIN.txt=\"");
      Serial2.print(a); 
      Serial2.print("\"");            
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
     
      while (inicio)
      {
        if (Serial2.available())
        {
          EstadoDeLlamada = Serial2.readStringUntil("\n");
          if (EstadoDeLlamada.indexOf ("contestar") >= 0)
          {
            Serial1.println("ATA");
          
            while (fin)
            {
              if (Serial2.available())
              {
                EstadoDeLlamada = Serial2.readStringUntil("\n");
                if (EstadoDeLlamada.indexOf ("colgar") >= 0)
                {
                  Serial1.println("ATH");
                  inicio = false;
                  fin = false;
                }
              }
              else if (Serial1.available())
              {
                EstadoDeLlamada = Serial1.readStringUntil("\n");
                if (EstadoDeLlamada.indexOf ("NO CARRIER") >= 0)
                {
                  Serial2.print("page 1");             
                  Serial2.write(0xff);
                  Serial2.write(0xff);
                  Serial2.write(0xff);
                  inicio = false;
                  fin = false;
                }
              }
            }
          }
          else if (EstadoDeLlamada.indexOf ("colgar") >= 0)
          {
            Serial1.println("ATH");
            inicio = false;
          }
        }
        else if (Serial1.available())
        {
          EstadoDeLlamada = Serial1.readStringUntil("\n");
          if (EstadoDeLlamada.indexOf ("NO CARRIER") >= 0)
          {
            Serial2.print("page 1");             
            Serial2.write(0xff);
            Serial2.write(0xff);
            Serial2.write(0xff);           
            inicio = false;                        
          }        
        }
      }     
    }
  }  
}
