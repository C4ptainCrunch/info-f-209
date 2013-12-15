GLOSSARY_FILES = *.idx *.ist *.alg *.glg *.glo *.gls *.acn *.acr *.ilg *.ind
TEX_FILES = *.aux *.log  *.out *.lof *.lot *.toc *.xdy
TEX = pdflatex -interaction=batchmode

RED=\e[0;31m
NC=\e[0m

all: srd.pdf
	@echo -e "$(RED) fin $(NC)"

clean:
	rm -f ${GLOSSARY_FILES} ${TEX_FILES}

%.pdf: %.tex %.glg2 %.idn
	@echo -e "$(RED) make pdf $(NC)"
	${TEX} $<

%.glg2: %.glg
	${TEX} $(subst .glg,.tex,$<)
	@echo -e "$(RED) make glossaries $(NC)"
	makeglossaries -q $(subst .glg,,$<)
	touch $@


%.glg: %.gls
	@echo -e "$(RED) make glossaries $(NC)"
	makeglossaries -q $(subst .gls,,$<)

%.gls %.idx: %.tex
	@echo -e "$(RED) make glossaries and index entry $(NC)"
	${TEX} $<

%.idn: %.idx
	@echo -e "$(RED) make index $(NC)"
	makeindex -q $(subst .tex,,$<)



.PHONY: clean all

