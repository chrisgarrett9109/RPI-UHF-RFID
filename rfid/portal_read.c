/*
  portal_read.c
  2021-03-04
  Chris Garrett

  - reader uri and antenna must be provided when program is executed 
    (tmr:///dev/ttyUSB0 --ant 1)
  - scans for 500ms, puts tag data into tagReads array and
    prints tag count + EPC of closest tag (based on rssi strength)
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <tm_reader.h> // Only header necessary for reader functions

/********* parseAntennaList taken from ../samples/antennaList.c ***********/
// gathers antenna data from calling arguments
void parseAntennaList(uint8_t *antenna, uint8_t *antennaCount, char *args)
{
  char *token = NULL;
  char *str = ",";
  uint8_t i = 0x00;
  int scans;

  /* get the first token */
  if (NULL == args)
  {
    fprintf(stdout, "Missing argument\n");
  }

  token = strtok(args, str);
  if (NULL == token)
  {
    fprintf(stdout, "Missing argument after %s\n", args);
  }
  while(NULL != token)
  {
    scans = sscanf(token, "%"SCNu8, &antenna[i]);
    if (1 != scans)
    {
      fprintf(stdout, "Can't parse '%s' as an 8-bit unsigned integer value\n", token);
    }
    i++;
    token = strtok(NULL, str);
  }
  *antennaCount = i;
}

int main(int argc, char *argv[])
{  
  TMR_Reader Reader;
  TMR_Reader *reader = &Reader;
  memset(reader, 0, sizeof(*reader));
  TMR_Status ret;
  TMR_ReadPlan plan;
  TMR_Region region = TMR_REGION_NA;
  TMR_TagReadData* tagReads;
  uint8_t i;
  uint8_t *antennaList = NULL;
  uint8_t buffer[20];
  uint8_t antennaCount = 0x0;
  uint32_t baud_rate = 115200;
  int32_t power = 1500;
  int32_t tagCount;
  int j;
  char epcStr[128];

  // setting antenna data for read plan
  for (i = 2; i < argc; i+=2)
  {
    if(0x00 == strcmp("--ant", argv[i]))
    {
      parseAntennaList(buffer, &antennaCount, argv[i+1]);
      antennaList = buffer;
    }
  }

  // connecting to reader
  ret = TMR_create(reader, argv[1]);
  ret = TMR_connect(reader);

  // setting necessary parameters
  ret = TMR_paramSet(reader, TMR_PARAM_REGION_ID, &region);
  ret = TMR_paramSet(reader, TMR_PARAM_RADIO_READPOWER, &power);
  ret = TMR_paramSet(reader, TMR_PARAM_BAUDRATE, &baud_rate);

  // initiating read plan
  ret = TMR_RP_init_simple(&plan, antennaCount, antennaList, TMR_TAG_PROTOCOL_GEN2, 1000);
  ret = TMR_paramSet(reader, TMR_PARAM_READ_PLAN, &plan);

  // printing number of tags read
  ret = TMR_readIntoArray(reader, 500, &tagCount, &tagReads);
  printf("%d tags found.\n", tagCount);

  // finding closest tag based on signal strength and print tag ID
  int largest = tagReads[0].rssi;
  uint8_t* final_epc = tagReads[0].tag.epc;
  uint8_t bytes = tagReads[0].tag.epcByteCount;

  for(j = 1; j < tagCount; j++) 
  {
    if(largest < tagReads[j].rssi)
    {
      largest = tagReads[j].rssi;
      final_epc = tagReads[j].tag.epc;
    }
  }

  TMR_bytesToHex(final_epc, bytes, epcStr);
  printf("Closest EPC:%s\n", epcStr);

  TMR_destroy(reader);
  return 0;
}