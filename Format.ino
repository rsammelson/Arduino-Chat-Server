String htmlFormat (String m) {
  String htmlMessage = m;
  htmlMessage.replace("\n", "<br>");
  return htmlMessage;
}

String htmlRemove (String m) {
  String me = m;
  me.replace("<", "<!--");
  me.replace(">", "-->");
  return me;
}

