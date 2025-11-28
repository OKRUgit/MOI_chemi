Восстановление ESP8266 с помощью esptool.py в Linux


установка в ubuntu
sudo apt update && sudo apt install pipx
Если не установлен /pipx/

проверка 
ok@OKEAN:~$ pipx –version
Команда «pipx» не найдена, но может быть установлена с помощью:
sudo apt install pipx
ok@OKEAN:~$ 

Далее устаоновить /Установка esptool.py
pipx install esptool

Проверьте

esptool.py version.

проверяем доступ к плате:

ls -l /dev/ttyUSB*

Вы должны увидеть crw-rw----это в группе владельцев dialout .

ВРОДЕ ПОНЯТЬН, СПАТЬ ПОРА, ЗАВТРА продолжу.

https://cubiclenate.com/2025/10/08/unbricking-an-esp8266-with-esptool-py-on-linux/#installing-pipx

СЫЛКА поможет.]