# Control LED RGB prin Interfață Web utilizând ESP32

Acest proiect are ca scop controlul unui modul LED RGB printr-o interfață web, folosind un microcontroller ESP32. Proiectul oferă o soluție intuitivă și interactivă pentru personalizarea iluminatului, permițând utilizatorilor să ajusteze parametrii LED-ului în timp real.

## Funcționalități Principale:

- **Controlul Intensității:** Utilizatorii pot ajusta luminozitatea LED-ului RGB folosind un slider intuitiv. Acesta permite modificarea valorilor de intensitate între 0 și 255, oferind un control fin asupra luminozității.
  
- **Schimbarea Culorii:** Interfața include un selector RGB, permițând utilizatorilor să aleagă o culoare specifică pentru LED. Această funcționalitate îmbunătățește experiența utilizatorului și permite personalizarea completă a iluminatului.
  
- **Funcția Pornit/Oprit:** Un buton dedicat permite utilizatorilor să pornească sau să oprească LED-ul cu ușurință. Această opțiune este utilă pentru economisirea energiei și controlul rapid al sistemului de iluminat.

## Tehnologii Utilizate:

- **ESP32:** Microcontroller performant cu capacități Wi-Fi și Bluetooth, folosit pentru a crea serverul web și pentru a controla LED-ul RGB prin pinii PWM.
  
- **HTML/CSS/JavaScript:** Tehnologii web standard utilizate pentru a crea interfața utilizatorului. Interfața este prietenoasă și responsivă, asigurând o experiență de utilizare plăcută.
  
- **PWM (Pulse Width Modulation):** Tehnica folosită pentru a controla intensitatea LED-ului RGB prin variația lățimii impulsului pentru fiecare canal (roșu, verde, albastru).

## Cerințe:

- **Hardware:**
  - ESP32
  - Modul LED RGB
  - Rezistențe (dacă este necesar)
  - Conexiuni electrice

- **Software:**
  - Arduino IDE cu bibliotecile necesare pentru ESP32
  - Conexiune la rețeaua Wi-Fi pentru accesarea interfeței web

## Instrucțiuni de Instalare:

1. **Conectați Hardware-ul:**
   - Conectați LED-ul RGB la pinii corespunzători ai ESP32, asigurându-vă că utilizați pinii care suportă PWM.
  
2. **Configurați Arduino IDE:**
   - Instalați biblioteca ESP32 în Arduino IDE.
   - Deschideți proiectul și modificați setările Wi-Fi (SSID și parolă) pentru rețeaua dumneavoastră.

3. **Încărcați Codul:**
   - Încărcați codul pe ESP32 și deschideți consola serială pentru a verifica adresa IP a serverului.

4. **Accesați Interfața Web:**
   - Deschideți un browser web și introduceți adresa IP a ESP32 pentru a accesa interfața web.
  
## Contribuții:
Contribuțiile sunt binevenite! Dacă aveți sugestii sau îmbunătățiri pentru proiect, nu ezitați să deschideți un **issue** sau să faceți un **pull request**.

## Licență:
Acest proiect este licențiat sub MIT License. Vă rugăm să consultați fișierul **LICENSE** pentru detalii.

## Contact:
Pentru întrebări sau asistență, vă rugăm să mă contactați prin intermediul platformei GitHub.
