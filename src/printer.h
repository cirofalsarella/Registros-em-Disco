#ifndef _PRINTER_H_
#define _PRINTER_H_

// FUNÇÕES RESPONSÁVEIS PELA FORMATAÇÃO DOS PRINTS

//  Printam um registro seguindo as normas
void Printer_Vehicle(Vehicle_t *vehicle);
void Printer_BusLine(BusLine_t *busLine);
void Printer_Node(BTreeCache_t* cache, BNode_t* node, RRN_t rrn);

#endif
