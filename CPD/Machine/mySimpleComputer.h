#ifndef mySimpleComputer
#define mySimpleComputer

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
// Порядковые биты регистров
// Выход за пределы памяти
#define REG_MEMOUTSIDE		0x0		
// Неизвестная команда
#define REG_UNKNOWNCOMMAND	0x1		
// Ошибка деления на ноль
#define REG_DIVIDEZERO		0x2		
// Переполнение ячейки
#define REG_OVERFLOW		0x3		
// Игнорирование тактовых импульсов 
#define REG_CLOCKIGNORE		0x4		
// Максимальный номер регистра (используется в проверках)
#define REG_MAX				0x4		
// Переменные для хранения активности регистров и указателя на текущую выполняемую команду
unsigned short int	regs,
					instructionCounter;
// Аккумулятор и массив, содержащий ячейки памяти					
short int EAX, memory[100];
// За пределами этого файла есть две функции, которые управляют графической составляющей машины.
// Необходимо их вызывать, когда изменяется содержимое ячеек или значение регистров.
extern void updateMemory(int);
extern void updateFlag(int);

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);
int sc_memoryLoad(char *filename);
int sc_memorySave(char *filename);

#endif
