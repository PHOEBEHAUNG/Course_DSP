#include <stdio.h>
#include <stdlib.h>

#define SIG_ARR_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_ARR_LENGTH];
double calt_signal_mean(double *sig_src_arr, int sig_ength);

int main()
{
  double mean_res = calt_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_ARR_LENGTH);
  printf("mean_res is : %.3f\n", mean_res);
  return 0;
}

double calt_signal_mean(double *sig_src_arr, int sig_ength)
{
  double mean = 0.0;
  for(int i = 0; i < sig_ength; i++)
  {
    mean = mean + sig_src_arr[i];
  }

  mean = mean / sig_ength;
  return mean;
}