package com.mycompany.WebSocket_Server;

public class OpenFoodFacts {

    public static String nutriscore(String bar_code) throws java.net.MalformedURLException, java.io.IOException {
        String _nutri_score = "";
        /* Open the connection to acess the API */
        java.net.URL url = new java.net.URL("https://world.openfoodfacts.org/api/v0/product/" + bar_code + ".json");
        java.net.URLConnection connection = (java.net.URLConnection) url.openConnection();
        /* Recovery of the desired element, in our case the nutri-score */
        if (connection != null) {
            javax.json.stream.JsonParserFactory factory = javax.json.Json.createParserFactory(null);
            /* Effective connection with the service */
            javax.json.stream.JsonParser parser = factory.createParser(connection.getInputStream());
            /* Return the JSON object */
            while (parser.hasNext()) {
                javax.json.stream.JsonParser.Event event = parser.next();
                if (event == javax.json.stream.JsonParser.Event.KEY_NAME && parser.getString().equals("nutriscore_grade")) {
                    while (parser.hasNext()) {
                        event = parser.next();
                        if (event == javax.json.stream.JsonParser.Event.VALUE_STRING) {
                                _nutri_score = parser.getString();
                            break;
                        }
                    }
                }
            }
        }
        /* Returns the nutriscore found or not */
        return _nutri_score;
    }
}