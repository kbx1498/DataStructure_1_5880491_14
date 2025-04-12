#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinearList.h"

void parsePolynomial(const char* input, listType* list) {
	int coef, expo;
	char term[20];
	const char* ptr = input;
	while (sscanf_s(ptr, "%[^+]", term, (unsigned)_countof(term)) == 1) {
		ptr += strlen(term);
		if (*ptr == '+') ptr++;

		if (strchr(term, 'x') != NULL) {
			if (strchr(term, '^') != NULL)
				sscanf_s(term, "%dx^%d", &coef, &expo);
			else
				sscanf_s(term, "%dx", &coef, &expo), expo = 1;
		}
		else {
			sscanf_s(term, "%d", &coef);
			expo = 0;
		}
		elementType e;
		e.coef = coef;
		e.expo = expo;
		ordered_insertItem(list, e);
	}
}

listType* polymul(listType* a, listType* b) {
	listType* result = createList(a->last + b->last + 2);
	for (int i = 0; i <= a->last; i++) {
		for (int j = 0; j <= b->last; j++) {
			int coef = a->array[i].coef * b->array[j].coef;
			int expo = a->array[i].expo + b->array[j].expo;

			int found = 0;
			for (int k = 0; k <= result->last; k++) {
				if (result->array[k].expo == expo) {
					result->array[k].coef += coef;
					found = 1;
					break;
				}
			}
			if (!found) {
				elementType temp;
				temp.coef = coef;
				temp.expo = expo;
				ordered_insertItem(result, temp);
			}
		}
	}
	return result;
}

int main() {
	char input1[100], input2[100];

	printf("다항식을 입력하세요 (예: 3x^2+4x+1): ");
	scanf_s("%[^\n]", input1, (unsigned)_countof(input1));
	getchar(); 

	printf("다항식을 입력하세요 (예: 3x^2+4x+1): ");
	scanf_s("%[^\n]", input2, (unsigned)_countof(input2));
	getchar();

	listType* poly1 = createList(20);
	listType* poly2 = createList(20);

	parsePolynomial(input1, poly1);
	parsePolynomial(input2, poly2);

	listType* result = polymul(poly1, poly2);

	printf("[곱셈 결과]\n");
	printList(result);

	destroyList(poly1);
	destroyList(poly2);
	destroyList(result);

	return 0;
}
