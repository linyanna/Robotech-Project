/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>


// include the library code:
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);


// Replace with your network credentials
char* ssid = "J.C";
const char* password = "password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";
String output28State = "off";
String output29State = "off";
char foo[] = "How are you today? "; 
int len = strlen(foo);
int i = 0;
char sad[] = "Are you feeling sad? Here is a song for you <3 "; 
int len2 = strlen(sad);
int s = 0;
char calm[] = "Do you want to relax? Here is a song for you <3 "; 
int len3 = strlen(calm);
int c = 0;
char angry[] = "Are you stressed? Here is a song for you <3 "; 
int len4 = strlen(angry);
int a = 0;
char happy[] = "Are you happy? Here is a song for you <3 "; 
int len5 = strlen(happy);
int h = 0;

// Assign output variables to GPIO pins
const int output26 = 32;
const int output27 = 33;
const int output28 = 26;
const int output29 = 25;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 200;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output28, OUTPUT);
  pinMode(output29, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output28, LOW);
  digitalWrite(output29, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
            for (i=0; i < 16; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
              
            lcd.setCursor(16,0);
            lcd.autoscroll();
            for (i=16; i < 19; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
}

            

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
              
                    
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
              digitalWrite(output27, LOW);
              digitalWrite(output28, LOW);
              digitalWrite(output29, LOW);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (s=0; s < 16; s++)
              {
                lcd.print(sad[s]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (s=16; s < 47; s++)
              {
                lcd.print(sad[s]);
                delay(300);
              }
              lcd.noAutoscroll();
              
              output27State = "off";
              output28State = "off";
              output29State = "off";              
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (i=0; i < 16; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (i=16; i < 19; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
              } 

            
            if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              digitalWrite(output26, LOW);
              digitalWrite(output28, LOW);
              digitalWrite(output29, LOW);
              output26State = "off";
              output28State = "off";
              output29State = "off";
              output27State = "on";
              digitalWrite(output27, HIGH);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (c=0; c < 16; c++)
              {
                lcd.print(calm[c]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (c=16; c < 48; c++)
              {
                lcd.print(calm[c]);
                delay(300);
              }
              lcd.noAutoscroll();
              
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (i=0; i < 16; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (i=16; i < 19; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
            } 
            
            if (header.indexOf("GET /28/on") >= 0) {
              Serial.println("GPIO 28 on");
              output28State = "on";
              digitalWrite(output26, LOW);
              digitalWrite(output27, LOW);
              digitalWrite(output29, LOW);
              output26State = "off";
              output27State = "off";
              output29State = "off";
              digitalWrite(output28, HIGH);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (h=0; h < 16; h++)
              {
                lcd.print(happy[h]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (h=16; h < 41; h++)
              {
                lcd.print(happy[h]);
                delay(300);
              }
              lcd.noAutoscroll();
            } else if (header.indexOf("GET /28/off") >= 0) {
              Serial.println("GPIO 28 off");
              output28State = "off";
              digitalWrite(output28, LOW);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (i=0; i < 16; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (i=16; i < 19; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
            } 
            
            if (header.indexOf("GET /29/on") >= 0) {
              Serial.println("GPIO 29 on");
              output29State = "on";
              digitalWrite(output29, HIGH);
              digitalWrite(output27, LOW);
              digitalWrite(output28, LOW);
              digitalWrite(output26, LOW);
              output27State = "off";
              output28State = "off";
              output26State = "off";
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (a=0; a < 16; a++)
              {
                lcd.print(angry[a]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (a=16; a < 44; a++)
              {
                lcd.print(angry[a]);
                delay(300);
              }
              lcd.noAutoscroll();
            } else if (header.indexOf("GET /29/off") >= 0) {
              Serial.println("GPIO 29 off");
              output29State = "off";
              digitalWrite(output29, LOW);
              lcd.begin(16, 2);
              lcd.setCursor(0,0);
              for (i=0; i < 16; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
              
              lcd.setCursor(16,0);
              lcd.autoscroll();
              for (i=16; i < 19; i++)
              {
                lcd.print(foo[i]);
                delay(300);
              }
            }
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Sad - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>Calm - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 28  
            client.println("<p>Happy - State " + output28State + "</p>");
            // If the output28State is off, it displays the ON button       
            if (output28State=="off") {
              client.println("<p><a href=\"/28/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/28/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 29  
            client.println("<p>Angry - State " + output29State + "</p>");
            // If the output29State is off, it displays the ON button       
            if (output29State=="off") {
              client.println("<p><a href=\"/29/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/29/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}