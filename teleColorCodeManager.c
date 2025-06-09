#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COLOR_COUNT 5
#define MAX_COLOR_NAME_LEN 20

// Abstract interface via function pointer (simulating virtual function)
typedef struct IColorPrinter {
    void (*print)(struct IColorPrinter* self, int index, const char* major, const char* minor);
} IColorPrinter;

// Concrete implementation: console printer
typedef struct {
    IColorPrinter base;
    // additional fields if needed (e.g., file handle)
} ConsoleColorPrinter;

void consolePrint(struct IColorPrinter* self, int index, const char* major, const char* minor) {
    (void)self; // unused
    printf("%d | %s | %s\n", index, major, minor);
}

void ConsoleColorPrinter_init(ConsoleColorPrinter* printer) {
    printer->base.print = consolePrint;
}

// ColorMap "class"
typedef struct {
    const char* majorColors[COLOR_COUNT];
    const char* minorColors[COLOR_COUNT];
    IColorPrinter* printer;
} ColorMap;

void ColorMap_init(ColorMap* map, IColorPrinter* printer) {
    static const char* majors[] = {"White", "Red", "Black", "Yellow", "Violet"};
    static const char* minors[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    memcpy(map->majorColors, majors, sizeof(majors));
    memcpy(map->minorColors, minors, sizeof(minors));
    map->printer = printer;
}

int ColorMap_print(ColorMap* map) {
    int count = 0;
    for (int i = 0; i < COLOR_COUNT; ++i) {
        for (int j = 0; j < COLOR_COUNT; ++j) {
            map->printer->print(map->printer, i * COLOR_COUNT + j, map->majorColors[i], map->minorColors[j]);
            count++;
        }
    }
    return count;
}

int main() {
    ConsoleColorPrinter consolePrinter;
    ConsoleColorPrinter_init(&consolePrinter);

    ColorMap colorMap;
    ColorMap_init(&colorMap, (IColorPrinter*)&consolePrinter);

    int result = ColorMap_print(&colorMap);
    assert(result == 25);

    printf("All is well (maybe!)\n");
    return 0;
}
