#Programma analisi dati
Il programma si articola in varie classi che sono suddivise in cartelle a seconda della funzione. Le cartelle presenti sono:
- __AnalysisFramework__: consiene o pattern classici o classi astratte usate per costruire i vari oggetti in AnalysisObjects;
- __AnalysisObjects__: contiene tutti gli oggetti dell'analisi, uno per tipo
    - Collinear (coll)
    - improved collinear (ImpColl)
    - non collinear (NonColl)
    - Analitica (An)
    - Analitica collinear (AnColl)
- __AnalysisPlugins__: contiene delle classi (derivate) che servono per fare operazioni sui vari oggetti dell'analisi, salvarli, stamparli ecc...
- __AnalysisUtilities__: contiene delle classi che contengono elementi static utiliti in varie situazioni non strettamente legate all'analisi in questione

Poi nella cartella corrente ci sono i file _run.cc_ che serve per caricare tutte le classi in root e avviare l'analisi, e _TagSide.h/.cc_ per il loop sugli eventi