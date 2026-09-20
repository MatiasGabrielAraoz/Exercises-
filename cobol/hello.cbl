       IDENTIFICATION DIVISION.
       PROGRAM-ID. hola.

       DATA DIVISION.
       WORKING-STORAGE SECTION.

       01 NOMBRE PIC X(20) VALUE "Jorge".
       01 EDAD PIC 99 VALUE 15.
       01 EDAD_NEXT PIC 99.

       PROCEDURE DIVISION.
       MAIN-PROCEDURE.
           DISPLAY "Hola " NOMBRE.
           DISPLAY "Tengo " EDAD.
           ADD 1 TO EDAD GIVING EDAD_NEXT.
           DISPLAY "El año q viene tengo " EDAD_NEXT.
           STOP RUN.
