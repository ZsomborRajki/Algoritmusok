
https://cses.fi/problemset/result/11439218/

## Megoldás

```
    unordered_map<long long, long long> remainder_count;
    remainder_count[0] = 1;
```

 - Létrehozunk egy hash map-et, ami számolja az egyes maradékok előfordulását
 - Az üres előtag (prefix) miatt a 0 maradék kezdeti értéke 1

```
    long long current_sum = 0;
    long long result = 0;
```

 - current_sum: az aktuális prefix összeg
 - result: a végeredmény (hány darab megfelelő részsorozat van)

```
    for(int i = 0; i < n; i++) {
        long long num;
        cin >> num;
```

 - Végigmegyünk a bemeneti számokon
 - Minden számot beolvasunk

```
    current_sum = (current_sum + num % n + n) % n;
```

Frissítjük az aktuális összeget:

 - num % n: az aktuális szám maradéka n-nel osztva
 - + n: hozzáadunk n-et, hogy biztosan pozitív legyen
 - Az egészet újra modulózzuk n-nel


```
    result += remainder_count[current_sum];
```

 - Ha már láttunk ilyen maradékot korábban, akkor az összes olyan részsorozat, 
ami a korábbi előfordulás és a jelenlegi pozíció között van, osztható lesz n-nel
 - Ezért hozzáadjuk az eddigi előfordulások számát az eredményhez

```
remainder_count[current_sum]++;
```

 - Növeljük az aktuális maradék előfordulásainak számát
}

A megoldás működési elve:

Ha két prefix összeg ugyanazt a maradékot adja n-nel osztva, akkor a közöttük lévő részsorozat összege osztható n-nel
Például ha az [1,4,3] sorozatnál:

Az első prefix (1) maradéka 1
A második prefix (1+4=5) maradéka 2
A harmadik prefix (1+4+3=8) maradéka 2
Mivel a második és harmadik prefix ugyanazt a maradékot adja, a közöttük lévő részsorozat (3) összege osztható n-nel


Ez a megoldás O(n) időbonyolultságú és O(n) tárigényű.
