CC =gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o my_string.o generic_vector.o tree.o
OBJECTS2 = my_string.o test_def.o unit_test.o
all: string_driver unit_test

string_driver:$(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.h generic.h tree.h my_string.c generic_vector.c tree.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
	$(CC) $(CFLAGS) -c tree.c -o tree.o
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o


unit_test: $(OBJECTS2)
	$(CC) $(CFLAGS) -o unit_test $(OBJECTS2)

test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
unit_test.o: unit_test.c unit_test.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o




clean:
	rm string_driver $(OBJECTS) unit_test $(OBJECTS2)
