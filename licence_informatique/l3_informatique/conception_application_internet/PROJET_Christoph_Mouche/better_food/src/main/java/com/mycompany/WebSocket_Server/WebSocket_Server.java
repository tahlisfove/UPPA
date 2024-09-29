package com.mycompany.WebSocket_Server;

/* Import to handle exceptions */
import java.io.IOException;

public class WebSocket_Server {
    
    /* Initialization of the necessary servers */
    static {
        System.setProperty("http.proxyHost", "cache.univ-pau.fr");
        System.setProperty("http.proxyPort", "3128");
    }
    
    /* My_ServerEndpoint constructor must be accessed by the WebSockets server */
    @javax.websocket.server.ServerEndpoint(value = "/WebSocket_Server")
    
    /* Creation of the necessary class for the WebSockets */
    public static class My_ServerEndpoint {
        /* WebSocket onClose function */
        @javax.websocket.OnClose
        public void onClose(javax.websocket.Session session, javax.websocket.CloseReason close_reason) {
            System.out.println("onClose: WebSocket connection closed");
        }
        /* WebSocket onError function */
        @javax.websocket.OnError
        public void onError(javax.websocket.Session session, Throwable throwable) {
            System.out.println("onError: " + throwable.getMessage());
        }
        /* WebSocket onMessage function */
        @javax.websocket.OnMessage
        public void onMessage(javax.websocket.Session session, String message)throws IOException {
            System.out.println("Bar code is: " + message);
            System.out.println("Nutriscore of this product is: "+ OpenFoodFacts.nutriscore(message));
            session.getBasicRemote().sendText(OpenFoodFacts.nutriscore(message));
        }
        /* WebSocket onOpen function */
        @javax.websocket.OnOpen
        public void onOpen(javax.websocket.Session session, javax.websocket.EndpointConfig ec) throws java.io.IOException {
            System.out.println("onOpen... Christoph Samuel and Mouche");
            session.getBasicRemote().sendText("");
        }
    }
    
    /* Fonction d'application */
    public static void main(String[] args) {
        java.util.Map<String, Object> user_properties = new java.util.HashMap();
        user_properties.put("Author", "Christoph Samuel and Mouche");
        org.glassfish.tyrus.server.Server server = new org.glassfish.tyrus.server.Server("localhost", 2002, "/ChristophMouche", user_properties, My_ServerEndpoint.class);
        try {
            server.start();
            System.out.println("\n*** Please press any key to stop the server... ***\n");
            /* Launching the html page */
            java.awt.Desktop.getDesktop().browse(java.nio.file.FileSystems.getDefault().getPath("bar_code_reader/index.html").toUri());
            /* Read the wanted line */
            java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
            reader.readLine();
            System.out.println("\n@@@\n" + "@@@\n");
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            server.stop();
        }
    }   
}