#include <iostream>
#include <stdio.h>      /* printf */
#include <stdarg.h>
int GetSum(int num...) {
	//int sum = 0;
	//int i = 0;
	//va_list ap;
	//int arg;
	//va_start(ap, num);
	//for (int i = 0; i < num; i++) {
	//	arg = va_arg(ap, int);
	//	sum += arg;
	//}
	//va_end(ap);
	//return sum;


	int sum = 0;

	int i;

	// va_list ap;

	char *ap;

	int arg;



	// va_start(ap,num);

	ap = (char *)&num + sizeof(num);

	for (i = 0; i < num; i++) {

		// arg=va_arg(ap,int);

		arg = *(int *)ap;

		ap += sizeof(int);

		sum += arg;

	}

	// va_end(ap);

	return sum;
}
void PrintSum(const char* msg...) {
	int sum = 0;
	va_list ap;
	int arg;
	va_start(ap, msg);
	while (true) {
		arg = va_arg(ap, int);
		if (arg == 0) break;
		sum += arg;
	}
	va_end(ap);
	printf(msg, sum);
}
double GetSum2(const char* types, ...) {
	double sum = 0;
	va_list ap;
	const char* p;
	va_start(ap, types);
	for (p = types; *p; p++) {
		switch (*p) {
		case 'i':
			sum += va_arg(ap, int);
			break;
		case 'd':
			sum += va_arg(ap, double);
			break;
		}
	}
	va_end(ap);
	return sum;
}
int main() {

	printf("1+2=%d\n", GetSum(2, 1, 2));

	printf("3+4+5+6=%d\n", GetSum(4, 3, 4, 5, 6));

	printf("10~15=%d\n", GetSum(6, 10, 11, 12, 13, 14, 15));

	PrintSum("1+2=%d\n", 1, 2, 0);

	PrintSum("3+4+5+6=%d\n", 3, 4, 5, 6, 0);

	PrintSum("10~15=%d\n", 10, 11, 12, 13, 14, 15, 0);

	printf("1+2=%f\n", GetSum2("ii", 1, 2));

	printf("2.5+3.8+4=%f\n", GetSum2("ddi", 2.5, 3.8, 4));

	printf("1+2.345+6+7.8901=%f\n", GetSum2("idid", 1, 2.345, 6, 7.8901));
	int n;
	scanf_s("%d", &n);
}