all:
	notebook-generator -s 12 -p a4paper Templates

clean:
	@rm notebook.pdf

install:
	npm install -g notebook-generator