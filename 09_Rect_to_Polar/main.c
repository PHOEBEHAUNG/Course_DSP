#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIG_LENGTH 320

extern double _320_pts_ecg_IMX[SIG_LENGTH];
extern double _320_pts_ecg_REX[SIG_LENGTH];

double Output_magnitude[SIG_LENGTH];
double Output_phase[SIG_LENGTH];
void rect_to_polar_conversion(double *sig_src_rex_arr,
                              double *sig_src_imx_arr,
                              double *sig_out_mag_arr,
                              double *sig_out_phase_arr,
                              int sig_length);

int main()
{
    FILE *fptr1, *fptr2, *fptr3, *fptr4;
    rect_to_polar_conversion((double*) &_320_pts_ecg_REX[0],
                              (double*) &_320_pts_ecg_IMX[0],
                              (double*) &Output_magnitude[0],
                              (double*) &Output_phase[0],
                              (int) SIG_LENGTH);
    
    fptr1 = fopen("output_magnitude.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr1, "%f\n", Output_magnitude[i]);
    }
    fclose(fptr1);

    fptr2 = fopen("output_phase.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr2, "%f\n", Output_phase[i]);
    }
    fclose(fptr2);

    fptr3 = fopen("input_rex.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr3, "%f\n", _320_pts_ecg_REX[i]);
    }
    fclose(fptr3);

    fptr4 = fopen("input_imx.dat", "w");
    for(int i = 0; i < SIG_LENGTH; i++)
    {
        fprintf(fptr4, "%f\n", _320_pts_ecg_IMX[i]);
    }
    fclose(fptr4);
    return 0;
}

void rect_to_polar_conversion(double *sig_src_rex_arr,
                              double *sig_src_imx_arr,
                              double *sig_out_mag_arr,
                              double *sig_out_phase_arr,
                              int sig_length)
{
    double PI = 3.14159245f;
    int k; 
    for(k = 0; k < sig_length; k++)
    {
        sig_out_mag_arr[k] = sqrt(powf(sig_src_rex_arr[k], 2) + powf(sig_src_imx_arr[k], 2));

        if(sig_src_rex_arr[k] == 0)
        {
            sig_src_rex_arr[k] = pow(10, -20);
            sig_out_phase_arr[k] = atan(sig_src_imx_arr[k] / sig_src_rex_arr[k]);
        }

        if((sig_src_rex_arr[k] < 0) && (sig_src_imx_arr[k] < 0))
        {
            sig_out_phase_arr[k] = sig_out_phase_arr[k] - PI;
        }

        if((sig_src_rex_arr[k] < 0) && (sig_src_imx_arr[k] >= 0))
        {
            sig_out_phase_arr[k] = sig_out_phase_arr[k] + PI;
        }
    }
}