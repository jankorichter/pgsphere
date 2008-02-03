#----------------------------------------------------------------------------
#
# pgSphere documentation makefile
#
#----------------------------------------------------------------------------

subdir = contrib/pg_sphere/doc
top_builddir = ../../..
include $(top_builddir)/src/Makefile.global

.SECONDARY:
.NOTPARALLEL:

ifndef COLLATEINDEX
COLLATEINDEX = $(DOCBOOKSTYLE)/bin/collateindex.pl
endif

ifndef JADE
JADE = jade
endif
SGMLINCLUDE = -D $(srcdir)

ALLSGML := $(wildcard $(srcdir)/*.sgm)

ifdef DOCBOOKSTYLE
CATALOG = -c $(DOCBOOKSTYLE)/catalog
endif

COLLATEINDEX := $(PERL) $(COLLATEINDEX) -f -g


all   : html

.PHONY: html pdf ps

XMLDCL = declaration/xml.dcl

html  : pg_sphere.xml $(ALLSGML) pg_sphere.dsl
	@rm -f *.html
	@rm -rf html
	mkdir html
	mkdir html/img
	cp img/*.jpg html/img
	$(JADE) $(JADEFLAGS) $(SGMLINCLUDE) $(CATALOG) -d pg_sphere.dsl -i html  -t sgml $(XMLDCL) $<
	mv *.html html

pg_sphere.tex : pg_sphere.xml $(ALLSGML) pg_sphere.dsl
	$(JADE) $(JADEFLAGS) $(SGMLINCLUDE) $(CATALOG) -d pg_sphere.dsl -i print -t tex -o $@ $(XMLDCL) $<

pg_sphere.dvi: pg_sphere.tex
	@rm -f $*.aux $*.log
	make -C img
	jadetex $<
	jadetex $<

pdf : jadetex.cfg pg_sphere.pdf

pg_sphere.pdf: pg_sphere.tex
	@rm -f $*.aux $*.log $*.out
	pdfjadetex $<
	pdfjadetex $<
	pdfjadetex $<

ps : pg_sphere.ps

pg_sphere.ps: jadetex.cfg pg_sphere.dvi
	dvips -o $@ $<

pg_sphere.dsl : pg_sphere.dsl-dist
	cp $< $@

jadetex.cfg : jadetex.cfg-dist
	cp $< $@



##
## Clean
##

clean distclean maintainer-clean:
# HTML
	rm -rf html
# print
	rm -f *.rtf *.tex *.dvi *.aux *.log *.ps *.pdf *.out *.fot
# img
	make clean -C img
