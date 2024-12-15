https://cses.fi/problemset/result/11440008/

## Megoldás

- Egy gráfot készítünk

minden élt be kell járnunk, addig amig egyszer végig nem mentünk az összesen.
minden élen elvégzünk egy ellenőrzést:

Mostani lépés (mondjuk 0):
- Hozzáadhatunk 0-t? (megnézzük "0→0" volt-e látogatva)
- ha igen, hozzáadjuk 0-t és megyünk kövezkező lépésre
- ha nem, hozzáadhatjuk az 1-t? (megnézzük "0→1" volt-e látogatva)
- ha igen, hozzáadjuk az 1-et és megyünk a következő lépésre
- ha nem, visszalépünk az előző lépésre és próbálunk mást hozzáadni

## Példa
 n=2:

Várt eredmény: 00, 01, 10, 11
Kezdek: 0, hozzáadok: + 0 → 00
+ 1 →  01
+ 1 →  11
+ 0 →  10
+ 0 → vissza 00
Eremeny: 00110

DFS használata:
 - minden lehetőség helyett, mindig egyre mélyebbre megyünk a gráfban
 - rögtön hozzáadjuk az eredményt
 - visszalépünk, ha zsákutcába kerülünk az előző lépésre
```
void generateSequence(int current)
    {         ...
               // Rekurzív hívás a következő csúcsra Depth-first search módszerrel
                generateSequence(next);
            }
        }
```
