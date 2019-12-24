all: pt10 pt12

pt10:template
	node_modules/notebook-generator/bin/notebookgen \
		-s 10 \
		-p a4paper \
		-o notebook10.pdf \
		Templates

pt12:template
	node_modules/notebook-generator/bin/notebookgen \
		-s 12 \
		-p a4paper \
		-o notebook12.pdf \
		Templates

template:
	cp template_header.tex node_modules/notebook-generator/template_header.tex

clean:
	@rm notebook.pdf

install:
	npm install notebook-generator

.PHONY: install clean template pt12 pt10
