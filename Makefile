all:
	notebook-generator -s 12 -p a4paper -c 3 Templates

clean:
	@rm notebook.pdf

install:
	npm install notebook-generator