#include <stdio.h>

int main() {
	int n = 0;

	for (char a = 0; a <= 9; a++)
		for (char b = 0; b <= 9; b++)
			for (char c = 0; c <= 9; c++)
				for (char d = 0; d <= 9; d++)
					for (char e = 0; e <= 9; e++)
						for (char f = 0; f <= 9; f++) {
							if (a+b+c == d+e+f) {
								n += 1;
							}
						} 

	printf("%d\n", n);
}
