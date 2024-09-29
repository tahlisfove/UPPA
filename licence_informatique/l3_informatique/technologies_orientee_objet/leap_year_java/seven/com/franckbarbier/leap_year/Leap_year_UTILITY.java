package com.franckbarbier.leap_year;

public class Leap_year_UTILITY {

    public static String Leap_year(final String date) throws Exception {
        java.util.Calendar calendar = java.util.Calendar.getInstance();
        calendar.setTime(new java.text.SimpleDateFormat("yyyy-MM-dd").parse(date));
        return " (before Java 8) " + (new java.util.GregorianCalendar()).isLeapYear(calendar.get(java.util.Calendar.YEAR));
    }
}
