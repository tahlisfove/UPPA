package com.franckbarbier.yesterday_tomorrow;

public class Yesterday_Tomorrow {

    public static void main(String[] args) {
        java.time.ZonedDateTime yesterday = java.time.LocalDateTime.now()
                .minusDays(1L)
                .atZone(java.time.ZoneId.systemDefault());
        System.out.println("Yesterday: " + java.time.format.DateTimeFormatter.ISO_LOCAL_DATE.format(yesterday));
        java.time.ZonedDateTime tomorrow = java.time.LocalDateTime.now()
                .plusDays(1L)
                .atZone(java.time.ZoneId.of("Europe/Paris"));
        System.out.println("Tomorrow: " + java.time.format.DateTimeFormatter.ofPattern("EEE, d MMM yyyy", java.util.Locale.FRENCH).format(tomorrow));
        java.time.ZonedDateTime next_friday = java.time.LocalDateTime.now()
                .with(java.time.temporal.TemporalAdjusters.next(java.time.DayOfWeek.FRIDAY))
                .atZone(java.time.ZoneId.of("Europe/Paris"));
        System.out.println(java.time.format.DateTimeFormatter.ofLocalizedDate(java.time.format.FormatStyle.SHORT).format(next_friday));

    }
}
