void shift_array(int arr[], int n, int shift) {
int temp[n];

// Adjust shift value in case of negative values or values greater than array length
shift = shift % n;

if (shift < 0) {
shift = n + shift;
}

for (int i = 0; i < n; i++) {
temp[(i + shift) % n] = arr[i];
}

for (int i = 0; i < n; i++) {
arr[i] = temp[i];
}
}

int main() {
int n, shift;

printf("Enter the number of elements in the array: ");
scanf("%d", &n);

int arr[n];

printf("Enter %d numbers:\n", n);
for (int i = 0; i < n; i++) {
scanf("%d", &arr[i]);
}

printf("Enter the number of positions to shift: ");
scanf("%d", &shift);

shift_array(arr, n, shift);

printf("Array after shifting by %d positions:\n", shift);
for (int i = 0; i < n; i++) {
printf("%d ", arr[i]);
}

return 0;
}
