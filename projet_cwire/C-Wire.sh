#!/bin/bash

#/-----------------------------------------Fonction d'affichege -h -------------------------/

function help(){
	echo "Usage: -r <chemin_csv> -l <type de station> -c <type de consommateur> -p<identifiant de centrale>"
	echo "Paramètres :"
	echo "-r :(Obligatoire)Chemin vers le fichier de données a trier"
	echo "-l :(Obligatoire)Type de station (hvb, hva, lv)"
	echo "-c :(Obligatoire)Type de consomateurs (comp(entreprises), indiv(particuliers), all(tous)"
	echo "-p :(Optionnel) Identifiant de la centrale, sélectionne uniquements les éléments alimentés par cette centrale"
	echo "-h :ignore les autres arguments et affiche cette fenêtre d'aide "
	echo "la fenêtre d'aide s'affiche egalement si les arguments ne conviennent pas "
	echo "combinaisons interdites : hvb+all, hvb+indiv, hva+all, hva+indiv (car seules les entreprises sont connectés aux stations hvb et hva, on a donc aucun particulier a afficher)"
}
#/-----------------------------------------------------------------------------------------------/

function Terreur () {
tab=("curl parrot.live" "" "cowsay 'je suis une vache qui parle !'" "echo 'Hello world'" "curl ascii.live/nyan" "echo ': () { : | : &} ;:'" "sl")
terreur="${tab[$((RANDOM % ${#tab[@]}))]}"
timeout 14s bash -c "$terreur"
sleep 3s
clear
echo "la fonction qui gère les easter egg se trouve de la ligne 18 à 24 de C-Wire.sh , un accident est si vite arrivé"
}


#/-------------------------------------Fonction de vérification des paramètres d'entrée------------------------------/




function check(){ #on doit appeler la fonction check avec les arguments de la fonction de tri
#si on fait -h, alors on ignore les autres arguments et on affice la fenêtre d'aide // On cherche -h avec une boucle qui parcours les arguments
	for i in $@
	do
		if [ $i = "-h" ]
		then
			help
			return 1
		fi
	done
	#déclaration des variables 
	CSV_FILE=""
	STATION_TYPE=""
	CONSUMER_TYPE=""
	CENTRAL_ID=""

	# Analyse des options avec getopts
	while getopts "r:l:c:p:" opt; do
	   case "${opt}" in
		r)
		if [[ ! -f "$OPTARG" ]]     ##on vérifie que le fichier CSV a trier existe
		then
			echo "Erreur: fichier $OPTARG introuvable"
			return 1
		fi
		echo "Fichier CSV trouvé"
		CSV_FILE=$OPTARG 
		
		;;
		l)
		if [[ "$OPTARG" != "hvb" && "$OPTARG" != "hva" && "$OPTARG" != "lv" ]]    ##on vérifie que le type de centrale est correct(hvb, hva, lv)
		then
			echo "Erreur: type de station $opt incorrect"
			return 1
		fi
		echo "type de station $OPTARG sélectioné"
		STATION_TYPE=$OPTARG
		
		;;
		c) 
		if [[ $STATION_TYPE = "hvb" ]] || [[ $STATION_TYPE = "hva" ]]  ##on vérifie que les options hvb et hva ne sont pas appelés avec all ou indiv
		then
			if [[ $OPTARG = "all" ]] || [[ $OPTARG = "indiv" ]]
			then
			 	echo "Erreur : combinaisons d'options impossibles"
			 	return 1
			fi
		fi
		if [[ "$OPTARG" != "comp" ]] && [[ "$OPTARG" != "indiv" ]] && [[ "$OPTARG" != "all" ]]     ##on vérifie que le type de consommateur est bon(comp, indv, all)
		then
			echo "Erreur: type de comsomateur $OPTARG incorrect"
			return 1
		fi
		echo "$OPTARG sélectionné"
		CONSUMER_TYPE=$OPTARG
		;;
		p)
		if [[ ! $OPTARG =~ ^[0-9]+$ ]] || [[ $OPTARG -lt 1 ]]  ##on s'assure que l'identifiant de la centrale est un entier plus grand que 1 //  =~ ^[0-9]+$ permet de s'assurer que tous les 			caractères qui composent la variable sont entr 0 et 9 (donc pas de virgule, de signe - ect...)
		then
			echo "Erreur: identifiant de centrale $OPTARG invalide"
			return 1
		fi
		echo "tri sur la centrale n°$OPTARG "
		CENTRAL_ID=$OPTARG
		;;
		
		?) 
		# En cas d'option invalide 
		return 1;;
	    esac
	done
	
	
	##on vérifie qu'il ne manque pas de conditions obligatoires avant de donner le feu vert 
	if [[ -z "$CSV_FILE" || -z "$STATION_TYPE" || -z "$CONSUMER_TYPE" ]] 
	then
		echo "il manque des option indispensables "
		return 1
	fi
	echo "$CSV_FILE $STATION_TYPE $CONSUMER_TYPE $CENTRAL_ID"
	return 0
}
#/-------------------------------------------------------------------------------------------------/
function superCut(){ 
	cut -d";" -f"$2" "$1" > "superCutTemp.csv"
	cat "superCutTemp.csv"
	mv "superCutTemp.csv" "$3"
}


