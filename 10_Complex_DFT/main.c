#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LENGTH 501

extern double _501pts_20Hz_sig_imx[SIG_LENGTH];
extern double _501pts_20Hz_sig_rex[SIG_LENGTH];

void complex_dft(double *sig_src_time_domain_rex,
                 double *sig_src_time_domain_imx,
                 double *sig_dest_freq_domain_rex,
                 double *sig_dest_freq_domain_imx,
                 int sig_length);

double Output_freq_imx[SIG_LENGTH];
double Output_freq_rex[SIG_LENGTH];

int main()
{
    FILE *fptr1, *fptr2, *fptr3, *fptr4;

    complex_dft((double*) _501pts_20Hz_sig_rex,
                 (double*) _501pts_20Hz_sig_imx,
                 (double*) Output_freq_rex,
                 (double*) Output_freq_imx,
                 (int) SIG_LENGTH);

    fptr1 = fopen("output_freq_imx.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr1, "%f\n", Output_freq_imx[i]);
    }
    fclose(fptr1);

    fptr2 = fopen("output_freq_rex.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr2, "%f\n", Output_freq_rex[i]);
    }
    fclose(fptr2);

    fptr3 = fopen("input_rex.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr3, "%f\n", _501pts_20Hz_sig_rex[i]);
    }
    fclose(fptr3);

    fptr4 = fopen("input_imx.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr4, "%f\n", _501pts_20Hz_sig_imx[i]);
    }
    fclose(fptr4);
    return 0;
}

void complex_dft(double *sig_src_time_domain_rex,
                 double *sig_src_time_domain_imx,
                 double *sig_dest_freq_domain_rex,
                 double *sig_dest_freq_domain_imx,
                 int sig_length)
{
    double PI = 3.14159265;
    double SR, SI;

    for(int k = 0; k < sig_length - 1; k++)
    {
        for(int i = 0; i < sig_length - 1; i++)
        {
            SR = cos(2 * PI * k * i / sig_length);
            SI = -sin(2 * PI * k * i / sig_length);

            sig_dest_freq_domain_rex[k] = sig_dest_freq_domain_rex[k] +
                                          sig_src_time_domain_rex[i] * SR - 
                                          sig_src_time_domain_imx[i] * SI;
                                           
            sig_dest_freq_domain_imx[k] = sig_dest_freq_domain_imx[k] +
                                          sig_src_time_domain_imx[i] * SI - 
                                          sig_src_time_domain_rex[i] * SR;
        }
    }
}