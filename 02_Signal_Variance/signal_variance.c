#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_ARR_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_ARR_LENGTH];

double calt_signal_mean(double *sig_src_arr, int sig_ength);
double calt_signal_variance(double *sig_src_arr, double sig_mean, int sig_length);

int main()
{
  double mean_res = calt_signal_mean(InputSignal_f32_1kHz_15kHz, SIG_ARR_LENGTH);
  printf("mean_res is : %.3f\n", mean_res);

  double variance_res = calt_signal_variance(InputSignal_f32_1kHz_15kHz, mean_res, SIG_ARR_LENGTH);
  printf("variance_res is : %.3f\n", variance_res);

  return 0;
}

double calt_signal_mean(double *sig_src_arr, int sig_length)
{
  double mean = 0.0;
  for(int i = 0; i < sig_length; i++)
  {
    mean = mean + sig_src_arr[i];
  }

  mean = mean / sig_length;
  return mean;
}

double calt_signal_variance(double *sig_src_arr, double sig_mean, int sig_length)
{
  double variance = 0.0f;

  for(int i = 0; i < sig_length; i++)
  {
    variance = variance + pow((sig_src_arr[i] - sig_mean), 2);
  }

  variance = variance / sig_length;
  return variance;
}