https://cses.fi/problemset/result/11441076/

## Megoldás

2 fáziara bontjuk a megoldás

- 1.  fázis
      minden cellához kiszámítjuk mennyi lépés lenne a szörny számára hogy elérjül
      mintha vízbe festék pöttyöt dobnánk

```
 for(const Point& monster : monsters) {
        monster_dist[monster.x][monster.y] = 0;
        q.push(monster);
    }
```

minden szörny hozzáadása

```
// BFS mindnen szörnyre
   while(!q.empty()) {
       Point curr = q.front();
       q.pop();

       // 4 irány
       for(int d = 0; d < 4; d++) {
           int nx = curr.x + dx[d];
           int ny = curr.y + dy[d];

           // jobb útvonalat laláltunk
           if(nx >= 0 && nx < n && ny >= 0 && ny < m &&
              grid[nx][ny] != '#' &&
              monster_dist[nx][ny] > monster_dist[curr.x][curr.y] + 1) {
               monster_dist[nx][ny] = monster_dist[curr.x][curr.y] + 1;
               q.push(Point(nx, ny));
           }
       }
   }
```

itt addig dolgozzuk fel a poziciükat amig lehet
minden pozícióbol megnézzük a szomszéd cellákat ahol:

- benne van a labirintiusba?
- nem fal?
- van ennél rövidepp útvonal ide

ha minden lefut, akkor frissítjük az útvonalat és elmentjük ezt a pozíciót hogy később
ellenőrizzük a szomszédait

- 2.  fázis
      Megkeressük a saját kezdő pozíciót és szörnyek kezdő pozícióját

```
for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'A') {
                start = Point(i, j);
                grid[i][j] = '.';
            }
            else if(grid[i][j] == 'M') {
                monsters.push_back(Point(i, j));
            }
        }
    }
```

Edge case, hogy kezdő pozíció biztonságos-e. ezt elfedjük.
Elkezdjük felépíteni a szükséges válltozókat a BFS (Breath first search) használatához.

```
vector<vector<bool>> visited(n, vector<bool>(m, false));  // Track visited positions
```

fenti sor fontos, ahol eltároljuk milyen mezőket látogattunk eddig,

Elindul egy másik BFS, a szörnyekhez hasonlóan

- Elsőször a célt keressük és kilépünk, ha célba értünk.
- Ezt követően szomszédokat próbáljuk ki mind a 4 irányban
- megnézzük pályán belül van-e
- nem voltunk-e ezen a mezőn már
- biztonságos-e a mező szörnyektől

ha ezek teljesülnek, akkor a biztonságos lépést hozzáadjuk és elmentjük mint látogatott mező.

```
  if(nx >= 0 && nx < n && ny >= 0 && ny < m &&    // pályán belül
           grid[nx][ny] != '#' && !visited[nx][ny]) {   // látogatott-e
            if(curr.path.length() + 1 < monster_dist[nx][ny]) {  // nincs-e szörny
```
