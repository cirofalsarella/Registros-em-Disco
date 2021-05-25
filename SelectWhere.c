#include "SelectWhere.h"

int BusLine_codLinha(void *pattern, BusLine *busLine){
    return 0;
}
int BusLine_aceitaCartao(void *pattern, BusLine *busLine){
    return 0;
}
int BusLine_nomeLinha(void *pattern, BusLine *busLine){
    return 0;
}
int BusLine_corLinha(void *pattern, BusLine *busLine){
    return 0;
}

int Vehicle_prefixo(void *pattern, Vehicle *vehicle){
    return 0;   
}
int Vehicle_data(void *pattern, Vehicle *vehicle){
    return 0;   
}
int Vehicle_quantidadeLugares(void *pattern, Vehicle *vehicle){
    return 0;   
}
int Vehicle_modelo(void *pattern, Vehicle *vehicle){
    return 0;   
}
int Vehicle_categoria(void *pattern, Vehicle *vehicle){
    return 0;   
}


void *SelectWhere_setCondition(char *fieldName){
    if (!strcmp(fieldName, "codLinha"))     return BusLine_codLinha;
    if (!strcmp(fieldName, "aceitaCartao")) return BusLine_aceitaCartao;
    if (!strcmp(fieldName, "nomeLinha"))    return BusLine_nomeLinha;
    if (!strcmp(fieldName, "corLinha"))     return BusLine_codLinha;

    if (!strcmp(fieldName, "prefixo"))              return Vehicle_prefixo;
    if (!strcmp(fieldName, "data"))                 return Vehicle_data;
    if (!strcmp(fieldName, "quantidadeLugares"))    return Vehicle_quantidadeLugares;
    if (!strcmp(fieldName, "modelo"))               return Vehicle_modelo;
    if (!strcmp(fieldName, "categoria"))            return Vehicle_categoria;

    return NULL;
}

void *SelectWhere_setPattern(char *fieldName){
    return NULL;
}


Vehicle **SelectWhere_selectVehicles(void *functionPt(void*, Vehicle*), void *pattern, Vehicle ***vehicles, int *n_vehicles){
    int n = *n_vehicles;
    for (int i=0; i<*n_vehicles; i++) {
        if (functionPt(pattern, *vehicles[i])){
            Vehicle_Free(*vehicles[i]);
            *vehicles[i] = NULL;
            n--;
        }
    }

    Vehicle **selectedVehicles = calloc (n, sizeof(Vehicle*));
    n = 0;
    for (int i=0; i<*n_vehicles; i++) {
        if (*vehicles[i] != NULL) {
            selectedVehicles[n] = *vehicles[i];
            n++;
        }
    }

    free(*vehicles);
    *n_vehicles = n;
    return selectedVehicles;
}

BusLine **SelectWhere_selectBusLines(void *functionPt(void*, BusLine*), void *pattern, BusLine ***busLines, int *n_busLines){
    int n = *n_busLines;
    for (int i=0; i<*n_busLines; i++) {
        if (functionPt(pattern, *busLines[i])){
            BusLine_Free(*busLines[i]);
            *busLines[i] = NULL;
            n--;
        }
    }

    BusLine **selectedBusLines = calloc (n, sizeof(BusLine*));
    n = 0;
    for (int i=0; i<*n_busLines; i++) {
        if (*busLines[i] != NULL) {
            selectedBusLines[n] = *busLines[i];
            n++;
        }
    }

    free(*busLines);
    *n_busLines = n;
    return selectedBusLines;
}