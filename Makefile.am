SUBDIRS     = src

clean:
	rm -rf doc/latex
	rm -rf doc/html

pdf: doc
	$(MAKE) -C doc/latex pdf
	cp doc/latex/refman.pdf ModFrame.pdf

# the awk statement removes the indexes from their own chapter putting them into one single chapter
html doc:
	doxygen
	awk '{ if (match($$0,/^\\chapter{.*Index}$$/)) { if (1!=fFound) {print "\chapter{Indexes}"; fFound=1} } else { print } }' doc/latex/refman.tex > doc/latex/refman2.tex
	mv doc/latex/refman2.tex doc/latex/refman.tex

.PHONY: doc html pdf
