/* Gadget version 0.1.3 

Hardware:
- MKR1000 / MKR1010 / MKRVIDOR4000 / Nano 33 IoT
- MKR ENV shield
- Water pump 3-6V
- Neo pixel ring, 12 pixels

Description:
This example connects to a Wi-Fi network,
hosts a web server which then can be accessed
from the browser.

The web-server contains a set of HTML elements
that are styled using an external spreadsheet 
hosted at GitHub pages. 

The basic function is that when each button is pressed,


*/

#include <WiFiNINA.h>
#include <Arduino_MKRENV.h>
#include <Adafruit_NeoPixel.h>

#define PIN 5
#define NUMPIXELS 12

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char ssid[] = "The_Shed";            //  your network SSID (name) between the " "
char pass[] = "ecamlndk";            // your network password between the " "
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS; //connection status
WiFiServer server(80);       //server socket

WiFiClient client = server.available();

int pump = 9;

int temperature;
int humidity;
int moisture;

int k = 0;
bool change = false;
int light_intensity = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(pump, OUTPUT);

    strip.begin();          // INITIALIZE NeoPixel strip object 
    strip.show();           // Turn OFF all pixels
    strip.setBrightness(0); // Set BRIGHTNESS 

    //uncomment line below to run rest of program ONLY if Serial Monitor opens
    //while(!Serial);

    if (!ENV.begin())
    {
        Serial.println("Failed to initialize MKR ENV shield!");
        // while (1);
    }

    enable_WiFi();
    connect_WiFi();
    welcome_serial();
    server.begin();
}

void loop()
{
    client = server.available();
    temperature = ENV.readTemperature();
    humidity = ENV.readHumidity();

    int moistureRaw = analogRead(A1);
    moisture = map(moistureRaw, 0, 1023, 100, 0);

    if (client)
    {
        printWEB();
    }
}

void printWifiStatus()
{
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

void enable_WiFi()
{
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE)
    {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true)
            ;
    }

    String fv = WiFi.firmwareVersion();
    if (fv < "1.0.0")
    {
        Serial.println("Please upgrade the firmware");
    }
}

void connect_WiFi()
{
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }
}

void welcome_serial()
{
    Serial.println();
    Serial.println("|||||    Gadget     |||||");
    Serial.println("||||| version 0.1.3 |||||");
    Serial.println("|||||||||||||||||||||||||");
    Serial.println();
    Serial.println("> A simple user interface for Arduino.");
    Serial.println("> Once connection is successful, you're good to go.");
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

void printWEB()
{

    if (client)
    { // if you get a client,
        // Serial.println("new client");           // print a message out the serial port
        String currentLine = ""; // make a String to hold incoming data from the client
        while (client.connected())
        { // loop while the client's connected
            if (client.available())
            {                           // if there's bytes to read from the client,
                char c = client.read(); // read a byte, then
                //Serial.write(c);                    // print it out the serial monitor
                if (c == '\n')
                { // if the byte is a newline character

                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0)
                    {

                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        //BEGIN HTML -->
                        client.println("<!DOCTYPE HTML>");

                        //uncomment below line to refresh every 5 seconds
                        //client.println("<meta http-equiv=\"refresh\" content=\"5\">");
                        client.print("<head>");

                        client.print("<link href='https://fonts.googleapis.com/css2?family=Barlow:wght@100&display=swap' rel='stylesheet'>");
                        client.print("<link href='https://karlsoderby.github.io/portfolio/style.css' rel='stylesheet' type='text/css'>");
                        client.print("<style> h1{margin-top: 0;} .sensordata {text-align: center; font-size: 72px; font-family: 'Barlow', sans-serif; color: white; padding-top: 20px;}</style>");
                        client.print("<script src='https://kit.fontawesome.com/0a4ce480d6.js'></script>");
                        client.print("</head>");

                        client.print("<body><div class='wrap'><h1>GADGET</h1><br><p class='center'>");
                        client.print("<button class='action' type='submit' onmousedown='location.href=\"/T\"'><i class='fas fa-seedling'></i></button><button class='action' type='submit' onmousedown='location.href=\"/O\"'><i class='far fa-lightbulb'></i></button></p><br>");

                        if (change == false)
                        {
                            client.print("<p class='center'><button class='red' type='submit' onmousedown='location.href=\"/R\"'>UV</button><button class='green' type='submit' onmousedown='location.href=\"/G\"'>WARM</button><button class='blue' type='submit' onmousedown='location.href=\"/B\"'>BREEZE</button></p><br>");
                            client.print("<p class='center'><button class='small-btn' type='submit' onmousedown='location.href=\"/Y\"'>-</button><button class='small-btn' type='submit' onmousedown='location.href=\"/F\"'><i class='far fa-gem'></i></button><button class='small-btn' type='submit' onmousedown='location.href=\"/X\"'>+</button></p>");
                            client.print("<p class='text'>");
                            client.print(light_intensity);
                            client.print(" %");
                            client.print("</p>");
                        }

                        else if (change == true)
                        {
                            client.print("<p class='center'><button class='action' type='submit' onmousedown='location.href=\"/Q\"'><i class='fas fa-faucet'></i></button></p>");
                            client.print("<p class='sensordata'>");
                            client.print(temperature);
                            client.print(" C &nbsp; | &nbsp;");
                            client.print(humidity);
                            client.print(" % &nbsp; | &nbsp;");
                            client.print(moisture);
                            client.print(" <i class='fas fa-tint'></i></p>");
                        }
                        client.println("</div></body> ");
                        // <-- END HTML

                        // The HTTP response ends with another blank line:
                        client.println();

                        // break out of the while loop:
                        break;
                    }
                    else
                    { // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {                     // if you got anything else but a carriage return character,
                    currentLine += c; // add it to the end of the currentLine
                }

                if (currentLine.endsWith("GET /X"))
                {
                    k += 25;
                    if (k >= 250)
                    {
                        k = 250;
                    }
                    strip.setBrightness(k);
                    strip.show();
                }

                if (currentLine.endsWith("GET /Y"))
                {
                    k -= 25;
                    if (k <= 0)
                    {
                        k = 0;
                    }
                    strip.setBrightness(k);
                    strip.show();
                }

                if (currentLine.endsWith("GET /Q"))
                {
                    analogWrite(pump, 130);
                    delay(1500);
                    analogWrite(pump, 0);
                }

                if (currentLine.endsWith("GET /R"))
                {
                    colorWipe(strip.Color(255, 0, 255), 50); // UV
                }
                if (currentLine.endsWith("GET /G"))
                {
                    colorWipe(strip.Color(255, 100, 40), 50); // Warm
                }

                if (currentLine.endsWith("GET /B"))
                {
                    colorWipe(strip.Color(0, 140, 185), 50); // Blue
                }

                if (currentLine.endsWith("GET /F"))
                {
                    colorWipe(strip.Color(0, 0, 0), 50); // Blue
                }

                if (currentLine.endsWith("GET /T"))
                {
                    change = true;
                }

                if (currentLine.endsWith("GET /O"))
                {
                    change = false;
                }

                light_intensity = map(k, 0, 250, 0, 100);
            }
        }
        client.stop();
    }
}

void colorWipe(uint32_t color, int wait)
{
    for (int i = 0; i < strip.numPixels(); i++)
    {                                  // For each pixel in strip...
        strip.setPixelColor(i, color); //  Set pixel's color (in RAM)
        strip.show();
        delay(wait); //  Update strip to match
    }
}
