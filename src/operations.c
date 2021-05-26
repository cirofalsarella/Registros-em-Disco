#include "operations.h"
#include "binaryWriter.h"
#include "binaryHeaders.h"
#include <ctype.h>

/**
 * @brief Prints a hash of the given binary file (aka binarioNaTela).
 * 
 * @param nomeArquivoBinario 
 */
void PrintHash(char* nomeArquivoBinario) {
	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;

	if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função PrintHash): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for (i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}

	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void Op_CreateTableVehicles() {
    // Reads csv and binary
    char csvFile[128], binFile[128];
    scanf("%s %s", csvFile, binFile);

    // Converts csv to binary and saves to disk
    StringTable* Table = StringTable_FromCsv(csvFile, ',');
    CsvToBinary_WriteVehicleFile(Table, binFile);

    StringTable_Free(Table);
    PrintHash(binFile);
}

void Op_CreateTableBuslines() {
    // Reads csv and binary
    char csvFile[128], binFile[128];
    scanf("%s %s", csvFile, binFile);

    // Converts csv to binary and saves to disk
    StringTable* Table = StringTable_FromCsv(csvFile, ',');
    CsvToBinary_WriteBusLineFile(Table, binFile);

    StringTable_Free(Table);
    PrintHash(binFile);
}

void Op_SelectVehicles() {
    // Reads file name
    char binFile[128];
    scanf("%s", binFile);

    // Reads binary file from disk
    VehicleHeader* header = NULL;
    Vehicle** vehicles = BinaryReader_Vehicles(&header, binFile);
    
    // Prints all vehicles
    printf("NUMERO DE VEICULOS: %d\n", header->numReg);
    for (int i = 0; i < header->numReg; i++) {
        Printer_Vehicle(vehicles[i]);
        Vehicle_Free(vehicles[i]);
    }

    free(vehicles);
}

void Op_SelectBusLines() {
    // Reads file name
    char binFile[128];
    scanf("%s", binFile);

    // Reads binary file from disk
    BusLineHeader* header = NULL;
    BusLine** buslines = BinaryReader_BusLines(&header, binFile);

    // Prints all bus lines
    printf("NUMERO DE LINHAS: %d\n", header->numReg);
    for (int i = 0; i < header->numReg; i++) {
        Printer_BusLine(buslines[i]);
        BusLine_Free(buslines[i]);
    }

    free(buslines);
}

void Op_SelectVehiclesWhere() {
    // Reads file name
    char binFile[128] = { '\0' };
    scanf("%s", binFile);

    // Reads binary file from disk
    VehicleHeader* header = NULL;
    Vehicle** vehicles = BinaryReader_Vehicles(&header, binFile);

    // Reads field name
    char fieldName[64] = { '\0' };
    scanf("%s", fieldName);

    // Calls our generic function that selects by an arbitrary field
    void *functionPt = SelectWhere_SetCondition(fieldName);
    void *pattern = SelectWhere_SetPattern(fieldName);
    vehicles = SelectWhere_SelectVehicles(functionPt, pattern, &vehicles, &header->numReg);

    // Linearly searches for the right vehicle
    printf("NUMERO DE VEICULOS: %d\n", header->numReg);
    for (int i = 0; i < header->numReg; i++) {
        Printer_Vehicle(vehicles[i]);
        Vehicle_Free(vehicles[i]);
    }

    free(vehicles);
}

void Op_SelectBuslinesWhere() {
    // Reads file name
    char binFile[128] = { '\0' };
    scanf("%s", binFile);

    // Reads binary file from disk
    BusLineHeader* header = NULL;
    BusLine **buslines = BinaryReader_BusLines(&header, binFile);

    // Reads field name
    char fieldName[64] = { '\0' };
    scanf("%s", fieldName);

    // Calls our generic function that selects by an arbitrary field
    void* functionPt = SelectWhere_SetCondition(fieldName);
    void* pattern = SelectWhere_SetPattern(fieldName);
    buslines = SelectWhere_SelectBusLines(functionPt, pattern, &buslines, &header->numReg);

    // Linearly searches for the right bus line
    printf("NUMERO DE LINHAS: %d\n", header->numReg);
    for (int i = 0; i < header->numReg; i++) {
        Printer_BusLine(buslines[i]);
        BusLine_Free(buslines[i]);
    }

    free(buslines);
}

void ScanQuoteString(char *str) {
	char R;

	while ((R = getchar()) != EOF && isspace(R));

	if (R == 'N' || R == 'n') {
		getchar(); getchar(); getchar();
		strcpy(str, "");
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) {
			strcpy(str, "");
		}
		getchar();
	} else if(R != EOF) {
		str[0] = R;
		scanf("%s", &str[1]);
	} else {
		strcpy(str, "");
	}
}

void Op_PushVehicles() {
    // Reads file name
    char binFile[128] = { '\0' };
    scanf("%s", binFile);

    // Reads binary file from disk
    VehicleHeader* header = NULL;
    Vehicle** vehicles = BinaryReader_Vehicles(&header, binFile);

    // Format: prefixo1 data1 quantidadeLugares1 codLinha1 modelo1 categoria1

    // Scans prefix, date, numSeats and lineCode (all fixed-length fields)
    char prefix[5] = { '\0' };
    ScanQuoteString(prefix);

    char date[10] = { '\0' };
    ScanQuoteString(date);

    int32_t numSeats;
    scanf("%d", &numSeats);

    char lineCode[4] = { '\0' };
    ScanQuoteString(lineCode);

    // Scans model and category (not fixed-length)
    char* model = calloc(100, sizeof(char));
    char* category = calloc(100, sizeof(char));

    ScanQuoteString(model);
    ScanQuoteString(category);

    // Creates a new vehicle and pushes it
    Vehicle* newVehicle = Vehicle_Create('1', prefix, date, numSeats, lineCode, model, category);
    header->numReg += 1;
    vehicles = (Vehicle**) realloc(vehicles, sizeof(Vehicle*) * header->numReg);
    vehicles[header->numReg-1] = newVehicle;

    // Writes to file
    BinaryWriter_CreateVehicleFile(vehicles, header->numReg, header, binFile);
}

void Op_PushBuslines() {
    // Format: codLinha1 aceitaCartao1 nomeLinha1 corLinha1

    // Reads file name
    char binFile[128] = { '\0' };
    scanf("%s", binFile);

    // Reads binary file from disk
    BusLineHeader* header = NULL;
    BusLine** busLines = BinaryReader_BusLines(&header, binFile);

    // Format: codLinha1 aceitaCartao1 nomeLinha1 corLinha1

    // Scans lineCode, acceptsCreditCard (all fixed-length fields)
    char lineCode[4] = { '\0' };
    ScanQuoteString(lineCode);

    char acceptsCreditCard[1] = { '\0' };
    ScanQuoteString(acceptsCreditCard);

    // Scans name and color (not fixed-length)
    char* name = calloc(100, sizeof(char));
    char* color = calloc(100, sizeof(char));

    ScanQuoteString(name);
    ScanQuoteString(color);

    // Creates a new vehicle and pushes it
    BusLine* newBusLine = BusLine_Create('1', lineCode, acceptsCreditCard[0], name, color);
    header->numReg += 1;
    busLines = (BusLine**) realloc(busLines, sizeof(BusLine*) * header->numReg);
    busLines[header->numReg-1] = newBusLine;

    // Writes to file
    BinaryWriter_CreateBusLineFile(busLines, header->numReg, header, binFile);
}