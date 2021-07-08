#ifndef _BINARY_WRITER_H_
#define _BINARY_WRITER_H_

#include "bTreeDataModel.h"
#include "bTree.h"

/**
 * @brief Writes a vector of vehicles to the end of dest file.
 * 
 * @param vehicles vector of vehicles that will be writen
 * @param vehiclesCount number of vehicles to be writen
 * @param fileName name of the file
 * 
 * @return int 
 */
int BinaryWriter_IncrementVehicleFile(Vehicle_t** vehicles, int vehiclesCount, char* fileName);

/**
 * @brief Writes a vector of bus lines to the end of dest file.
 * 
 * @param busLines 
 * @param buslinesCount 
 * @param fileName 
 *
 * @return 1 == error, 0 == success
 */
int BinaryWriter_IncrementBusLineFile(BusLine_t** busLines, int buslinesCount, char* fileName);


// FUNÇÕES DE ESCRITA RELACIONADAS A B-TREES

/**
 * @brief Increments a B-Tree index with the given nodes.
 * 
 * @param BusLine vector of BusLines that will be writen
 * @param BusLineCount number of BusLines to be writen
 * @param header header of the file
 * @param fileName name of the file
 * 
 * @return 1 == error, 0 == success
 */
int BinaryWriter_IncrementBTree(BNode_t* node, BTreeMetadata_t* cache);

/**
 * @brief Writes the header of a BTree in the B-Tree file.
 * 
 * @param cache The cache that contains the header and file pointer.
 */
void BinaryWriter_BTreeHeader(BTreeMetadata_t* cache);


#endif
