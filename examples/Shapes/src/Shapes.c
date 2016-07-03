#include "Shapes.h"

void onUpdate(corto_object this, corto_object shape) {
    corto_string value = corto_str(shape, 0);
    printf("Update %s %s = %s\n", corto_idof(corto_parentof(shape)), corto_idof(shape), value);
    corto_dealloc(value);
}

int ShapesMain(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: Shapes [topic] [color]\n");
        printf("  Example: Shapes Circle RED\n");
        return -1;
    }

    corto_string topic = argv[1];
    corto_string instance = argv[2];

    /* Connect shape topic */
    ospl_Connector connector = ospl_ConnectorCreateChild(
        root_o,       /* create connector in root */
        topic,    /* object name of connector */
        NULL,         /* store instances in scope of connector */
        topic,        /* topic */
        "/ShapeType", /* type */
        "color"       /* keylist */
    );

    /* Observe updates in connector scope */
    corto_observerCreate(CORTO_ON_UPDATE|CORTO_ON_SCOPE, connector, onUpdate);

    /* Create shape */
    ShapeType *s = ShapeTypeCreateChild(connector, instance, 0, 0, 20);

    /* Make the shape turn in circles */
    corto_float32 t = 0;
    while (1) {
        ShapeTypeUpdate(s, cos(t) * 100, sin(t) * 100, 20);
        corto_sleep(0, 400000000);
        t += 0.01;
    }

    return 0;
}
