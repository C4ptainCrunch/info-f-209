GLOSSARY_FILES = *.idx *.ist *.alg *.glg *.glo *.gls *.acn *.acr *.ilg *.ind
TEX_FILES = *.aux *.log  *.out *.lof *.lot *.toc *.xdy
TEX = pdflatex -interaction=batchmode

all: srd.pdf

clean:
	rm -f ${GLOSSARY_FILES} ${TEX_FILES}

%.pdf: %.tex %.glo2 %.idn
	${TEX} $<

%.glo: %.tex
	${TEX} $<
	makeglossaries $(subst .tex,,$<)

%.glo2: %.glo
	${TEX} $(subst .glo,,$<).tex
	makeglossaries $(subst .glo,,$<)
	touch $@

%.idn: %.tex
	makeindex $(subst .tex,,$<)

.PHONY: clean all

