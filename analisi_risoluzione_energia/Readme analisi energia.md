## Introduzione
in questo readme sono presenti le informazioni base che servono per interpretare i grafici in questa cartella e nelle relative sottocoartelle.

- 3 cartelle: **collinear**, **imporved_collinear**, **non_collinear**,  nelle quali sono presenti i seguenti oggetti:
    * un png Resolution... che contiene l'istogramma bidimensionale della risoluzione sull'energia come (en_vera-en_calcolata)/en_vera.
    * un png Profile...png che contiene il TProfile istogram relativo all'istogramma bidimensionale della risoluzione

- cartella **analitica**: questa contiene lo studio della soluzione analitica del problema, al suo interno ci sono:
    * due png con la risoluzione calcolata con l'energia maggiore e minore (provenienti dell'equazione di secondo grado)
    * un .png che contiene un istogramma costruito con i residui (energia_vera-energia_calcolata) scegliendo l'energia_calcolata come quella che corrisponde al cos(theta) più vicino a 1 tra le due soluzioni dell'equazione di secondo grado.
- il png proiezioni_totali.png che contiene le proiezioni per vari intervalli di massa invariante sulla risoluzione per gli istogramma bidimensionali salvati nei file Resolution...png. In questo file gli istogrammi rossi fanno riferimento al metodo collinear, quelli blu all'improved collinear e quelli verdi all'improved non collinear.
