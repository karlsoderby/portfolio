#include <WiFiNINA.h>

char ssid[] = "Annmari";             //  your network SSID (name) between the " "
char pass[] = "lakrifun";      // your network password between the " "
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;      //connection status
WiFiServer server(80);            //server socket

WiFiClient client = server.available();

//int ledPin = 2;

int r = 2;
int g = 3;
int b = 4;

int k = 0;
int color = 0;
bool change = false;
int light_intensity = 0;

String IP_ADDRESS;

void setup() {
  Serial.begin(9600);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  while (!Serial);

  enable_WiFi();
  connect_WiFi();
  welcome_serial();
  server.begin();


}

void loop() {
  client = server.available();

  if (client) {
    printWEB();
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void enable_WiFi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}

void connect_WiFi() {
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
}

void welcome_serial() {
  Serial.println();
  Serial.println("|||||    Amethyst   |||||");
  Serial.println("||||| version 0.1.1 |||||");
  Serial.println("|||||||||||||||||||||||||");
  Serial.println();
  Serial.println("> A simple user interface for Arduino. <");
  Serial.println("> Once connection is successful, you're good to go <");
  Serial.println();
  Serial.println("How to use:");
  Serial.print("1. Go to page http://");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  Serial.println("2. Select color and light intensity.");
  Serial.println("3. Click the amethyst to update board.");
  Serial.println();
  Serial.println("Have fun!");
}

void printWEB() {

  if (client) {                             // if you get a client,
    // Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<!DOCTYPE HTML>");
            //        client.println("<meta http-equiv=\"refresh\" content=\"5\">");
            client.print("<head>");
            client.print("<style> h1{margin-top: 0;} .sensordata {text-align: center; font-size: 72px; font-family: 'Barlow', sans-serif; color: white;}</style>");
            client.print("<link href='https://fonts.googleapis.com/css2?family=Barlow:wght@100&display=swap' rel='stylesheet'>");
            /*            client.print("<style>");


                        client.print("body { background-color: #8EC5FC; background-image: linear-gradient(62deg, #8EC5FC 0%, #E0C3FC 100%);}");
                        client.print("h1 { font-family: 'Barlow', sans-serif; letter-spacing: 5px; margin-top: 150px; text-align: center; font-size: 3em;}");

                        client.print("</style>");*/
            client.print("<link href='https://karlsoderby.github.io/portfolio/style.css' rel='stylesheet' type='text/css'>");

            client.print("<script src='https://kit.fontawesome.com/0a4ce480d6.js'></script>");
            client.print("</head>");

            /*  client.print("<body>");
              //create the buttons
              client.print("<h1>AMETHYST</h1>");
              client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
              client.print("Click <a href=\"/L\">here</a> turn the LED off<br><br>");
              client.print("</body>");

              int randomReading = analogRead(A1);
              client.print("Random reading from analog pin: ");
              client.print(randomReading);

              client.println("</body>");*/

            // old line (working)client.println("<body> <h1>AMETHYST</h1><br> <p class='center'><a class='center' href=\"/H\">ON</a></p> <br><br> <p class='center'><a href=\"/L\">OFF</a></p> <br><br> <button class='red' type='submit' onmousedown='location.href=\"/H\"'>RED</button> </body>");
            
            client.print("<body><div class='wrap'><h1>AMETHYST</h1><br><p class='center'>");
            client.print("<button class='red' type='submit' onmousedown='location.href=\"/T\"'><i class='fas fa-temperature-high'></i></button><button class='red' type='submit' onmousedown='location.href=\"/O\"'><i class='fas fa-gamepad'></i></button></p><br>");
            

            if (change == false) {
              client.print("<p class='center'><button class='red' type='submit' onmousedown='location.href=\"/R\"'>RED</button><button class='green' type='submit' onmousedown='location.href=\"/G\"'>GREEN</button><button class='blue' type='submit' onmousedown='location.href=\"/B\"'>BLUE</button></p><br>");
              client.print("<p class='center'><button class='small-btn' type='submit' onmousedown='location.href=\"/Y\"'>-</button><button class='small-btn' type='submit' onmousedown='location.href=\"/F\"'><i class='far fa-gem'></i></button><button class='small-btn' type='submit' onmousedown='location.href=\"/X\"'>+</button></p>");
              client.print("<p class='text'>");
              client.print(light_intensity);
              client.print(" %");
              client.print("</p>");
            }
            if (change == true) {
              client.print("<p class='sensordata'>25.87 C  |  32.67 % </p>");
            }

            client.println("<p class='text'>This interface is run on an Arduino MKR WiFi 1010 board.</p></div></body> ");


            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        if (currentLine.endsWith("GET /X")) {
          k += 25;
          if (k >= 255) {
            k = 255;
          }
          Serial.print("intensity = ");
          Serial.println(k);
        }

        if (currentLine.endsWith("GET /Y")) {
          k -= 25;

          if (k <= 0) {
            k = 0;
          }
          Serial.print("intensity = ");
          Serial.println(k);
        }


        if (currentLine.endsWith("GET /R")) {
          /*analogWrite(r, k);
            analogWrite(g, 0);
            analogWrite(b, 0);*/
          color = 1;
          Serial.print("Color= ");
          Serial.println(color);
        }
        if (currentLine.endsWith("GET /G")) {
          /*analogWrite(r, 0);
            analogWrite(g, k);
            analogWrite(b, 0);*/
          color = 2;
          Serial.print("Color= ");
          Serial.println(color);
        }

        if (currentLine.endsWith("GET /B")) {
          /*analogWrite(r, 0);
            analogWrite(g, 0);
            analogWrite(b, k);*/
          color = 3;
          Serial.print("Color= ");
          Serial.println(color);
        }

        if (currentLine.endsWith("GET /F")) {
          if (color == 1) {
            analogWrite(r, k);
        
          }
          else if (color == 2) {
            analogWrite(g, k);
          }
          else if (color == 3) {
            analogWrite(b, k);
          }

        }

        if (currentLine.endsWith("GET /T")) {
          change = true;
        }

          if (currentLine.endsWith("GET /O")) {
          change = false;
        }
        
        light_intensity = map(k, 0, 255, 0, 100);
        
      }
    }
    // close the connection:
    client.stop();
    //  Serial.println("client disconnected");
  }
}