package com.franckbarbier.leap_year;

public class Leap_year_UTILITY {

    public static String Leap_year_(final String date) throws Exception {
        // 'java.time.format.DateTimeFormatter.ISO_LOCAL_DATE' => "2020-04-15"
        java.time.LocalDate locale_date = java.time.LocalDate.parse(date, java.time.format.DateTimeFormatter.ISO_LOCAL_DATE);
        // return " (from Java 8) " + java.time.Year.isLeap(locale_date.getYear());
        return " (from Java 8) " + locale_date.isLeapYear();
    }
}
