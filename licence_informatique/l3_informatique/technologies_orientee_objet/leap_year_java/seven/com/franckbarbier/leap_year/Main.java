package com.franckbarbier.leap_year;

public class Main {

    public static void main(String[] args) {
        try {
            System.out.println("2020-04-15: " + Leap_year_UTILITY.Leap_year("2020-04-15"));
            System.out.println("2021-04-15: " + Leap_year_UTILITY.Leap_year("2021-04-15"));
        } catch (Exception e) {
            System.err.println(Leap_year_UTILITY.class.getSimpleName() + ": " + e.getMessage());
        }
    }
}
