#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

ESP8266WiFiMulti WiFiMulti;
SoftwareSerial NodeMCU(D2,D3);
 
const char* ssid = "sid";
const char* pwd = "sidd123456";
WiFiServer server(80);

void setup() 
{
  Serial.begin(9600);
  NodeMCU.begin(4800);
  delay(100);
  Serial.println();
  Serial.print("Connecting to wifi ");
  Serial.println(ssid);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("."); //progress with dots until the wifi is connected
  }
  Serial.println("");
  Serial.println("Wifi connected");
  server.begin();
  Serial.println("Server started.");
  Serial.print("This is your ip address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");  
}

void loop()
{
    WiFiClient client = server.available();
    if (!client)
    {
      return;
    }
    
    //wait for the data to be sent from client
    Serial.println("New client connection");
    while(!client.available())
    {
      delay(1);
    }

    //Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    
    HTTPClient http;
    String url = "http://192.168.43.67/";
    Serial.println(url);
    http.begin(url);
    client.println("<html>\n");
    client.println("<head>\n");
    client.println("    <title>Project Work</title>\n");
    client.println("    <style>\n");
    client.println("        body\n");
    client.println("        {\n");
    client.println("            font-family: sans-serif;\n");
    client.println("            font-size: 20pt;\n");
    client.println("            background-image: url(Pollution.jpeg);\n");
    client.println("            background-size: cover;\n");
    client.println("            background-attachment: fixed;\n");
    client.println("        }\n");
    client.println("    </style>\n");
    client.println("    <!--<style>\n");
    client.println("img {\n");
    client.println("  display: block;\n");
    client.println("  margin-left: auto;\n");
    client.println("  margin-right: auto;\n");
    client.println("}\n");
    client.println("</style>-->\n");
    client.println("</head>\n");
    client.println("<body>\n");
    client.println("    <header>\n");
    client.println("        <h1 align= \"center\">PROJECT WEBPAGE</h1>\n");
    client.println("        <h1 align= \"center\">AIR POLLUTION MANAGEMENT SYSTEM</h1>\n");
    client.println("    </header>\n");
    client.println("    <!--<img src=\"Pollution.jpeg\" style=\"width:50%;\">\n");
    client.println("    -->\n");
    client.println("<table>\n");
    client.println("    <table border=\"2\" align=\"Center\"width=\"400\" height=\"150\">    \n");
    client.println("<tr>");
    client.println("<th>Date</th><th>Temperature</th><th>Humidity</th><th>Air Quality</th><th>Status</th>");
    client.println("</tr>");        
    client.println("<tr>");
    while(client.available()>0)
    {
      float val = NodeMCU.parseFloat();
      float val1 = NodeMCU.parseFloat();
      float val2 = NodeMCU.parseFloat();     
      if(NodeMCU.read()== '\n')
      {
        client.println("<td align= \"center\">");
        client.println("7/5/2019");
        client.println("</td>");
        client.println("<td align= \"center\">");
        client.println(val);      
        client.println("</td>");
        client.println("<td align= \"center\">");
        client.print(val1);   
        client.println("</td>");
        client.println("<td align= \"center\">");
        client.print(val2);
        client.println("</td>");
        client.println("<td align= \"center\">");
        if(val2>=400)
        {
          client.print("Danger! Pollution level high");
        }
        else
        {
          client.print("Normal air");
        }
        client.println("</td>");
        delay(10000);
      }
      client.println("</tr>");
    }
    client.println("</table>\n");
    client.println("</body>\n");
    client.println("</html>");
    Serial.println("Client disconnected!");
    Serial.println("");
}
