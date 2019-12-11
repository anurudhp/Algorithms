all:
	cp template_header.tex node_modules/notebook-generator/template_header.tex
	node_modules/notebook-generator/bin/notebookgen \
		-s 12 \
		-p a4paper \
		Templates

clean:
	@rm notebook.pdf

install:
	npm install notebook-generator