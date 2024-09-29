#!/bin/bash
clear
/usr/libexec/java_home -V
echo -e "\nJava Virtual Machine (JVM) ver.: " `java --version` " (" `which java` ")\n"
javac --release 7 -d ./7 ./seven/com/franckbarbier/leap_year/*.java
javac --release 9 -d ./9 ./nine/module-info.java ./nine/com/franckbarbier/leap_year/*.java
#
#
# Single release packaging (caution: '--main-class=seven.com.franckbarbier.leap_year.Main' right after created jar file):
jar --create --file ./Leap_year.jar --main-class=com.franckbarbier.leap_year.Main -C 7 .
# Execution (before Java 8):
java -jar ./Leap_year.jar
#
#
# Multi-release packaging:
jar --create --file ./Leap_year.jar --main-class=com.franckbarbier.leap_year.Main -C 7 . \
--release 9 -C 9 .
# Clean up:
rm -rf 7
rm -rf 9
# Execution (from Java 8):
java -jar ./Leap_year.jar
# Or:
java --module-path . --module Leap_year/com.franckbarbier.leap_year.Main
rm Leap_year.jar
