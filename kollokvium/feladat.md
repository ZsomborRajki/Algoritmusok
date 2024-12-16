https://www.spoj.com/problems/WATER/

# WATER - Water among Cubes

## Feladat

Egy négyszögletű sakktábla van n\*m négyzet és erre kockákat pakolunk.
Minden kocka egy négyzetméter felületű.
Egy sakk mezőt takar le a kocka felszíne. A kockák közvetlen egymás mellett vannak, érintkeznek, nincs köztük rés. Eső esik, és víztócsák keletkeznek az alsó kockáknál.

Írjunk egy programot:

Bementől kiolvasva beolvassuk a sakktábla méretét és a magasságát, hogy hány kockát, milyen magasra pakolunk.
És ki kell számolni a maximális mennyiséget, hogy a tócsa mekkora mennyiségre duzzad fel. Ezt visszadni a kiemnete.

## Bemenet

Első bemenet _t_ szám, a tesztesetek száma. Következő sor _n_ és _m_ két száma a sakktábla mérete.
Következő _n_ sornyi és _m_ oszlopnyi szám a kockák magassága a sakktáblán.
ezt jelöljük : _j_

The number of test cases t is in the first line of input, then t test cases follow separated by an empty line. In the first line of each test case two positive integers 1 <= n <= 100, 1 <= m <= 100 are written. They are the size of the mesh. In each of the following n lines there are m integers from the interval [1..10000]; i-th number in j-th line denotes a height of a cuboid given in inches put on the field in the i-th column and j-th raw of the chessboard.

## Kiemnet

Minden esethez egy integer számot kell visszaadni, ami a maximális vízmennyiség köbméterben

## Megkötés

1 <= n <= 100
1 <= m <= 100
1 <= j <= 10000

## Példa

Bemenet:
1
3 6
3 3 4 4 4 2
3 1 3 2 1 4
7 3 1 6 4 1

Kimenet:
5
