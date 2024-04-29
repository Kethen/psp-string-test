#include <pspsdk.h>
#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <pspthreadman.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MODULE_NAME "STRING_TEST"

PSP_MODULE_INFO(MODULE_NAME, PSP_MODULE_KERNEL, 1, 0);

static int logfd = -1;
#define LOG(...) {\
	if(logfd < 0){ \
		logfd = sceIoOpen("ms0:/PSP/"MODULE_NAME".log", PSP_O_WRONLY|PSP_O_CREAT|PSP_O_APPEND, 0777); \
		if(logfd < 0){ \
			logfd = sceIoOpen("ef0:/PSP/"MODULE_NAME".log", PSP_O_WRONLY|PSP_O_CREAT|PSP_O_APPEND, 0777); \
		} \
	} \
	char _log_buf[2048]; \
	int _log_len = sprintf(_log_buf, __VA_ARGS__); \
	_log_buf[_log_len] = '\n'; \
	_log_len++; \
	if(logfd >= 0){ \
		if(_log_len != 0){ \
			sceIoWrite(logfd, _log_buf, _log_len); \
		} \
		sceIoClose(logfd); \
		logfd = -1; \
	}else{ \
		sceIoWrite(2, _log_buf, _log_len); \
	} \
}

int module_start(SceSize args, void *argp){
	sceIoRemove("ms0:/PSP/"MODULE_NAME".log");
	sceIoRemove("ef0:/PSP/"MODULE_NAME".log");
	LOG("module started");
	LOG("test1 |%s %s %s %s %s %s %s %s %s %s %s %s| test1", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12");
	LOG("test2 |%u %u %u %u %u %u %u %u %u %u %u %u| test2", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
	LOG("test3 |%i %i %i %i %i %i %i %i %i %i %i %i| test3", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
	LOG("test4 |%x %x %x %x %x %x %x %x %x %x %x %x| test4", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
	LOG("test5 |%s %x %s| test5", "123", 0x45677654, "321");
	LOG("test6 |%u %lu %llu %i %li %lli %x %lx %llx| test6", 0x12345678, 0x90abcdef, (uint64_t)0x1234567890abcdef, 0x12345678, 0x90abcdef, (uint64_t)0x1234567890abcdef, 0x12345678, 0x90abcdef, (uint64_t)0x1234567890abcdef);
	LOG("test7 |%x %lx %llx %x %lx %llx %x %lx %llx| test7", 0x12345678, 0x90abcdef, (uint64_t)0x1234567890abcdef, 0x12345678, 0x90abcdef, (uint64_t)0x1234567890abcdef, 0x12345678, 0x90abcdef, (uint64_t)0x1234567890abcdef);
	LOG("test8 |%s %x %llx %x %s| test8", "123", 0x456, (uint64_t)0x1234567887654321, 0x654, "321");

	return 0;
}

int module_stop(SceSize args, void *argp){
	return 0;
}
