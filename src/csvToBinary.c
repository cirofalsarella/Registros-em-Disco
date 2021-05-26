#include "csvToBinary.h"
#include "binaryHeaders.h"
#include "binaryWriter.h"
#include "utils.h"

// Vehicle

Vehicle* CsvToBinary_CreateVehicleFromRow(StringTable* table, int row) {
    // Gets each cell from csv, and converts to int when necessary
    char* prefix = StringTable_GetCellAt(table, 0, row);
    char* date = StringTable_GetCellAt(table, 1, row);
    char* numSeats = StringTable_GetCellAt(table, 2, row);
    char* lineCode = StringTable_GetCellAt(table, 3, row);
    char* model = StringTable_GetCellAt(table, 4, row);
    char* category = StringTable_GetCellAt(table, 5, row);

    char removed = '1';
    if (prefix[0] == '*') {
        removed = '0';
        // Removes '*' from name
        char* prefixCopy = Utils_StrCopy(prefix+1); // Copies without the '*'
        int prefixCopyLen = strlen(prefixCopy);
        strcpy(prefix, prefixCopy);
        prefix[prefixCopyLen] = '\0';
        free(prefixCopy);
    }

    return Vehicle_Create(removed, prefix, date, Utils_StrToInt(numSeats), Utils_StrToInt(lineCode), strdup(model), strdup(category));
}

void CsvToBinary_WriteVehicleFile(StringTable *table, char *fileName) {
    // Creates a list of vehicles
    Vehicle** vehicles = (Vehicle**) malloc((table->rowCount - 1) * sizeof(Vehicle*));
    VehicleHeader* header = VehicleHeader_CreateFromTable(table);
    int vehiclesCount = table->rowCount-1;

    for (int i = 0; i < vehiclesCount; i++) {
        vehicles[i] = CsvToBinary_CreateVehicleFromRow(table, i);
    }

    // Creates the binary file
    BinaryWriter_CreateVehicleFile(vehicles, vehiclesCount, header, fileName);
}


//  BusLine

BusLine* CsvToBinary_CreateBusLineFromRow(StringTable* table, int row) {
    // Gets each cell from csv, and converts to int when necessary
    char* lineCode = StringTable_GetCellAt(table, 0, row);
    char* acceptsCreditCard = StringTable_GetCellAt(table, 1, row);
    char* name = StringTable_GetCellAt(table, 2, row);
    char* color = StringTable_GetCellAt(table, 3, row);

    char removed = '1';
    if (lineCode[0] == '*') {
        removed = '0';
        // Removes '*' from name
        char* lineCodeCopy = Utils_StrCopy(lineCode+1); // Copies without the '*'
        int lineCodeLen = strlen(lineCodeCopy);
        strcpy(lineCode, lineCodeCopy);
        lineCode[lineCodeLen] = '\0';
        free(lineCodeCopy);
    }

    return BusLine_Create(removed, Utils_StrToInt(lineCode), acceptsCreditCard[0], strdup(name), strdup(color));
}

void CsvToBinary_WriteBusLineFile(StringTable *table, char *fileName) {
    // Creates a list of bus lines
    BusLine** busLines = (BusLine**) malloc((table->rowCount - 1) * sizeof(BusLine*));
    BusLineHeader* header = BusLineHeader_CreateFromTable(table);
    int busLinesCount = table->rowCount-1;

    for (int i = 0; i < busLinesCount; i++) {
        busLines[i] = CsvToBinary_CreateBusLineFromRow(table, i);
    }

    // Creates binary file
    BinaryWriter_CreateBusLineFile(busLines, busLinesCount, header, fileName);
}
