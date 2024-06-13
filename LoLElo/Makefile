CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address

TARGET = main
OUTPUT_FILE = lol_stats.html

all: $(TARGET)

$(TARGET): main.c player_loader.c match_loader.c html_generator.c
	$(CC) $(CFLAGS) $^ -o $(TARGET)

run: $(TARGET)
	./$(TARGET) matches.txt players.txt $(OUTPUT_FILE)
	xdg-open $(OUTPUT_FILE)

clean:
	rm -f $(TARGET) $(OUTPUT_FILE)