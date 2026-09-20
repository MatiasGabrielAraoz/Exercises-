       IDENTIFICATION DIVISION.
       PROGRAM-ID. input.

       DATA DIVISION.
       WORKING-STORAGE SECTION.

       01 EDAD PIC Z(2)9.

       PROCEDURE DIVISION.
       MAIN-PROCEDURE.
           DISPLAY "Inserta tu edad: " WITH NO ADVANCING.
           ACCEPT EDAD.
           
           DISPLAY FUNCTION TRIM(EDAD).
