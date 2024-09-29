#include "config.h"

char *VERSION = "1.4-ALPHA";
unsigned long int MAX_BUFF_LEN = 1000;
unsigned long int MAX_CMD_LEN = 20;

const wchar_t *CMD_DISPLAY_DIR = L"dd";      // working
const wchar_t *CMD_DISPLAY_CWD = L"dcd";     // working
const wchar_t *CMD_CHANGE_CWD = L"ccd";      // working
const wchar_t *CMD_MOVE_FILE = L"mvf";       // working
const wchar_t *CMD_MOVE_DIR = L"mvd";        // working
const wchar_t *CMD_COPY_FILE = L"cpf";       // working
const wchar_t *CMD_COPY_DIR = L"cpd";        // working
const wchar_t *CMD_CREATE_FILE = L"crf";     // working
const wchar_t *CMD_CREATE_DIR = L"crd";      // working
const wchar_t *CMD_REMOVE_FILE = L"rmf";     // working
const wchar_t *CMD_REMOVE_DIR = L"rmd";      // working
const wchar_t *CMD_CLEAR_SCREEN = L"clrscr"; // working
const wchar_t *CMD_QUIT = L"quit";           // working