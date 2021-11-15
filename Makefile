CC = cc
main = main.c
output = bfrt

run:
	$(CC) $(main) -o $(output)
	./$(output) test.bf

build:
	$(CC) $(main) -o $(output)

clear:
	rm $(output)
