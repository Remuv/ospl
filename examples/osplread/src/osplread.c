#include "osplread.h"

void onUpdate(corto_object this, corto_eventMask mask, corto_object o, corto_observer observer) {
    printf("%s => %s = %s\n",
      corto_idof(corto_parentof(o)),
      corto_idof(o),
      corto_contentof(NULL, "text/json", o));
}

int osplreadMain(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: osplread <topic>\n");
        printf("  Example: osplread durabilityPartition.d_status\n");
        return -1;
    }

    printf("osplread: subscribing to '%s'\n", argv[1]);

    /* Connect to a specific DDS topic */
    ospl_ConnectorCreateChild_auto(
        root_o,                /* create connector in root */
        osplx,                 /* name of connector */
        NULL,                  /* store instances in scope of connector */
        NULL,                  /* discover type from DDS*/
        NULL,                  /* default policy */
        argv[1],               /* topic */
        NULL                   /* discover keylist from DDS */
    );

    /* Observe updates in connector scope, where instances are stored */
    corto_observe(CORTO_ON_UPDATE|CORTO_ON_TREE, osplx).callback(onUpdate);

    while (TRUE) {
        corto_sleep(1, 0);
    }

    return 0;
}
