Le projet se compose en deux parties, une partie c et une partie en shell
Le shell gère tout seul la compilation du c, assurez vous juste de bien avoir AVL.c, AVL.h et cwire.c dans le dossier CodeC
Les colones du fichiers csv doivent êtres organisés comme suit (et dans ce même ordre): Power plant; HV-B Station ; HV-A Station ; LV Station ; Company ; Individual ; Capacity ; Load

Usage: -r <chemin_csv> -l <type de station> -c <type de consommateur> -p<identifiant de centrale>
les option peuvent êtres appelés dans l'ordre voulu
Paramètres :
  -r :(Obligatoire)Chemin vers le fichier de données a trier
  -l :(Obligatoire)Type de station (hvb, hva, lv)
	-c :(Obligatoire)Type de consomateurs (comp(entreprises), indiv(particuliers), all(tous)
	-p :(Optionnel) Identifiant de la centrale, sélectionne uniquements les éléments alimentés par cette centrale
	-h :ignore les autres arguments et affiche cette fenêtre d'aide 
la fenêtre d'aide s'affiche egalement si les arguments ne conviennent pas 
combinaisons interdites : hvb+all, hvb+indiv, hva+all, hva+indiv (car seules les entreprises sont connectés aux stations hvb et hva, on a donc aucun particulier a afficher)

Une fois les donnés d'entrée validés, le programme shell va réaliser un pré-tri, éliminant les lignes et les colones qui ne concernent pas nos filtres, programme qu'il stoquera dans le dossier temp
On appelle ensuite le c afin de calculer la somme des consomations sur chaque station filtrée 
Le
