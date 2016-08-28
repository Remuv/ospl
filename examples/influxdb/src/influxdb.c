#include "influxdb.h"

#define GREY    "\033[0;37m"
#define NORMAL  "\033[0;49m"

int influxdbMain(int argc, char *argv[]) {
    printf("Vortex influxdb bridge v0.1\n");
    printf("  OSPL_URI      = %s'%s'%s\n", GREY, *ospl_uri_o, NORMAL);
    printf("  domainName    = %s'%s'%s\n", GREY,*ospl_domainName_o, NORMAL);
    printf("  domainId      = %s%d%s\n", GREY,*ospl_domainId_o, NORMAL);
    printf("  sharedMemory  = %s%s%s\n", GREY,ospl_singleProcess_o ? "false" : "true", NORMAL);
    printf("  admin address = %shttp://localhost:9090%s\n\n", GREY, NORMAL);

    /* Connect all DDS topics */
    ospl_ConnectorCreateChild_auto(
        root_o,                /* create connector in root */
        osplx,                 /* name of connector */
        NULL,                  /* store instances in scope of connector */
        NULL,                  /* discover type from DDS*/
        NULL,                  /* default policy */
        "*.*",                 /* topic */
        NULL                   /* discover keylist from DDS */
    );

    /* Create influxdb connector */
    influxdb_ConnectorCreate_auto(
      influxdb,       /* name */
      osplx,    /* connect to data in temperature scope */
      "sampleRate=1", /* store at most updates at 1 second intervals */
      CORTO_ON_TREE, /* trigger on updates in scope */
      "http://localhost:8086",  /* hostname */
      "mydb");        /* database name */

    /* Keep alive */
    while (1) {
        corto_sleep(1, 0);
    }

    return 0;
}