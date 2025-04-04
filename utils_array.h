
// This file contains Arrays function used in the program

/// To find the sum of all elements of an array
float Arrays_sum(const float arr[], int len) {
    float sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += arr[i];
    }
    return sum;
}

/// To find the maximum element of an array

float Arrays_maxOf(const float *arr, int n) {
    float maximum = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}

/// This function converts an array to a String

char *Arrays_toString(const int *arr, int n) {
    char *ch = (malloc(200));
    ch[0] = '[';
    ch[1] = '\0';
    int count;
    if (n == 0) {
        count = snprintf(ch, 2000, "%s%s", ch, "NULL");
        ch[count] = ']';
        ch[count + 1] = '\0';
    } else {
        for (int i = 0; i < n; i = i + 1) {
            count = snprintf(ch, 2000, "%s%d, ", ch, arr[i]);
        }
        ch[count - 2] = ']';
        ch[count - 1] = '\0';
    }
    return ch;
}