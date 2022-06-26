HEADERS = src/contact.h src/utils.h

default: contact

contact.o: src/main.c $(HEADERS)
	gcc -c src/main.c -o build/contact.o

contact: contact.o
	gcc build/contact.o -o build/contact

clean:
	-rm -f build/contact.o
	-rm -f build/contact

run:
	./build/contact
