#include "binaryReader.h"
#include "printer.h"
#include <assert.h>

VehicleHeader* ReadVehicleHeader(FILE *srcFile) {
    VehicleHeader* header = calloc(1, sizeof(VehicleHeader));

    fread(&header->status, sizeof(char), 1, srcFile);
    fread(&header->nextReg, sizeof(long), 1, srcFile);
    fread(&header->numReg, sizeof(int), 1, srcFile);
    fread(&header->numRegRemov, sizeof(int), 1, srcFile);

    fread(&header->describePrefix, sizeof(char), 18, srcFile);
    fread(&header->describeDate, sizeof(char), 35, srcFile);
    fread(&header->describePlaces, sizeof(char), 42, srcFile);
    fread(&header->describeLine, sizeof(char), 26, srcFile);
    fread(&header->describeModel, sizeof(char), 17, srcFile);
    fread(&header->describeCategory, sizeof(char), 20, srcFile);

    return header;
}

Vehicle* ReadVehicle(FILE *srcFile) {
    Vehicle* vehicle = calloc(1, sizeof(Vehicle));

    fread(&vehicle->removed, sizeof(char), 1, srcFile);
    fread(&vehicle->regSize, sizeof(int32_t), 1, srcFile);
    fread(&vehicle->prefix[0], sizeof(char), 5, srcFile);
    fread(&vehicle->date[0], sizeof(char), 10, srcFile);
    fread(&vehicle->numSeats, sizeof(int32_t), 1, srcFile);
    fread(&vehicle->lineCode[0], sizeof(char), 4, srcFile);

    // Variable-length fields
    fread(&vehicle->modelLength, sizeof(int32_t), 1, srcFile);
    vehicle->model = calloc(vehicle->modelLength+1, sizeof(char));
    fread(vehicle->model, sizeof(char), vehicle->modelLength, srcFile);

    fread(&vehicle->categoryLength, sizeof(int32_t), 1, srcFile);
    vehicle->category = calloc(vehicle->categoryLength+1, sizeof(char));
    fread(vehicle->category, sizeof(char), vehicle->categoryLength, srcFile);

    return vehicle;
}

BusLineHeader* ReadBusLineHeader(FILE *srcFile) {
    BusLineHeader* header = calloc(1, sizeof(VehicleHeader));

    // freads the fields stored in the binary file, in order
    fread(&header->status, sizeof(char), 1, srcFile);
    fread(&header->nextReg, sizeof(int64_t), 1, srcFile);
    fread(&header->numReg, sizeof(int32_t), 1, srcFile);
    fread(&header->numRegRemov, sizeof(int32_t), 1, srcFile);

    fread(&header->describeCode, sizeof(char), 15, srcFile);
    fread(&header->describeCard, sizeof(char), 13, srcFile);
    fread(&header->describeName, sizeof(char), 13, srcFile);
    fread(&header->describeLine, sizeof(char), 24, srcFile);

    return header;
}

BusLine* ReadBusLine(FILE *srcFile) {
    BusLine* busLine = calloc(1, sizeof(BusLine));

    // freads the fields stored in the binary file, in order
    fread(&busLine->removed, sizeof(char), 1, srcFile);
    fread(&busLine->regSize, sizeof(int32_t), 1, srcFile);

    fread(&busLine->lineCode[0], sizeof(char), 4, srcFile);
    fread(&busLine->acceptsCreditCard, sizeof(char), 1, srcFile);

    fread(&busLine->nameLength, sizeof(int32_t), 1, srcFile);
    busLine->name = calloc(busLine->nameLength+1, sizeof(char));
    fread(busLine->name, sizeof(char), busLine->nameLength, srcFile);

    fread(&busLine->colorLength, sizeof(int32_t), 1, srcFile);
    busLine->color = calloc(busLine->colorLength+1, sizeof(char));
    fread(busLine->color, sizeof(char), busLine->colorLength, srcFile);

    return busLine;
}

Vehicle** BinaryReader_Vehicles(VehicleHeader** header, char* fileName) {
    FILE* srcFile = fopen(fileName, "rb");

    // Reads the header
    *header = ReadVehicleHeader(srcFile);

    int validRegisters = (*header)->numReg - (*header)->numRegRemov;
    assert(validRegisters > 0);

    // Allocates space for the vehicles
    Vehicle** vehicles = calloc(validRegisters, sizeof(Vehicle*));

    // Gets the vehicles from the file
    int i = 0;
    while (i < validRegisters) {
        Vehicle* aux = ReadVehicle(srcFile);
        if (aux != NULL) {
            vehicles[i] = aux;
            i++;
        }
    }

    fclose(srcFile);
    return vehicles;
}

BusLine** BinaryReader_BusLines(BusLineHeader** header, char* fileName) {
    FILE* srcFile = fopen(fileName, "rb");

    // Reads the header
    *header = ReadBusLineHeader(srcFile);

    int validRegisters = (*header)->numReg - (*header)->numRegRemov;
    assert(validRegisters > 0);

    // Allocates space for the bus lines
    BusLine** busLines = calloc(validRegisters, sizeof(BusLine*));

    // Gets the bus lines from the file
    int i = 0;
    while (i < validRegisters) {
        BusLine* aux = ReadBusLine(srcFile);
        if (aux != NULL) {
            busLines[i] = aux;
            i++;
        }
    }

    fclose(srcFile);
    return busLines;
}
