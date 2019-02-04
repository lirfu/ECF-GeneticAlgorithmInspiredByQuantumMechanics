# qBIT:

Superpozicija je pojava u kojoj se elementarna čestica može nalaziti u dva ili više različitih 'kvantnih stanja' istovremeno, s određenom vjerojatnošću pronalaženja čestice u svakom od tih stanja.

Kako računala rade u binarnom sustavu, fokusiramo se na binarni kvantni sustav sa 2 stanja.<br>Podatkovna jedinica binarnog kvantnog sustava naziva se kvantnim bitom, skraćeno: qBit.

Primjenom qBita, *teoretski* je moguće ostvariti značajna ubrzanja nekih NP problema kvantnim algoritama (Shor-ov algoritam faktorizacije cijelih brojeva, Grover-ov algoritam pretrage nesortiranih polja, ...).<br>Jedan primjer primjene qBita je kvantni registar kao spremnik podataka, kojim se opisuje značaj superpozicije:

```
Pomoću 1 registra velićine n bitova moguće je pohraniti 1 od mogućih 2^n vrijednosti.

Pomoću 1 kvantnog registra velićine n qBita moguće je pohraniti 2^n od mogućih 2^n vrijednosti, odnosno sve vrijednosti od jednom. 
```

Superpozicija jednog qBita opisana je vjerojatnosnim amplitudama qBita svakom od mogućih stanja.<br>Za opis superpozicije qBita često se koristi Dirac-ova ("bra-ket" odnosno "<x| |x>") notacija:
```
|q> = a |0> + b |1> ,  a,b su kompleksni brojevi
```
uz normalizaciju:
```
|a|^2 + |b|^2 = 1
```

Dodatno, zbog lakše matematičke primjene koristi se i vektorska notacija:

```
        / a \
|q>  =  \ b /
```

Prostor stanja jednog qBita prikazuje se Blochovom sferom, gdje nasuprotne točke (polovi) predstavljaju klasična stanja.<br>
Kvantno stanje jednog qBita prikazuje se jednim vektorom iz središta sfere do točke na njenoj površini.

