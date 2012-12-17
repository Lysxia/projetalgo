slides.pdf: slides.tex datastrassen.dat
	pdflatex $<
	evince slides.pdf &

clean:
	rm -f *\~ *.aux *.nav *.toc *.log *.out *.snm *.vrb