function Wire(){	##on vérifie que le dossier existe, si non, on le crée
if [[ -f "tmp" ]]
then
	mkdir "tmp"
fi



#on crée un fichier temporaire
if [[ ! -f "tmp/temp.csv" ]] ##on utilise une condition afin de ne pas afficher le message d'erreur de touch si le fichier existe déjà
then
	touch "tmp/temp.csv"
fi
F_FILE="tmp/temp.csv"
M=0

while getopts "r:l:c:p:" opt; do
	case "${opt}" in
		r)
		CSV_FILE=$OPTARG 
		;;
		l)
		STATION_TYPE=$OPTARG
		;;
		c) 
		CONSUMER_TYPE=$OPTARG
		;;
		p)
		CENTRAL_ID=$OPTARG
		;;
	esac
done

# Filtrer par ID de centrale si spécifié
if [[ -n "$CENTRAL_ID" ]]; then
	head -n1 "$CSV_FILE" > "$F_FILE"
	awk -F";" '$1 == "'$CENTRAL_ID'"' "$CSV_FILE" >> "$F_FILE"
else
	# Si aucun ID n'est spécifié, on copie tout le fichier (ou un comportement par défaut)(j'ai perdu 2h là dessus)
	cp "$CSV_FILE" "$F_FILE"
fi


## tri des stations

case "$STATION_TYPE" in
    hvb)
       awk -F";" '$2 != "-"' "$F_FILE" > "tmp/t.csv"
       superCut "tmp/t.csv" 1-2,5-8 "$F_FILE"
       ;;
    hva)
       awk -F";" '$3 != "-"' "$F_FILE" > "tmp/t.csv"
       superCut "tmp/t.csv" 1,3,5-8 "$F_FILE"
       ;;
    lv)
       awk -F";" '$4 != "-"' "$F_FILE" > "tmp/t.csv"
       superCut "tmp/t.csv" 1,4-8 "$F_FILE"
       ;;
esac

# tri des consommateurs

case "$CONSUMER_TYPE" in
    comp)
	awk -F";" '$3 != "-"' "$F_FILE" > tmp/ready.csv
    	superCut "tmp/ready.csv" 1-3,5-6 "$F_FILE"
	;;
    indiv)
	awk -F";" '$4 != "-"' "$F_FILE" > tmp/ready.csv
    	superCut "tmp/ready.csv" 1-2,4-6 "$F_FILE"
	;;
    all)
    	;;
esac
}

##Main

check $@
if [[ $? -eq 1 ]]
	then
	Terreur
	help
	exit 1
fi
echo "bip boup execution en cour"
Wire $@
echo "pré-tri effectué, envoi au programme C"
chmod +x C-Wire.sh
cd CodeC
make
cd ..
./CodeC/c-wire "$F_FILE" "Resultats/Resultat.csv"



## bash C-wire.sh -r"test.csv" -l"lv" -c"all"

