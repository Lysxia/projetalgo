slides.pdf: slides.tex databireme.dat datatamarin.dat optibireme.dat optitetragone.dat
	pdflatex $<
	evince slides.pdf &

clean:
	rm -f *\~ *.aux *.nav *.toc *.log *.out *.snm *.vrb
