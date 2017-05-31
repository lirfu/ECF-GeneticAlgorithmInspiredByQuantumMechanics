# Genetski algoritam inspiriran kvantnom mehanikom<br>_Genetic algorithm inspired by quantum mechanics_<br>(GAIQM)

Ovaj je projekt raspoređen na sljedeći način:
* `main.cpp` - glavni program, definira koji se problem pokreće
* `QuantumRegistrer.cpp` - definicija kvantnog registra, sadrži kod za inicijalizaciju registra i pretvorbu u bitove (mjerenje registra)
* `Algorithms/` - sadrži algoritam GAIQM koji implementira i adapter tipa 'radnog genotipa'
* `Operators/` - sadrži operatore mutacije i rotacije
* `Problems/` - sadrži probleme nad kojima se pokreću eksperimenti
> Svaki problem ima svoj direktorij `__NazivProblema__` u kojem se nalaze:
> * `__NazivEvaluatora__.cpp` - evaluator problema, potrebno ga je postaviti kao radnog u `main.cpp`
> * `parametersClassical.txt` - datoteka parametara za klasični eksperiment
> * `parametersQuantum.txt` - datoteka parametara za kvantni eksperiment
> * *Ostale pomoćne datoteke za definiciju problema* (vidi: `NeuralNetwork`)
> * *Podaci pojedinih testova*
* `TestGround/` - sadrži skripte za automatizirano pokretanje eksperimenata
* `TestGround/compare.sh` - pokreće jedan eksperiment, generira pomoćne datoteke u `results/` i ispisuje krajnje rezultate uz mogućnost prikaza rezultata na grafu, u zaglavlju skripte je potrebno definirati ime eksperimenta (ime direktorija)
* `TestGround/multipleCompare.sh` - pokreće niz istih eksperimenata te usrednjuje njihove rezultate, u argumentu prima broj ponavljanja eksperimenta
* `TestGround/GenerateKnapsack.exe` - program koji generira jedan 'Knapsack' problem, interaktivno prima parametre te generira cjelobrojne podatke unifomnom vjerojatnošću do zadanih granica težina i vijednosti predmeta i izračunatu statistiku ispisuje u datoteci<br>(*statistika je u zaglavlju datoteke komentirana znakom #*)
* `UnitTests/` - sustav za automatsko testiranje komponenti projekta (*nedovršeno*)
* `Docs/` - pismenog dio završnog rada