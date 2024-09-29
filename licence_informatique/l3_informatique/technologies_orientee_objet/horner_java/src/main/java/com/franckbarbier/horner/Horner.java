package com.franckbarbier.horner;

public class Horner {

    public static void main(String[] args) {
        Polynomial p = new Polynomial();
        p.print();
        System.out.println(p.horner_method(1.D));
    }
}
