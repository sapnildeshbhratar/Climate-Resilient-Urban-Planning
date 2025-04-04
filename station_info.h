
// This file contains the structure/body of the code where all the functions related to given queries are provided

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils_array.h"
#include <limits.h>
#include <stdbool.h>

typedef struct {


    int station;
    float sky_view_factor;
    float vegetation_density_ratio;
    float population_density;
    int previous_surface_fraction;
    int impervious_surface_fraction;
    int station_status;
    int distance_of_station[100];

    /** Weather Parameters are recorded over 30 days
     * It consist of air temperature and relative humidity
     * The 30 days data is in the form of an array of size 30*/
    float air_temp[30];
    float rel_humidity[30];

} Station_param;


/// Query - 1
/** Count the number of heat degree days for a particular station */
int heat_degree_days(Station_param x, float avg) {
    int count = 0;
    for (int i = 0; i < 30; ++i) {
        if (x.air_temp[i] > avg)
            count++;
    }
    return count;
}


/// Query - 2
/** Find Thermally comfortable days */
void displayThermally_comfortable_days(Station_param x, Station_param rural) {

    if (!x.station_status) {
        printf("Not a urban station\n");
        return;
    }

    //Find the thermally comfortable days
    float min_temp = (float) INT_MAX;
    int days[30], k = 0;
    for (int i = 0; i < 30; ++i) {
        float temp = fabsf(x.air_temp[i] - rural.air_temp[i]);
        if (temp == min_temp) {
            days[k++] = i + 1;
        } else if (temp < min_temp) {
            k = 0;
            min_temp = temp;
            days[k++] = i + 1;
        }
    }
    // After completion of the loop, days[] will contain all days whose temperature difference is minimum
    printf("Thermally comfortable days for the station is/are :-\n");
    char *ch = Arrays_toString((const int *) days, k);
    printf("%s\n", ch);
    free(ch);
}


/// Query - 3
/** List dates for all stations with decreasing vegetation density ratio and for which the temperature was more
than average city temperature. */

// The following function implements quick sort on basis of vegetation density ratio
int partition(Station_param arr[], float x, int init, int l) {
    int i = init, j = l;
    while (i < j) {
        if (arr[i].vegetation_density_ratio == x) {
            Station_param temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        if (arr[i].vegetation_density_ratio < x) {
            Station_param temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j--;
        } else i++;
    }

    return i;
}

void quick_sort_vegetation(Station_param arr[], int st, int len) {

    if (st < len) {
        int index = partition(arr, arr[st].vegetation_density_ratio, st, len);
        quick_sort_vegetation(arr, 0, index - 1);
        quick_sort_vegetation(arr, index + 1, len);
    }
}

void temp_grt_avg(Station_param total[], int n, float avg) {
    for (int i = 0; i < n; ++i) {
        int days[30], k = 0;
        for (int j = 0; j < 30; ++j) {
            if (total[i].air_temp[j] > avg)
                days[k++] = j + 1;
        }
        char *s = Arrays_toString((const int *) days, k);
        printf("V D : %f  Station %d  Days : %s\n", total[i].vegetation_density_ratio, total[i].station, s);
        free(s);
    }

}


/// Query - 4
/**  List the (top ‘k’, k-input) stations with minimum population density with highest maximum temperature.
If two stations have same population density, then list those in the order of highest maximum temperature. */

// The following function implements quick sort on basis of population density ratio
int partition2(Station_param arr[], float x, int init, int l) {
    int i = init, j = l;
    while (i < j) {
        if (arr[i].population_density == x) {
            Station_param temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        if (arr[i].population_density > x) {
            Station_param temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j--;
        } else i++;
    }

    return i;
}

void quick_sort_population(Station_param arr[], int st, int len) {

    if (st < len) {
        int index = partition2(arr, arr[st].population_density, st, len);
        quick_sort_population(arr, 0, index - 1);
        quick_sort_population(arr, index + 1, len);
    }
}

// The following function implements quick sort on basis of highest maximum temperature
int partition3(Station_param arr[], float x, int init, int l) {
    int i = init, j = l;
    while (i < j) {
        if (Arrays_maxOf(arr[i].air_temp, 30) == x) {
            Station_param temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        if (Arrays_maxOf(arr[i].air_temp, 30) < x) {
            Station_param temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j--;
        } else i++;
    }

    return i;
}

void quick_sort_temperature(Station_param arr[], int st, int len) {

    if (st < len) {
        int index = partition3(arr, Arrays_maxOf(arr[st].air_temp, 30), st, len);
        quick_sort_temperature(arr, st, index - 1);
        quick_sort_temperature(arr, index + 1, len);
    }
}


/** Query- 5
 * Find the heat island intensity for all urban stations.
 */

int identify_nearest_rural(Station_param urban, Station_param total[], int n, Station_param rural[]) {
    int minimum = INT_MAX;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (total[i].station_status == 0) {
            if (urban.distance_of_station[total[i].station - 1] < minimum) {
                k = 0;
                minimum = urban.distance_of_station[total[i].station - 1];
                rural[k++] = total[i];
            } else if (urban.distance_of_station[total[i].station - 1] == minimum) {
                rural[k++] = total[i];
            }
        }
    }
    return k;
}


// The quick sort implemented below, sorts the rural array in order of decreasing pervious fraction
int partition4(Station_param arr[], int x, int init, int l) {
    int i = init, j = l;
    while (i < j) {
        if (arr[i].previous_surface_fraction == x) {
            Station_param temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
        if (arr[i].previous_surface_fraction < x) {
            Station_param temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j--;
        } else i++;
    }

    return i;
}

void quick_sort_PSF(Station_param rural[], int st, int len) {

    if (st < len) {
        int index = partition4(rural, rural[0].previous_surface_fraction, st, len);
        quick_sort_PSF(rural, st, index - 1);
        quick_sort_PSF(rural, index + 1, len);
    }
}