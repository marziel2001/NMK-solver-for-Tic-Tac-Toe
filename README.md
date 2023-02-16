# Tic Tac Toe - NMK Solver

***Tic Tac Toe NMK Solver*** jest programem rozwiązującym plansze do kółko i krzyżyk w dowolnym etapie gry. 
Program pozwala na wygenerowanie wszystkich możliwych ruchów, razem z odcięciem czyli w momencie
gdy znajdzie ruch wygrywający przestaje generować plansze. Kolejną funkcjonalnością jest odpowiadanie
na pytanie któy gracz wygra grę jeżeli obaj gracze grają optymalnie.

### Przykładowe polecenia:

> GEN_ALL_POS_MOV 4 4 3 1 1 2 0 1 0 1 0 2 0 2 0 1 0 0 2 0
>>GEN_ALL_POS_MOV - funkcja której chcemy użyć
>>4 4 - wymiary planszy
>>3 - ilość pionów po kolei gwarantująca wygraną
>>1 - aktywny gracz
>>plansza:
>>1 2 0 1 
>>0 1 0 2 
>>0 2 0 1 
>>0 0 2 0
>>Generuje wszystkie plansze gdzie 1 to piony gracza nr 1, 2 to piony gracza nr 2 a 0 to puste miejsca
