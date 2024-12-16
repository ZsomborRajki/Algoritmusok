https://www.spoj.com/status/WATER,zsrajki/

## Megoldás

A megoldáshoz le kell fektetnük szabályokat, hogy a víz felülről lefelé folyik, tud azonos magasságnál szomszéd kockára folyni.

A víz tud gyűlni egy tócsában, amig akkora nem lesz hogy kifollyon.

És a víz ki tud szökni a sakktába szélén.

Víz szint mérése:
minden cellánál a lehető legalacsonyabbra fog emelkedni

keresnünk kell cellánként szökési stratégiákat a víz számára mindenhol

a szökési útvonal és minimum magassághoz kötött a víz szintje.

Sakktábla szélén nem lehet víz mert rögtön kifolyik.

Ahoz, hogy legyen tócsa egy cellán, ahoz magas celláknak kel körül ölelnie.

megoldás kód levezetése:

```
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

struct Cell {
    int row, col, height;
    Cell(int r, int c, int h) : row(r), col(c), height(h) {}
};

struct CompareCell {
    bool operator()(const Cell& a, const Cell& b) {
        return a.height > b.height;
    }
};
```

irányok meghatározása, segéd osztályok.
CompareCell fontos lesz a prioritásban, a magasabb cellák később lesznek ellenőzizve
és alulról felfelé fog halani a feldolgozás

Cell magassága pedig lehet a víz állása vagy a saját cella magassága is

```
int calculateWaterVolume(vector<vector<int>>& heights) {
```

ez fogja a magasságot tárolni 2d vektor-ban

```
int n = heights.size();
int m = heights[0].size();
vector<vector<bool>> visited(n, vector<bool>(m, false));
priority_queue<Cell, vector<Cell>, CompareCell> pq;
```

BFS kereséshez készítjuk fel az algoritmust

vannak a feldolgozott/ látogatott cellák

van egy prioritásunk, ami hol a legalacsonyabb magasságokat dolgozzuk fel először,
a víz magasról alacsonyra folyik ezért fontos a prioritás

```
for(int i = 0; i < n; i++) {
        pq.push(Cell(i, 0, heights[i][0]));
        pq.push(Cell(i, m-1, heights[i][m-1]));
        visited[i][0] = visited[i][m-1] = true;
    }
```

sakktábla széleit töltjük fel először

```
while(!pq.empty()) {
    Cell current = pq.top();
    pq.pop();

    // Szomszédos cellák ellenőrzése
    for(int i = 0; i < 4; i++) {
        int newRow = current.row + dx[i];
        int newCol = current.col + dy[i];
```

elindul a BFS, megnézzük a szomszédokat, a legalacsonyabb cellákat nézzük először

```
int waterHeight = max(current.height - heights[newRow][newCol], 0);
totalWater += waterHeight;

pq.push(Cell(newRow, newCol, max(current.height, heights[newRow][newCol])));
```

fő számítási logika:

- ha szomszádos cella alacsonyabb, oda fog folyni a víz és tócsa lesz ott
- waterHeight maga a víz magassága
- az új cella a magasság és a szomszédos cella maximumából jön ki

példa erre a számolásra:

Sakktábla:

3 5 3 → 3~5~3 (~ víz)

2 1 2 → 2~5~2

3 5 3 → 3~5~3

Lépésről lépésre:

1.  5 magasról folyik a mellette 1 magasságúba

- current.height = 5
- heights[newRow][newCol] = 1
- waterHeight = max(5 - 1, 0) = 4
- new effective height = max(5, 1) = 5

2. Ez 5-re teszi a víz szintet
   - Középső cell 4 köbméter vizet tartalmaz ez után (5 - 1 = 4)
   - Sarok cellák 2 unköbméter vizet tartalmaznak (5 - 3 = 2)

Mivel kívülről befelé haladunk mindig figyelni fogunk a menekülési utakra.
ezért fontos a sorrendje a feldolgozásnak.

Local minima:
vannak cellák, amik alacsonyabban mint minden szomszédja,
csak olyan cella gyűjt vizet, akinek magasabban vannak a menekülési útvonalai.
maga a vízszint a legalacsonyabb menekülési út magassága

Local minima are cells that are lower than all their neighbors
Not all local minima will collect water
Only local minima whose escape routes are higher than their own height will collect water
The amount of water collected is determined by the height of the lowest escape route

ez egyébként egy módosított Dijkstra's algoritmus.

A futási idő legalább O(nm) mert minden cellát be kell jármni legalább egyszer.
