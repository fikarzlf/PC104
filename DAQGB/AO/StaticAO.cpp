/*******************************************************************************
Copyright (c) 1983-2012 Advantech Co., Ltd.
********************************************************************************
THIS IS AN UNPUBLISHED WORK CONTAINING CONFIDENTIAL AND PROPRIETARY INFORMATION
WHICH IS THE PROPERTY OF ADVANTECH CORP., ANY DISCLOSURE, USE, OR REPRODUCTION,
WITHOUT WRITTEN AUTHORIZATION FROM ADVANTECH CORP., IS STRICTLY PROHIBITED.
================================================================================
REVISION HISTORY
--------------------------------------------------------------------------------
$Log: $
--------------------------------------------------------------------------------
$NoKeywords:  $
*/
/******************************************************************************
*
* Windows Example:
*    StaticAO.cpp
*
* Example Category:
*    AO
*
* Description:
*    This example demonstrates how to use Static AO  voltage function.
*
* Instructions for Running:
*    1  Set the 'deviceDescription' for opening the device.
*    2  Set the 'channelStart' as the first channel for analog data Output  .
*    3  Set the 'channelCount' to decide how many sequential channels to output analog data.
*
* I/O Connections Overview:
*    Please refer to your hardware reference manual.
*
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../inc/compatibility.h"
#include "../inc/bdaqctrl.h"
using namespace Automation::BDaq;
//-----------------------------------------------------------------------------------
// Configure the following three parameters before running the demo
//-----------------------------------------------------------------------------------
#define     ONE_WAVE_POINT_COUNT  512 //define how many data to makeup a waveform period.
#define     deviceDescription  L"PCM-3810,BID#0"

int32       channelStart = 0;
int32       channelCount = 1;

enum WaveStyle{Abs};
//function GenerateWaveform: generate one waveform for each selected analog data output channel
ErrorCode GenerateWaveform( InstantAoCtrl * instantAoCtrl,int32 channelStart,int32 channelCount,  double * waveBuffer, int32 SamplesCount,WaveStyle style);


inline void waitAnyKey()
{
   do{SLEEP(1);} while(!kbhit());
}

int main(int argc, char* argv[])
{
   ErrorCode ret = Success;
   // Step 1: Create a 'InstantAoCtrl' for Static AO function.
   InstantAoCtrl * instantAoCtrl = AdxInstantAoCtrlCreate();
   do
   {
      // Step 2: Select a device by device number or device description and specify the access mode.
      // in this example we use AccessWriteWithReset(default) mode so that we can
      // fully control the device, including configuring, sampling, etc.
      DeviceInformation devInfo(deviceDescription);
      ret = instantAoCtrl->setSelectedDevice(devInfo);
      CHK_RESULT(ret);

      // Step 3: Output data
      // Generate waveform data
      double *waveform = (double*)malloc( channelCount*ONE_WAVE_POINT_COUNT*sizeof(double));
      if( NULL  == waveform )
      {
         printf( "Insufficient memory available\n" );
         break;
      }
      ret = GenerateWaveform( instantAoCtrl,channelStart,channelCount, waveform,channelCount*ONE_WAVE_POINT_COUNT,Abs);
      CHK_RESULT(ret);

      printf("\n Outputting data...  any key to quit!\n");
      bool enforced = false;
      do
      {
         for( int32 i = 0; i < ONE_WAVE_POINT_COUNT; i++ )
         {
	   // ret = instantAoCtrl->Write( channelStart,channelCount,&waveform[channelCount*i] );
            ret = instantAoCtrl->Write( channelStart,channelCount, &waveform[i]);
            CHK_RESULT(ret);
       SLEEP(1);
      if(kbhit())
       {
         printf("\n Static AO is over compulsorily");
           enforced = true;
           break;
        }
       }
    } while (false);
      free(waveform);
//  if (!enforced)
//  {
//     printf("\n Static AO is over, press any key to quit!\n");
//  }
   }while(false);

	// Step 4: Close device and release any allocated resource.
	instantAoCtrl->Dispose();

	// If something wrong in this execution, print the error code on screen for tracking.
   if(BioFailed(ret))
   {
      printf("Some error occurred. And the last error code is Ox%X.\n", ret);
      waitAnyKey();// Wait any key to quit!.
   }

   waitAnyKey();// Wait any key to quit !
   return 0;
}


ErrorCode GenerateWaveform( InstantAoCtrl * instantAoCtrl, int32 channelStart,int32 channelCount, double * waveBuffer,int32 SamplesCount,WaveStyle style)

{
   ErrorCode ret = Success;

   int32    oneWaveSamplesCount = 100;
   int32    i = 0;


   for(i = 0; i < oneWaveSamplesCount; i++ )
   {

         switch ( style)
         {
         case Abs:
            *waveBuffer++ = 1.1+0.01*i;
            break;
 
         default:
            printf("invalid wave style,generate waveform error !");
            ret = ErrorUndefined;
         }
      
   }
   return ret;
};



