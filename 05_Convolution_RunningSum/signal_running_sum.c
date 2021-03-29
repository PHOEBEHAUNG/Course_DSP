#include <stdio.h>
#include <stdlib.h>

#define SIG_ARR_LENGTH 320
extern double InputSignal_f32_1kHz_15kHz[SIG_ARR_LENGTH];

void cals_running_sum(double *sig_src_arr, double *sig_dest_arr, int sig_length);

int main()
{
  double  Output_signal[SIG_ARR_LENGTH];
  FILE *input_sig_fptr, *output_sig_fptr;

  cals_running_sum(&InputSignal_f32_1kHz_15kHz[0],
                   &Output_signal[0],
                   SIG_ARR_LENGTH);

  output_sig_fptr = fopen("output_signal.dat", "w");
  for(int i = 0; i < (SIG_ARR_LENGTH); i++)
  {
    fprintf(output_sig_fptr, "\n%f", Output_signal[i]);
  }
  fclose(output_sig_fptr);

  input_sig_fptr = fopen("input_signal.dat", "w");
  for(int i = 0; i < SIG_ARR_LENGTH; i++)
  {
    fprintf(input_sig_fptr, "\n%f", InputSignal_f32_1kHz_15kHz[i]);
  }
  fclose(input_sig_fptr);

  return 0;
}

void cals_running_sum(double *sig_src_arr, double *sig_dest_arr, int sig_length)
{
  for(int i = 1; i < sig_length; i++)
  {
    sig_dest_arr[i] = sig_dest_arr[i - 1] + sig_src_arr[i];
  }
}
