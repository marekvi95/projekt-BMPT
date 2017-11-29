**Projekt BMPT**

**<u>Super mega giga nejlepsí Domácí meteostanice s LCD displejem nokia 5110</u>**

<u>zadání:</u> 

* Vytvoření embedded aplikace pro mikrokontrolér AVR (ATmega16 nebo ATmega328p) v jazyce C (překladač avr-gcc). Minimálně jedna funkce musí být naprogramována v 


* Nejsou specifikovány konkrétní výstupy projektů; jen moduly, HW. Studenti si sami navrhnou demo aplikaci, ve které moduly použijí.

Jako samostatný projekt jsme vytvořili domácí meteostanici, která zobrazuje na displeji **vlhkost** a **teplotu**. K měření jsme využili čidlo **DHT11**, které umožňuje tuto aplikaci. Čidlo má rozsah měřených teplot od 0 °C do 50 °C s přesností ±1 °C a vlhkost měří v rozmezí 20- 90% s přesností ±4 %.

Na obrázku je zobrazeno zapojení jednotlivých pinů čidla DHT11.

![DHT11_Sensor](C:\Users\ZávorkaRadek(186242)\projekt-BMPT\DHT11_Sensor.jpg)

K zobrazování využíváme **Nokia LCD displej 5110**. Ten je připojen 8 piny k **arduinu UNO**.