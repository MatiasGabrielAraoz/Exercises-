import pyautogui
import time

amnt = int(input("Selecciona la cantidad de mensajes a mandar: "))
msg = input("Que mensaje hay q mandar: ")

print("abrir chat, tiempo 5s")

time.sleep(5)

for i in range(amnt):
    pyautogui.write(msg) # volvé por favor lucía
    pyautogui.press("enter")
    time.sleep(0.2)