![Bloch sfere](https://dal.objectstorage.open.softlayer.com/v1/AUTH_039c3bf6e6e54d76b8e66152e2f87877/images-classroom/bloch-sphere0g2aifid2kpgb9.png)

Pojednostavljenje opisa qBita može se izvesti uklanjanjem 3. dimenzije. To je dozvoljeno jer se rotacijom vektora oko *z*-osi dobivaju ekvivalentna kvantna stanja.<br>Opis pojednostavljenog kvantnog stanja je slijedeći:
```
|q> = a |0> + b |1> ,  a,b su realni brojevi
```
uz normalizaciju:
```
|a|^2 + |b|^2 = 1
```

Prostor stanja jednog qBita prikazuje se kružnicom radijusa 1, gdje točka (0, 1) predstavlja stanje |0> a točka (0, -1) predstavlja stanje |1>.<br>
Kvantno stanje jednog qBita prikazuje se jednim vektorom iz središta kružnice do točke na njenoj površini.

Sada se otvara mogućnost jednostavnog opisa kvantnog stanja, samo jednom varijablom i to kutom vektora:
```
Kut vektora θ je realni broj iz intervala <-π, π]
a = cos(θ/2)
b = sin(θ/2)
```
Normalizacija je zadovoljena:
```
|a|^2 + |b|^2 = cos^2(θ/2) + sin^2(θ/2) = 1
```

>  Važno je primjetiti da u oba opisa vrijednosti `|a|^2` i `|b|^2` predstavljaju vjerojatnosti pronalaženja (mjerenja) qBita u stanju `|0>` i `|1>` respektivno.

# qRegistar (kvantni registar)

Kvantni registar pohranjuje više qBita u zadanom redoslijedu, te omogućuje ne-destruktivno čitanje i zapisivanje istih.
```
[ q1 | q2 | ... | qi | ... | qn ] , qi je i-ti qBit
```

Simulacija kvantnog registra pohranjuje vjerojatnosti npr. pojednostavljenih kvantnih stanja:
```
 / a1 | a2 | ... | ai | ... | an \
 \ b1 | b2 | ... | bi | ... | bn / , a,b su realni brojevi
```

Uz dodatno pojednostavljenje opisa kvantnih stanja, registar pohranjuje samo kutove kvantnih stanja:
```
[ θ1 | θ2 | ... | θi | ... | θn ]
```

# Algoritam QIGA<br>(Quantum Inspired Genetic Algorithm)

**POČETAK**

1.  Inicijaliziraj populaciju

2.  Izmjeri qRegistre (pretvorba qBita u klasični bit)

3.  Evaluiraj klasična mjerenja (niz bitova)

**PETLJA DOK (!UVJET)**

4. Pohrani najboljeg (elitizam)

5. Ostatak populacije izmijeni kvantnim genetskim operatorima

6. Izmjeri qRegistre (pretvorba qBita u klasični bit)

7. Evaluiraj klasična mjerenja (niz bitova)

8. **POVRATAK NA PETLJU**

**KRAJ**



## Inicijaliziraj populaciju

Stvori se zadani broj qRegistara veličine *n*.

Svaki qBit svakog registra postavi se u stanje superpozicije:
```
|q> = (|0> + |1>) / sqrt(2)
```
Na taj način ostvarujemo jednaku vjerojatnost mjerenja qBita u svakom od stanja (50:50):

```
a = b = 1 / sqrt(2)
|a|^2 = |b|^2 = 1 / 2
```

što znači da su vrijednosti kuteva:

```
θ = π/2
```



> Ponekad se u po završetku inicijalizacije izvršava i izmjena kuta vektora matricom rotacije:
>
> ```
> / cos(φ)  -sin(φ) \
> \ sin(φ)   cos(φ) / , gdje je φ nasumični kut iz intervala <-π, π]
> ```
> Time se ostvaruje raznolikost populacije i njihovih vektora stanja.



## Izmjeri qRegistre (pretvorba qBita u klasični bit) 

qRegistri sadrže qBite s kojima ne možemo na smislen način baratati na klasičnom računalu.<br>
Stoga je potrebno svaki qBit svakog qRegistra pretvoriti u klasični bit.<br>
Time svaki qRegistar postaje registrom klasičnih bitova (sadrži niz klasičnih bitova).

Mjerenje qBita vrši se nasumičnim odabirom boolean vrijednosti na temelju vjerojatnosti qBita:

```
Random r = new Random(0, 1)  // Stvori generator nasumičnih realnih brojeva iz intervala [0, 1>

bool bit = r.next() > cos^2(θ/2)
```

Vrijednosti klasičnih bitova pohranjuju se u klasični registar i proslijeđuju evaluacijskoj funkciji za izračun fitnessa.



## Ostatak populacije izmijeni kvantnim genetskim operatorima

Korištenjem kvantnih genetskih operatora ostatak populacije (dakle bez najbolje jedinke) ostvaruje se pretraživanje prostora stanja.

### Kvantna rotacijska vrata (kvantna interferencija)

Rotacijom vektora kvantnog stanja, jedinke se umjeravaju s najboljom jedinkom.<br>
Na taj način ostatak populacije teži ka najboljoj jedinci, tj. gradi svoje osobine prema njenim.<br>
U konačnici, primjenom kvantnih vrata ostvaruje se koncentracija populacije oko najbolje jedinke.

Rotacija vektora ostvaruje se skalarnim množenjem matrice rotacije s vektorom qBita:

``` 
/ a' \     / cos(δθ)  -sin(δθ) \  / a \
\ b' /  =  \ sin(δθ)   cos(δθ) /  \ b /
```

Zbog potrebe reduciranog zapisa pomoću kuteva, korisna je slijedeća relacija koja se dobiva iz prethodne jednadžbe:

```
θ' = θ + 2 δθ
```

Velićina kuta zakreta (*δθ*) određuje smjer i količinu rotacije, te se generalno računa na slijedeći način:

```
δθ = sg(a, b) ∆θ
```

gdje *sg(a, b)* određuje smjer rotacije, a *∆θ* količinu rotacije odnosno brzinu evolucije (konvergencije).

Te vrijednosti mogu biti zapisane u tzv. *look-up tablici* jer su ovisne o odnosu jedinke i najbolje jedinke.<br>
Postoji standardna tablica koja je korisna za mnoge probleme koja izgleda ovako:

|  qi  |  bi  | f(q) > f(b) |  ∆θ  | sg(a, b) | sg(a, b) | sg(a, b) | sg(a, b) |
| :--: | :--: | :---------: | :--: | :------: | :------: | :------: | :------: |
|      |      |             |      |  ab > 0  |  ab < 0  |  a = 0   |  b = 0   |
|  0   |  0   |    False    |  0   |    -     |    -     |    -     |    -     |
|  0   |  0   |    True     |  0   |    -     |    -     |    -     |    -     |
|  0   |  1   |    False    |  φ   |    +1    |    -1    |    0     |    ±1    |
|  0   |  1   |    True     |  φ   |    -1    |    +1    |    ±1    |    0     |
|  1   |  0   |    False    |  φ   |    -1    |    +1    |    ±1    |    0     |
|  1   |  0   |    True     |  φ   |    +1    |    -1    |    0     |    ±1    |
|  1   |  1   |    False    |  0   |    -     |    -     |    -     |    -     |
|  1   |  1   |    True     |  0   |    -     |    -     |    -     |    -     |

gdje qi i bi predstavljaju i-ti qBit kromosoma jedinke i najbolje jedinke respektivno, a *φ* određuje količinu zakreta odnosno brzinu evolucije (konvergencije), te se najčešće postavlja na vrijednost iz intervala [0.005π ,0.1π].

> *Look-up* tablicu generalno zadajemo sami ovisno o problemu koji rješavamo i brzina pojedinog algoritma ovisi o njoj. To joj je vrlo veliki nedostatak.

> Dodatni nedostatci se pokazuju u praksi.<br>
> Jedan je prebrza konvergencija zbog koje populacija rapidno gubi raznolikost, stoga algoritam često završi u lokalnom optimumu.<br>
> Drugi je nemogućnost lokalne pretrage što otežava finu pretragu oko globalnog optimuma.

Kao drugo rješenje, umjesto *look-up* tablice postoji adaptivna strategija odabira vrijednosti *∆θ* ovisno o odnosu fitness-a jedinke i najbolje jedinke. Potrebno je samo zadati interval unutar kojeg će se ∆θ mijenjati:

```
h = 0.05 // gornja granica
l = 0.005 // donja granica
∆θ = l + (h - l) |f(x) - f(b)| / max(f(x), f(b))
```

Ovim se pristupom velićina kuta zakreta određuje dinamički što generalizira i olakšava korištenje algoritma.

### Kvantna mutacija

* *Inverzija* (X-vrata)

  Korištenjem Pauli-jevih X vrata ostvaruje se zamjena vjerojatnosnih amplituda:

  ```
  / a' \     / 0 1 \  / a \
  \ b' /  =  \ 1 0 /  \ b /
  ```

  odnosno korištenjem zapisa s kutom kvantnog vektora:

  ```
  // θ je normaliziran na interval <-π, π]

  ako(θ > 0)
    θ' = π - θ
  inače
    θ' = -π - θ
  ```

* *Zamjena*

  Vrši se zamjena dvaju nasumično odabranih qBita unutar qRegistra:

  ```
  Unutar registra: 
  [ θ1 | θ2 | θ3 | ... | θi | ... | θn ]
   
  zamjene se qBit 1 i 3:
   [ θ3 | θ2 | θ1 | ... | θi | ... | θn ]
  ```

### Kvantno križanje

* *Klasično*

  Za dva qRegistra odabire se točka (indeks) sijecanja, te jedan dobiveni segment zamijeni mjesto s istim u drugom qRegistru:

  ```
  Registar 1:
  [ θ1 | θ2 | θ3 | ... | θi | ... | θn ]
  Registar 2:
  [ θ1' | θ2' | θ3' | ... | θi' | ... | θn' ]

  Točka presijecanja je između 2 i 3, te se izvrši zamjena.
  Novi sadržaj registara je:

  Registar 1:
  [ θ1 | θ2 | θ3' | ... | θi' | ... | θn' ]
  Registar 2:
  [ θ1' | θ2' | θ3 | ... | θi | ... | θn ]
  ```

* *Interferencijom*

  Vrši se rekombinacija qBita po više qRegistara na način da se za svaki qRegistar biraju qBiti po dijagonali.<br>
  Dakle, za prvi qRegistar uzima se 1. qBit prvog qRegistra, 2. drugog, 3. trećeg i td., dok za drugi qRegistar uzima se 2. qBit prvog qRegistra, 3. drugog, 4. trećeg i td.

  Primjer:

  ```
  Populacija prije križanja:
  [ θ11 | θ12 | θ13 | ... | θ1i | ... | θ1n ]
  [ θ21 | θ22 | θ23 | ... | θ2i | ... | θ2n ]
  [ θ31 | θ32 | θ33 | ... | θ3i | ... | θ3n ]
  ...

  Populacija nakon križanja:
  [ θ11 | θ22 | θ33 | ... | θii | ... | θnn ]
  [ θ12 | θ23 | θ34 | ... | θi(i+1) | ... | θn1 ]
  [ θ13 | θ24 | θ35 | ... | θi(i+2) | ... | θn2 ]
  ...
  ```
