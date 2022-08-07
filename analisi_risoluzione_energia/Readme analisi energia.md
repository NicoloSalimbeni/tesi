## Introduzione
in questo readme sono presenti le informazioni base che servono per interpretare i grafici in questa cartella e nelle relative sottocoartelle.

- 3 cartelle: **collinear**, **imporved_collinear**, **non_collinear**,  nelle quali sono presenti i seguenti oggetti:
    * un png Resolution... che contiene l'istogramma bidimensionale della risoluzione sull'energia come (en_vera-en_calcolata)/en_vera.
    * un png Profile...png che contiene il TProfile istogram relativo all'istogramma bidimensionale della risoluzione e il relativo fit

- cartella **analitica**: questa contiene lo studio della soluzione analitica del problema, al suo interno ci sono:
    * due png con la risoluzione calcolata con l'energia maggiore e minore (provenienti dell'equazione di secondo grado)
    * un .png che contiene un istogramma costruito con i residui (energia_vera-energia_calcolata) scegliendo l'energia_calcolata come quella che corrisponde al cos(theta) più vicino a 1 tra le due soluzioni dell'equazione di secondo grado.
    * i plot bidimensionali della risoluzione e i TProfile per l'energia del B calcolata con la soluzione dell'equazione di secondo grada scelta in base al coseno maggiore (__*an_cos*__), scelta a posteriori (__*an_corr*__), e con la media della due soluzioni (__*an_mean*__)
    * il plot della risoluzione e il TProfile usando l'approssimazione collineare ma E_B != da P_B, in questa caso scegliendo la soluzione dell'equazione di secondo grado con il coseno maggiore (__*an_coll*__)

- il png proiezioni_totali.png che contiene le proiezioni per vari intervalli di massa invariante sulla risoluzione per gli istogramma bidimensionali salvati nei file Resolution...png. In questo file gli istogrammi rossi fanno riferimento al metodo collinear, quelli blu all'improved collinear e quelli verdi all'improved non collinear.

- un file_fit_profile.root che contiene le informazioni sia sul tipo di funzione utilizzata che sui parametri trovati per i vari fit dei TProfile


###### Cose da chiedere:
- la media delle soluzioni analitiche da un istogramma di forma **IDENTICA** a quello della non collinear
- la soluzione con il coseno e quella scelta a posteriori danno anche qui istogrammi identici in forma, ma quello della soluzione a posteriori è molto più piccato verso lo 0 (grazie a dio), questo ci dice che siamo sulla strada giusta?