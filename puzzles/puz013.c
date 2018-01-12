/*****************************************************************************************************
 * Array Sum Challenge
 *
 * In this challenge, given an array of integers, the goal is to efficiently find the subarray
 * that has the greatest value when all of its elements are summed together.
 * Note that because some elements of the array may be negative,
 * the problem is not solved by simply picking the start and end elements
 * of the array to be the subarrray, and summing the entire array.
 * For example, given the array
 *         {1, 2, -5, 4, -3, 2}
 * The maximum sum of a subarray is 4.
 * It is possible for the subarray to be zero elements in length
 **********************************************************************************************************/

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint16_t start_index;
    uint16_t end_index;
    int32_t sum;
} subarray_t;

subarray_t find_max_sum_subarray(int8_t* parray, uint16_t len)
{
    uint8_t i;
    subarray_t sub = { 0, 0, 0 };
    int32_t sum = 0;

    for (i = 0; i < len; i += 1) {
        sum += *(parray + i);
        if (sum < 0) {
            if (i < len - 1) {
                sub.start_index = i + 1;
            }
            sum = 0;
        } else {
            if (sum > sub.sum) {
                sub.sum = sum;
                sub.end_index = i;
            }
        }
    }

    return sub;
}

int main(int argc, char* argv[])
{
    int8_t test_array[] = { 1, 2, -5, 4, -3, 2 };
    uint16_t i, len = sizeof(test_array) / sizeof(test_array[0]);
    subarray_t sub = find_max_sum_subarray(test_array, len);

    printf("array is:\t");
    for (i = 0; i < len; i += 1) {
        printf("%d ", test_array[i]);
    }
    printf("\n\n");

    if (sub.sum > 0) {
        printf("max sum subarray, start index=%d, end index=%d, max sum=%ld, subarray:\t", sub.start_index, sub.end_index, sub.sum);
        for (i = sub.start_index; i <= sub.end_index; i += 1) {
            printf("%d ", test_array[i]);
        }
        printf("\n");
    } else {
        printf("all negetive, max sum is 0\n");
    }

    return 0;
}
