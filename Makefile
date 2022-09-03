CC = gcc
CFLAGS = -std=c99

files := $(wildcard *.c)
outputDir := "Build/"

hanoi: $(files) makeOutputDir clean
	$(CC) $(CFLAGS) $(files) -o $(outputDir)hanoi

debug: $(files) makeOutputDir clean
	$(CC) $(CFLAGS) -g $(files) -o $(outputDir)hanoi

makeOutputDir:
	mkdir -p $(outputDir)

clean:
	rm -f $(outputDir)hanoi.exe