https://cses.fi/problemset/result/11440576/

## Megoldás

Dinamikus programozást használva két dolgot kell figyelemmel tartani
 - Rá tudunk lépni a mezőre? Csadpa-e
 - Hányféleképpen tudjuk ezt a mezőt megközelíteni, útvonalak száma
 
Példa
....
.*..
...*
*...

Lépés 1 - Első cella:
1 ... 
.... 
.... 
.... 

Lépés 2 - Feltöltjuk az első sort:
1 1 1 1
.... 
.... 
.... 



Lépés 3 - Feltöltjük az első oszlopot:
1 1 1 1
1 *.. 
1 ..* 
* ... 

```
   dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % MOD;
```

- dp[i][j] cellába útvonalak száma
- dp[i-1][j] a cél cella feletti útvonalak száma
- dp[i][j-1] is the number of paths to reach the cell to the left
- dp[i-1][j] + dp[i][j-1] összeadjuk mert ezt a cellát felülről vagy balról tudjuk megközelíteni
    3 2 1
    1 2 *
    4 3 5
    Első pozi (1,1) értéke 2:

    Felülről: dp[0][1] = 2 útvonal
    Balról: dp[1][0] = 1 útvonal
    Összes: (1,1): 2 + 1 = 3 útvonal

Lépés 4 - Végig járjuk a lehetséges cellákat és számoljuk az útvonalakak:
1 1 1  1
1 0 1  1
1 1 1  0
0 1 2  3

O(n²) komplexitás a 2 egymásba ágyazott for ciklus miatt.
