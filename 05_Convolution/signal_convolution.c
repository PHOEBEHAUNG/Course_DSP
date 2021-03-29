#include <stdio.h>
#include <stdlib.h>

#define SIG_ARR_LENGTH 320
#define IMPULSE_ARR_LENGTH 29

extern double InputSignal_f32_1kHz_15kHz[SIG_ARR_LENGTH];
extern double Impulse_response[IMPULSE_ARR_LENGTH];

void convolution(double *sig_src_arr,
                 double *sig_dest_arr,
                 double *imp_reponse_arr,
                 int sig_src_length,
                 int imp_reponse_length);

int main()
{
  double  Output_signal[SIG_ARR_LENGTH + IMPULSE_ARR_LENGTH];
  FILE *input_sig_fptr, *imp_rsp_fptr, *output_sig_fptr;

  convolution(&InputSignal_f32_1kHz_15kHz[0],
              &Output_signal[0],
              &Impulse_response[0],
              SIG_ARR_LENGTH,
              IMPULSE_ARR_LENGTH);

  output_sig_fptr = fopen("output_signal.dat", "w");
  for(int i = 0; i < (SIG_ARR_LENGTH + IMPULSE_ARR_LENGTH); i++)
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

  imp_rsp_fptr = fopen("impulse_response.dat", "w");
  for(int i = 0; i < IMPULSE_ARR_LENGTH; i++)
  {
    fprintf(imp_rsp_fptr, "\n%f", Impulse_response[i]);
  }
  fclose(imp_rsp_fptr);
  return 0;
}

void convolution(double *sig_src_arr,
                 double *sig_dest_arr,
                 double *imp_reponse_arr,
                 int sig_src_length,
                 int imp_reponse_length)
{
  int i = 0;
  int j = 0;

  for(i = 0; i < (sig_src_length + imp_reponse_length); i++)
  {
    sig_dest_arr[i] = 0;
  }

  for(i = 0; i < sig_src_length; i++)
  {
    for(j = 0; j < imp_reponse_length; j++)
    {
      sig_dest_arr[i + j] = sig_dest_arr[i + j] + sig_src_arr[i] * imp_reponse_arr[j];
    }
  }
}