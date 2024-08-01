#include "../include/header.h"

/* Binary Search */
bool searchByDate(transaction** transactionArray, int transactionArraySize, int targetMonth, int targetDay, int targetYear, int* left, int* right) {
	bool found = false;
	int l = 0, r = transactionArraySize-1, m = 0;

	while (l <= r) {
		m = (l+r)/2;
		int month = 0, day = 0, year = 0;
		stringUnformatDate(transactionArray[m]->serviceDate, &month, &day, &year);

		/* Compare year first, then month, then day; best way to
		see which date comes first */
		if (year == targetYear) {
			if (month == targetMonth) {
				if (day == targetDay) {
					found = true;

					*left = m;
					*right = m;

					char tempDate[DATE_MAXLEN] = "";
					sprintf(tempDate, "%d/%d/%d", month, day, year);

					/* Find first and last occurence of this date */
					while (*left >= 0 && strcmp(transactionArray[*left]->serviceDate, tempDate) == 0) {
						(*left)--;
					}
					(*left)++;

					while (*right < transactionArraySize && strcmp(transactionArray[*right]->serviceDate, tempDate) == 0) {
						(*right)++;
					}
					(*right)--;

					break;
				} else if (day < targetDay) {
					l = m + 1;
				} else {
					r = m - 1;
				}
			} else if (month < targetMonth) {
				l = m + 1;
			} else {
				r = m - 1;
			}
		} else if (year < targetYear) {
			l = m + 1;
		} else {
			r = m - 1;
		}
	}

	return found;
}
