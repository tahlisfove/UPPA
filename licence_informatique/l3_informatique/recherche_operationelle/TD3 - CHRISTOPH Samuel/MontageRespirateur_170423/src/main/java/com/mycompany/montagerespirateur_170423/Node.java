package com.mycompany.montagerespirateur_170423;

/**
 *
 * @author schristoph
 */
public class Node {
    private final char id;
    private final int duration;
    
    public Node(char id, int duration) {
        this.id = id;
        this.duration = duration;
    }
    
    public char getId() {
        return id;
    }
    
    public int getDuration() {
        return duration;
    }

    Integer getDuree() {
        return duration;
    }
}