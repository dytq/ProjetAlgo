# make: pour compiler le fichier .tex & clean & afficher le pdf
# Version de Latexmk utilisé: 14 March 2019, version: 4.63.

N = rapport
compilandclean:
	latexmk $(N).tex
	dvipdf $(N).dvi
	mv rapport.pdf ProjetAlgo.pdf
	rm -vf $(N).dvi
	rm -vf $(N).log
	rm -vf $(N).fdb_latexmk
	rm -vf $(N).fls
	rm -vf $(N).aux
	rm -vf $(N).toc
	evince ProjetAlgo.pdf &
	
