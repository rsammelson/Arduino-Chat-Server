bool is_authenticated() {
  Serial.println("\nEnter is_authenticated");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentication Successful");
      return true;
    }
    Serial.println("Has header");
  }
  Serial.println("Authentication Failed");
  return false;
}


int level_authenticated() {
  Serial.println("Enter is_authenticated");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentication Successful 1");
      return 1;
    }
    if (cookie.indexOf("ESPSESSIONID=2") != -1) {
      Serial.println("Authentication Successful 2");
      return 2;
    }
  }
  Serial.println("Authentication Failed");
  return 0;
}
void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=0\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (checkCode(server.arg("USERNAME"), server.arg("PASSWORD"))) {
      String header = "HTTP/1.1 301 OK\r\nSet-Cookie: ESPSESSIONID=1\r\nLocation: /\r\nCache-Control: no-cache\r\n\r\n";
      server.sendContent(header);
      Serial.println("Log in Successful");
//      server.send(200, "text/html", "<html><button onclick='goBack()'>Go Back</button><script>function goBack(){window.history.back();}</script></html>");
      return;
    }
    msg = "Wrong username/password! try again.";
    Serial.println("Log in Failed");
  }
//  String content = "<html><body><form action='/login' method='POST'>To log in, please use : admin/admin<br>";
  String content = "<html><body><form action='/login' method='POST'>";
  content += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
  content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
  server.send(200, "text/html", content);
}

void authenticate () {
  if (!is_authenticated()) {
    String header = "HTTP/1.1 301 OK\r\nLocation: /login\r\nCache-Control: no-cache\r\n\r\n";
    server.sendContent(header);
    Serial.println("Not Authenticated");
  }
}

bool checkCode (String u, String p) {
  for (int i = 0; i < numUsers; i++) {
    if (users[i][0] == u) {
      if (users[i][1] == p) {
        Serial.println("Correct login");
        return true;
      } else {
        Serial.println("Wrong password");
        return false;
      }
    }
  }
  Serial.println("Unknown Username");
  return false;
}

