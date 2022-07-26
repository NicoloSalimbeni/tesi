# tesi
All'interno di grafici.root si trovano i seguenti grafici:
-CosAlpha  contiene cos-angle vs L
-MassRatio 1-M(sum)/M(const)
-Resolution 
-T_Angle
-En_profile
-B_energy

# fit angolo
L'idea di usare gauss+exp funziona, ma ho riscontrato vari problemi che possono essere risolti singolarmente ma non sempre tutti insieme:
-il primo bin rovina tutti i fit, posso toglierlo e funziona
-oltre a toglierlo posso anche fare bin più larghi, ma così ho pochi bin su cui fittare
-i primi istogrammi funzionano malissimo, ma è prevedibile perchè lì l'anadamente non è gaussiano

