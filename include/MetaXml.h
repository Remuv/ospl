#ifndef DDDS_METAXML_H
#define DDDS_METAXML_H

#include "corto/corto.h"

corto_string ospl_metaXmlGet(corto_type type);
corto_int16 ospl_metaXmlParse(corto_string type);

#ifdef __cplusplus
}
#endif
#endif
