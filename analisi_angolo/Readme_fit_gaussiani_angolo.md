# Analisi angolo di diffusione
Per prima cosa è stato proiettato l'istogramma bidimensionale contenuto in Distribuzione_angolo.png in vari intervalli di L/sigma_L. Fatto ciò i vari istogrammi sono stati fittati con una gaussiana più un esponenziale calante. Per fare i fit i parametri relativi alla gaussiana sono stati limitati a valori considerati fisici, in particolare la media è stata limitata tra 0 e 0.03 radianti. È possibile notare dai risultati dei fit che tutti i centroidi delle gaussiane sono essenzialmente zero come sperato.

###### Cose da chiedere:
- il numero di eventi dell'esponenziale è simile a quello della gaussiana, il fit è corretto? oppure è solo un "artificio matematico" e il fit converge ma il risultato non è fisico? in questo modo l'anadamente dei dati sembra essere più un esponenziale che una gaussiana.

###### Cosa da comunicare:
- ho fissato il centroide della gaussiana a 0 e continua a funzionare tutto bene come previsto
