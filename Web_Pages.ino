void startServer () {
  Serial.print("Starting server");
  server.on("/", handleRoot);
  Serial.write('.');
  server.on("/chat", handleChatPage);
  Serial.write('.');
  server.on("/addmessage", handleChatAddPage);
  Serial.write('.');
  server.onNotFound(handleNotFound);
  Serial.write('.');
  server.begin();
  Serial.write('.');
  Serial.println(" done");
}

void handleRoot () {
  Serial.print("Request to '/':");
  String message = "<html><title>Hi</title>";
  message += "<a href=/chat>Chat</a><br>";
  message += "<a href=/addmessage>Add chat message</a></html>";
  server.send(200, "text/html", message);
  Serial.println(" done");
}

void handleNotFound () {
  Serial.print("Not found:");
  String message = "File Not Found\n\n";
  message += "URI: ";
  String Uri = server.uri();
  message += Uri;
  server.send(404, "text/plain", message);
  //  Serial.println(" done");
  //  Serial.print("URI: ");
  Serial.println(Uri);
}

String chat = "";

void handleChatPage () {
  Serial.print("Request to '/chat':");
  String message = "<html><title>Chat</title>";
  //  message += "<head style='font-size:72px'>Chat</head>";
  message += "<head><h1 style='font-size:40px'><span style='text-decoration: underline;'>Chat</span><br>";
  message += "<a href='/' style='font-size:14px'>Main page</a></h1></head><body>"; // <p></p>
  message += "<p style='font-size:22px'>";
  message += chat;
  message += "</p></body></html>";
  server.send(200, "text/html", message);
  Serial.println(" done");
}

//void handleChatPage () {
//  Serial.print("Request to '/chat':");
//
//  Serial.println(" done");
//}
//<input type="submit" value="Submit">

void handleChatAddPage () {
  Serial.print("Request to '/addmessage':");

  String n = server.arg("name");
  String s = server.arg("subject");
  String m = server.arg("message");

  if (n != "" && s != "" && m != "") {
    Serial.println("Message recieved:");
    Serial.println("  Args: " + String(server.args()));
    Serial.println("  Subject: " + s);
    Serial.println("\n  Message: " + m + "\n");
    Serial.println("  Name: " + n);
    //    chat += s + "<br>";
    //    String htmlMessage = m;
    //    htmlMessage.replace("\n", "<br>");
    //    chat += "<span style='font-size:12px'>" + htmlMessage + "</span><span style='font-size:10px'><br>Posted by: " + n + "</span>";
    //    chat += "<br><br>";
    addToChat(n, s, m);
    String redirect = "<head><meta charset='UTF-8'><meta http-equiv='refresh' content='1; url='";
    redirect += redirectURL;
    redirect += "'><script type='text/javascript'>window.location.href = '";
    redirect += redirectURL;
    redirect += "'</script><title>Page Redirection</title></head><body>If you are not redirected automatically, follow this <a href='";
    redirect += redirectURL;
    redirect += "'>link to the chat page</a>.</body>";
    server.send(200, "text/html", redirect);
  } else {
    Serial.print(" No message...");
    //  String message = "<html><title>Add Chat Message</title>";
    //  message += "<body><a href='/'>Main page</a>";
    String message = "<html><title>Add Chat Message</title>";
    message += "<head><h1 style='font-size:40px'><span style='text-decoration: underline;'>Add Message</span><br>";
    message += "<a href='/' style='font-size:14px'>Main page</a></h1></head><body>"; // <p></p>
    message += "<form method=get>";
    message += "Name: <input type='text' name='name' placeholder='Name:'><br>";
    message += "Subject: <input type='text' name='subject' placeholder='Subject:'><br>";
    //  message += "Message: <input type='text' name='message' style='height:200px;width:200px;'><br>";
    message += "Message: <br><textarea cols='50' rows='4' name='message' placeholder='Your message:'></textarea><br>";
    message += "<input type='submit' value='Send Message'>";
    message += "</form></body></html>";
    server.send(200, "text/html", message);
    Serial.println(" done");
    //  WifiClient cl = server.available();
  }
}

//String readHeader (WiFiClient cl) {
//  for (int i = 0; true; i++) {
//    String HttpHeader = "";
//    char c = cl.read();
//    //read MaxHeaderLength number of characters in the HTTP header
//    //discard the rest until \n
//    if (HttpHeader.length() < MaxHeaderLength)
//    {
//      //store characters to string
//      HttpHeader = HttpHeader + c;
//    } else {
//      Serial.println(HttpHeader);
//      return HttpHeader;
//    }
//    //if HTTP request has ended
//    if (c == '\n') {
//      // show the string on the monitor
//      Serial.println(HttpHeader);
//      return HttpHeader;
//    }
//    Serial.println(i);
//  }
//}

void addToChat (String n, String s, String m, bool allowAdmin) {
  if (allowAdmin || checkName(n)) {
    chat += s + "<br>";
    chat += "<span style='font-size:12px'>" + htmlFormat(m) + "</span><span style='font-size:10px'><br>Posted by: " + n + "</span>";
    chat += "<br><br>";
  } else {
    Serial.println("Illegal name:");
    Serial.println(n);
  }
}

String htmlFormat (String m) {
  String htmlMessage = m;
  htmlMessage.replace("\n", "<br>");
  return htmlMessage;
}

bool checkName (String n) {
  String na = n;
  na.toUpperCase();
  na.replace(" ", "");
  na.replace("  ", "");
  na.replace(".", "");
  String ns = na;
  na.replace("ADMIN", "");
  na.replace("SERVER", "");
  bool goodName1 = na == ns;
  bool goodName2 = (na != "ADMIN") && (na != "A") && (na != "AD") && (na != "ADM") && (na != "ADMI") && (na != "ADMINISTRATION");
  bool goodName = goodName1 && goodName2;
  return goodName;
}

void serverMessageSend(String m, String s) {
  addToChat("Server", s, m, true);
}

