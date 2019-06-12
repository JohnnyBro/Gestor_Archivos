#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <time.h>

typedef struct {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
}PARTITION;

typedef struct
{
    int mbr_tamanio;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    char mbr_disk_fit;
    PARTITION part[4];
}MBR;

#endif // ESTRUCTURAS_H
