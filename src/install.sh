make
i=1 # on initialise le compteur
while [ $i -le 10000 ]; do
  echo $i
  ./graph
  let $[ i+=1 ] # incremente i de 1 a chaque boucle
done 
