GLOSSARY_FILES = *.idx *.ist *.alg *.glg *.glo *.gls *.acn *.acr *.ilg *.ind
TEX_FILES = *.aux *.log  *.out *.lof *.lot *.toc *.xdy
TEX = pdflatex -interaction=batchmode

DIASSOURCES=$(wildcard ./uml/*/*.dia) $(wildcard ./uml/*.dia)
DIAOUT=$(subst .dia,.eps,$(DIASSOURCES))

DOTSOURCE=$(wildcard ./uml/*/*.dot) $(wildcard ./uml/*/*.neato) $(wildcard ./uml/*.dot) $(wildcard ./uml/*.neato)
DOTOUT=$(subst .neato,.eps,$(subst .dot,.eps,$(DOTSOURCE)))

ROOT=$(realpath .)/

RED=\e[0;31m
NC=\e[0m

all: diagrams srd.pdf
	@echo -e "$(RED) fin $(NC)"

clean: clean-diagrams
	rm -f ${GLOSSARY_FILES} ${TEX_FILES} srd.synctex.gz

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

diagrams: $(DIAOUT) $(DOTOUT)

%.eps: %.dia
	dia -e $(ROOT)$@ $(ROOT)$<

%.eps: %.neato
	neato -Teps $< > $@

%.eps: %.dot
	dot -Teps $< > $@

clean-diagrams:
	find . -name "*-eps-converted-to.pdf" -exec rm -rf {} \;
	find . -name "*.eps" -exec rm -rf {} \;

debug:
	@echo $(DOTOUT)

.PHONY: clean all

